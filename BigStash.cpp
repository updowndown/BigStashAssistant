#include "StdAfx.h"
#include ".\bigstash.h"

CBigStash::CBigStash(void)
{
}

CBigStash::~CBigStash(void)
{
}

unsigned int CBigStash::PageSize()
{
	return (unsigned int)m_vPages.size();
}

void CBigStash::PageSize( unsigned int val )
{
	m_vPages.resize(val);
}

void CBigStash::setPage( unsigned int index, CBigStashPage& page )
{
	if( index < m_vPages.size() )
	{
		m_vPages[index] = page;
	}
}

bool CBigStash::getPage( unsigned int index, CBigStashPage& page )
{
	if( index < m_vPages.size() )
	{
		page = m_vPages[index];

		return true;
	}
	else
	{
		return false;
	}
}

unsigned CBigStash::getNumberOf( E_ItemType ar_eItemType )
{
	unsigned lo_nCount = 0;

	for( unsigned i = 0; i < m_vPages.size(); ++i )
	{
		lo_nCount += m_vPages[i].getNumberOf(ar_eItemType);
	}

	return lo_nCount;
}

std::vector<BYTE> CBigStash::asBytes()
{
	std::vector<BYTE> lo_vFileBytes;

	/// 文件头
	lo_vFileBytes.push_back(0x53);
	lo_vFileBytes.push_back(0x53);
	lo_vFileBytes.push_back(0x53);
	lo_vFileBytes.push_back(0x00);

	/// 版本号
	lo_vFileBytes.push_back( LOBYTE(m_sVersion) );
	lo_vFileBytes.push_back( HIBYTE(m_sVersion) );

	/// 金币
	if( m_nGold > 0 )
	{
		lo_vFileBytes.push_back( LOBYTE( LOWORD(m_nGold) ) );
		lo_vFileBytes.push_back( HIBYTE( LOWORD(m_nGold) ) );
		lo_vFileBytes.push_back( LOBYTE( HIWORD(m_nGold) ) );
		lo_vFileBytes.push_back( HIBYTE( HIWORD(m_nGold) ) );
	}

	/// 页数
	lo_vFileBytes.push_back( LOBYTE( LOWORD(m_vPages.size()) ) );
	lo_vFileBytes.push_back( HIBYTE( LOWORD(m_vPages.size()) ) );
	lo_vFileBytes.push_back( LOBYTE( HIWORD(m_vPages.size()) ) );
	lo_vFileBytes.push_back( HIBYTE( HIWORD(m_vPages.size()) ) );

	for( unsigned i = 0; i < m_vPages.size(); ++i )
	{
		std::vector<BYTE> lo_vPageBytes;

		lo_vPageBytes = m_vPages[i].asBytes();

		lo_vFileBytes.insert( lo_vFileBytes.end(), lo_vPageBytes.begin(), lo_vPageBytes.end() );
	}

	return lo_vFileBytes;
}

void CBigStash::deleteItem( E_ItemType ar_eItemType )
{
	for( unsigned i = 0; i < m_vPages.size(); ++i )
	{
		if( m_vPages[i].getNumberOf(ar_eItemType) > 0 )
		{
			m_vPages[i].deleteItem(ar_eItemType);

			return;
		}
	}
}

void CBigStash::addPage( CBigStashPage& page )
{
	m_vPages.push_back(page);
}