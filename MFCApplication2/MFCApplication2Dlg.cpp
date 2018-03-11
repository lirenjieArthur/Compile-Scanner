
// MFCApplication2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "util.h"
#include "ParserAnalyzeDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, resultlist);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_selectLEX, &CMFCApplication2Dlg::OnBnClickedSelectLEX)
	ON_EN_CHANGE(IDC_lexFileName, &CMFCApplication2Dlg::OnEnChangeLexFileName)
	ON_BN_CLICKED(IDC_SelectFile, &CMFCApplication2Dlg::OnBnClickedSelectfile)
	ON_EN_CHANGE(IDC_FileName, &CMFCApplication2Dlg::OnEnChangeFilename)
	ON_BN_CLICKED(IDC_wordAnalyze, &CMFCApplication2Dlg::OnBnClickedwordanalyze)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CMFCApplication2Dlg::OnLvnItemchangedList2)
	ON_EN_CHANGE(IDC_SouceCode, &CMFCApplication2Dlg::OnEnChangeSoucecode)
	ON_BN_CLICKED(IDC_ParserAnalyze, &CMFCApplication2Dlg::OnBnClickedParserAnalyze)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	resultlist.SetExtendedStyle(resultlist.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);// 为列表视图控件添加全行选中和栅格风格
	resultlist.InsertColumn(0, _T("行号"), LVCFMT_CENTER, 100);
	resultlist.InsertColumn(1, _T("类型"), LVCFMT_CENTER, 150);
	resultlist.InsertColumn(2, _T("名称"), LVCFMT_CENTER, 150);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//选择文法
void CMFCApplication2Dlg::OnBnClickedSelectLEX()
{
	// TODO: 在此添加控件通知处理程序代码
	// 设置过滤器     
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	// 显示打开文件对话框     
	if (IDOK == fileDlg.DoModal()) {
		lexFilePath = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名;
		GetDlgItem(IDC_lexFileName)->SetWindowTextW(lexFilePath);
	}
}

void CMFCApplication2Dlg::OnEnChangeLexFileName()
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

		G = new Traid[linenum];
		lexFile.Seek(0,CFile::begin);
		int num = 0;
		//将文法转换为NFA,NFA用三元组形式表示 
		while (lexFile.ReadString(temp) && num < linenum) {
			int pos = temp.Find(_T("->"));
			G[num].start = temp.GetAt(0);

			//temp.GetAt(pos+2)<='z' && temp.GetAt(pos + 2) >= 'a'	temp.GetAt(pos+2)>'Z' || temp.GetAt(pos + 2) < 'A'
			if (temp.GetAt(pos + 2)>'Z' || temp.GetAt(pos + 2) < 'A') {
				if (temp.GetAt(pos + 3) <= 'Z' && temp.GetAt(pos + 3) >= 'A') {
					G[num].edge = temp.GetAt(pos + 2);
					G[num].end = temp.GetAt(pos + 3);
				}
				else {
					if (temp.GetAt(pos + 2)=='@') {
						G[num].edge = '*';
					}
					else {
						G[num].edge = temp.GetAt(pos + 2);
					}
					G[num].end = '#';
				}
			}
			else {
				G[num].edge = '*';
				G[num].end = temp.GetAt(pos + 2);
			}
			num++;
		}
		// 关闭文件句柄  
		lexFile.Close();
		// 释放缓冲区域  
		strFile.ReleaseBuffer();
		//SetDlgItemText(IDC_SouceCode,CString(strFile));
		set<char> Edge;//边集
		for (int j = 0; j<linenum; j++)
		{
			Edge.insert(G[j].edge);
		}
		int n = Edge.size(); //n为边的数目
		char*input = new char[n];
		set<char>::iterator it;
		int j = 0;
		for (it = Edge.begin(); it != Edge.end(); it++)
		{
			input[j] = *it;
			j++;
		}
		determined(G, linenum, input, n);//NFA转DFA


		//拼接NFA成便于输出的字符串
		/*
		for (int j = 0; j<linenum; j++)
		{
			CString str;
			str.AppendChar(G[j].start);
			str.AppendChar(' ');
			str.AppendChar(G[j].edge);
			str.AppendChar(' ');
			str.AppendChar(G[j].end);
			strFile += str+_T("\r\n");
		}*/
		
		for (auto val : DFA)
		{
			CString str;
			str = int2CString(val.start)+_T(" ");
			str.AppendChar(val.edge);
			str += _T(" ");
			str += int2CString(val.end);
			strFile += str + _T("\r\n");
		}
		strFile += _T("终态为：");//遍历状态map
		for (auto it = state.begin(); it != state.end(); ++it) {
			if (it->second == 1) {
				strFile+= int2CString(it->first);
				strFile += _T(" ");
			}
			else {
				continue;
			}
		}


		GetDlgItem(IDC_SouceCode)->SetWindowTextW(strFile);
		GetDlgItem(IDC_SouceCode)->ShowScrollBar(SB_VERT, TRUE);
		GetDlgItem(IDC_SouceCode)->ShowScrollBar(SB_HORZ, TRUE);
	}
	catch (CFileException *e) {
		CString str;
		str.Format(_T("读取数据失败的原因是:%d"), e->m_cause);
		MessageBox(str);
		lexFile.Abort();
		e->Delete();
	}
}


