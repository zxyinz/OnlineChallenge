#include"StdHeader.h"
using namespace std;
#pragma once
#ifndef __CTERMINAL_H__
#define __CTERMINAL_H__

/*Callback Func Defineation*/
typedef void (*CALLBACKFUNCPTR)(const vector<string> &ParameterSet);

class cTerminal
{
public:
	struct CMDINFO
	{
	public:
		string strDesc;
		CALLBACKFUNCPTR pFunc;
	public:
		CMDINFO(const string strDesc = "", CALLBACKFUNCPTR pFunc = nullptr) : strDesc(strDesc), pFunc(pFunc) {};
		~CMDINFO() {};
	};
private:
	unordered_map<string, CMDINFO> m_CmdTable;
	string m_strBanner;
	string m_strPrefix;
	bool m_bStatus;
public:
	cTerminal(const string &strPrefix = "Terminal>", const string &strBanner = "[-----Terminal-----]");
	~cTerminal();

	void iCreateCommand(const string &strCmd, CALLBACKFUNCPTR pFunc, const string &strDesc = "");
	void iUpdateCommand(const string &strCmd, CALLBACKFUNCPTR pFunc, const string &strDesc = "");
	void iDeleteCommand(const string &strCmd);

	void iSetPrefix(const string &strPrefix);
	void iSetBanner(const string &strBanner);

	bool iSetStatus(const bool bStatus);

	string iGetPrefix() const;
	string iGetBanner() const;

	bool iGetStatus() const;

	CMDINFO iGetCommand(const string &strCmd) const;
	string iGetCommandDesc(const string &strCmd) const;

	void iPrintBanner() const;
	void iPrintCmdList() const;

	void iProcess();
};
#endif
