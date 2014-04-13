#include "StdAfx.h"
#include ".\bigstashitem.h"

/// 无暇紫宝石
const static BYTE g_scbFlawlessAmethyst[] = { 0xA6, 0x67, 0x07, 0x02 };

const static BYTE g_scbFlawlessRuby[] = { 0xC6, 0x26, 0x07, 0x02 };

const static BYTE g_scbFlawlessSkull[] = { 0xB7, 0xC6, 0x06, 0x02 };

const static BYTE g_scbFlawlessDiamond[] = { 0xC6, 0x76, 0x07, 0x02 };

const static BYTE g_scbFlawlessTopaz[] = { 0xC6, 0x96, 0x07, 0x02 };

const static BYTE g_scbFlawlessSapphire[] = { 0xC6, 0x26, 0x06, 0x02 };

const static BYTE g_scbFlawlessEmerald[] = { 0xC6, 0x76, 0x06, 0x02 };

const static int g_scnHeaderLength = 10;

CBigStashItem::CBigStashItem(void)
{
}

CBigStashItem::~CBigStashItem(void)
{
}

void CBigStashItem::setItemBuffer( const BYTE* ar_pData, unsigned ar_nStart, unsigned ar_nSize )
{
	if( ar_pData == NULL || ar_nSize <= 0 )
	{
		return;
	}

	for( unsigned i = 0; i < ar_nSize; ++i )
	{
		m_vItemBuffer.push_back(ar_pData[ar_nStart+i]);
	}
}

bool CBigStashItem::isTypeOf( E_ItemType ar_eItemType )
{
	S_ItemCode lo_sItemCode = getItemCode();

	S_ItemCode lo_sItemCode2 = g_getItemCode(ar_eItemType);

	return lo_sItemCode == lo_sItemCode2;
}

bool CBigStashItem::isValid()
{
	return (m_vItemBuffer.size() >= 14);
}

vector<BYTE> CBigStashItem::asBytes()
{
	return m_vItemBuffer;
}

void CBigStashItem::setPos( BYTE ar_nRow, BYTE ar_nCol )
{
	ar_nCol = ar_nCol&0x0F;
	ar_nRow = ar_nRow&0x0F;

	/// 1110 0001 抹掉66-69位
	m_vItemBuffer[8] = m_vItemBuffer[8] & 0xE1;

	ar_nCol = ar_nCol << 1;

	m_vItemBuffer[8] = m_vItemBuffer[8] | ar_nCol;

	//// 0001 1111 抹掉70-72
	m_vItemBuffer[8] = m_vItemBuffer[8] & 0x1F;

	//// 0111 取低三位
	BYTE ar_nRowHighThreeBit = ar_nRow & 0x07;

	ar_nRowHighThreeBit = ar_nRowHighThreeBit << 5;

	m_vItemBuffer[8] = m_vItemBuffer[8] | ar_nRowHighThreeBit;

	//// 1111 1110 抹掉最后一位
	m_vItemBuffer[9] = m_vItemBuffer[9] & 0xFE;

	//// 1000 取高一位
	BYTE ar_nRowLowOneBit = ar_nRow & 0x08;

	ar_nRowLowOneBit = ar_nRowLowOneBit >> 3;

	m_vItemBuffer[9] = m_vItemBuffer[9] | ar_nRowLowOneBit;

}

S_ItemCode CBigStashItem::getItemCode()
{
	S_ItemCode lo_sItemCode;
	
	char lo_cTest = 'g';

	char lo_cCode = 0;

	lo_cCode = (m_vItemBuffer[9] & 0xF0) >> 4;

	lo_cCode = lo_cCode + ((m_vItemBuffer[10] & 0x0F) << 4);

	lo_sItemCode.m_cItemCode[0] = lo_cCode;

	lo_cCode = 0;

	lo_cCode = (m_vItemBuffer[10] & 0xF0) >> 4;

	lo_cCode = lo_cCode + ((m_vItemBuffer[11] & 0x0F) << 4);

	lo_sItemCode.m_cItemCode[1] = lo_cCode;

	lo_cCode = 0;

	lo_cCode = (m_vItemBuffer[11] & 0xF0) >> 4;

	lo_cCode = lo_cCode + ((m_vItemBuffer[12] & 0x0F) << 4);

	lo_sItemCode.m_cItemCode[2] = lo_cCode;

	lo_cCode = 0;

	lo_cCode = (m_vItemBuffer[12] & 0xF0) >> 4;

	lo_cCode = lo_cCode + ((m_vItemBuffer[13] & 0x0F) << 4);

	lo_sItemCode.m_cItemCode[3] = lo_cCode;

	return lo_sItemCode;
}
