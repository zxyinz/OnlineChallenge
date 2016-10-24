#include"iostream"
#include"cstdio"
#include"fstream"
#include"sstream"
#include"ostream"
#include"cmath"
#include"vector"
#include"list"
#include"queue"
#include"stack"
#include"map"
#include"unordered_map"
#include"set"
#include"unordered_set"
#include"algorithm"
#include"string"
#include"thread"
#include"mutex"
#pragma once
using namespace std;
#ifndef __LEETCODERELYON_H__
#define __LEETCODERELYON_H__
namespace Leetcode
{
	struct LinkList
	{
	public:
		int val;
		LinkList* next;
	public:
		LinkList(const int val = 0, LinkList* next = nullptr)
			:val(val), next(next)
		{
		};
		~LinkList(){};
	};

	struct TreeNode
	{
	public:
		int val;
		TreeNode* left;
		TreeNode* right;
	public:
		TreeNode(const int val, TreeNode* left = nullptr, TreeNode* right = nullptr)
			:val(val), left(left), right(right)
		{
		};
		~TreeNode(){};
	};

	struct Point
	{
	public:
		int x;
		int y;
	public:
		Point(const int x = 0, const int y = 0)
			:x(x), y(y)
		{
		};
		~Point(){};
	};

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
		~cSolutionObj(){};

		virtual void operator()() = 0;
		virtual void operator()(const string &strUserInput) = 0;

		string iGetName() const { return this->m_strName; };
		string iGetDesc() const { return this->m_strDesc; };
	};

	class cSolutionList
	{
	private:
		list<cSolutionObj*> m_ObjList;
	protected:
		void _PrintMaxMatchList(const string &strName) const;
	public:
		cSolutionList();
		~cSolutionList();

		bool iCreateSolution(cSolutionObj* pObj);
		void iDeleteSolution(const string &strName);

		void iRun(const string &strName);

		void iPrintDesc(const string &strName, const string &strPrefix = "") const;
		void iPrintList(const string &strPrefix = "") const;
	};
}
#endif
