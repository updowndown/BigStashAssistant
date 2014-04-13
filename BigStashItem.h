#pragma once

#include <vector>

using std::vector;

class CBigStashItem
{
public:
	CBigStashItem(void);
	~CBigStashItem(void);

public:
	vector<BYTE> asBytes();

public:
	S_ItemCode getItemCode();

public:
	bool isValid();

	void setItemBuffer( const BYTE* ar_pData, unsigned ar_nStart, unsigned ar_nSize );

public:
	void setPos( BYTE ar_nRow, BYTE ar_nCol );

public:
	bool isTypeOf( E_ItemType ar_eItemType );

private:
	vector<BYTE> m_vItemBuffer;
};
