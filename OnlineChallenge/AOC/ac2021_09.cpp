#include "common.h"

using namespace std;

class Map
{
private:
    vector<vector<int32>> data;

public:
    int32 width;
    int32 height;

public:
    Map(const vector<vector<int32>> &data = {}) : data(data)
    {
        height = data.size();
        width = height == 0 ? 0 : data[0].size();
    };
    Map(const vector<string> &str_data)
    {
        for (const auto &str : str_data)
        {
            std::vector<int32> vec;
            for (char c : str)
            {
                vec.push_back(c - '0');
            }
            data.push_back(vec);
        }

        height = data.size();
        width = height == 0 ? 0 : data[0].size();
    };
    ~Map() = default;

    int32 iGetValue(const int32 x, const int32 y) const
    {
        if (x < 0 || y < 0)
        {
            return std::numeric_limits<int32>::max();
        }

        if (x >= width || y >= height)
        {
            return std::numeric_limits<int32>::max();
        }

        return data[y][x];
    }

    void iSetValue(const int32 x, const int32 y, const int32 value)
    {
        if (x < 0 || y < 0)
        {
            return;
        }

        if (x >= width || y >= height)
        {
            return;
        }

        data[y][x] = value;
    }

    bool iIsLowPoint(const int32 x, const int32 y) const
    {
        const int32 val = iGetValue(x, y);
        return (val < iGetValue(x - 1, y)) && (val < iGetValue(x + 1, y)) && (val < iGetValue(x, y - 1)) && (val < iGetValue(x, y + 1));
    }

    int32 iFlow(const int32 x, const int32 y, const int32 target)
    {
        const int32 val = iGetValue(x, y);

        if (val < 0)
        {
            return 0;
        }

        if (val > (target + 1))
        {
            return 0;
        }

        if (val == 9)
        {
            return 0;
        }

        iSetValue(x, y, -1);

        return 1 + iFlow(x - 1, y, val) + iFlow(x + 1, y, val) + iFlow(x, y - 1, val) + iFlow(x, y + 1, val);
    }

    void iPrint() const
    {
        std::cout << "\r\n";
        for (int seek_y = 0; seek_y < height; seek_y = seek_y + 1)
        {
            for (int seek_x = 0; seek_x < width; seek_x = seek_x + 1)
            {
                const int32 val = data[seek_y][seek_x];
                std::cout << (val < 0 ? "*" : to_string(val));
            }

            std::cout << "\r\n";
        }
        std::cout << "\r\n";
    }
};

void ResolvePart1(const Map &input)
{
    int32 sum = 0;
    for (int seek_y = 0; seek_y < input.height; seek_y = seek_y + 1)
    {
        for (int seek_x = 0; seek_x < input.width; seek_x = seek_x + 1)
        {
            //std::cout << input.iGetValue(seek_x, seek_y) << " \t" << input.iIsLowPoint(seek_x, seek_y) << "\r\n";
            sum = sum + (input.iIsLowPoint(seek_x, seek_y) ? (input.iGetValue(seek_x, seek_y) + 1) : 0);
        }
    }

    std::cout << sum << "\r\n";
}

void ResolvePart2(Map input)
{
    vector<int32> size;
    for (int seek_y = 0; seek_y < input.height; seek_y = seek_y + 1)
    {
        for (int seek_x = 0; seek_x < input.width; seek_x = seek_x + 1)
        {
            if (input.iIsLowPoint(seek_x, seek_y))
            {
                size.push_back(input.iFlow(seek_x, seek_y, input.iGetValue(seek_x, seek_y)));
                std::cout << size.back() << "\r\n";
                //input.iPrint();
            }
        }
    }

    std::sort(size.begin(), size.end());

    for (int seek = 0; seek < size.size(); seek = seek + 1)
    {
        std::cout << size[seek] << " ";
    }

    std::cout << "\r\n";

    int32 val = 1;

    for (int seek = 0; seek < 3; seek = seek + 1)
    {
        val = val * size[size.size() - seek - 1];
    }

    std::cout << val << "\r\n";
}

#include "ac2021_09_input.h"

int main()
{
    //ResolvePart1(input_raw);
    ResolvePart2(input_raw);
    return 0;
}