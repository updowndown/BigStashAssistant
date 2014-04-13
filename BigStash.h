#pragma once
#include "BigStashPage.h"
#include <vector>

using std::vector;

enum E_BigStashType
{
	PERSONAL_BIG_STASH,
	SHARE_BIG_STASH,
	UNKNOWN_BIG_STASH,
};


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

	E_BigStashType BigStashType() const { return m_eBigStashType; }
	void BigStashType(E_BigStashType val) { m_eBigStashType = val; }

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

	E_BigStashType m_eBigStashType;
};
