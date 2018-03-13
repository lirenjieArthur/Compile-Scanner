#pragma once
#include "afxcmn.h"
#include<set>
#include<stack>
#include<vector>
#include<map>
using namespace std;
// ParserAnalyzeDlg 对话框

class ParserAnalyzeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ParserAnalyzeDlg)

public:
	ParserAnalyzeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ParserAnalyzeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Parser_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedselectlexfile();
	afx_msg void OnBnClickeddoparseranalyze();
	afx_msg void OnEnChangeEdit1();

	vector<CString> grammar;
	set<char> VN;
	set<char> VT;
	map<char,set<char>> firstOfVN;//非终结符的first集

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
	};//项目集的每一项
	map<int, set<Item>> projectSet;
	//vector<set<Item>> projectSet;
	int setCount = 0;

	struct transItem {
		int begin;
		int end;
		char path;
	};
	vector<transItem> transTable;//项目集族的DFA

	vector<map<char,int>> LR1Table;//数组下标为LR1分析表的行，map为列和值，int负数表示用相应的产生式规约，正数表示转移到相应状态

	bool is_done = false;//语法分析是否完成
	bool is_error;//语法错误
	int state;
	int strIndex;
	bool is_conflict = false;//判断项目集是否有冲突

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
