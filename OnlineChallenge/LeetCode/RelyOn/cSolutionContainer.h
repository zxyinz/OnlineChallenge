#include"StdHeader.h"
using namespace std;
#pragma once
#ifndef __CSOLUTIONCONTAINER_H__
#define __CSOLUTIONCONTAINER_H__
class cSolutionObj
{
private:
	string m_strName;
	string m_strDesc;
public:
	cSolutionObj(const string &strName, const string &strDesc)
		:m_strName(strName), m_strDesc(strDesc)
	{
	};
	~cSolutionObj() {};

	virtual void operator()() = 0;
	virtual void operator()(const string &strUserInput) = 0;

	string iGetName() const { return this->m_strName; };
	string iGetDesc() const { return this->m_strDesc; };
};

class cSolutionContainer
{
private:
	list<cSolutionObj*> m_ObjList;
protected:
	void _PrintMaxMatchList(const string &strName) const;
public:
	cSolutionContainer();
	~cSolutionContainer();

	bool iCreateSolution(cSolutionObj* pObj);
	void iDeleteSolution(const string &strName);

	void iRun(const string &strName);

	void iPrintDesc(const string &strName, const string &strPrefix = "") const;
	void iPrintList(const string &strPrefix = "") const;
};
#endif
