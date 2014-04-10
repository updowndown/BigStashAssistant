#pragma once
#include "BigStashPage.h"
#include <vector>

using std::vector;

class CBigStash
{
public:
	CBigStash(void);
	~CBigStash(void);

public:
	std::vector<BYTE> asBytes();

public:
	unsigned short Version() const { return m_sVersion; }
	void Version(unsigned short val) { m_sVersion = val; }

	unsigned int Gold() const { return m_nGold; }
	void Gold(unsigned int val) { m_nGold = val; }

	unsigned int PageSize();
	void PageSize(unsigned int val);

public:
	void setPage( unsigned index, CBigStashPage& page );
	bool getPage( unsigned index, CBigStashPage& page );

	void addPage( CBigStashPage& page );

public:
	unsigned getNumberOf( E_ItemType ar_eItemType );

	void deleteItem( E_ItemType ar_eItemType );

private:
	unsigned short m_sVersion;

	unsigned int m_nGold;

	std::vector<CBigStashPage> m_vPages;
};
