// BigStashAssistantDlg.h : ͷ�ļ�
//

#pragma once

#include "BigStash.h"
#include "afxwin.h"
#include "afxcmn.h"

// CBigStashAssistantDlg �Ի���
class CBigStashAssistantDlg : public CDialog
{
// ����
public:
	CBigStashAssistantDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BIGSTASHASSISTANT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
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
