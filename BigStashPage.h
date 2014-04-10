#pragma once
#include "BigStashItem.h"

#include <vector>

using std::vector;

class CBigStashPage
{
public:
	CBigStashPage(void);
	~CBigStashPage(void);

public:
	std::vector<BYTE> asBytes();

public:
	unsigned int ItemSize();
	void ItemSize(unsigned int val); 

	void setItem( unsigned index, CBigStashItem& item );
	bool getItem( unsigned index, CBigStashItem& item );

public:
	unsigned getNumberOf( E_ItemType ar_eItemType );

	void deleteItem( E_ItemType ar_eItemType );

	bool addItem( CBigStashItem& item );

private:
	vector<CBigStashItem> m_vItems;
};
