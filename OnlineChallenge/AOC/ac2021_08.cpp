#include "common.h"

using namespace std;

std::string to_string(const std::set<char> &set)
{
    string str;
    for (char c : set)
    {
        str = str + c;
    }
    return str;
}

namespace std
{
    template <>
    struct hash<std::set<char>>
    {
        size_t operator()(const std::set<char> &container)
        {
            string str;
            for (char c : container)
            {
                str = str + c;
            }
            return hash<string>()(str);
        }
    };
}

bool operator==(const std::set<char> &s1, const std::set<char> &s2)
{
    if (s1.size() != s2.size())
    {
        return false;
    }

    for (char c : s1)
    {
        if (s2.find(c) == s2.end())
        {
            return false;
        }
    }

    for (char c : s2)
    {
        if (s1.find(c) == s1.end())
        {
            return false;
        }
    }

    return true;
}

class Display
{
public:
    std::vector<std::set<char>> input;
    std::vector<std::set<char>> output;

    std::vector<uint32> output_decoded;

    std::map<uint32, std::set<char>> raw_number_map;
    std::map<std::set<char>, uint32> decode_map;

public:
    Display(std::string str)
    {
        raw_number_map[0] = std::set<char>({'a', 'b', 'c', 'e', 'f', 'g'});
        raw_number_map[1] = std::set<char>({'c', 'f'});
        raw_number_map[2] = std::set<char>({'a', 'c', 'd', 'e', 'g'});
        raw_number_map[3] = std::set<char>({'a', 'c', 'd', 'f', 'g'});
        raw_number_map[4] = std::set<char>({'b', 'c', 'd', 'f'});
        raw_number_map[5] = std::set<char>({'a', 'b', 'd', 'f', 'g'});
        raw_number_map[6] = std::set<char>({'a', 'b', 'd', 'e', 'f', 'g'});
        raw_number_map[7] = std::set<char>({'a', 'c', 'f'});
        raw_number_map[8] = std::set<char>({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        raw_number_map[9] = std::set<char>({'a', 'b', 'c', 'd', 'f', 'g'});

        decode_map[std::set<char>({'a', 'b', 'c', 'e', 'f', 'g'})] = 0;
        decode_map[std::set<char>({'c', 'f'})] = 1;
        decode_map[std::set<char>({'a', 'c', 'd', 'e', 'g'})] = 2;
        decode_map[std::set<char>({'a', 'c', 'd', 'f', 'g'})] = 3;
        decode_map[std::set<char>({'b', 'c', 'd', 'f'})] = 4;
        decode_map[std::set<char>({'a', 'b', 'd', 'f', 'g'})] = 5;
        decode_map[std::set<char>({'a', 'b', 'd', 'e', 'f', 'g'})] = 6;
        decode_map[std::set<char>({'a', 'c', 'f'})] = 7;
        decode_map[std::set<char>({'a', 'b', 'c', 'd', 'e', 'f', 'g'})] = 8;
        decode_map[std::set<char>({'a', 'b', 'c', 'd', 'f', 'g'})] = 9;

        bool push_input = true;
        int32 begin = 0;

        str = str + " ";

        for (int32 seek = 0; seek < str.size(); seek = seek + 1)
        {
            if (str[seek] == ' ' || str[seek] == '|')
            {
                if (begin != seek)
                {
                    if (push_input)
                    {
                        input.push_back(_ToSet(str.substr(begin, seek - begin)));
                    }
                    else
                    {
                        output.push_back(_ToSet(str.substr(begin, seek - begin)));
                    }
                }

                begin = seek + 1;
                push_input = str[seek] == '|' ? false : push_input;
                continue;
            }
        }
    };
    ~Display() = default;

    std::set<char> _ToSet(const std::string &str)
    {
        std::set<char> result;
        for (char c : str)
        {
            result.insert(c);
        }
        return result;
    }

    std::set<char> _CalcOverlap(const std::set<char> &s1, const std::set<char> &s2)
    {
        std::set<char> common;

        for (char c : s1)
        {
            if (s2.find(c) != s2.end())
            {
                common.insert(c);
            }
        }

        return common;
    }

    bool _Contain(const set<char> &container, const char target)
    {
        return container.find(target) != container.end();
    }

    bool _Contain(const set<char> &container, const set<char> &target)
    {
        for (char c : target)
        {
            if (container.find(c) == container.end())
            {
                return false;
            }
        }
        return true;
    }

    void _Print(std::map<char, std::set<char>> &digit_map)
    {
        for (const auto &it : digit_map)
        {
            std::cout << it.first << "\t" << to_string(it.second) << "\r\n";
        }
    }

    const std::set<char> _FindNumberBySize(const std::vector<std::set<char>> &total, const int32 target)
    {
        for (const auto &item : total)
        {
            if (item.size() == target)
            {
                return item;
            }
        }

        return std::set<char>();
    }

    void _UpdateDigitMap(const std::set<char> &raw_set, const std::set<char> &target_set, std::map<char, std::set<char>> &digit_map)
    {
        for (auto &digit : digit_map)
        {
            //std::cout << digit.first << " contain [" << to_string(target_set) << "] " << (_Contain(target_set, digit.first) ? "true" : "false") << "\t";

            if (_Contain(target_set, digit.first))
            {
                //std::cout << "\tcalc overlap:\t[" << to_string(digit.second) << "]\t[" << to_string(raw_set) << "] - ";

                digit.second = _CalcOverlap(digit.second, raw_set);

                //std::cout << "\tafter overlap:\t[" << to_string(digit.second) << "]\r\n";
            }
            else
            {
                //std::cout << "\tremove overlap:\t[" << to_string(digit.second) << "]\t[" << to_string(raw_set) << "] - ";
                for (char c : raw_set)
                {
                    if (digit.second.find(c) != digit.second.end())
                    {
                        digit.second.erase(digit.second.find(c));
                    }
                }
                //std::cout << "\tafter remove:\t[" << to_string(digit.second) << "]\r\n";
            }
        }
    }

    void _SetNumber(std::vector<std::set<char>> &total, std::map<uint32, std::set<char>> &number_map, uint32 number, const std::set<char> &result)
    {
        //std::cout << "\r\nRemove resolved number " << number << "\t[" << to_string(result) << "]\r\n";

        // _Print(total);

        number_map[number] = result;

        auto it = total.begin();

        while (it != total.end())
        {
            //std::cout << "Check equal\t" << to_string(*it) << "\t" << to_string(result) << "\r\n";
            if (*it == result)
            {
                it = total.erase(it);
                continue;
            }

            it++;
        }

        // _Print(total);
    }

    void _ResolveByNumber(std::vector<std::set<char>> &total, std::map<uint32, std::set<char>> &number_map, std::map<char, std::set<char>> &digit_map, uint32 number, uint32 size)
    {
        std::cout << "\r\nResolve number " << number << "\r\n";
        const auto result = _FindNumberBySize(total, size);
        if (result.empty())
        {
            return;
        }

        _SetNumber(total, number_map, number, result);
        _UpdateDigitMap(raw_number_map[number], result, digit_map);
    }

    void _ResolveByOverlap(std::vector<std::set<char>> &total, std::map<uint32, std::set<char>> &number_map, std::map<char, std::set<char>> &digit_map, uint32 number, uint32 size, uint32 overlap_number)
    {
        std::cout << "\r\nResolve number overlap " << number << "\t" << overlap_number << "\r\n";
        if (number_map.find(overlap_number) != number_map.end())
        {
            std::set<char> result;
            for (const auto &item : total)
            {
                if (item.size() == size && _Contain(item, number_map[overlap_number]))
                {
                    result = item;
                    break;
                }
            }

            if (!result.empty())
            {
                std::cout << "Found " << to_string(result) << "\r\n";
                _UpdateDigitMap(raw_number_map[number], result, digit_map);
                _SetNumber(total, number_map, number, result);
            }
        }
    }

    void _ResolveFive(std::vector<std::set<char>> &total, std::map<uint32, std::set<char>> &number_map, std::map<char, std::set<char>> &digit_map)
    {
        std::cout << "\r\nResolve 5\r\n";
        char e = 0;

        for (const auto &it : digit_map)
        {
            if (it.second.size() == 1 && (*it.second.begin() == 'e'))
            {
                e = it.first;
                break;
            }
        }

        if (e == 0)
        {
            std::cout << "\t No e found\r\n";
            return;
        }

        std::cout << "\t Found e [" << e << "]\t";

        for (const auto &item : total)
        {
            if (item.size() == 5)
            {
                std::cout << "\t Found 5 [" << to_string(item) << "]\r\n";
            }

            if (item.size() == 5 && (item.find(e) == item.end()))
            {
                std::cout << "\t Found match [" << to_string(item) << "]\r\n";
                _UpdateDigitMap(raw_number_map[5], item, digit_map);
                _SetNumber(total, number_map, 5, item);
                return;
            }
        }

        std::cout << "\r\n";
    }

    void _PrintNumberMap(const std::map<uint32, std::set<char>> &map)
    {
        for (const auto &it : map)
        {
            std::cout << it.first << "\t" << to_string(it.second) << "\r\n";
        }
    }

    int iResolve()
    {
        std::vector<std::set<char>> total;

        for (const auto item : input)
        {
            total.push_back(item);
        }

        for (const auto item : output)
        {
            total.push_back(item);
        }

        std::map<char, std::set<char>> digit_map;
        std::map<uint32, std::set<char>> number_map;

        digit_map['a'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        digit_map['b'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        digit_map['c'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        digit_map['d'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        digit_map['e'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        digit_map['f'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});
        digit_map['g'] = std::set({'a', 'b', 'c', 'd', 'e', 'f', 'g'});

        _ResolveByNumber(total, number_map, digit_map, 1, 2);
        _ResolveByNumber(total, number_map, digit_map, 4, 4);
        _ResolveByNumber(total, number_map, digit_map, 7, 3);
        _ResolveByNumber(total, number_map, digit_map, 8, 7);

        _Print(digit_map);

        _ResolveByOverlap(total, number_map, digit_map, 3, 5, 7);
        _ResolveByOverlap(total, number_map, digit_map, 9, 6, 4);

        _Print(digit_map);

        _ResolveFive(total, number_map, digit_map);
        _Print(digit_map);

        if (number_map.find(9) != number_map.end())
        {
            _ResolveByOverlap(total, number_map, digit_map, 0, 6, 1);
            _ResolveByOverlap(total, number_map, digit_map, 0, 6, 7);
        }

        _PrintNumberMap(number_map);

        bool fully_resolved = true;

        for (const auto &item : digit_map)
        {
            fully_resolved = fully_resolved && (item.second.size() == 1);
        }

        if (!fully_resolved)
        {
            iPrint();
            return 0;
        }

        for (int32 seek = 0; seek < 10; seek = seek + 1)
        {
            if (number_map.find(seek) == number_map.end())
            {
                std::set<char> result;
                for (char c : raw_number_map[seek])
                {
                    for (const auto &it : digit_map)
                    {
                        if (*it.second.begin() == c)
                        {
                            result.insert(it.first);
                        }
                    }
                }

                number_map[seek] = result;
            }
        }

        int number = 0;

        std::cout << "Output size: " << output.size() << "\r\n";

        for (const std::set<char> &item : output)
        {
            for (const auto &it : number_map)
            {
                if (it.second == item)
                {
                    std::cout << "[ ----- ] " << to_string(item) << "\t" << it.first << "\r\n";
                    number = number * 10 + it.first;
                    break;
                }
            }
        }

        std::cout << number << "\r\n";
        return number;
    }

    void _Print(const std::vector<std::set<char>> &list)
    {
        std::cout << "\r\n[ ----- ] ";
        for (const auto &item : list)
        {
            std::cout << to_string(item) << " ";
        }
        std::cout << "\r\n";
    }

    void iPrint() const
    {
        for (const auto &val : input)
        {
            for (char c : val)
            {
                std::cout << c;
            }
            std::cout << ",";
        }

        std::cout << "| ";

        for (const auto &val : output)
        {
            for (char c : val)
            {
                std::cout << c;
            }
            std::cout << ",";
        }

        std::cout << "\r\n";
    }

    uint32 iGetOutputCount(const uint32 digit) const
    {
        std::map<uint32, uint32> counter;

        for (const auto &item : output)
        {
            counter[item.size()] = counter[item.size()] + 1;
        }

        if (digit == 1)
        {
            return counter[2];
        }

        if (digit == 4)
        {
            return counter[4];
        }

        if (digit == 7)
        {
            return counter[3];
        }

        if (digit == 8)
        {
            return counter[7];
        }

        return 0;
    }
};
void ResolvePart1(const vector<std::string> &input)
{
    std::vector<Display> displays;
    std::map<uint32, uint32> counter;

    for (const std::string &item : input)
    {
        Display record(item);
        displays.push_back(record);

        //record.iPrint();

        counter[1] = counter[1] + record.iGetOutputCount(1);
        counter[4] = counter[4] + record.iGetOutputCount(4);
        counter[7] = counter[7] + record.iGetOutputCount(7);
        counter[8] = counter[8] + record.iGetOutputCount(8);
    }

    uint32 count = 0;

    for (const auto &it : counter)
    {
        count = count + it.second;
    }

    std::cout << count << "\r\n";
}

void ResolvePart2(const vector<std::string> &input)
{
    std::vector<Display> displays;
    std::map<uint32, uint32> counter;

    uint32 sum = 0;
    for (const std::string &item : input)
    {
        Display record(item);
        displays.push_back(record);

        sum = sum + record.iResolve();
    }

    std::cout << sum << "\r\n";
}

#include "ac2021_08_input.h"

int main()
{
    //ResolvePart1(input_raw);
    ResolvePart2(input_raw);
    return 0;
}