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
	switch( ar_eItemType )
	{
	case ITEM_FLAWLESS_RUBY:
		return isSameTo(g_scbFlawlessRuby, sizeof(g_scbFlawlessRuby)/sizeof(g_scbFlawlessRuby[0]), g_scnHeaderLength);
		break;
	case ITEM_FLAWLESS_AMETHYST:
		return isSameTo(g_scbFlawlessAmethyst, sizeof(g_scbFlawlessAmethyst)/sizeof(g_scbFlawlessAmethyst[0]), g_scnHeaderLength);
		break;
	case ITEM_FLAWLESS_SKULL:
		return isSameTo(g_scbFlawlessSkull, sizeof(g_scbFlawlessSkull)/sizeof(g_scbFlawlessSkull[0]), g_scnHeaderLength);
		break;
	case ITEM_FLAWLESS_DIAMOND:
		return isSameTo(g_scbFlawlessDiamond, sizeof(g_scbFlawlessDiamond)/sizeof(g_scbFlawlessDiamond[0]), g_scnHeaderLength);
		break;
	case ITEM_FLAWLESS_SAPPHIRE:
		return isSameTo(g_scbFlawlessSapphire, sizeof(g_scbFlawlessSapphire)/sizeof(g_scbFlawlessSapphire[0]), g_scnHeaderLength);
		break;
	case ITEM_FLAWLESS_EMERALD:
		return isSameTo(g_scbFlawlessEmerald, sizeof(g_scbFlawlessEmerald)/sizeof(g_scbFlawlessEmerald[0]), g_scnHeaderLength);
		break;
	case ITEM_FLAWLESS_TOPAZ:
		return isSameTo(g_scbFlawlessTopaz, sizeof(g_scbFlawlessTopaz)/sizeof(g_scbFlawlessTopaz[0]), g_scnHeaderLength);
		break;
	default:
		return false;
		break;
	}

	return false;
}

bool CBigStashItem::isSameTo( const BYTE* ar_pData, int lo_nLength, int lo_nStartPos )
{
	if( ar_pData == NULL || lo_nLength <= 0 )
	{
		return false;
	}

	if( m_vItemBuffer.size() != lo_nStartPos+lo_nLength )
	{
		return false;
	}

	bool bIsSame = true;

	for( int i = 0; i < lo_nLength; ++i )
	{
		if( m_vItemBuffer[lo_nStartPos+i] != ar_pData[i] )
		{
			bIsSame = false;

			break;
		}
	}

	return bIsSame;
}

bool CBigStashItem::isValid()
{
	return (m_vItemBuffer.size() > 0);
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

	//// 1111 1110 抹掉73
	m_vItemBuffer[9] = m_vItemBuffer[9] & 0xFE;

	//// 1000 取高一位
	BYTE ar_nRowLowOneBit = ar_nRow & 0x08;

	ar_nRowLowOneBit = ar_nRowLowOneBit >> 3;

	m_vItemBuffer[9] = m_vItemBuffer[9] | ar_nRowLowOneBit;

}