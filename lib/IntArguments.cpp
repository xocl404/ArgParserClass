#include "IntArguments.h"

ArgumentParser::ArgParser::IntArgument::IntArgument(const std::string& name): name(name) {}

ArgumentParser::ArgParser::IntArgument::IntArgument(const std::string& name, char short_name)
        : name(name)
        , short_name(short_name) {}

ArgumentParser::ArgParser::IntArgument::IntArgument(const std::string& name, const std::string& info): name(name), help_info(info) {}

ArgumentParser::ArgParser::IntArgument::IntArgument(const std::string& name, char short_name, const std::string& info)
        : name(name)
        , short_name(short_name)
        , help_info(info) {}

const std::string& ArgumentParser::ArgParser::IntArgument::GetName () const {
    return name;
}

char ArgumentParser::ArgParser::IntArgument::GetShortName () const {
    return short_name;
}

int ArgumentParser::ArgParser::IntArgument::GetValue () const {
    return value;
}

int ArgumentParser::ArgParser::IntArgument::GetMultiValue (size_t index) const {
    return (*store_values)[index];
}

size_t ArgumentParser::ArgParser::IntArgument::GetSize () const {
    return (*store_values).size();
}

size_t ArgumentParser::ArgParser::IntArgument::GetMinArgsCount () const {
    return min_args_count;
}

bool ArgumentParser::ArgParser::IntArgument::GetPositional() const {
    return is_positional;
}

const std::string& ArgumentParser::ArgParser::IntArgument::GetHelpInfo() const {
    return help_info;
}

bool ArgumentParser::ArgParser::IntArgument::IsValue() const{
    return is_value;
}

void ArgumentParser::ArgParser::IntArgument::WriteValue (int argument) {
    is_value = true;
    if (is_multi_value) {
        (*store_values).push_back(argument);

        return;
    }
    value = argument;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::IntArgument::MultiValue() {
    is_multi_value = true;

    return *this;
}
ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::IntArgument::MultiValue(size_t minimum) {
    is_multi_value = true;
    min_args_count = minimum;

    return *this;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::IntArgument::Positional() {
    is_positional = true;

    return *this;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::IntArgument::Default(int argument) {
    WriteValue(argument);

    return *this;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::IntArgument::StoreValues (std::vector<int>& store) {
    store_values = &store;

    return *this;
}
