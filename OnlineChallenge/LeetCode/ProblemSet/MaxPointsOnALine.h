#include"..\RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
class cMaxPointsOnALine : public cSolutionObj
{
private:
public:
	cMaxPointsOnALine()
		:cSolutionObj("MaxPointsOnALine", "")
	{
	};
	~cMaxPointsOnALine(){};

	int maxPointsOnALine(vector<Point>& points)
	{
		unordered_map<float, int> DSet(0);

		for (int seek = 0; seek < points.size(); seek = seek + 1)
		{
			for (int seek_p = seek; seek_p < points.size(); seek_p = seek_p + 1)
			{
				if ((points[seek].x == points[seek_p].x) && (points[seek].y == points[seek_p].y))
				{
					continue;
				}

				if (points[seek].x == points[seek_p].x) { DSet[FLT_MAX] = DSet[FLT_MAX]; continue; }

				float Delta = (float)abs(points[seek].y - points[seek_p].y) / (float)abs(points[seek].x - points[seek_p].x);
				DSet[Delta] = DSet[Delta] + 1;
			}
		}

		int Max = 0;

		for (auto N : DSet)
		{
			if (N.second > Max) { Max = N.second; }
		}

		return Max;
	};

	void operator()() override final
	{

	};

	void operator()(const string &strUserInput) override final
	{

	};
};