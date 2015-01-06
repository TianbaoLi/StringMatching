
// StringMatchingShowDlg.h : 头文件
//

#pragma once
#include "afxwin.h"



// CStringMatchingShowDlg 对话框
class CStringMatchingShowDlg : public CDialogEx
{
// 构造
public:
	CStringMatchingShowDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_STRINGMATCHINGSHOW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
