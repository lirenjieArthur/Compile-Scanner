#pragma once

struct Token {
	CString val;
	CString type;
	int linenum;
};
static vector<Token*> tokenList;//存储词法分析得到的token串
#define reserve _T("保留字")
#define ID _T("标识符")
#define constnum _T("常量")
#define delimiter _T("界符")
#define operators _T("运算符")
#define error _T("ERROR")
//保留字
static set<CString> ReserveWords = { _T("auto"),_T("break"),_T("case"),_T("char"),_T("const"),_T("continue"),_T("default") ,_T("do"),
_T("double") ,_T("else") ,_T("enum") ,_T("extern") ,_T("float"),_T("for"),_T("goto"),_T("if"),
_T("int"),_T("long"),_T("register"),_T("return"),_T("short"),_T("signed"),_T("sizeof"),_T("static"),
_T("struct") ,_T("switch") ,_T("typedef") ,_T("union") ,_T("unsinged") ,_T("void") ,_T("volatile") ,_T("while") };
//界符
static set<CString> Delimiter = { _T("{"),_T("}"),_T("("),_T(")"),_T("["),_T("]"),_T("'"),_T("\""),_T(";"),_T(",") };
//运算符
static set<CString> OperationSymbol = { _T("="),_T("+"),_T("-"),_T("*"),_T("/"),_T("<"),_T(">"),_T("+="),_T("-="),_T("*="),_T("/="),_T("<="),_T(">="),_T("!="),
_T("&") , _T("&&") , _T("|") , _T("||"), _T("~"), _T("^") };

