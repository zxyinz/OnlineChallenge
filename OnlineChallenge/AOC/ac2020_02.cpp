#include "common.h"
using namespace std;

int main()
{
    char Str[128];
    vector<string> DataSet;

    unsigned int MaxSize = 0;

    while (true)
    {
        cin.getline(Str, 128);
        const string strInstance = Str;

        if (strInstance.empty())
        {
            break;
        }

        DataSet.push_back(strInstance);
        MaxSize = MaxSize > strInstance.size() ? MaxSize : strInstance.size();
    }

    int DCount = 0;
    int TCount = 0;

    for (const string &strInstance : DataSet)
    {
        unordered_map<char, int> CountTable;

        for (const char c : strInstance)
        {
            CountTable[c]++;
        }

        bool DMatch = false;
        bool TMatch = false;
        for (const auto &Pair : CountTable)
        {
            DMatch = DMatch || Pair.second == 2;
            TMatch = TMatch || Pair.second == 3;
        }

        DCount = DCount + (DMatch ? 1 : 0);
        TCount = TCount + (TMatch ? 1 : 0);
    }

    ::cout << "CheckSum: " << DCount * TCount << "\r\n";

    for (int seek = 0; seek < MaxSize; seek = seek + 1)
    {
        unordered_set<string> LookupTable;

        for (string strInstance : DataSet)
        {
            if (strInstance.size() < seek)
            {
                continue;
            }

            strInstance[seek] = ' ';
            if (LookupTable.find(strInstance) != LookupTable.end())
            {
                ::cout << "Common String: \'" << strInstance << "\'\r\n";
                return 0;
            }

            LookupTable.insert(strInstance);
        }
    }

    return 0;
}