#include "common.h"

using namespace std;

void ResolvePart1(vector<int32> input)
{
    for (int32 seek = 0; seek < 80; seek = seek + 1)
    {
        int count = 0;

        for (int32 &val : input)
        {
            if (val == 0)
            {
                count = count + 1;
                val = 6;
                continue;
            }

            val = val - 1;
        }

        for (int seek_count = 0; seek_count < count; seek_count = seek_count + 1)
        {
            input.push_back(8);
        }
    }

    std::cout << input.size() << "\r\n";
}

void ResolvePart2(const vector<int32> &input)
{
    map<int32, uint64> counter;

    for (int32 val : input)
    {
        counter[val] = counter[val] + 1;
    }

    for (int32 seek = 0; seek < 256; seek = seek + 1)
    {
        int32 new_count = 0;
        map<int32, uint64> current;

        for (auto &record : counter)
        {
            if (record.first == 0)
            {
                new_count = record.second;
                record.second = 0;
                continue;
            }

            if (counter.find(record.first - 1) == counter.end())
            {
                current[record.first - 1] = record.second;
            }
            else
            {
                counter[record.first - 1] = record.second;
            }

            record.second = 0;
        }

        for (auto &record : current)
        {
            counter[record.first] = record.second;
        }

        counter[6] = counter[6] + new_count;
        counter[8] = counter[8] + new_count;

        // std::cout << "Day " << seek << "\t";
        // for (auto &record : counter)
        // {
        //     if (record.second == 0)
        //     {
        //         //   std::cout << "     ";
        //         continue;
        //     }
        //     std::cout << record.first << ":" << record.second << ", ";
        // }
        // std::cout << "\r\n";
    }

    uint64 total = 0;

    for (const auto &record : counter)
    {
        total = total + record.second;
    }

    std::cout << total << "\r\n";
}

#include "ac2021_06_input.h"

int main()
{
    //ResolvePart1(input_raw);
    ResolvePart2(input_raw);
    return 0;
}