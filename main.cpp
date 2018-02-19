#include <toml11/toml.hpp>
#include <iostream>

int main()
{
    const std::string fname("example.toml");
    const auto data = toml::parse(fname);

    const auto answer    = toml::get<std::int64_t>(data.at("answer"));
    const auto pi        = toml::get<double>(data.at("pi"));
    const auto numbers   = toml::get<std::vector<int>>(data.at("numbers"));
    const auto timepoint = toml::get<std::chrono::system_clock::time_point>(data.at("time"));
    const auto tab       = toml::get<toml::Table>(data.at("tab"));
    const auto key       = toml::get<std::string>(tab.at("key"));

    std::cerr << "answer  = " << answer << std::endl;
    std::cerr << "pi      = " << pi << std::endl;
    std::cerr << "numbers = " << numbers[0] << std::endl;
    std::cerr << "key     = " << key << std::endl;
}