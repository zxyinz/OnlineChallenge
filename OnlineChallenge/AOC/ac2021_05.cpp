#include "common.h"

using namespace std;

template <class T>
bool Equal(const T v1, const T v2) { return v1 == v2; };

template <>
bool Equal<double>(const double v1, const double v2) { return abs(v1 - v2) < 0.01; };

template <class T>
void PrintP(const std::string &Prefix, const T &v)
{
    std::cout << Prefix << "\t" << v.x << " " << v.y << "\r\n";
};

template <class T>
void PrintLine(const std::string &Prefix, const T &l)
{
    printf("%s\t(%3i,%3i)\t(%3i,%3i)\t(%f, %f)\r\n", Prefix.c_str(), l.p1.x, l.p1.y, l.p2.x, l.p2.y, l.dir.x, l.dir.y);
};

template <class T>
struct _Vector
{
public:
    T x;
    T y;

public:
    _Vector(T x = 0, T y = 0) : x(x), y(y){};
    _Vector(const _Vector<int32> &vec) : x(vec.x), y(vec.y){};
    _Vector(const _Vector<double> &vec) : x(vec.x), y(vec.y){};
    ~_Vector() = default;

    bool operator==(const _Vector<T> &v) const
    {
        return Equal(x, v.x) && Equal(y, v.y);
    };

    bool operator!=(const _Vector<T> &v) const
    {
        return !Equal(x, v.x) || !Equal(y, v.y);
    };

    _Vector<T> operator+(const _Vector<T> &v) const
    {
        return _Vector<T>(x + v.x, y + v.y);
    }

    _Vector<T> operator-(const _Vector<T> &v) const
    {
        return _Vector<T>(x - v.x, y - v.y);
    }

    _Vector<T> operator*(const double val) const
    {
        return _Vector<T>(x * val, y * val);
    }

    double iLength() const
    {
        return sqrt(x * x + y * y);
    }

    _Vector<double> iNormalize() const
    {
        return _Vector<double>(static_cast<double>(x), static_cast<double>(y)) * (1.0 / iLength());
    };

    double iDot(const _Vector<T> &v) const
    {
        return x * v.x + y * v.y;
    }

    double iCross(const _Vector<T> &v) const
    {
        return x * v.y - y * v.x;
    }
};

typedef _Vector<int32> Point;

namespace std
{
    template <>
    struct hash<Point>
    {
        size_t operator()(const Point &v) const
        {
            return hash<string>()(std::to_string(v.x) + "," + std::to_string(v.y));
        }
    };
}

struct Line
{
public:
    Point p1, p2;
    _Vector<double> dir;

protected:
    bool _IsPositive(const double val) const
    {
        return val > 0;
    }

public:
    Line(const Point &p1, const Point &p2) : p1(p1), p2(p2)
    {
        dir = (p2 - p1).iNormalize();
    };
    ~Line() = default;

    int32 iGetLeft() const { return std::min(p1.x, p2.x); };
    int32 iGetRight() const { return std::max(p1.x, p2.x); };
    int32 iGetTop() const { return std::min(p1.y, p2.y); };
    int32 iGetBottom() const { return std::max(p1.y, p2.y); };

    bool iIsRegularLine() const { return p1.x == p2.x || p1.y == p2.y; };
    bool iIsVerticalLine() const { return p1.x == p2.x; }
    bool iIsHorizontalLine() const { return p1.y == p2.y; }

    bool iOverlap(const Line &line) const
    {
        if (p1 == line.p1 || p1 == line.p2 || p2 == line.p1 || p2 == line.p2)
        {
            return true;
        }

        return (_IsPositive(dir.iDot(line.p1 - p1)) != _IsPositive(dir.iDot(line.p2 - p1))) && (_IsPositive(line.dir.iDot(p1 - line.p1)) != _IsPositive(line.dir.iDot(p2 - line.p1)));
    };

    bool iContain(const Point &p) const
    {
        if (p == p1)
        {
            return true;
        }

        const Point vec = (p - p1);
        return vec.iNormalize() == dir && vec.iLength() <= p.iLength();
    }

