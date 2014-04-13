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

	ITEM_TYPE_SIZE,
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


struct S_ItemCode
{
	char m_cItemCode[5];

	S_ItemCode()
	{
		memset( m_cItemCode, 0, 5*sizeof(char) );
	}

	S_ItemCode( const char ar_cItemCode[5] )
	{
		memcpy( m_cItemCode, ar_cItemCode, 4*sizeof(char) );
	}

	bool operator==( const S_ItemCode& other )
	{
		for( int i = 0; i < 5; ++i )
		{
			if( m_cItemCode[i] != other.m_cItemCode[i] )
			{
				return false;
			}
		}

		return true;
	}
};

S_ItemCode g_getItemCode( E_ItemType ar_eItemType );

extern S_ItemCode g_scvItemCodes[ITEM_TYPE_SIZE];

#endif