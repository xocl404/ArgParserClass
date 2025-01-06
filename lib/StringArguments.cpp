#include "StringArguments.h"

ArgumentParser::ArgParser::StringArgument::StringArgument (const std::string& name): name(name) {}

ArgumentParser::ArgParser::StringArgument::StringArgument (const std::string& name, char short_name): name(name), short_name(short_name) {}


ArgumentParser::ArgParser::StringArgument::StringArgument (const std::string& name, const std::string& info): name(name), help_info(info) {}

ArgumentParser::ArgParser::StringArgument::StringArgument (const std::string& name, char short_name, const std::string& info)
        : name(name)
        , short_name(short_name)
        , help_info(info) {}

const std::string& ArgumentParser::ArgParser::StringArgument::GetName () const {
    return name;
}

char ArgumentParser::ArgParser::StringArgument::GetShortName () const {
    return short_name;
}

const std::string& ArgumentParser::ArgParser::StringArgument::GetValue () const {
    return *store_value;
}

const std::string& ArgumentParser::ArgParser::StringArgument::GetMultiValue (size_t index) const {
    return values[index];
}

size_t ArgumentParser::ArgParser::StringArgument::GetSize () const {
    return values.size();
}

size_t ArgumentParser::ArgParser::StringArgument::GetMinArgsCount () const {
    return min_args_count;
}

const std::string& ArgumentParser::ArgParser::StringArgument::GetHelpInfo() const {
    return help_info;
}

bool ArgumentParser::ArgParser::StringArgument::IsValue () const {
    return is_value;
}

void ArgumentParser::ArgParser::StringArgument::WriteValue (const std::string& argument) {
    is_value = true;
    if (is_multi_value) {
        values.push_back(argument);

        return;
    }
    *store_value = argument;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::StringArgument::MultiValue() {
    is_multi_value = true;

    return *this;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::StringArgument::MultiValue(size_t minimum) {
    is_multi_value = true;
    min_args_count = minimum;

    return *this;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::StringArgument::Default(const std::string& argument) {
    WriteValue(argument);

    return *this;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::StringArgument::StoreValue (std::string& store) {
    store_value = &store;

    return *this;
}
