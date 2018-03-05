
// MFCApplication2Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include<set>
#include<stack>
#include<vector>
#include<map>
using namespace std;


// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	const static int MAX_NODES = 50;
	struct Traid
	{
		char start;
		char edge;
		char end;
	}*G;//G为NFA
	struct Traid2
	{
		int start;
		char edge;
		int end;
	};
	vector<Traid2> DFA;
	map<int, int> state;//是否是终态,1表示终态
	

	CString int2CString(int i);
	set<char> e_closure(set<char>, Traid[], int);
	set<char> move(set<char>, char, Traid[], int);
	void determined(Traid[], int, char*, int);
	int getNextState(int start, char edge);
	void scanner();
	void addToTokenList(int linenum,CString token);

	afx_msg void OnBnClickedSelectLEX();
	afx_msg void OnEnChangeLexFileName();
	afx_msg void OnBnClickedSelectfile();
	afx_msg void OnEnChangeFilename();
	afx_msg void OnBnClickedwordanalyze();
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl resultlist;
	afx_msg void OnEnChangeSoucecode();
	

	CString FilePath;
	CStdioFile file;
	CString lexFilePath;
	CStdioFile lexFile;
	vector<CString> fileLines;//存放源代码的每一行
	
};
