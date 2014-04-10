#pragma once

#include "BigStashItem.h"

class CItemFactory
{
public:
	CItemFactory(void);
	~CItemFactory(void);

public:
	static CBigStashItem createItem( E_ItemType ar_eItem );
};