    vector<Point> iCalcOverlap(const Line &line) const
    {
        vector<Point> points;

        // No overlap.
        if (iGetLeft() > line.iGetRight() || iGetRight() < line.iGetLeft())
        {
            return points;
        }

        if (iGetTop() > line.iGetBottom() || iGetBottom() < line.iGetTop())
        {
            return points;
        }

        // if (iOverlap(line))
        // {
        //     return points;
        // }

        if (iIsVerticalLine() && line.iIsVerticalLine())
        {
            const int32 x = iGetLeft();

            int32 top = std::max(iGetTop(), line.iGetTop());
            int32 bottom = std::min(iGetBottom(), line.iGetBottom());

            for (int32 seek = top; seek <= bottom; seek = seek + 1)
            {
                points.push_back(Point(x, seek));
            }

            return points;
        }

        if (iIsHorizontalLine() && line.iIsHorizontalLine())
        {
            const int32 y = iGetTop();

            int32 left = std::max(iGetLeft(), line.iGetLeft());
            int32 right = std::min(iGetRight(), line.iGetRight());

            for (int32 seek = left; seek <= right; seek = seek + 1)
            {
                points.push_back(Point(seek, y));
            }

            return points;
        }

        if (iIsRegularLine() && line.iIsRegularLine())
        {
            points.push_back(iIsVerticalLine() ? Point(p1.x, line.p1.y) : Point(line.p1.x, p1.y));
            return points;
        }

        _Vector<double> dir = (p2 - p1).iNormalize();

        dir.x = dir.x < -0.1 ? -1 : dir.x;
        dir.x = dir.x > 0.1 ? 1 : dir.x;

        dir.y = dir.y < -0.1 ? -1 : dir.y;
        dir.y = dir.y > 0.1 ? 1 : dir.y;

        Point current = p1;

        while (current != p2)
        {
            if (line.iContain(current))
            {
                points.push_back(current);
            }

            current = current + dir;
        }

        if (line.iContain(p2))
        {
            points.push_back(p2);
        }

        // if (points.empty())
        // {
        //     PrintLine("L1", *this);
        //     PrintLine("L2", line);
        //     std::cout << "\r\n";
        // }

        return points;
    };
};

void ResolvePart1(const vector<Line> &input)
{
    unordered_map<Point, int32> counter;

    for (int seek = 0; seek < input.size(); seek = seek + 1)
    {
        if (!input[seek].iIsRegularLine())
        {
            continue;
        }

        const Line &l1 = input[seek];
        for (int seek_internal = seek + 1; seek_internal < input.size(); seek_internal = seek_internal + 1)
        {
            if (!input[seek_internal].iIsRegularLine())
            {
                continue;
            }

            const vector<Point> points = l1.iCalcOverlap(input[seek_internal]);

            for (const Point &p : points)
            {
                counter[p] = counter[p] + 1;
            }
        }
    }

    std::cout << counter.size() << "\r\n";
};

void ResolvePart2(const vector<Line> &input)
{
    unordered_map<Point, int32> counter;

    for (int seek = 0; seek < input.size(); seek = seek + 1)
    {
        const Line &l1 = input[seek];

        _Vector<double> dir = l1.dir;

        dir.x = dir.x < -0.1 ? -1 : dir.x;
        dir.x = dir.x > 0.1 ? 1 : dir.x;

        dir.y = dir.y < -0.1 ? -1 : dir.y;
        dir.y = dir.y > 0.1 ? 1 : dir.y;

        Point current = l1.p1;

        while (current != l1.p2)
        {
            counter[current] += 1;
            current = current + dir;
        }

        counter[l1.p2] += 1;

        // for (int seek_internal = seek + 1; seek_internal < input.size(); seek_internal = seek_internal + 1)
        // {
        //     const vector<Point> points = l1.iCalcOverlap(input[seek_internal]);

        //     for (const Point &p : points)
        //     {
        //         counter[p] = counter[p] + 1;
        //     }
        // }
    }

    int32 count = 0;

    for (auto &item : counter)
    {
        //cout << item.first.x << "," << item.first.y << "\t" << item.second << "\r\n";
        count = count + (item.second > 1 ? 1 : 0);
    }

    std::cout << count << "\r\n";
};

#include "ac2021_05_input.h"

int main()
{
    std::cout << "\33c\e[3]";

    //ResolvePart1(input);
    ResolvePart2(input);

    return 0;
}