// ParserAnalyzeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "ParserAnalyzeDlg.h"
#include "afxdialogex.h"
#include "util.h"
// ParserAnalyzeDlg 对话框

IMPLEMENT_DYNAMIC(ParserAnalyzeDlg, CDialogEx)

ParserAnalyzeDlg::ParserAnalyzeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_Parser_DIALOG, pParent)
{

}

ParserAnalyzeDlg::~ParserAnalyzeDlg()
{
}

void ParserAnalyzeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ParserAnalyzeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_selectLexFile, &ParserAnalyzeDlg::OnBnClickedselectlexfile)
	ON_BN_CLICKED(IDC_doParserAnalyze, &ParserAnalyzeDlg::OnBnClickeddoparseranalyze)
	ON_EN_CHANGE(IDC_EDIT1, &ParserAnalyzeDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ParserAnalyzeDlg 消息处理程序


BOOL ParserAnalyzeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ParserAnalyzeDlg::OnBnClickedselectlexfile()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器     
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	// 显示打开文件对话框     
	if (IDOK == fileDlg.DoModal()) {
		lexFilePath = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名;
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(lexFilePath);
	}
}


void ParserAnalyzeDlg::OnBnClickeddoparseranalyze()
{
	// TODO: 在此添加控件通知处理程序代码
}

//处理二型文法
void ParserAnalyzeDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	try {
		if (!lexFile.Open(lexFilePath, CFile::modeRead)) {
			MessageBox(_T("error"));
			return;
		}
		CString strFile;
		CString temp;
		int linenum = 0;
		// 按行读取打开文件内容  
		while (lexFile.ReadString(temp)) {
			linenum++;
		}
		lexFile.Seek(0, CFile::begin);//文件指针回到文件头
		
		int num = 0;
		while (lexFile.ReadString(temp) && num < linenum) {
			//取VN和VT
			for (int i = 0; i < temp.GetLength();i++) {
				if (i == temp.Find(_T("->")) || i == temp.Find(_T("->")) + 1)
					continue;
				if (temp.GetAt(i) <= 'Z' && temp.GetAt(i) >= 'A') {
					if (VN.count(temp.GetAt(i)) == 0)
						VN.insert(temp.GetAt(i));
				}
				else {
					if (VT.count(temp.GetAt(i)) == 0)
						VT.insert(temp.GetAt(i));
				}
			}
			//
			if (num == 0) {
				grammar.push_back(_T("$->") + temp.Left(1));
				grammar.push_back(temp);
			}
			else {
				grammar.push_back(temp);
			}
			num++;
		}
	}
	catch (CFileException *e) {
		CString str;
		str.Format(_T("读取数据失败的原因是:%d"), e->m_cause);
		MessageBox(str);
		lexFile.Abort();
		e->Delete();
	}
	get_VNfirst();//checked
	createProjSet();
	get_LR1Table();
	is_conflict;
	
	int k = tokenList.size();
	CString str = tokenListToString();
	bool isdone = LR1Analyze(str);
	is_done;
	is_error;
	
	int q=state;
	int i = strIndex;
}

void ParserAnalyzeDlg::get_VNfirst()
{
	bool flag1;
	do {
		flag1 = false;
		for (int i = 1; i < grammar.size();i++) {
			int t = grammar[i].Find(_T("->"))+2;
			bool flag2;
			do {
				flag2 = false;
				if (grammar[i].GetAt(t)>='A' && grammar[i].GetAt(t)<='Z') {
					set<char>::iterator iter = VT.begin();
					while (iter != VT.end()) {
						if (firstOfVN[grammar[i].GetAt(t)].count(*iter) == 1 && firstOfVN[grammar[i].GetAt(0)].count(*iter) == 0) {
							firstOfVN[grammar[i].GetAt(0)].insert(*iter);
							flag1 = true;
						}
						iter++;
					}
					if (firstOfVN[grammar[i].GetAt(t)].count('@') != 0) {
						t++;
						flag2 = true;
					}
				}
				else if( firstOfVN[grammar[i].GetAt(0)].count(grammar[i].GetAt(t)) == 0) {
					firstOfVN[grammar[i].GetAt(0)].insert(grammar[i].GetAt(t));
					flag1 = true;
				}
			} while (flag2 && t < grammar[i].GetLength());
			if (t == grammar[i].GetLength()) {
				firstOfVN[grammar[i].GetAt(0)].insert('@');
			}
		}
	} while (flag1);
}

//求项目集IT的closure（）
void ParserAnalyzeDlg::get_eclosure(int T)
{
	for (auto each : projectSet[T]) {
		Item temp;
		if (grammar[each.grammar_numb].GetAt(each.part) >= 'A' && grammar[each.grammar_numb].GetAt(each.part) <= 'Z') {
			for (int i = 0; i < grammar.size();i++ ) {
				if (grammar[i].GetAt(0) == grammar[each.grammar_numb].GetAt(each.part)) {
					for (auto eachchar : get_expchar(each)) {
						temp.key = itemnum;
						temp.grammar_numb = i;
						temp.part = 3;
						temp.expchar = eachchar;
						if (!isInSet(T, temp)) {
							projectSet[T].insert(temp);
							itemnum++;
						}
					}
				}
			}
		}
	}
}

