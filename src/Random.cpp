#include "Random.hpp"

nlohmann::json RandJson::GenTypedJson(const int num_key)
{
    nlohmann::json resp;
    int count = 0;

    for (auto [key, type] : _template_json)
    {
        if (num_key && count == num_key)
            break;

        auto elements = split(key, ".");

        if (elements.size() == 2)
        {
            auto &value = resp[elements[0]][elements[1]];
            _InsertData(value, type);
        }
        else
        {
            auto &value = resp[key];
            _InsertData(value, type);
        }

        ++count;
    }

    return resp;
}

nlohmann::json RandJson::GenUntypedJson(const int num_key)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 4);

    nlohmann::json resp;
    int count = 0;

    for (auto [key, type] : _template_json)
    {
        if (num_key && count == num_key)
            break;

        auto elements = split(key, ".");
        if (elements.size() == 2)
        {
            auto &value = resp[elements[0]][elements[1]];
            _InsertData(value, Type(dist(rng)));
        }
        else
        {
            auto &value = resp[key];
            _InsertData(value, Type(dist(rng)));
        }

        ++count;
    }

    return resp;
}

nlohmann::json RandJson::GetFullRandJson(const int num_key, const int depth)
{
    nlohmann::json resp;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 4);

    for (int index = 0; index < num_key; ++index)
    {
        auto &it = resp[makeRandStr(5)];
        _InsertData(it, Type(dist(rng)));
    }

    return resp;;
}

void RandJson::_InsertTemplate(const std::string &key, const nlohmann::json::value_type type)
{
    switch (type)
    {
    case nlohmann::json::value_t::boolean:
        _template_json.insert({key, BOOL});
        break;

    case nlohmann::json::value_t::number_integer:
        _template_json.insert({key, INT});
        break;

    case nlohmann::json::value_t::string:
        _template_json.insert({key, STRING});
        break;

    case nlohmann::json::value_t::number_float:
        _template_json.insert({key, FLOAT});
        break;

    case nlohmann::json::value_t::array:
        _template_json.insert({key, ARRAY});
        break;

    default:
        std::cout << "Fail type value insert template" << std::endl;
        break;
    }
}

void RandJson::_InsertData(nlohmann::json &key, const Type type)
{
    std::random_device dev;
    std::mt19937 rng(dev());

    switch (type)
    {
    case BOOL:
    {
        std::uniform_int_distribution<std::mt19937::result_type> dis(0, 1);
        key = bool(dis(rng));
        break;
    }

    case INT:
    {
        std::uniform_int_distribution<std::mt19937::result_type> dis(0, 10000);
        key = dis(rng);
        break;
    }

    case STRING:
    {
        key = makeRandStr(9);
        break;
    }

    case FLOAT:
    {
        std::uniform_real_distribution<float> dis(0, 5);
        key = dis(rng);
        break;
    }

    case ARRAY:
    {
        std::vector<std::string> str;
        for (int i = 0; i < 3; ++i)
        {
            str.push_back(makeRandStr(9));
        }

        key = str;
        break;
    }


    default:
    {
        std::cout << "Fail" << std::endl;
        break;
    }
    }
}

// void RandJson::_AssignKeyValuePairToJson(nlohmann::json &t, Type type, int jsonDepth)
// {
//     std::random_device dev;
//     std::mt19937 rng(dev());

//     switch (type)
//     {
//     case BOOL:
//     {
//         std::uniform_int_distribution<std::mt19937::result_type> dis(0, 1);
//         t[makeRandStr(5)] = bool(dis(rng));
//         break;
//     }

//     case INT:
//     {
//         std::uniform_int_distribution<std::mt19937::result_type> dis(0, 10000);
//         t[makeRandStr(5)] = dis(rng);
//         break;
//     }

//     case STRING:
//     {
//         t[makeRandStr(5)] = makeRandStr(9);
//         break;
//     }

//     case FLOAT:
//     {
//         std::uniform_real_distribution<float> dis(0, 5);
//         t[makeRandStr(5)] = dis(rng);
//         break;
//     }

//     default:
//     {
//         t[makeRandStr(5)] = GetFullRandJson(jsonDepth + 1);
//         break;
//     }
//     }
// }