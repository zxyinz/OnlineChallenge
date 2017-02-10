#include"cTerminal.h"
using namespace std;
cTerminal::cTerminal(const string &strPrefix, const string &strBanner)
	:m_strPrefix(strPrefix), m_strBanner(strBanner), m_bStatus(true)
{
}
cTerminal::~cTerminal()
{
	this->m_CmdTable.clear();
}
void cTerminal::iCreateCommand(const string &strCmd, CALLBACKFUNCPTR pFunc, const string &strDesc)
{
	if (this->m_CmdTable.find(strCmd) == this->m_CmdTable.end())
	{
		this->m_CmdTable[strCmd] = CMDINFO(strDesc, pFunc);
	}
}
void cTerminal::iUpdateCommand(const string &strCmd, CALLBACKFUNCPTR pFunc, const string &strDesc)
{
	if (this->m_CmdTable.find(strCmd) != this->m_CmdTable.end())
	{
		this->m_CmdTable[strCmd] = CMDINFO(strDesc, pFunc);
	}
}
void cTerminal::iDeleteCommand(const string &strCmd)
{
	const auto It = this->m_CmdTable.find(strCmd);
	if (It != this->m_CmdTable.end()) { this->m_CmdTable.erase(It); }
}
void cTerminal::iSetPrefix(const string &strPrefix)
{
	this->m_strPrefix = strPrefix;
}
void cTerminal::iSetBanner(const string &strBanner)
{
	this->m_strBanner = strBanner;
}
bool cTerminal::iSetStatus(const bool bStatus)
{
	this->m_bStatus = bStatus;
	return this->m_bStatus;
}
string cTerminal::iGetPrefix() const
{
	return this->m_strPrefix;
}
string cTerminal::iGetBanner() const
{
	return this->m_strBanner;
}
bool cTerminal::iGetStatus() const
{
	return this->m_bStatus;
}
cTerminal::CMDINFO cTerminal::iGetCommand(const string &strCmd) const
{
	const auto It = this->m_CmdTable.find(strCmd);
	if (It == this->m_CmdTable.end()) { return CMDINFO(); }

	return It->second;
}
string cTerminal::iGetCommandDesc(const string &strCmd) const
{
	return this->iGetCommand(strCmd).strDesc;
}
void cTerminal::iPrintBanner() const
{
	::cout<<this->m_strBanner.c_str();
}
void cTerminal::iPrintCmdList() const
{
	string strInfo;

	for (const auto &Item : this->m_CmdTable)
	{
		strInfo = strInfo + Item.first + "\r\n\t" + Item.second.strDesc + "\r\n";
	}

	::cout << strInfo.c_str();
}
void cTerminal::iProcess()
{

}