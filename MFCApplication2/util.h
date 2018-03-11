#pragma once

struct Token {
	CString val;
	CString type;
	int linenum;
};
static vector<Token*> tokenList;//�洢�ʷ������õ���token��
#define reserve _T("������")
#define ID _T("��ʶ��")
#define constnum _T("����")
#define delimiter _T("���")
#define operators _T("�����")
#define error _T("ERROR")
//������
static set<CString> ReserveWords = { _T("auto"),_T("break"),_T("case"),_T("char"),_T("const"),_T("continue"),_T("default") ,_T("do"),
_T("double") ,_T("else") ,_T("enum") ,_T("extern") ,_T("float"),_T("for"),_T("goto"),_T("if"),
_T("int"),_T("long"),_T("register"),_T("return"),_T("short"),_T("signed"),_T("sizeof"),_T("static"),
_T("struct") ,_T("switch") ,_T("typedef") ,_T("union") ,_T("unsinged") ,_T("void") ,_T("volatile") ,_T("while") };
//���
static set<CString> Delimiter = { _T("{"),_T("}"),_T("("),_T(")"),_T("["),_T("]"),_T("'"),_T("\""),_T(";"),_T(",") };
//�����
static set<CString> OperationSymbol = { _T("="),_T("+"),_T("-"),_T("*"),_T("/"),_T("<"),_T(">"),_T("+="),_T("-="),_T("*="),_T("/="),_T("<="),_T(">="),_T("!="),
_T("&") , _T("&&") , _T("|") , _T("||"), _T("~"), _T("^") };

