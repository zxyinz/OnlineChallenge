#include"..\RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
class cMaxDepthOfBinaryTree : public cSolutionObj
{
public:
	cMaxDepthOfBinaryTree()
		:cSolutionObj("MaxDepthOfBinaryTree","")
	{
	};
	~cMaxDepthOfBinaryTree(){};

	int maxDepth(TreeNode* root)
	{
		if (root == nullptr) { return 0; }
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}

	void operator()() override final
	{

	};

	void operator()(const string &strUserInput) override final
	{

	};
};