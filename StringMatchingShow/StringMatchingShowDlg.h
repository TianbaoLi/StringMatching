
// StringMatchingShowDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"



// CStringMatchingShowDlg �Ի���
class CStringMatchingShowDlg : public CDialogEx
{
// ����
public:
	CStringMatchingShowDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STRINGMATCHINGSHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit pattern;
	CEdit source;
	CButton choice_Simple;
	CButton choice_Rabink;
	CButton choice_KMP;
	afx_msg void OnBnClickedButtonmatch();
	CEdit answer_Simple;
	CEdit answer_Rabink;
	CEdit answer_KMP;
	CEdit time_Simple;
	CEdit time_Rabink;
	CEdit time_KMP;
	afx_msg void OnBnClickedButtonopen();

private:
	char *sSource;
	char *sPattern;
};
