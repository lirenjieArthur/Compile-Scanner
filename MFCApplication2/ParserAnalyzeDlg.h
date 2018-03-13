#pragma once
#include "afxcmn.h"
#include<set>
#include<stack>
#include<vector>
#include<map>
using namespace std;
// ParserAnalyzeDlg �Ի���

class ParserAnalyzeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParserAnalyzeDlg)

public:
	ParserAnalyzeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ParserAnalyzeDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Parser_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedselectlexfile();
	afx_msg void OnBnClickeddoparseranalyze();
	afx_msg void OnEnChangeEdit1();

	vector<CString> grammar;
	set<char> VN;
	set<char> VT;
	map<char,set<char>> firstOfVN;//���ս����first��

	int itemnum = 0;
	struct Item{
		int key;
		int grammar_numb;
		int part;
		char expchar;
		/*!!!!!!!!!!!!!*/
		bool operator < (const Item &o) const
		{
			if (key<o.key) {
				return true;
			}
			else {
				return false;
			}
		}
	};//��Ŀ����ÿһ��
	map<int, set<Item>> projectSet;
	//vector<set<Item>> projectSet;
	int setCount = 0;

	struct transItem {
		int begin;
		int end;
		char path;
	};
	vector<transItem> transTable;//��Ŀ�����DFA

	vector<map<char,int>> LR1Table;//�����±�ΪLR1��������У�mapΪ�к�ֵ��int������ʾ����Ӧ�Ĳ���ʽ��Լ��������ʾת�Ƶ���Ӧ״̬

	bool is_done = false;//�﷨�����Ƿ����
	bool is_error;//�﷨����
	int state;
	int strIndex;
	bool is_conflict = false;//�ж���Ŀ���Ƿ��г�ͻ

	CString lexFilePath;
	CStdioFile lexFile;

	void get_VNfirst();
	void get_eclosure(int T);
	set<char> get_expchar(Item item);
	bool isInSet(int T,Item item);
	void createProjSet();
	int is_existed();
	void get_LR1Table();
	bool LR1Analyze(CString string);
	CString tokenListToString();
	void is_Conflict(int setNum, char ch);
};
