#include <iostream>
#include "Random.hpp"

int main()
{
    nlohmann::json test
    {
        {"id",     "test"},
        {"num",    123},
        {"status", false},
        {"date",   158.2}
    };

    test["basic"] = {
        {"name", "worker"},
        {"comment", "Cleaner"},
        {"array", {"arr", "abo"}}
    };

    std::unordered_map<std::string, std::shared_ptr<RandJson>> templates;

    {
        auto temp = std::make_shared<RandJson>(test);
        templates["worker"] = temp;
    }

    auto typed = templates["worker"]->GenTypedJson();
    // auto untyped = templates["worker"]->GenUntypedJson();
    // auto random = templates["worker"]->GetFullRandJson(4, 3);

    std::cout << typed.dump(3) << std::endl;
    // std::cout << untyped.dump(3) << std::endl;
    // std::cout << random.dump(3) << std::endl;

    return 0;
}