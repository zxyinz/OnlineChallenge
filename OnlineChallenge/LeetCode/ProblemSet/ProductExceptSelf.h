#include"..\RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
//Problem description:
//
// Given an array of n integers where n > 1, nums
// return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
// Solve it without division and in O(n).
// For example, given[1, 2, 3, 4], return[24, 12, 8, 6].
// Follow up :
// Could you solve it with constant space complexity ?
// (Note : The output array does not count as extra space for the purpose of space complexity analysis.)
//

class cProductExceptSelf : public cSolutionObj
{
private:
public:
	cProductExceptSelf()
		:cSolutionObj("ProductExceptSelf","")
	{
	};
	~cProductExceptSelf(){};

	vector<int> productExceptSelf(vector<int>& nums)	// Time: O(n), Space: O(n)
	{
		vector<int> ProductRes(nums.size());

		int Product = 1;

		for (int seek = 0; seek < nums.size(); seek = seek + 1)
		{
			ProductRes[seek] = Product;
			Product = Product * nums[seek];
		}

		Product = 1;
		int CurrentVal = 1;

		for (int seek = nums.size() - 1; seek >= 0; seek = seek - 1)
		{
			CurrentVal = nums[seek];

			nums[seek] = ProductRes[seek] * Product;
			Product = Product * CurrentVal;
		}

		return nums;
	};

	void operator()() override final
	{
		vector<int> nums = {};
		vector<int> res = this->productExceptSelf(nums);

		for (auto val : res) { ::cout << val << " "; }
		::cout << "\r\n";
	};

	void operator()(const string &strUserInput) override final
	{

	};
};