//获得·后面的first集
set<char> ParserAnalyzeDlg::get_expchar(Item item)
{
	int temp = item.part;
	bool flag;//控制非终结符推出空的情况
	set<char> expchar;
	do {
		flag = false;
		if (temp+1 >= grammar[item.grammar_numb].GetLength()) {
			expchar.insert(item.expchar);
			return expchar;
		}
		else if(grammar[item.grammar_numb].GetAt(temp+1) < 'A' || grammar[item.grammar_numb].GetAt(temp + 1) > 'Z') {
			expchar.insert(grammar[item.grammar_numb].GetAt(temp + 1));
		}
		else if (grammar[item.grammar_numb].GetAt(temp + 1) >= 'A' && grammar[item.grammar_numb].GetAt(temp + 1) <= 'Z') {
			for (auto each : firstOfVN[grammar[item.grammar_numb].GetAt(temp + 1)]) {
				//expchar.insert(each);
				/*if (firstOfVN[grammar[item.grammar_numb].GetAt(temp + 1)].count('@')) {
					temp++;
					flag == true;
				}*/
				//2018.3.13,向前搜索符不为@
				if (each != '@') {
					expchar.insert(each);
				}
				else {
					temp++;
					flag = true;
				}
				//
			}
		}
	} while (flag);
	return expchar;
}
//判断一个项目是否在项目集T中
bool ParserAnalyzeDlg::isInSet(int T, Item item)
{
	for (auto eachItem:projectSet[T]) {
		if (eachItem.grammar_numb == item.grammar_numb && eachItem.part == item.part && eachItem.expchar == item.expchar) {
			return true;
		}
	}
	return false;
}

void ParserAnalyzeDlg::createProjSet()
{
	Item init;
	init.key = itemnum;
	itemnum++;
	init.grammar_numb = 0;
	init.part = 3;
	init.expchar = '#';
	projectSet[0].insert(init);
	get_eclosure(0);
	//
	for (int num = 0; num <= setCount;num++) {
		//go所有非终结符
		for (auto eachVN : VN) {
			Item temp;
			set<Item> buf;
			for (auto eachItem : projectSet[num]) {
				//对项目集的每一项，·不在最后，且为非终结符
				if ((eachItem.part < grammar[eachItem.grammar_numb].GetLength()) && 
					(grammar[eachItem.grammar_numb].GetAt(eachItem.part) == eachVN)) {
					temp.key = itemnum;
					itemnum++;
					temp.grammar_numb = eachItem.grammar_numb;
					temp.expchar = eachItem.expchar;
					temp.part = eachItem.part + 1;
					buf.insert(temp);
				}
			}
			if (buf.size() != 0) {
				setCount++;
				projectSet[setCount] = buf;
				get_eclosure(setCount);

				int next = is_existed();//next！=0 则求得的项目集已经存在
				if (next != 0) {
					//projectSet[setCount].empty();//清空
					projectSet.erase(setCount);
					setCount--;

					transItem item =transItem();//加到转换表中
					item.begin = num;
					item.end = next;
					item.path = eachVN;
					transTable.push_back(item);
				}
				else {
					transItem item = transItem();//加到转换表中
					item.begin = num;
					item.end = setCount;
					item.path = eachVN;
					transTable.push_back(item);
				}
			}
		}
		//go所有终结符
		for (auto eachVT : VT) {
			//@只走一次
			if (eachVT == '@') {
				continue;
			}
			Item temp;
			set<Item> buf;
			for (auto eachItem : projectSet[num]) {
				//对项目集的每一项，·不在最后，且为终结符
				if ((eachItem.part < grammar[eachItem.grammar_numb].GetLength()) &&
					(grammar[eachItem.grammar_numb].GetAt(eachItem.part) == eachVT)) {
					temp.key = itemnum;
					itemnum++;
					temp.grammar_numb = eachItem.grammar_numb;
					temp.expchar = eachItem.expchar;
					temp.part = eachItem.part + 1;
					buf.insert(temp);
				}
			}
			if (buf.size() != 0) {
				setCount++;
				projectSet[setCount] = buf;
				get_eclosure(setCount);

				int next = is_existed();//next！=0 则求得的项目集已经存在
				if (next != 0) {
					//清空,bool erase(key_type key) 
					projectSet.erase(setCount);
					setCount--;

					transItem item = transItem();//加到转换表中
					item.begin = num;
					item.end = next;
					item.path = eachVT;
					transTable.push_back(item);
				}
				else {
					transItem item = transItem();//加到转换表中
					item.begin = num;
					item.end = setCount;
					item.path = eachVT;
					transTable.push_back(item);
				}
			}
		}
	}
}
//判断项目集是否已存在
int ParserAnalyzeDlg::is_existed()
{
	for (int i = 0; i < setCount;i++) {
		int s = 0;
		if (projectSet[i].size() == projectSet[setCount].size()) {
			for (auto eachItem : projectSet[setCount]) {
				for (auto eachItemI : projectSet[i]) {
					if ((eachItem.grammar_numb == eachItemI.grammar_numb) &&
						(eachItem.part == eachItemI.part) &&
						(eachItem.expchar == eachItemI.expchar) ) {
						s++;
						break;
					}
				}
			}
		}
		if (s == projectSet[setCount].size()) {
			return i;
		}
	}
	return 0;
}

