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
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ�챦ʯ ==> �����챦ʯ");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_AMETHYST );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_AMETHYST );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_AMETHYST );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_AMETHYST );
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ�ϱ�ʯ ==> �����ϱ�ʯ");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SKULL );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SKULL );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SKULL );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_SKULL );
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ���� ==> ��������");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_DIAMOND );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_DIAMOND );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_DIAMOND );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_DIAMOND );
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ��ʯ ==> ������ʯ");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SAPPHIRE );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SAPPHIRE );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_SAPPHIRE );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_SAPPHIRE );
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ����ʯ ==> ��������ʯ");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_EMERALD );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_EMERALD );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_EMERALD );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_EMERALD );
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ�̱�ʯ ==> �����̱�ʯ");
	g_scvCubeChoices.push_back(lo_sCubeChoice);

	lo_sCubeChoice.m_vInputs.clear();
	lo_sCubeChoice.m_vOutput.clear();
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_TOPAZ );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_TOPAZ );
	lo_sCubeChoice.m_vInputs.push_back( ITEM_FLAWLESS_TOPAZ );
	lo_sCubeChoice.m_vOutput.push_back( ITEM_PERFECT_TOPAZ );
	lo_sCubeChoice.m_strDescripe = _T("3*��Ͼ�Ʊ�ʯ ==> �����Ʊ�ʯ");
	g_scvCubeChoices.push_back(lo_sCubeChoice);
}

CString toString( E_ItemType ar_eItemType )
{
	switch( ar_eItemType )
	{
	case ITEM_FLAWLESS_RUBY:
		return _T("��Ͼ�ĺ챦ʯ");
	case ITEM_FLAWLESS_AMETHYST:
		return _T("��Ͼ�ϱ�ʯ");
	case ITEM_FLAWLESS_SKULL:
		return _T("��Ͼ����");
	case ITEM_FLAWLESS_DIAMOND:
		return _T("��Ͼ��ʯ");
	case ITEM_FLAWLESS_SAPPHIRE:
		return _T("��Ͼ����ʯ");
	case ITEM_FLAWLESS_EMERALD:
		return _T("��Ͼ�̱�ʯ");
	case ITEM_FLAWLESS_TOPAZ:
		return _T("��Ͼ�Ʊ�ʯ");
	case ITEM_PERFECT_RUBY:
		return _T("�����챦ʯ");
	case ITEM_PERFECT_AMETHYST:
		return _T("�����ϱ�ʯ");
	case ITEM_PERFECT_SKULL:
		return _T("��������");
	case ITEM_PERFECT_DIAMOND:
		return _T("������ʯ");
	case ITEM_PERFECT_SAPPHIRE:
		return _T("��������ʯ");
	case ITEM_PERFECT_EMERALD:
		return _T("�����̱�ʯ");
	case ITEM_PERFECT_TOPAZ:
		return _T("�����Ʊ�ʯ");
	default:
		return _T("δ֪����Ʒ");
	}
}