void CMFCApplication2Dlg::OnBnClickedSelectfile()
{
	// TODO: 在此添加控件通知处理程序代码

	// 设置过滤器     
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	// 显示打开文件对话框     
	if (IDOK == fileDlg.DoModal()) {
		FilePath = fileDlg.GetPathName();//得到完整的文件名和目录名拓展名;
		GetDlgItem(IDC_FileName)->SetWindowTextW(FilePath);
	}
}

//文件名Edit Control
void CMFCApplication2Dlg::OnEnChangeFilename()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	try {
		if (!file.Open(FilePath, CFile::modeRead)) {
			MessageBox(_T("error"));
			return;
		}
		CString strFile;
		CString temp;
		int linenum=1;
		// 按行读取打开文件内容  
		while (file.ReadString(temp)) {
			fileLines.push_back(temp);
			CString strlinenum;
			strlinenum.Format(_T("%d"), linenum);
			CString line = strlinenum + " " +temp + "\r\n";
			strFile += line;
			linenum++;
		}
		// 关闭文件句柄  
		file.Close();

		// 释放缓冲区域  
		strFile.ReleaseBuffer();
		//SetDlgItemText(IDC_SouceCode,CString(strFile));
		GetDlgItem(IDC_SouceCode)->SetWindowTextW(strFile);
		GetDlgItem(IDC_SouceCode)->ShowScrollBar(SB_VERT,TRUE);
		GetDlgItem(IDC_SouceCode)->ShowScrollBar(SB_HORZ, TRUE);
	}
	catch (CFileException *e) {
		CString str;
		str.Format(_T("读取数据失败的原因是:%d"), e->m_cause);
		MessageBox(str);
		file.Abort();
		e->Delete();
	}
}

//点击 词法分析
void CMFCApplication2Dlg::OnBnClickedwordanalyze()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!tokenList.empty()) {
		return;
	}
	scanner();
	int size = tokenList.size();
	reverse(tokenList.begin(),tokenList.end());
	//CString TOKEN;
	//GetDlgItem(IDC_SouceCode)->SetWindowTextW(int2CString(size));
	/*for (auto val : tokenList) {
		if (val->val != "") {
			TOKEN += int2CString(val->linenum);
			TOKEN += val->val;
			TOKEN += val->type;
			TOKEN += _T("\r\n");
		}
	}
	GetDlgItem(IDC_SouceCode)->SetWindowTextW(TOKEN);*/
	for (auto val : tokenList) {
		if (val->val != "") {
			resultlist.InsertItem(0, int2CString(val->linenum));
			resultlist.SetItemText(0, 1, val->type);
			resultlist.SetItemText(0, 2, val->val);
		}
	}
	reverse(tokenList.begin(), tokenList.end());
}


