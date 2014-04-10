#include "stdafx.h"
#include "BigStashDefines.h"

std::vector<S_CubeChoice> g_scvCubeChoices;
void g_initGlobleVariable()
{
	S_CubeChoice lo_sCubeChoice;
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_RUBY );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_RUBY );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_RUBY );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_RUBY );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇红宝石 ==> 完美红宝石");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_AMETHYST );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_AMETHYST );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_AMETHYST );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_AMETHYST );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇紫宝石 ==> 完美紫宝石");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SKULL );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SKULL );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SKULL );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_SKULL );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇骷髅 ==> 完美骷髅");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_DIAMOND );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_DIAMOND );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_DIAMOND );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_DIAMOND );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇钻石 ==> 完美钻石");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SAPPHIRE );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SAPPHIRE );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SAPPHIRE );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_SAPPHIRE );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇蓝宝石 ==> 完美蓝宝石");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_EMERALD );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_EMERALD );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_EMERALD );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_EMERALD );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇绿宝石 ==> 完美绿宝石");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_TOPAZ );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_TOPAZ );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_TOPAZ );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_TOPAZ );
	lo_sCubeChoice.m_strDescripe = _T("3*无暇黄宝石 ==> 完美黄宝石");
	g_scvCubeChoices.push_back(lo_sCubeChoice);
}

CString toString( E_ItemType ar_eItemType )
{
	switch( ar_eItemType )
	{
	case ITEM_FLAWLESS_RUBY:
		return _T("无暇的红宝石");
	case ITEM_FLAWLESS_AMETHYST:
		return _T("无暇紫宝石");
	case ITEM_FLAWLESS_SKULL:
		return _T("无暇骷髅");
	case ITEM_FLAWLESS_DIAMOND:
		return _T("无暇钻石");
	case ITEM_FLAWLESS_SAPPHIRE:
		return _T("无暇蓝宝石");
	case ITEM_FLAWLESS_EMERALD:
		return _T("无暇绿宝石");
	case ITEM_FLAWLESS_TOPAZ:
		return _T("无暇黄宝石");
	case ITEM_PERFECT_RUBY:
		return _T("完美红宝石");
	case ITEM_PERFECT_AMETHYST:
		return _T("完美紫宝石");
	case ITEM_PERFECT_SKULL:
		return _T("完美骷髅");
	case ITEM_PERFECT_DIAMOND:
		return _T("完美钻石");
	case ITEM_PERFECT_SAPPHIRE:
		return _T("完美蓝宝石");
	case ITEM_PERFECT_EMERALD:
		return _T("完美绿宝石");
	case ITEM_PERFECT_TOPAZ:
		return _T("完美黄宝石");
	default:
		return _T("未知的物品");
	}
}