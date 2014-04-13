#ifndef BIG_STASH_DEFINE_H
#define BIG_STASH_DEFINE_H

#include <vector>

enum E_ItemType
{
	ITEM_FLAWLESS_RUBY,
	ITEM_FLAWLESS_AMETHYST,
	ITEM_FLAWLESS_SKULL,
	ITEM_FLAWLESS_DIAMOND,
	ITEM_FLAWLESS_SAPPHIRE,
	ITEM_FLAWLESS_EMERALD,
	ITEM_FLAWLESS_TOPAZ,


	ITEM_PERFECT_RUBY,
	ITEM_PERFECT_AMETHYST,
	ITEM_PERFECT_SKULL,
	ITEM_PERFECT_DIAMOND,
	ITEM_PERFECT_SAPPHIRE,
	ITEM_PERFECT_EMERALD,
	ITEM_PERFECT_TOPAZ,
};

CString toString( E_ItemType ar_eItemType );

struct S_CubeFormula
{
	std::vector<E_ItemType> m_vInputs;
	std::vector<E_ItemType> m_vOutput;
	CString m_strDescripe;
};

extern std::vector<S_CubeFormula> g_scvCubeFormulas;

void g_initGlobleVariable();

#endif