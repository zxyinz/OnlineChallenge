#include"RelyOn.h"
#include"ProblemSet.h"
using namespace std;
using namespace Leetcode;
int main(int argc, char** argv)
{
	cSolutionList List;

	//Push problem set
	List.iCreateSolution(static_cast<cSolutionObj*>(new cMaxDepthOfBinaryTree()));
	List.iCreateSolution(static_cast<cSolutionObj*>(new cMaxPointsOnALine()));
	List.iCreateSolution(static_cast<cSolutionObj*>(new cProductExceptSelf()));
	List.iCreateSolution(static_cast<cSolutionObj*>(new cSkyLine()));

	List.iPrintList("- ");

	return 0;
}