//求LR1分析表
void ParserAnalyzeDlg::get_LR1Table()
{
	LR1Table.resize(setCount+1);
	//根据transTable，获得要移进的项
	for (int i = 0; i < transTable.size();i++) {
		if (transTable[i].path == '@') {
			continue;
		}
		int setNum = transTable[i].begin;
		int next = transTable[i].end;
		char ch = transTable[i].path;
		LR1Table[setNum].insert(pair<char,int>(ch,next));
	}
	//遍历每个项目集，寻找能规约的项
	for (int i = 0; i <= setCount;i++) {
		for (auto eachItem : projectSet[i]) {
			//2018.3.13，TODO:判断移进规约冲突，在insert之前判断向前搜索符是否在移进项中
			/*if (grammar[eachItem.grammar_numb].Find('@') >= 0) {
				int setNum = i;
				int next = eachItem.grammar_numb*(-1);
				char ch = eachItem.expchar;
				LR1Table[setNum].insert(pair<char, int>(ch, next));

			}*/
			if (eachItem.part == grammar[eachItem.grammar_numb].GetLength() ||
				grammar[eachItem.grammar_numb].Find('@') >= 0) {
				int setNum = i;
				int next = eachItem.grammar_numb*(-1);
				char ch = eachItem.expchar;
				is_Conflict(setNum, ch);//判断是否冲突
				LR1Table[setNum].insert(pair<char, int>(ch, next));
				
			}
		}
	}
}

//LR1分析
bool ParserAnalyzeDlg::LR1Analyze(CString string)
{
	stack<pair<int,char>> s;
	int init_state = 0;
	char init_char = '#';
	strIndex = 0;
	s.push(pair<int, char>(init_state, init_char));
	
	do {
		state = s.top().first;
		is_error = true;
		for (auto each : LR1Table[state]) {//对当前项目集的所有移进规约项
			if (each.first == string.GetAt(strIndex)) {
				is_error = false;
				if (each.second == 0) {
					is_done = true;
					break;
				}
				else if(each.second > 0){//移进，入栈
					s.push(pair<int,char>(each.second,each.first));
					strIndex++;
					break;
				}
				else {//规约,出栈
					int grammarNum = each.second*(-1);
					if (grammar[grammarNum].GetAt(3) == '@') {
						//遇到空规约时，栈不pop
						string.Insert(strIndex, grammar[grammarNum].GetAt(0));
					}
					else {
						for (int i = 0; i < grammar[grammarNum].GetLength() - 3; i++) {
							s.pop();
						}
						strIndex--;
						string.SetAt(strIndex, grammar[grammarNum].GetAt(0));
					}
					break;
				}
			}
		}
	} while ( !is_done && !is_error);
	return is_done | is_error;
}

CString ParserAnalyzeDlg::tokenListToString()
{
	CString str;
	for (int i = 0; i < tokenList.size();i++) {
		if (tokenList[i]->type == reserve) {
			if (tokenList[i]->val == _T("int")|| tokenList[i]->val == _T("float") || tokenList[i]->val == _T("double") || tokenList[i]->val == _T("bool")) {
				str += _T("1");
			}
			else if (tokenList[i]->val == _T("void")) {
				str += _T("2");
			}
			else if (tokenList[i]->val == _T("while")) {
				str += _T("6");
			}
			else if (tokenList[i]->val == _T("if")) {
				str += _T("7");
			}
			else if (tokenList[i]->val == _T("else")) {
				str += _T("8");
			}
			else {
				str += _T("@");
			}
		}
		else if (tokenList[i]->type == ID) {
			str += _T("3");
		}
		else if (tokenList[i]->type == constnum) {
			str += _T("4");
		}
		else{
			if (tokenList[i]->val.GetLength() == 1) {
				str += tokenList[i]->val;
			}
			else {
				str += _T("@");
			}
		}
	}
	return str+_T("#");
}

void ParserAnalyzeDlg::is_Conflict(int setNum, char ch)
{
	if (LR1Table[setNum].count(ch) != 0) {
		is_conflict = true;
	}
}


