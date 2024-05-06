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
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);

    nlohmann::json resp;
    int count = 0;

    nlohmann::json test = nlohmann::json::object();

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

nlohmann::json RandJson::GetFullRandJson(const int num_key, const int nesting)
{

}

void RandJson::_InsertTemplate(const std::string &key, const nlohmann::json::value_type type)
{
    switch (type)
    {
    case nlohmann::json::value_t::boolean:
        _template_json.insert({key, BOOL});
        std::cout << key << " BOOL" << std::endl;
        break;

    case nlohmann::json::value_t::number_integer:
        _template_json.insert({key, INT});
        std::cout << key << " INT" << std::endl;
        break;

    case nlohmann::json::value_t::string:
        _template_json.insert({key, STRING});
        std::cout << key << " STRING" << std::endl;
        break;

    case nlohmann::json::value_t::number_float:
        _template_json.insert({key, FLOAT});
        std::cout << key << " FLOAT" << std::endl;
        break;

    default:
        std::cout << "Fail type value" << std::endl;
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

        default:
        {
            std::cout << "Fail type value" << std::endl;
            break;
        }
    }
}