#include"../RelyOn.h"
#pragma once
using namespace std;
using namespace Leetcode;
//Problem description:
//
// A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance.
// Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A)
// write a program to output the skyline formed by these buildings collectively (Figure B).
//
// The geometric information of each building is represented by a triplet of integers[Li, Ri, Hi],
// where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi is its height.
// It is guaranteed that 0 ¡Ü Li, Ri ¡Ü INT_MAX, 0 < Hi ¡Ü INT_MAX, and Ri - Li > 0.
// You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
//
// For instance, the dimensions of all buildings in Figure A are recorded as : [[2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8]] .
//
// The output is a list of "key points" (red dots in Figure B) in the format of[[x1, y1], [x2, y2], [x3, y3], ...] that uniquely defines a skyline.
// A key point is the left endpoint of a horizontal line segment.
// Note that the last key point, where the rightmost building ends, is merely used to mark the termination of the skyline, and always has zero height.
// Also, the ground in between any two adjacent buildings should be considered part of the skyline contour.
//
// For instance, the skyline in Figure B should be represented as : [[2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0]].
//
// Notes :
//
//	   The number of buildings in any input list is guaranteed to be in the range[0, 10000].
//	   The input list is already sorted in ascending order by the left x position Li.
//	   The output list must be sorted by the x position.
//	   There must be no consecutive horizontal lines of equal height in the output skyline.
//			For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable;
//			the three lines of height 5 should be merged into one in the final output as such : [...[2 3], [4 5], [12 7], ...]

class cSkyLine : public cSolutionObj
{
private:
public:
	cSkyLine()
		:cSolutionObj("SkyLine","")
	{
	};
	~cSkyLine(){};

	vector<pair<int, int>> getSkyline(vector<vector<int>> buildings)
	{
		int Size = buildings.size();

		if (Size == 0){ return vector<pair<int, int>>(); }

		vector<pair<int, int>> KeyPointSet(buildings.size() + 1);

		int Count = 1;

		KeyPointSet[0] = make_pair(buildings[0][0], buildings[0][2]);

		int px1 = buildings[0][0];
		int px2 = buildings[0][1];
		int ph = buildings[0][2];

		for (int seek = 1; seek < Size; seek = seek + 1)
		{
			int x1 = buildings[seek][0];
			int x2 = buildings[seek][1];
			int h = buildings[seek][2];

			if (px2 < x1)
			{
				KeyPointSet[Count] = make_pair(px2, 0);
				KeyPointSet[Count + 1] = make_pair(x1, h);

				Count = Count + 2;
			}
			else
			{
				if (ph != h)
				{ 
					KeyPointSet[Count] = make_pair(x1, h);
					Count = Count + 1;
				}
			}

			px1 = x1;
			px2 = x2;
			ph = h;
		}

		::cout << buildings[Size - 1][0] << "\r\n";
		::cout << buildings[Size - 1][1] << "\r\n";
		::cout << buildings[Size - 1][2] << "\r\n";

		KeyPointSet[Count] = make_pair(buildings[Size - 1][1], buildings[Size - 1][2]);

		KeyPointSet.resize(Count);

		return KeyPointSet;
	};

	void operator()() override final
	{

	};

	void operator()(const string &strUserInput) override final
	{

	};
};