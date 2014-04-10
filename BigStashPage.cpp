#include "StdAfx.h"
#include ".\bigstashpage.h"

CBigStashPage::CBigStashPage(void)
{
}

CBigStashPage::~CBigStashPage(void)
{
}

unsigned int CBigStashPage::ItemSize()
{
	return (unsigned int)m_vItems.size();
}

void CBigStashPage::ItemSize( unsigned int val )
{
	m_vItems.resize(val);
}

void CBigStashPage::setItem( unsigned index, CBigStashItem& item )
{
	if( index < m_vItems.size() )
	{
		m_vItems[index] = item;
	}
}

bool CBigStashPage::getItem( unsigned index, CBigStashItem& item )
{
	if( index < m_vItems.size() )
	{
		item = m_vItems[index];

		return true;
	}
	else
	{
		return false;
	}
}

unsigned CBigStashPage::getNumberOf( E_ItemType ar_eItemType )
{
	unsigned lo_nCount = 0;

	for( unsigned i = 0; i < m_vItems.size(); ++i )
	{
		if( m_vItems[i].isTypeOf(ar_eItemType) )
		{
			++lo_nCount;
		}
	}

	return lo_nCount;
}

std::vector<BYTE> CBigStashPage::asBytes()
{
	std::vector<BYTE> lo_vPageBytes;

	/// 页首
	lo_vPageBytes.push_back(0x53);
	lo_vPageBytes.push_back(0x54);
	lo_vPageBytes.push_back(0x00);
	lo_vPageBytes.push_back(0x4A);
	lo_vPageBytes.push_back(0x4D);

	/// 物品数
	lo_vPageBytes.push_back( LOBYTE(m_vItems.size()) );
	lo_vPageBytes.push_back( HIBYTE(m_vItems.size()) );

	for( unsigned i = 0; i < m_vItems.size(); ++i )
	{
		std::vector<BYTE> lo_vItemBytes;

		lo_vItemBytes = m_vItems[i].asBytes();

		lo_vPageBytes.insert( lo_vPageBytes.end(), lo_vItemBytes.begin(), lo_vItemBytes.end() );
	}

	return lo_vPageBytes;
}

void CBigStashPage::deleteItem( E_ItemType ar_eItemType )
{
	for( unsigned i = 0; i < m_vItems.size(); ++i )
	{
		if( m_vItems[i].isTypeOf(ar_eItemType) )
		{
			m_vItems.erase(m_vItems.begin()+i);

			return;
		}
	}
}

bool CBigStashPage::addItem( CBigStashItem& item )
{
	if( m_vItems.size() >= 100 )
	{
		return false;
	}

	m_vItems.push_back(item);

	return true;
}