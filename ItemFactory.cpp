#include "StdAfx.h"
#include ".\itemfactory.h"

const static BYTE g_scbPerfectSkull[]    = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x3A, 0xB7, 0xA6, 0x07, 0x02 };

const static BYTE g_scbPerfectDiamond[]  = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x7A, 0x06, 0x77, 0x07, 0x02 };

/// À¶
const static BYTE g_scbPerfectSapphire[] = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x7A, 0x06, 0x27, 0x06, 0x02 };

/// ÂÌ
const static BYTE g_scbPerfectEmerald[]  = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x7A, 0x06, 0x77, 0x06, 0x02 };

/// »Æ
const static BYTE g_scbPerfectTopaz[]    = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x7A, 0x06, 0x97, 0x07, 0x02 };

/// ×Ï
const static BYTE g_scbPerfectAmethyst[] = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x7A, 0x06, 0x67, 0x07, 0x02 };

/// ºì
const static BYTE g_scbPerfectRuby[]     = { 0x4A, 0x4D, 0x10, 0x00, 0xA0, 0x00, 0x65, 0x00, 0x04, 0x7A, 0x06, 0x27, 0x07, 0x02 };

CItemFactory::CItemFactory(void)
{
}

CItemFactory::~CItemFactory(void)
{
}

CBigStashItem CItemFactory::createItem( E_ItemType ar_eItem )
{
	CBigStashItem lo_oItem;

	switch( ar_eItem )
	{
	case ITEM_PERFECT_RUBY:
		lo_oItem.setItemBuffer( g_scbPerfectRuby, 0, sizeof(g_scbPerfectRuby)/sizeof(g_scbPerfectRuby[0]) );
		break;
	case ITEM_PERFECT_SAPPHIRE:
		lo_oItem.setItemBuffer( g_scbPerfectSapphire, 0, sizeof(g_scbPerfectSapphire)/sizeof(g_scbPerfectSapphire[0]) );
		break;
	case ITEM_PERFECT_DIAMOND:
		lo_oItem.setItemBuffer( g_scbPerfectDiamond, 0, sizeof(g_scbPerfectDiamond)/sizeof(g_scbPerfectDiamond[0]) );
		break;
	case ITEM_PERFECT_SKULL:
		lo_oItem.setItemBuffer( g_scbPerfectSkull, 0, sizeof(g_scbPerfectSkull)/sizeof(g_scbPerfectSkull[0]) );
		break;
	case ITEM_PERFECT_EMERALD:
		lo_oItem.setItemBuffer( g_scbPerfectEmerald, 0, sizeof(g_scbPerfectEmerald)/sizeof(g_scbPerfectEmerald[0]) );
		break;
	case ITEM_PERFECT_TOPAZ:
		lo_oItem.setItemBuffer( g_scbPerfectTopaz, 0, sizeof(g_scbPerfectTopaz)/sizeof(g_scbPerfectTopaz[0]) );
		break;
	case ITEM_PERFECT_AMETHYST:
		lo_oItem.setItemBuffer( g_scbPerfectAmethyst, 0, sizeof(g_scbPerfectAmethyst)/sizeof(g_scbPerfectAmethyst[0]) );
		break;
	}

	return lo_oItem;
}