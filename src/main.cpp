#include <iostream>
#include "json.hpp"
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

    test["aboba"] = {
        {"name", "hui"},
        {"comment", "aboba"}
    };

    std::shared_ptr<RandJson> rand_tuple = std::make_shared<RandJson>(test);

    // auto resp = rand_tuple->GenTypedJson();

    auto resp = rand_tuple->GenUntypedJson();


    std::cout << resp.dump(3) << std::endl;

    return 0;
}