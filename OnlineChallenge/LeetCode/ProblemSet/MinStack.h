#include"../RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
//Problem description:
//Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
//
//push(x) --Push element x onto stack.
//pop() --Removes the element on top of the stack.
//top() --Get the top element.
//getMin() --Retrieve the minimum element in the stack.
//Example:
//MinStack minStack = new MinStack();
//minStack.push(-2);
//minStack.push(0);
//minStack.push(-3);
//minStack.getMin();   --> Returns - 3.
//minStack.pop();
//minStack.top();      --> Returns 0.
//minStack.getMin();   --> Returns - 2.

struct MINSTACK_NODE
{
public:
	int     val;
	MINSTACK_NODE*   p_next;
	MINSTACK_NODE*   p_min_prev;
	MINSTACK_NODE*   p_min_next;
public:
	MINSTACK_NODE(const int val, MINSTACK_NODE* p_next = nullptr, MINSTACK_NODE* p_min_prev = nullptr, MINSTACK_NODE* p_min_next = nullptr)
		:val(val), p_next(p_next), p_min_prev(p_min_prev), p_min_next(p_min_next)
	{};
	~MINSTACK_NODE(){};
};

class cMinStack : public cSolutionObj
{
private:
	MINSTACK_NODE m_Root;
public:
	cMinStack()
		:cSolutionObj("MinStack", ""), m_Root(0)
	{
	};
	~cMinStack(){};

	void push(int x)
	{
		MINSTACK_NODE* pNode = new MINSTACK_NODE(x, this->m_Root.p_next);

		//Stack
		this->m_Root.p_next = pNode;

		//Min List
		MINSTACK_NODE* pCurrent = this->m_Root.p_min_next;

		//Empty
		if (pCurrent == nullptr)
		{
			this->m_Root.p_min_next = pNode;
			pNode->p_min_prev = &this->m_Root;

			return;
		}

		while (pCurrent->p_min_next != nullptr)
		{
			if (pCurrent->val >= pNode->val)
			{
				pNode->p_min_prev = pCurrent->p_min_prev;
				pCurrent->p_min_prev->p_min_next = pNode;

				pNode->p_min_next = pCurrent;
				pCurrent->p_min_prev = pNode;

				return;
			}

			pCurrent = pCurrent->p_min_next;
		}

		if (pCurrent->val >= pNode->val)
		{
			pNode->p_min_prev = pCurrent->p_min_prev;
			pCurrent->p_min_prev->p_min_next = pNode;

			pNode->p_min_next = pCurrent;
			pCurrent->p_min_prev = pNode;
		}
		else
		{
			pCurrent->p_min_next = pNode;
			pNode->p_min_prev = pCurrent;
		}
	}

	void pop()
	{
		MINSTACK_NODE* pNode = this->m_Root.p_next;

		if (pNode == nullptr) { return; }

		//Stack
		this->m_Root.p_next = pNode->p_next;

		//Min List
		pNode->p_min_prev->p_min_next = pNode->p_min_next;

		if (pNode->p_min_next != nullptr)
		{
			pNode->p_min_next->p_min_prev = pNode->p_min_prev;
		}

		delete pNode;
		pNode = nullptr;
	}

	int top()
	{
		return m_Root.p_next == nullptr ? 0 : m_Root.p_next->val;
	}

	int getMin()
	{
		return m_Root.p_min_next == nullptr ? 0 : m_Root.p_min_next->val;
	}

	void operator()() override final
	{
		//["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"]
		//[[], [-2], [0], [-3], [], [], [], []]
	};

	void operator()(const string &strUserInput) override final
	{

	};
};