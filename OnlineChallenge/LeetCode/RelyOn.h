#include"RelyOn/StdHeader.h"
#include"RelyOn/cTerminal.h"
#include"RelyOn/cSolutionContainer.h"
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
}
#endif
