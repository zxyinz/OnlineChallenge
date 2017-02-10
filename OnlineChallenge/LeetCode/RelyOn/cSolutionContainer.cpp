#include"cSolutionContainer.h"
using namespace std;
cSolutionContainer::cSolutionContainer()
{

}
cSolutionContainer::~cSolutionContainer()
{

}
void cSolutionContainer::_PrintMaxMatchList(const string &strName) const
{
	list<string> MatchList;
	for (auto &pPtr : this->m_ObjList)
	{
		if (pPtr->iGetName().find(strName) == 0)
		{
			MatchList.push_back(pPtr->iGetName());
		}
	}

	for (const auto &str : MatchList)
	{
		::cout << str << "\t";
	}
	::cout << "\r\n";
}
bool cSolutionContainer::iCreateSolution(cSolutionObj* pObj)
{
	//Find solution by name
	if (pObj == nullptr) { return false; }

	const string &strName = pObj->iGetName();
	for (const auto &pPtr : this->m_ObjList) { if (strName == pPtr->iGetName()) { return false; } }

	this->m_ObjList.push_back(pObj);
}
void cSolutionContainer::iDeleteSolution(const string &strName)
{
	for (list<cSolutionObj*>::iterator It = this->m_ObjList.begin(); It != this->m_ObjList.end(); It++)
	{
		if (strName == (*It)->iGetName())
		{
			delete (*It);
			(*It) = nullptr;

			this->m_ObjList.erase(It);
			return;
		}
	}

	//Solution not found, print max-match
	this->_PrintMaxMatchList(strName);
}
void cSolutionContainer::iRun(const string &strName)
{
	//Find solution by name
	for (auto &pPtr : this->m_ObjList)
	{
		if (strName == pPtr->iGetName())
		{
			pPtr->operator()();
			return;
		}
	}

	//Solution not found, print max-match
	this->_PrintMaxMatchList(strName);
}
void cSolutionContainer::iPrintDesc(const string &strName, const string &strPrefix) const
{
	//Find solution by name
	for (const auto &pPtr : this->m_ObjList)
	{
		if (strName == pPtr->iGetName())
		{
			::cout << strPrefix << pPtr->iGetDesc() << "\r\n";
			return;
		}
	}

	//Solution not found, print max-match
	this->_PrintMaxMatchList(strName);
}
void cSolutionContainer::iPrintList(const string &strPrefix) const
{
	for (auto &pPtr : this->m_ObjList)
	{
		::cout << strPrefix << pPtr->iGetName() << "\r\n";
	}
}