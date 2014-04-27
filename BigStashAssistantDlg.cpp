// BigStashAssistantDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BigStashAssistant.h"
#include "BigStashAssistantDlg.h"
#include ".\bigstashassistantdlg.h"
#include "BigStashPaser.h"
#include "ItemFactory.h"
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const static int g_scnCostPerCube = 5000;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBigStashAssistantDlg �Ի���



CBigStashAssistantDlg::CBigStashAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBigStashAssistantDlg::IDD, pParent)
	, m_strStashType(_T(""))
	, m_nGold(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBigStashAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strBigStashPath);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
	DDX_Text(pDX, IDC_EDIT_STASH_TYPE, m_strStashType);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_nGold);
	DDX_Control(pDX, IDC_BUTTON_CUBE, m_btnCube);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_STATIC_COST_INFO, m_staticCostInfo);
}

BEGIN_MESSAGE_MAP(CBigStashAssistantDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN_BIG_STASH, OnBnClickedButtonOpenBigStash)
	ON_BN_CLICKED(IDC_BUTTON_CUBE, OnBnClickedButtonCube)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CUBE_CHOICE, OnBnClickedButtonAddCubeChoice)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnBnClickedButtonTest)
END_MESSAGE_MAP()


// CBigStashAssistantDlg ��Ϣ�������

BOOL CBigStashAssistantDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_listLog.AddString(_T("���������ڽ���������������Ͼ��ʯ�ϳ�Ϊ������ʯ��"));
	m_listLog.AddString(_T(""));
	m_listLog.AddString(_T("��ע�⣺"));
	m_listLog.AddString(_T("1�����뵥�����׵����ѣ��뾡����ȡ�ý���Ȧͬ�����ʹ�ñ����ߣ�"));
	m_listLog.AddString(_T("2��ʹ�ù���ǰ�뱸�ݴ浵�Ա���浵�𻵣�"));
	m_listLog.AddString(_T("3���ϳ��ز���������ڷţ��ϳɽ���ڴ����ӵ����ҳ��"));
	m_listLog.AddString(_T("4���ϳɺ���������Ż������޸Ĵ浵�ļ���"));
	m_listLog.AddString(_T(""));
	m_listLog.AddString(_T("������ɷ������~�~�� @updowndown"));
	
	CString lo_strCostInfo;

	lo_strCostInfo.Format(_T("ÿ�ϳ�һ�λ���%d��"), g_scnCostPerCube);

	m_staticCostInfo.SetWindowText(lo_strCostInfo);

	m_btnCube.EnableWindow(FALSE);

	m_btnSave.EnableWindow(FALSE);

	return TRUE;
}

void CBigStashAssistantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBigStashAssistantDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CBigStashAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBigStashAssistantDlg::OnBnClickedButtonOpenBigStash()
{
	CFileDialog m_oFileDialog( TRUE, _T("sss") );

	if( m_oFileDialog.DoModal() == IDOK )
	{
		m_btnCube.EnableWindow(FALSE);
		
		m_btnSave.EnableWindow(FALSE);

		m_strBigStashPath = m_oFileDialog.GetPathName();

		UpdateData(FALSE);

		if( !openBigStash(m_strBigStashPath, m_oBigStash) )
		{
			AfxMessageBox(_T("�������ļ���ʧ��"));

			return;
		}

		switch( m_oBigStash.BigStashType() )
		{
		case PERSONAL_BIG_STASH:
			{
				int lo_oPos = m_strBigStashPath.ReverseFind('\\');

				m_strSharedBigStashPath = m_strBigStashPath.Left(lo_oPos);

				m_strSharedBigStashPath = m_strSharedBigStashPath + "\\_LOD_SharedStashSave.sss";

				if( !openBigStash(m_strSharedBigStashPath, m_oSharedBigStash) )
				{
					AfxMessageBox(_T("�������ļ���ʧ��"));

					return;
				}

				m_strStashType = _T("������");

				m_nGold = m_oSharedBigStash.Gold();

				m_btnCube.EnableWindow(TRUE);

				m_btnSave.EnableWindow(TRUE);
			}
			break;
		case SHARE_BIG_STASH:
			m_strStashType = _T("������");

			m_nGold = m_oBigStash.Gold();

			m_btnCube.EnableWindow(TRUE);

			m_btnSave.EnableWindow(TRUE);
			break;
		default:
			m_strStashType = _T("");
			break;
		}
		
		UpdateData(FALSE);
	}
}


