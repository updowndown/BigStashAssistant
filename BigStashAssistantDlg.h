// BigStashAssistantDlg.h : 头文件
//

#pragma once

#include "BigStash.h"
#include "afxwin.h"
#include "afxcmn.h"

// CBigStashAssistantDlg 对话框
class CBigStashAssistantDlg : public CDialog
{
// 构造
public:
	CBigStashAssistantDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BIGSTASHASSISTANT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButtonCube();
	afx_msg void OnBnClickedButtonOpenBigStash();
	afx_msg void OnBnClickedButtonAddCubeChoice();
	DECLARE_MESSAGE_MAP()

private:
	void InitCubeChoiceCombo();

private:
	CComboBox m_cmbCubeChoice;

	CString m_strBigStashPath;

	CBigStash m_oBigStash;

private:
	CListCtrl m_listCubeChoices;
	
	std::vector<S_CubeChoice> m_vSelectedChoices;
public:
	afx_msg void OnBnClickedButtonSave();
	CListBox m_listLog;
};
