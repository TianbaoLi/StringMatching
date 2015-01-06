
// StringMatchingShowDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StringMatchingShow.h"
#include "StringMatchingShowDlg.h"
#include "afxdialogex.h"
#include "StringMatching.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _CRT_SECURE_NO_WARNINGS
// CStringMatchingShowDlg �Ի���



CStringMatchingShowDlg::CStringMatchingShowDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStringMatchingShowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStringMatchingShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_StringPattern, pattern);
	DDX_Control(pDX, IDC_StringSource, source);
	DDX_Control(pDX, IDC_CHECKSimple, choice_Simple);
	DDX_Control(pDX, IDC_CHECKRabink, choice_Rabink);
	DDX_Control(pDX, IDC_CHECKKMP, choice_KMP);
	DDX_Control(pDX, IDC_EDIT3, answer_Simple);
	DDX_Control(pDX, IDC_EDIT4, answer_Rabink);
	DDX_Control(pDX, IDC_EDIT5, answer_KMP);
	DDX_Control(pDX, IDC_EDIT6, time_Simple);
	DDX_Control(pDX, IDC_EDIT7, time_Rabink);
	DDX_Control(pDX, IDC_EDIT8, time_KMP);
}

BEGIN_MESSAGE_MAP(CStringMatchingShowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONMatch, &CStringMatchingShowDlg::OnBnClickedButtonmatch)
	ON_BN_CLICKED(IDC_BUTTONOpen, &CStringMatchingShowDlg::OnBnClickedButtonopen)
END_MESSAGE_MAP()


// CStringMatchingShowDlg ��Ϣ�������

BOOL CStringMatchingShowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CStringMatchingShowDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CStringMatchingShowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStringMatchingShowDlg::OnBnClickedButtonmatch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	StringMatching *strmatch = new StringMatching();
	const int maxnum = 4e8;
	CString sou, pat, temp, text, tim;
	clock_t start_simple, end_simple, start_rab, end_rab, start_kmp, end_kmp;
	if (sou.IsEmpty()==0)
	{ 
		source.GetWindowText(sou);
		sSource = new char[sou.GetLength()+1];
		strncpy(sSource, sou, sou.GetLength() + 1);
	}
	pattern.GetWindowText(pat);
	sPattern = new char[pat.GetLength() + 1];
	strncpy(sPattern, pat, pat.GetLength() + 1);
	int x = pat.GetLength();
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECKSimple))
	{
		start_simple = clock();
		vector<int> answer_simple = strmatch->Simple(sSource, sPattern);
		end_simple = clock();
		CString textS;
		for (vector<int>::iterator iter = answer_simple.begin(); iter != answer_simple.end(); iter++)
		{
			temp.Format("%d", *iter);
			textS += temp;
			textS += "\r\n";
		}
		answer_Simple.SetWindowTextA(textS);
		CString timeS;
		timeS.Format("%0.lf", (double)(end_simple - start_simple));
		time_Simple.SetWindowTextA(timeS);
	}
	else
	{
		answer_Simple.SetWindowTextA(text);
		time_Simple.SetWindowTextA(tim);
	}
	
	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECKRabink))
	{
		start_rab = clock();
		vector<int> answer_rab = strmatch->rabink(sSource, sPattern);
		end_rab = clock();
		CString textR;
		for (vector<int>::iterator iter = answer_rab.begin(); iter != answer_rab.end(); iter++)
		{
			temp.Format("%d", *iter);
			textR += temp;
			textR += "\r\n";
		}
		answer_Rabink.SetWindowTextA(textR);
		CString timeR;
		timeR.Format("%0.lf", (double)(end_rab - start_rab));
		time_Rabink.SetWindowTextA(timeR);
	}
	else
	{
		answer_Rabink.SetWindowTextA(text);
		time_Rabink.SetWindowTextA(tim);
	}

	if (BST_CHECKED == IsDlgButtonChecked(IDC_CHECKKMP))
	{
		start_kmp = clock();
		vector<int> answer_kmp = strmatch->kmp(sSource, sPattern, start_kmp);
		//vector<int> answer_kmp = strmatch->KMP_LOOP(sSource, sPattern, start_kmp);
		end_kmp = clock();
		CString textK;
		for (vector<int>::iterator iter = answer_kmp.begin(); iter != answer_kmp.end(); iter++)
		{
			temp.Format("%d", *iter);
			textK += temp;
			textK += "\r\n";
		}
		answer_KMP.SetWindowTextA(textK);
		CString timeK;
		timeK.Format("%0.lf", (double)(end_kmp - start_kmp));
		time_KMP.SetWindowTextA(timeK);
	}
	else
	{
		answer_KMP.SetWindowTextA(text);
		time_KMP.SetWindowTextA(tim);
	}
	//delete strmatch;
	//delete sPattern;
	//delete sSource;
}


void CStringMatchingShowDlg::OnBnClickedButtonopen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, _T("txt"), _T(""), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("�ı�|*.txt|�����ļ�|*||"));
	if (dlg.DoModal() == IDOK)
	{
		CopyFile(dlg.GetPathName(), dlg.GetFileName(), FALSE);
		FILE *fin = fopen(dlg.GetFileName(), "r");
		long long size;
		fseek(fin, 0, SEEK_END);
		size = ftell(fin);
		fseek(fin, 0, SEEK_SET);
		sSource = new char[size];
		memset(sSource, 0, size);
		int i = 0;
		fgets(sSource + i, 4e8, fin);
		CString t;
		t.Format("%s", sSource);
		source.SetWindowText(t.Left(32000));
	}
}
