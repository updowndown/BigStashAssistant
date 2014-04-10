#include "StdAfx.h"
#include ".\bigstashpaser.h"

const static int g_scnMinStashDataLength = 17;

const static BYTE g_scbFileHeader[] = { 0x53, 0x53, 0x53, 0x00 };

const static int g_scnFileHeaderLength = sizeof(g_scbFileHeader)/sizeof(g_scbFileHeader[0]);

const static BYTE g_scbPageHeader[] = { 0x53, 0x54, 0x00, 0x4A, 0x4D };

const static int g_scnPageHeaderLength = sizeof(g_scbPageHeader)/sizeof(g_scbPageHeader[0]);

const static BYTE g_scbItemHeader[] = { 0x4A, 0x4D };

const static int g_scnItemHeaderLength = sizeof(g_scbItemHeader)/sizeof(g_scbItemHeader[0]);

CBigStashPaser::CBigStashPaser(void)
{
}

CBigStashPaser::~CBigStashPaser(void)
{
}

bool CBigStashPaser::parse( BYTE* ar_pBigStashData, int ar_nDataLength, CBigStash& ar_oBigStash )
{
	if( !ar_pBigStashData || ar_nDataLength <= 0 )
	{
		AfxMessageBox("大箱子文件解析失败：无数据");
		return false;
	}

	if( ar_nDataLength < g_scnMinStashDataLength || ar_nDataLength < g_scnFileHeaderLength )
	{
		AfxMessageBox("大箱子文件解析失败：大箱子文件长度过短");
		return false;
	}

	m_pBigStashDatas = ar_pBigStashData;

	m_nDataLength = ar_nDataLength;

	m_nIndex = 0;

	if( !checkHeader() )
	{
		AfxMessageBox("大箱子文件解析失败：数据头校验失败");
		return false;
	}

	if( !parseVersion(ar_oBigStash) )
	{
		AfxMessageBox("大箱子文件解析失败：版本解析失败");
		return false;
	}

	if( !parseGoldAndPageSize(ar_oBigStash) )
	{
		AfxMessageBox("大箱子文件解析失败：金钱及页数解析失败");
		return false;
	}
	
	for( unsigned i = 0; i < ar_oBigStash.PageSize(); ++i )
	{
		CBigStashPage lo_oPage;

		if( !parsePage(lo_oPage) )
		{
			CString lo_strErrorInfo;

			lo_strErrorInfo.Format( _T("大箱子文件解析失败：第%d页解析失败"), i);

			AfxMessageBox(lo_strErrorInfo);

			return false;
		}

		ar_oBigStash.setPage( i, lo_oPage );
	}

	return true;
}

bool CBigStashPaser::parseVersion( CBigStash& ar_oBigStash )
{
	if( m_nIndex >= m_nDataLength )
	{
		return false;
	}

	unsigned short lo_nVersion = getShortValue( m_pBigStashDatas, m_nDataLength, m_nIndex );

	ar_oBigStash.Version( lo_nVersion );

	m_nIndex += 2;

	return true;
}


bool CBigStashPaser::checkHeader()
{
	for( int i = m_nIndex; i < g_scnFileHeaderLength; ++i )
	{
		if( m_pBigStashDatas[i] != g_scbFileHeader[i] )
		{
			return false;
		}
	}

	m_nIndex += g_scnFileHeaderLength;

	return true;
}

bool CBigStashPaser::parseGoldAndPageSize( CBigStash& ar_oBigStash )
{
	if( m_nIndex >= m_nDataLength )
	{
		return false;
	}

	BYTE* lo_pByteData = &m_pBigStashDatas[m_nIndex];

	int lo_nNextPageIndex = findNextPageHeader();

	if( lo_nNextPageIndex < 0 )
	{
		return false;
	}

	int lo_nDataLength = lo_nNextPageIndex - m_nIndex;

	unsigned int lo_nGold = 0;

	unsigned int lo_nPageSize = 0;

	switch( lo_nDataLength )
	{
	case 4:
		lo_nPageSize = getIntValue( m_pBigStashDatas, m_nDataLength, m_nIndex );
		break;
	case 8:
		lo_nGold = getIntValue( m_pBigStashDatas, m_nDataLength, m_nIndex );

		lo_nPageSize = getIntValue( m_pBigStashDatas, m_nDataLength, m_nIndex+4 );
		break;
	default:
		return false;
	}

	if( lo_nPageSize <= 0 )
	{
		return false;
	}

	ar_oBigStash.Gold(lo_nGold);

	ar_oBigStash.PageSize(lo_nPageSize);

	m_nIndex = lo_nNextPageIndex;

	return true;
}

