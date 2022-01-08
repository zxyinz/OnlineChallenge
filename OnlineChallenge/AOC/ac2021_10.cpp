#include "common.h"

using namespace std;

std::unordered_map<char, uint32> score_map = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
std::unordered_map<char, uint32> score_map2 = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
std::unordered_map<char, char> symbol_map = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};

int32 CalcScore(const std::string &str)
{
    stack<char> s;

    for (int32 seek = 0; seek < str.size(); seek = seek + 1)
    {
        char c = str[seek];
        if (c == '(' || c == '[' || c == '{' || c == '<')
        {
            s.push(c);
            continue;
        }

        if (c != symbol_map[s.top()])
        {
            //std::cout << str << " Pos:\t" << seek << "\t[" << c << "]\r\n";
            return score_map[c];
        }

        s.pop();
    }

    return 0;
}

int32 CalcScore2(const std::string &str)
{
    stack<char> s;

    for (int32 seek = 0; seek < str.size(); seek = seek + 1)
    {
        char c = str[seek];
        if (c == '(' || c == '[' || c == '{' || c == '<')
        {
            s.push(c);
            continue;
        }

        if (c != symbol_map[s.top()])
        {
            return -1;
        }

        s.pop();
    }

    int score = 0;

    while (!s.empty())
    {
        char target = symbol_map[s.top()];
        s.pop();

        //std::cout << target;
        score = score * 5 + score_map2[target];
    }

    //std::cout << "\t" << score << "\r\n";

    return score;
}

void ResolvePart1(vector<std::string> input)
{
    int32 sum = 0;

    for (const std::string &str : input)
    {
        sum = sum + CalcScore(str);
    }

    std::cout << sum << "\r\n";
}

void ResolvePart2(const vector<std::string> &input)
{
    vector<int32> score;

    for (const std::string &str : input)
    {
        const int32 val = CalcScore2(str);
        if (val >= 0)
        {
            score.push_back(val);
        }
    }

    std::sort(score.begin(), score.end());

    for (int32 val : score)
    {
        std::cout << val << "\r\n";
    }

    std::cout << score[(score.size() >> 1)] << "\r\n";
}

#include "ac2021_10_input.h"

int main()
{
    ResolvePart1(input_raw);
    ResolvePart2(input_test);
    return 0;
}