
// MFCApplication2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include<set>
#include<stack>
#include<vector>
#include<map>
using namespace std;


// CMFCApplication2Dlg �Ի���
class CMFCApplication2Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	}*G;//GΪNFA
	struct Traid2
	{
		int start;
		char edge;
		int end;
	};
	vector<Traid2> DFA;
	map<int, int> state;//�Ƿ�����̬,1��ʾ��̬
	

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
	vector<CString> fileLines;//���Դ�����ÿһ��
	
};
