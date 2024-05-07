#pragma once

#include <any>
#include <string>
#include <random>
#include <iostream>
#include <unordered_map>

#include "json.hpp"

class RandJson
{
public:
    enum Type
    {
        INT,
        STRING,
        BOOL,
        FLOAT,
        ARRAY
    };

    RandJson(const nlohmann::json &req)
    {
        for (auto it = req.begin(); it != req.end(); ++it)
        {
            if (it->is_object())
                for (auto i = it->begin(); i != it->end(); ++i)
                    _InsertTemplate(it.key() + "." + i.key(), i.value().type());

            else
                _InsertTemplate(it.key(), it.value().type());
        }
    };

    nlohmann::json GenUntypedJson(const int num_key = 0);

    nlohmann::json GenTypedJson(const int num_key = 0);

    nlohmann::json GetFullRandJson(const int num_key, const int depth);

private:
    void _InsertTemplate(const std::string &key, const nlohmann::json::value_type type);
    void _InsertData(nlohmann::json &key, const Type type);

    std::unordered_map<std::string, Type> _template_json;
};

[[maybe_unused]] static std::vector<std::string> split(const std::string &s, const char *delim)
{
    std::vector<std::string> ret;
    size_t last = 0;
    auto index = s.find(delim, last);
    while (index != std::string::npos)
    {
        if (index - last > 0)
        {
            ret.push_back(s.substr(last, index - last));
        }
        last = index + strlen(delim);
        index = s.find(delim, last);
    }
    if (!s.size() || s.size() - last > 0)
    {
        ret.push_back(s.substr(last));
    }
    return ret;
}

[[maybe_unused]] static std::string makeRandStr(int sz, bool printable = true)
{
    char CCH[] = "0123456789abcdefghijklmnopqrstu"
                 "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string ret;
    ret.resize(sz);
    std::mt19937 rng(std::random_device{}());
    for (int i = 0; i < sz; ++i)
    {
        if (printable)
        {
            uint32_t x = rng() % (sizeof(CCH) - 1);
            ret[i] = CCH[x];
        }
        else
        {
            ret[i] = rng() % 0xFF;
        }
    }
    return ret;
}