#include"../RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
//Problem description:
//Compare two version numbers version1 and version2.
//If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
//
//You may assume that the version strings are non - empty and contain only digits and the.character.
//The.character does not represent a decimal point and is used to separate number sequences.
//For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second - level revision of the second first - level revision.
//
//Here is an example of version numbers ordering :
//
//0.1 < 1.1 < 1.2 < 13.37
class cCompareVersionNumbers : public cSolutionObj
{
public:
	cCompareVersionNumbers()
		:cSolutionObj("CompareVersionNumbers", "")
	{
	};
	~cCompareVersionNumbers(){};

	int iGetMaxVersion(string &strVersion)
	{
		if (strVersion.back() == '_') { return -1; }

		int Version = 0;

		for (auto &N : strVersion)
		{
			if (N == '_') { continue; }
			if (N == ' ') { N = '_'; continue; }
			if (N == '.') { N = '_'; break; }
			Version = Version * 10 + (N - '0');
			N = '_';
		}

		return Version;
	};

	void iPreprocess(string &strVersion)
	{
		const int Size = strVersion.size();
		int Val = 0;
		for (int seek = Size - 1; seek >= 0; seek = seek - 1)
		{
			if (strVersion[seek] == ' ') { continue; }
			if (strVersion[seek] == '.')
			{
				if (Val == 0)
				{
					for (int Index = seek; Index < Size; Index = Index + 1)
					{
						strVersion[Index] = ' ';
					}
					continue;
				}
				else
				{
					break;
				}
			}
			Val = Val + (strVersion[seek] - '0');
		}
	};

	int compareVersion(string version1, string version2)
	{
		iPreprocess(version1);
		iPreprocess(version2);

		while (true)
		{
			int v1 = iGetMaxVersion(version1);
			int v2 = iGetMaxVersion(version2);

			if (v1 > v2){ return 1; }
			if (v1 < v2){ return -1; }
			if ((v1 == -1) && (v2 == -1)) { break; }
		}

		return 0;
	};

	void operator()() override final
	{
		//1.0 1.0.0
		//1.0 1.0.15
	};

	void operator()(const string &strUserInput) override final
	{

	};
};