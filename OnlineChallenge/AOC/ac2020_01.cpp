#include "common.h"

int main()
{
    char Str[128];
    vector<int> FSet;

    while (true)
    {
        cin.getline(Str, 128);
        string strVal = Str;

        if (strVal.empty())
        {
            break;
        }

        const int Symbol = strVal[0] == '+' ? 1.0 : -1.0;
        FSet.push_back(Symbol * atoi(strVal.substr(1, strVal.size() - 1).c_str()));
    }

    int Index = 0;
    int Sum = 0;
    unordered_set<int> Table;

    while (true)
    {
        Sum = Sum + FSet[Index % FSet.size()];
        Index = Index + 1;

        if (Table.find(Sum) != Table.end())
        {
            ::cout << "Target: " << Sum << "\r\n";
            break;
        }
        Table.insert(Sum);
    }

    return 0;
}