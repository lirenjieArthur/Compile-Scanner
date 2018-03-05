#pragma once

struct Token {
	CString val;
	CString type;
	int linenum;
};
vector<Token*> tokenList;//存储词法分析得到的token串

set<CString> reserveWords = { _T("auto"),_T("break"),_T("case"),_T("char"),_T("const"),_T("continue"),_T("default") ,_T("do") 
_T("double") ,_T("else") ,_T("enum") ,_T("extern") ,_T("float"),_T("for"),_T("goto"),_T("if"),
_T("int"),_T("long"),_T("register"),_T("return"),_T("short"),_T("signed"),_T("sizeof"),_T("static"),
_T("struct") ,_T("switch") ,_T("typedef") ,_T("union") ,_T("unsinged") ,_T("void") ,_T("volatile") ,_T("while") };
set<CString> jiefu = { _T("{"),_T("}"),_T("("),_T(")"),_T("["),_T("]"),_T("'"),_T("\""),_T(";"),_T(",") };
set<CString> yunsuanfu = { _T("+"),_T("-"),_T("*"),_T("/"),_T("<"),_T(">"),_T("+="),_T("-="),_T("*="),_T("/="),_T("<="),_T(">=") };