void CMFCApplication2Dlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//源代码EditControl
void CMFCApplication2Dlg::OnEnChangeSoucecode()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

CString CMFCApplication2Dlg::int2CString(int i)
{
	CString str;
	str.Format(_T("%d"), i);
	return str;
}

set<char> CMFCApplication2Dlg::e_closure(set<char> T, Traid G[], int N)
{
	set<char> U = T;
	stack<char> S;//状态栈 
	set<char>::iterator it;
	for (it = U.begin(); it != U.end(); it++){
		S.push(*it);
	}
	char t;
	while (!S.empty()){
		t = S.top();
		S.pop();
		for (int i = 0; i<N; i++){
			if (G[i].start == t&&G[i].edge == '*'){
				U.insert(G[i].end);
				S.push(G[i].end);
			}
		}
	}
	return U;
}
set<char> CMFCApplication2Dlg::move(set<char> I, char a, Traid G[], int N)
{
	set<char> U;
	set<char>::iterator it;
	for (it = I.begin(); it != I.end(); it++){
		for (int i = 0; i<N; i++){
			if (G[i].start == *it&&G[i].edge == a) {
				U.insert(G[i].end);
			}
		}
	}
	return U;
}

void CMFCApplication2Dlg::determined(Traid G[], int N, char* input, int n)
{
	bool marked[MAX_NODES];
	for (int i = 0; i<MAX_NODES; i++)
		marked[i] = false;
	set<char> C[MAX_NODES];
	// 初始化，e_closure(S0)是C中的唯一成员 ，没有被标记 
	char s0 = G[0].start;
	set<char> T0, T1;
	T0.insert(s0);
	T1 = e_closure(T0, G, N);
	C[0] = T1;
	int i = 0;
	while (!C[i].empty() && marked[i] == false && i<MAX_NODES)//C中存在尚未被标记的子集T 
	{
		marked[i] = true;//标记T 
		/*
		set<char>::iterator it;
		cout<<i<<":"
		for(it=C[i].begin();it!=C[i].end();it++)
		cout<<*it<<",";
		cout<<endl;
		 */
		for (int j = 0; j<n; j++){
			if (input[j] != '*'){
				set<char> U = e_closure(move(C[i], input[j], G, N), G, N);
				if (!U.empty()){
					bool inC = false;
					int k = 0;
					//判断U是否在C中
					while (!C[k].empty() && k<MAX_NODES) { 
						if (U == C[k]){
							inC = true;
							break;
						}
						k++;
					}
					//U不在C中，将U作为未标记的子集加在C中
					if (!inC){
						k = 0;
						while (!C[k].empty() && k<MAX_NODES)
						{
							k++;
						}
						C[k] = U;
					}
					Traid2 each;
					each.start = i;
					each.edge = input[j];
					each.end = k;
					DFA.push_back(each);
					state[i] = 0;
					state[k] = 0;
					//cout << i << "->" << input[j] << " " << k << endl;//i起点 k终点 input[j]边
				}
			}
		}
		i++;
	}

	int m = 0;
	while (!C[m].empty()){
		bool is_final_state = false;
		set<char>::iterator it;
		for (it = C[m].begin(); it != C[m].end(); it++){
			if (*it == '#'){
				is_final_state = true;
				break;
			}
		}
		if (is_final_state) 
			state[m] = 1;
		m++;
	}
}

int CMFCApplication2Dlg::getNextState(int start, char edge)
{
	for (auto val : DFA) {
		if (val.start == start && val.edge == edge) {
			return val.end;
		}
	}
	return -1;
}

