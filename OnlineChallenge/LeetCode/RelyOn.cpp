#include"RelyOn.h"
using namespace std;
using namespace Leetcode;
cSolutionList::cSolutionList()
{

}
cSolutionList::~cSolutionList()
{

}
void cSolutionList::_PrintMaxMatchList(const string &strName) const
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
bool cSolutionList::iCreateSolution(cSolutionObj* pObj)
{
	//Find solution by name
	if (pObj == nullptr){ return false; }

	const string &strName = pObj->iGetName();
	for (const auto &pPtr : this->m_ObjList){ if (strName == pPtr->iGetName()){ return false; } }

	this->m_ObjList.push_back(pObj);
}
void cSolutionList::iDeleteSolution(const string &strName)
{
	for (list<cSolutionObj*>::iterator It = this->m_ObjList.begin(); It != this->m_ObjList.end();It++)
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
void cSolutionList::iRun(const string &strName)
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
void cSolutionList::iPrintDesc(const string &strName, const string &strPrefix) const
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
void cSolutionList::iPrintList(const string &strPrefix) const
{
	for (auto &pPtr : this->m_ObjList)
	{
		::cout << strPrefix << pPtr->iGetName() << "\r\n";
	}
}