int CBigStashPaser::findNextPageHeader()
{
	int lo_nNextPageIndex = -1;

	for( int i = m_nIndex; i < m_nDataLength; ++i )
	{
		int lo_nLeftSize = m_nDataLength - i;

		if( lo_nLeftSize < g_scnPageHeaderLength )
		{
			break;
		}

		lo_nNextPageIndex = i;

		for( int j = 0; j < g_scnPageHeaderLength; ++j )
		{
			if( m_pBigStashDatas[i+j] != g_scbPageHeader[j] )
			{
				lo_nNextPageIndex = -1;

				break;
			}
		}

		if( lo_nNextPageIndex != -1 )
		{
			break;
		}
	}

	return lo_nNextPageIndex;
}

unsigned short CBigStashPaser::getShortValue( BYTE* ar_pData, int ar_nDataLength, int ar_nIndex )
{
	if( ar_pData == NULL || ar_nIndex >= ar_nDataLength )
	{
		return 0;
	}

	BYTE* lo_pByteData = &ar_pData[ar_nIndex];

	unsigned short* lo_pShortValue = (unsigned short*)lo_pByteData;

	unsigned short lo_sValue = lo_pShortValue[0];

	return lo_sValue;
}

unsigned int CBigStashPaser::getIntValue( BYTE* ar_pData, int ar_nDataLength, int ar_nIndex )
{
	if( ar_pData == NULL || ar_nIndex >= ar_nDataLength )
	{
		return 0;
	}

	BYTE* lo_pByteData = &ar_pData[ar_nIndex];

	unsigned int* lo_pIntValue = (unsigned int*)lo_pByteData;

	unsigned int lo_nValue = lo_pIntValue[0];

	return lo_nValue;
}


bool CBigStashPaser::parsePage( CBigStashPage& ar_oPage )
{
	if( m_nIndex >= m_nDataLength )
	{
		return false;
	}

	/// 跳过页首
	m_nIndex += g_scnPageHeaderLength;
	
	int lo_nNextPage = findNextPageHeader();

	if( lo_nNextPage < 0 )
	{
		lo_nNextPage = m_nDataLength;
	}

	int lo_nPageEnd = lo_nNextPage;

	unsigned short lo_sItemSize = getShortValue( m_pBigStashDatas, m_nDataLength, m_nIndex );

	m_nIndex += 2;

	if( lo_sItemSize > 0 )
	{
		ar_oPage.ItemSize(lo_sItemSize);

		int lo_nStartItem = findNextItem( m_nIndex, lo_nPageEnd );

		if( lo_nStartItem < 0 )
		{
			AfxMessageBox("未找到任何物品信息");

			return false;
		}

		for( unsigned i = 0; i < ar_oPage.ItemSize(); ++i )
		{
			if( lo_nStartItem >= lo_nPageEnd )
			{
				CString lo_strErrorInfo;

				lo_strErrorInfo.Format(_T("物品%d解析错误"), i );

				AfxMessageBox(lo_strErrorInfo);

				return false;
			}

			CBigStashItem lo_oItem;

			int lo_nNextItem = findNextItem( lo_nStartItem+g_scnItemHeaderLength, lo_nPageEnd );

			BYTE lo_bLocation = m_pBigStashDatas[lo_nNextItem+7]&0x1C;

			while( lo_bLocation == 0x18 )
			{
				lo_nNextItem = findNextItem( lo_nNextItem+g_scnItemHeaderLength, lo_nPageEnd );

				if( lo_nNextItem < 0 )
				{
					break;
				}
			
				lo_bLocation = m_pBigStashDatas[lo_nNextItem+7]&0x1C;	
			}

			if( lo_nNextItem < 0 )
			{
				lo_nNextItem = lo_nPageEnd;
			}

			int lo_nItemBufferSize = lo_nNextItem-lo_nStartItem;

			lo_oItem.setItemBuffer( m_pBigStashDatas, lo_nStartItem, lo_nItemBufferSize );

			lo_nStartItem = lo_nNextItem;

			ar_oPage.setItem( i, lo_oItem );
		}
	}

	m_nIndex = lo_nPageEnd;

	return true;
}

int CBigStashPaser::findNextItem( int ar_nPageStart, int ar_nPageEnd )
{
	int lo_nNextItemIndex = -1;

	for( int i = ar_nPageStart; i < ar_nPageEnd; ++i )
	{
		int lo_nLeftSize = ar_nPageEnd - i;

		if( ar_nPageEnd < g_scnItemHeaderLength )
		{
			break;
		}

		lo_nNextItemIndex = i;

		for( int j = 0; j < g_scnItemHeaderLength; ++j )
		{
			if( m_pBigStashDatas[i+j] != g_scbItemHeader[j] )
			{
				lo_nNextItemIndex = -1;

				break;
			}
		}

		if( lo_nNextItemIndex != -1 )
		{
			break;
		}
	}

	return lo_nNextItemIndex;
}

