#include "common.h"

using namespace std;

struct Board
{
public:
    vector<vector<int32>> b;

public:
    Board() = default;
    Board(const vector<vector<int32>> &b) : b(b){};
    ~Board() = default;

    bool iCheck(int32 x, int32 y) const
    {
        bool match = true;

        for (uint32 seek_x = 0; seek_x < b[y].size(); seek_x = seek_x + 1)
        {
            if (b[y][seek_x] >= 0)
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            return true;
        }

        match = true;

        for (uint32 seek_y = 0; seek_y < b.size(); seek_y = seek_y + 1)
        {
            if (b[seek_y][x] >= 0)
            {
                match = false;
                break;
            }
        }

        return match;
    };

    int32 iSum() const
    {
        int32 sum = 0;
        for (uint32 seek_y = 0; seek_y < b.size(); seek_y = seek_y + 1)
        {
            const vector<int32> &vec = b[seek_y];
            for (uint32 seek_x = 0; seek_x < vec.size(); seek_x = seek_x + 1)
            {
                if (vec[seek_x] < 0)
                {
                    continue;
                }

                sum = sum + vec[seek_x];
            }
        }

        return sum;
    }

    bool iMark(int32 val)
    {
        bool match = false;
        for (uint32 seek_y = 0; seek_y < b.size(); seek_y = seek_y + 1)
        {
            vector<int32> &vec = b[seek_y];
            for (uint32 seek_x = 0; seek_x < vec.size(); seek_x = seek_x + 1)
            {
                if (vec[seek_x] == val)
                {
                    vec[seek_x] = -1;
                    match = match | iCheck(seek_x, seek_y);
                }
            }
        }

        return match;
    };
};

void ResolvePart1(const vector<int32> &input, vector<Board> &boards)
{
    for (const uint32 val : input)
    {
        for (Board &b : boards)
        {
            if (b.iMark(val))
            {
                std::cout << b.iSum() * val << "\r\n";
                return;
            }
        }
    }
}

void ResolvePart2(std::vector<int32> &input, vector<Board> &boards)
{
    int32 index = -1;
    int32 value = 1;
    unordered_set<int32> completed;

    for (const uint32 val : input)
    {
        for (int32 seek = 0; seek < boards.size(); seek = seek + 1)
        {
            if (completed.find(seek) != completed.end())
            {
                continue;
            }

            if (boards[seek].iMark(val))
            {
                index = seek;
                value = val;
                completed.insert(seek);
            }
        }
    }

    std::cout << boards[index].iSum() * value << "\r\n";
}

#include "ac2021_04_input.h"

int main()
{
    vector<int32> operation = input_raw;
    vector<Board> data;

    for (const auto &b : board_raw)
    {
        data.push_back(b);
    }

    ResolvePart1(operation, data);
    ResolvePart2(operation, data);
    return 0;
}