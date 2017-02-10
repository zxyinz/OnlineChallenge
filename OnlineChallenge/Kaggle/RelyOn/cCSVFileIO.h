#include"iostream"
#include"fstream"
#include"vector"
using namespace std;
namespace Kaggle
{
#ifndef __CCSVFILEIO_H__
#define __CCSVFILEIO_H__
	class cCSVFileIO
	{
	private:
		string m_FilePath;
		vector<vector<string>> m_Data;
	public:
		cCSVFileIO();
		~cCSVFileIO();

		bool iReadFile(const string &strFilePath);

		bool iWriteFile(const string &strFilePath) const;
	};
#endif
}