bool CBigStashAssistantDlg::openBigStash( CString ar_strPath, CBigStash& ar_oBigStash )
{
	CFile lo_oFile;

	BOOL lo_bSucc = lo_oFile.Open( ar_strPath,CFile::modeRead|CFile::typeBinary);

	if( !lo_bSucc )
	{
		return false;
	}

	BYTE* lo_pStashData = NULL;

	int lo_nStashDataLength = 0;

	int lo_nBuffLength = (int)lo_oFile.GetLength();

	lo_pStashData = new BYTE[lo_nBuffLength];

	int lo_nReadLength = lo_oFile.Read( lo_pStashData,lo_nBuffLength );

	lo_oFile.Close();

	if( lo_nReadLength != lo_nBuffLength )
	{
		delete[] lo_pStashData;

		lo_pStashData = 0;

		return false;
	}

	lo_nStashDataLength = lo_nBuffLength;

	CBigStashPaser lo_oBigStashPaser;

	lo_bSucc = lo_oBigStashPaser.parse(lo_pStashData, lo_nStashDataLength, ar_oBigStash);

	delete[] lo_pStashData;

	return lo_bSucc;
}

void CBigStashAssistantDlg::OnBnClickedButtonCube()
{
	m_listLog.ResetContent();

	m_listLog.AddString(_T("��ʼ�ϳ�..."));

	for( unsigned i = 0; i < g_scvCubeFormulas.size(); ++i )
	{
		S_CubeFormula lo_sCubeChoice = g_scvCubeFormulas[i];

		std::map< E_ItemType, int > lo_mapInputItemCount;

		for( unsigned j = 0; j < lo_sCubeChoice.m_vInputs.size(); ++j )
		{
			++lo_mapInputItemCount[lo_sCubeChoice.m_vInputs[j]];
		}

		int lo_nCubeCount = -1;

		std::map< E_ItemType, int >::iterator it;

		for( it = lo_mapInputItemCount.begin(); it != lo_mapInputItemCount.end(); ++it )
		{
			E_ItemType lo_eItemType = it->first;

			int lo_nItemCount = m_oBigStash.getNumberOf(lo_eItemType);

			int lo_nMaxCubeCount = lo_nItemCount / it->second;

			if( lo_nMaxCubeCount < lo_nCubeCount || lo_nCubeCount < 0 )
			{
				lo_nCubeCount = lo_nMaxCubeCount;
			}
		}

		if( lo_nCubeCount > m_nGold/g_scnCostPerCube )
		{
			lo_nCubeCount = m_nGold/g_scnCostPerCube;
		}

		if( lo_nCubeCount > 0 )
		{
			int lo_nTotalCost = lo_nCubeCount*g_scnCostPerCube;

			m_nGold = m_nGold - lo_nTotalCost;

			switch( m_oBigStash.BigStashType() )
			{
			case PERSONAL_BIG_STASH:
				m_oSharedBigStash.Gold( m_nGold );
				break;
			case SHARE_BIG_STASH:
				m_oBigStash.Gold( m_nGold );
				break;
			default:
				break;
			}

			UpdateData(FALSE);

			/// ɾ��ԭ��
			for( it = lo_mapInputItemCount.begin(); it != lo_mapInputItemCount.end(); ++it )
			{
				E_ItemType lo_eItemType = it->first;

				int lo_nItemCountUsed = it->second*lo_nCubeCount;

				for( int j = 0; j < lo_nItemCountUsed; ++j )
				{
					m_oBigStash.deleteItem(lo_eItemType);
				}
			}

			/// ��Ӻϳɽ��
			for( unsigned j = 0; j < lo_sCubeChoice.m_vOutput.size(); ++j )
			{
				int lo_nLeftCount = lo_nCubeCount;

				while( lo_nLeftCount > 0 )
				{
					int lo_nPutCount = 0;

					if( lo_nLeftCount > 100 )
					{
						lo_nPutCount = 100;
					}
					else
					{
						lo_nPutCount = lo_nLeftCount;
					}

					lo_nLeftCount = lo_nLeftCount - lo_nPutCount;

					CBigStashPage lo_oPage;

					for( int k = 0; k < lo_nPutCount; ++k )
					{
						CBigStashItem lo_oItem = CItemFactory::createItem( lo_sCubeChoice.m_vOutput[j] );

						if( lo_oItem.isValid() )
						{
							BYTE lo_nRow = k / 10;

							BYTE lo_nCol = k % 10;

							lo_oItem.setPos( lo_nRow, lo_nCol );

							lo_oPage.addItem(lo_oItem);
						}
					}

					m_oBigStash.addPage(lo_oPage);
				}
			}
			

			CString strLog;

			strLog.Format(_T("�ϳ���%d��"), lo_nCubeCount);

			for( unsigned j = 0; j < lo_sCubeChoice.m_vOutput.size(); ++j )
			{
				CString strTemp = strLog;

				CString strItem = toString(lo_sCubeChoice.m_vOutput[j]);

				strLog.Format(_T("%s %s, ���� %d Gold"), strTemp, strItem, lo_nCubeCount*g_scnCostPerCube );
			}

			m_listLog.InsertString( m_listLog.GetCount(), strLog);
		}
	}

	m_listLog.AddString(_T("�ϳɽ�����"));
}

