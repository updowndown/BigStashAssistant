#pragma once
#include "BigStash.h"

class CBigStashPaser
{
public:
	CBigStashPaser(void);
	~CBigStashPaser(void);

public:
	bool parse( BYTE* ar_pBigStashData, int ar_nDataLength, CBigStash& ar_oBigStash );

private:
	bool checkHeader();

	bool parseVersion( CBigStash& ar_oBigStash );

	bool parseGoldAndPageSize( CBigStash& ar_oBigStash );

	bool parseAllPages( CBigStash& ar_oBigStash );

private:
	bool parsePage( CBigStashPage& ar_oPage );

private:
	int findNextPageHeader();

	int findNextItem( int ar_nPageStart, int ar_nPageEnd );
private:
	unsigned short getShortValue( BYTE* ar_pData, int ar_nDataLength, int ar_nIndex );

	unsigned int getIntValue( BYTE* ar_pData, int ar_nDataLength, int ar_nIndex );

private:
	BYTE* m_pBigStashDatas;
	int m_nDataLength;
	int m_nIndex;
};
