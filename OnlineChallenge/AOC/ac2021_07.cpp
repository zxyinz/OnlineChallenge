#include "common.h"

using namespace std;

void ResolvePart1(vector<int32> input)
{
    int32 min_cost = std::numeric_limits<int32>::max();

    for (int32 seek = 0; seek < input.size(); seek = seek + 1)
    {
        int32 cost = 0;

        for (int32 &val : input)
        {
            cost = cost + std::abs(val - seek);
        }

        min_cost = std::min<int32>(cost, min_cost);

        //std::cout << cost << "\r\n";
    }

    std::cout << min_cost << "\r\n";
}

void ResolvePart2(const vector<int32> &input)
{
    map<int32, int32> counter;

    for (int32 val : input)
    {
        counter[val] = counter[val] + 1;
    }

    int32 min_cost = std::numeric_limits<int32>::max();

    for (int32 seek = 0; seek < input.size(); seek = seek + 1)
    {
        int32 cost = 0;

        for (const auto &item : counter)
        {
            const int32 distance = std::abs(item.first - seek);
            const int32 current_cost = distance * (1 + distance) * 0.5;
            cost = cost + current_cost * item.second;
        }

        min_cost = std::min<int32>(cost, min_cost);

        //std::cout << cost << "\r\n";
    }

    std::cout << min_cost << "\r\n";
}

#include "ac2021_07_input.h"

int main()
{
    ResolvePart1(input_raw);
    ResolvePart2(input_raw);
    return 0;
}