void CMFCApplication2Dlg::scanner()
{
	int linenum = 0;
	for (auto val : fileLines) {
		linenum++;
		val.Replace(_T("	"),_T(""));
		val.Replace(_T("\r\n"), _T(""));
		int length = val.GetLength();//该行的长度
		int currentpos = 0;//该行中当前位置
		int currentState = 0;//当前状态
		CString currentToken;//当前的token值
		Token *token;
		while (currentpos<=length) {
			char currentchar = val.GetAt(currentpos);
			if (currentchar==' ') {
				currentpos++;

				addToTokenList(linenum,&currentToken,&currentState);

				/*currentToken.Empty();
				currentState = 0;*/
			}
			else {
				int nextState = getNextState(currentState,currentchar);
				currentToken.AppendChar(currentchar);
				currentpos++;
				if (nextState == -1) {
					//currentpos -= 1;
					/*currentpos--;
					currentToken.Left(currentToken.GetLength()-1);*/
					if (currentState==0) {
						currentToken = currentToken + _T(",error");

						addToTokenList(linenum, &currentToken, &currentState);

						/*currentToken.Empty();
						currentState = 0;*/
						continue;
					}
					

					currentToken=currentToken.Left(currentToken.GetLength() - 1);
					currentpos -= 1;

					addToTokenList(linenum, &currentToken, &currentState);

					/*currentToken.Empty();
					currentState = 0;*/
				}
				else {
					//处理字符串常量
					if (currentToken == "\"") {
						while (currentpos <= length ) {
							currentchar = val.GetAt(currentpos);
							currentToken.AppendChar(currentchar);
							currentpos++;
							if (currentchar == '\"') {
								break;
							}
						}
						addToTokenList(linenum, &currentToken, &currentState);

						/*currentToken.Empty();
						currentState = 0;*/
						continue;
					}
					currentState = nextState;
					/*if (state[nextState]==1) {
						token = new Token();
						token->linenum = linenum;
						token->val = currentToken;
						tokenList.push_back(token);
						currentToken.Empty();
						currentState = 0;
					}
					else {
						currentState = nextState;

					}*/
				}
			}
		}
	}

	//判断token类型
	for (auto eachtoken : tokenList) {
		CString token = eachtoken->val;
		if (token.Find(_T("error")) == -1) {
			if (ReserveWords.count(token) == 0) {
				//不是保留字
				if (Delimiter.count(token) == 0) {
					//不是界符
					if (OperationSymbol.count(token) == 0) {
						//不是运算符
						if ((token.GetAt(0)<='9' && token.GetAt(0)>='0') || token.GetAt(0) == '.') {
							//以数字或小数点开头，则为常量。若有e，则e后必须有+/-和数字。
							if (token.Find(_T("e")) != -1) {
								if (token.GetAt(token.GetLength()-1) >= '0' && token.GetAt(token.GetLength()-1) <= '9')
									eachtoken->type = constnum;
								else
									eachtoken->type = error;
							}
							else {
								eachtoken->type = constnum;
							}
						}
						else {
							//不以数字,小数点开头，则为标识符或字符常量
							if (token.GetAt(0)=='\"') {
								if(token.GetAt(token.GetLength()-1) == '\"')
									eachtoken->type = constnum;
								else
									eachtoken->type = error;
							}
							else {
								eachtoken->type = ID;
							}
						}
					}
					else {
						//是运算符
						eachtoken->type = operators;
					}
				}
				else {
					//是界符
					eachtoken->type = delimiter;
				}
			}
			else {
				//是保留字
				eachtoken->type = reserve;
			}
		}
		else {
			eachtoken->val = eachtoken->val.Left(token.Find(_T("error"))-1);
			eachtoken->type = error;
		}
	}
}

void CMFCApplication2Dlg::addToTokenList(int linenum, CString *currentToken,int *currentstate)
{
	Token *token = new Token();
	token->linenum = linenum;
	token->val = *currentToken;
	tokenList.push_back(token);
	(*currentToken).Empty();
	(*currentstate) = 0;
	int a = 1e1;
}


void CMFCApplication2Dlg::OnBnClickedParserAnalyze()
{
	// TODO: 在此添加控件通知处理程序代码
	ParserAnalyzeDlg newDlg;
	newDlg.DoModal();
}


/*int main() {
int a = 0;
int b, b1;
int c = a + b;
double d = 1e-3;
++ + ;
float f = "qw qwdf";
in f;
if (a >= 0 && d != 0) {
a += a & 1;
}
###
}
int main() {
float f = "qw qwdf";
}*/


