#include "FlagArguments.h"

ArgumentParser::ArgParser::FlagArgument::FlagArgument(const std::string& name): name(name) {}

ArgumentParser::ArgParser::FlagArgument::FlagArgument(const std::string& name, char short_name)
        : name(name)
        , short_name(short_name) {}

ArgumentParser::ArgParser::FlagArgument::FlagArgument(const std::string& name, const std::string& info)
        : name(name)
        , help_info(info) {}

ArgumentParser::ArgParser::FlagArgument::FlagArgument(const std::string& name, char short_name, const std::string& info)
        : name(name)
        , short_name(short_name)
        , help_info(info) {}

const std::string& ArgumentParser::ArgParser::FlagArgument::GetName () const {
    return name;
}

char ArgumentParser::ArgParser::FlagArgument::GetShortName () const {
    return short_name;
}

bool ArgumentParser::ArgParser::FlagArgument::GetValue () const {
    return *store_value;
}

const std::string& ArgumentParser::ArgParser::FlagArgument::GetHelpInfo() const {
    return help_info;
}

bool ArgumentParser::ArgParser::FlagArgument::IsDefault () const {
    return is_default;
}

void ArgumentParser::ArgParser::FlagArgument::WriteValue () {
    *store_value = true;
}

ArgumentParser::ArgParser::FlagArgument& ArgumentParser::ArgParser::FlagArgument::Default(bool argument) {
    is_default = true;
    *store_value = argument;

    return *this;
}

ArgumentParser::ArgParser::FlagArgument& ArgumentParser::ArgParser::FlagArgument::StoreValue (bool& store) {
    store_value = &store;

    return *this;
}
