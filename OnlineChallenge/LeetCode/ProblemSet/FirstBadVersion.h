#include"../RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
//Problem description:
//You are a product manager and currently leading a team to develop a new product.
//Unfortunately, the latest version of your product fails the quality check.
//Since each version is developed based on the previous version, all the versions after a bad version are also bad.
//Suppose you have n versions[1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
//
//You are given an API bool isBadVersion(version) which will return whether version is bad.
//Implement a function to find the first bad version.You should minimize the number of calls to the API.

// Forward declaration of isBadVersion API.
vector<bool> VersionArray;
bool isBadVersion(int version){ return VersionArray[version]; };

class cFirstBadVersion : public cSolutionObj
{
public:
	cFirstBadVersion()
		:cSolutionObj("FirstBadVersion", "")
	{
	};
	~cFirstBadVersion(){};

	int iBinarySearch(int Start, int End)
	{
		if (Start == End) { return isBadVersion(Start) ? Start : Start + 1; }

		int Mid = Start + (End - Start) / 2;
		return isBadVersion(Mid) ? iBinarySearch(Start, Mid) : iBinarySearch(Mid + 1, End);
	};
	int firstBadVersion(int n)
	{
		return iBinarySearch(1, n);
	};

	void operator()() override final
	{
	};

	void operator()(const string &strUserInput) override final
	{

	};
};