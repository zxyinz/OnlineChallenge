#include"RelyOn.h"
#include"ProblemSet.h"
using namespace std;
using namespace Leetcode;
int main(int argc, char** argv)
{
	cSolutionContainer Container;
	cTerminal Terminal;

	//Push problem set
	Container.iCreateSolution(static_cast<cSolutionObj*>(new cMaxDepthOfBinaryTree()));
	Container.iCreateSolution(static_cast<cSolutionObj*>(new cMaxPointsOnALine()));
	Container.iCreateSolution(static_cast<cSolutionObj*>(new cProductExceptSelf()));
	Container.iCreateSolution(static_cast<cSolutionObj*>(new cSkyLine()));

	Container.iPrintList("- ");

	Terminal.iPrintBanner();

	while (Terminal.iGetStatus())
	{
		Terminal.iProcess();
	}

	return 0;
}