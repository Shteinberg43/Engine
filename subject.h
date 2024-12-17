#pragma once
#include <string>
#include <map>
#include <sstream>

using ArgsMap = std::map<std::string, std::string>;

class Subject {
public:
    std::string replace_words(const  ArgsMap& args);
    std::string find_phrases(const ArgsMap& args);
    std::string capitalize_words(const ArgsMap& args);
    std::string capitalize_sentences(const ArgsMap& args);
    std::string number_sentences(const ArgsMap& args);
};