void CBigStashAssistantDlg::InitCubeChoiceCombo()
{
	m_cmbCubeChoice.ResetContent();

	for( unsigned i = 0; i < g_scvCubeFormulas.size(); ++i )
	{
		m_cmbCubeChoice.AddString( g_scvCubeFormulas[i].m_strDescripe );
	}

	if( m_cmbCubeChoice.GetCount() > 0 )
	{
		m_cmbCubeChoice.SetCurSel(0);
	}
}
void CBigStashAssistantDlg::OnBnClickedButtonAddCubeChoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CBigStashAssistantDlg::OnBnClickedButtonSave()
{
	std::vector<BYTE> lo_vFileBytes;

	switch( m_oBigStash.BigStashType() )
	{
	case SHARE_BIG_STASH:
		lo_vFileBytes = m_oBigStash.asBytes();

		if( lo_vFileBytes.size() > 0 )
		{
			CFile lo_oFile;

			BOOL lo_bSucc = lo_oFile.Open( m_strBigStashPath,CFile::modeWrite|CFile::typeBinary);

			if( !lo_bSucc )
			{
				AfxMessageBox(_T("����������ļ�ʧ�ܣ�"));

				return;
			}

			lo_oFile.Write( &lo_vFileBytes[0], (UINT)lo_vFileBytes.size() );

			lo_oFile.Flush();

			lo_oFile.Close();
		}
		break;
	case PERSONAL_BIG_STASH:
		lo_vFileBytes = m_oBigStash.asBytes();

		if( lo_vFileBytes.size() > 0 )
		{
			CFile lo_oFile;

			BOOL lo_bSucc = lo_oFile.Open( m_strBigStashPath,CFile::modeWrite|CFile::typeBinary);

			if( !lo_bSucc )
			{
				AfxMessageBox(_T("����������ļ�ʧ�ܣ�"));

				return;
			}

			lo_oFile.Write( &lo_vFileBytes[0], (UINT)lo_vFileBytes.size() );

			lo_oFile.Flush();

			lo_oFile.Close();
		}

		lo_vFileBytes = m_oSharedBigStash.asBytes();

		if( lo_vFileBytes.size() > 0 )
		{
			CFile lo_oFile;

			BOOL lo_bSucc = lo_oFile.Open( m_strSharedBigStashPath,CFile::modeWrite|CFile::typeBinary);

			if( !lo_bSucc )
			{
				AfxMessageBox(_T("���湫�������ļ�ʧ�ܣ�"));

				return;
			}

			lo_oFile.Write( &lo_vFileBytes[0], (UINT)lo_vFileBytes.size() );

			lo_oFile.Flush();

			lo_oFile.Close();
		}
		break;
		break;
	default:
		break;
	}
}

void CBigStashAssistantDlg::OnBnClickedButtonTest()
{
	for( int i = ITEM_FLAWLESS_RUBY; i <= ITEM_PERFECT_TOPAZ; ++i )
	{
		CBigStashPage lo_oPage;

		for( int k = 0; k < 100; ++k )
		{
			CBigStashItem lo_oItem = CItemFactory::createItem( (E_ItemType)i );

			if( lo_oItem.isValid() )
			{
				BYTE lo_nRow = k / 10;

				BYTE lo_nCol = k % 10;

				lo_oItem.setPos( lo_nRow, lo_nCol );

				lo_oPage.addItem(lo_oItem);
			}
		}

		m_oBigStash.addPage(lo_oPage);
	}
}
