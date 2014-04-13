// BigStashAssistantDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CBigStashAssistantDlg 对话框



CBigStashAssistantDlg::CBigStashAssistantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBigStashAssistantDlg::IDD, pParent)
	, m_strStashType(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBigStashAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strBigStashPath);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
	DDX_Text(pDX, IDC_EDIT_STASH_TYPE, m_strStashType);
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


// CBigStashAssistantDlg 消息处理程序

BOOL CBigStashAssistantDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_listLog.AddString(_T("本工具用于将大箱子中所有无暇宝石合成为完美宝石。"));
	m_listLog.AddString(_T(""));
	m_listLog.AddString(_T("请注意："));
	m_listLog.AddString(_T("1、参与单机交易的朋友，请尽量在取得交易圈同意后再使用本工具；"));
	m_listLog.AddString(_T("2、使用工具前请备份存档以避免存档损坏；"));
	m_listLog.AddString(_T("3、合成素材无需特意摆放，合成结果在大箱子的最后几页；"));
	m_listLog.AddString(_T("4、合成后需点击保存才会真正修改存档文件。"));
	m_listLog.AddString(_T(""));
	m_listLog.AddString(_T("有问题可反馈至鈤鈤铺 @updowndown"));
	

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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBigStashAssistantDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CBigStashAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBigStashAssistantDlg::OnBnClickedButtonOpenBigStash()
{
	CFileDialog m_oFileDialog( TRUE, _T("sss") );

	if( m_oFileDialog.DoModal() == IDOK )
	{
		m_strBigStashPath = m_oFileDialog.GetPathName();

		UpdateData(FALSE);

		CFile lo_oFile;

		BOOL lo_bSucc = lo_oFile.Open( m_strBigStashPath,CFile::modeRead|CFile::typeBinary);

		if( !lo_bSucc )
		{
			AfxMessageBox(_T("读取大箱子文件失败！"));

			return;
		}

		BYTE* lo_pStashData = NULL;

		int lo_nStashDataLength = 0;

		int lo_nBuffLength = (int)lo_oFile.GetLength();

		lo_pStashData = new BYTE[lo_nBuffLength];

		int lo_nReadLength = lo_oFile.Read( lo_pStashData,lo_nBuffLength );

		if( lo_nReadLength != lo_nBuffLength )
		{
			delete[] lo_pStashData;

			lo_pStashData = 0;

			AfxMessageBox(_T("读取大箱子文件失败！"));

			return;
		}

		lo_nStashDataLength = lo_nBuffLength;

		lo_oFile.Close();

		CBigStashPaser lo_oBigStashPaser;

		if( lo_oBigStashPaser.parse(lo_pStashData, lo_nStashDataLength, m_oBigStash) )
		{
			switch( m_oBigStash.BigStashType() )
			{
			case PERSONAL_BIG_STASH:
				m_strStashType = _T("个人箱");
				break;
			case SHARE_BIG_STASH:
				m_strStashType = _T("公共箱");
				break;
			default:
				m_strStashType = _T("");
				break;
			}

			UpdateData(FALSE);
		}

		delete[] lo_pStashData;
	}
}

void CBigStashAssistantDlg::OnBnClickedButtonCube()
{
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
		
		if( lo_nCubeCount > 0 )
		{
			/// 删除原料
			for( it = lo_mapInputItemCount.begin(); it != lo_mapInputItemCount.end(); ++it )
			{
				E_ItemType lo_eItemType = it->first;

				int lo_nItemCountUsed = it->second*lo_nCubeCount;

				for( int j = 0; j < lo_nItemCountUsed; ++j )
				{
					m_oBigStash.deleteItem(lo_eItemType);
				}
			}

			/// 添加合成结果
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

			strLog.Format(_T("合成了%d个"), lo_nCubeCount);

			for( unsigned j = 0; j < lo_sCubeChoice.m_vOutput.size(); ++j )
			{
				CString strTemp = strLog;

				CString strItem = toString(lo_sCubeChoice.m_vOutput[j]);

				strLog.Format(_T("%s %s"), strTemp, strItem );
			}

			m_listLog.InsertString( m_listLog.GetCount(), strLog);
		}
	}
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
	// TODO: 在此添加控件通知处理程序代码
}

void CBigStashAssistantDlg::OnBnClickedButtonSave()
{
	std::vector<BYTE> lo_vFileBytes = m_oBigStash.asBytes();

	if( lo_vFileBytes.size() > 0 )
	{
		CFile lo_oFile;

		BOOL lo_bSucc = lo_oFile.Open( m_strBigStashPath,CFile::modeWrite|CFile::typeBinary);

		if( !lo_bSucc )
		{
			AfxMessageBox(_T("保存大箱子文件失败！"));

			return;
		}

		lo_oFile.Write( &lo_vFileBytes[0], (UINT)lo_vFileBytes.size() );

		lo_oFile.Flush();

		lo_oFile.Close();
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
