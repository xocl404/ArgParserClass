#ifndef LABWORK4_STRINGARGUMENTS_H
#define LABWORK4_STRINGARGUMENTS_H

#include "ArgParser.h"

class ArgumentParser::ArgParser::StringArgument {
private:
    std::string name;
    char short_name = ' ';
    std::string value = "=";
    std::vector<std::string> values;
    std::string* store_value = &value;
    bool is_value = false;
    size_t min_args_count = 0;
    bool is_multi_value = false;
    std::string help_info = " ";
public:
    StringArgument(const std::string& name);
    StringArgument(const std::string& name, char short_name);
    StringArgument(const std::string& name, const std::string& info);
    StringArgument(const std::string& name, char short_name, const std::string& info);
    const std::string& GetName () const;
    char GetShortName () const;
    const std::string& GetValue () const;
    const std::string& GetMultiValue (size_t index) const;
    size_t GetSize () const;
    size_t GetMinArgsCount () const;
    const std::string& GetHelpInfo() const;
    bool IsValue () const;
    void WriteValue (const std::string& argument);
    StringArgument& MultiValue ();
    StringArgument& MultiValue (size_t minimum);
    StringArgument& Default (const std::string& argument);
    StringArgument& StoreValue (std::string& store);
};

#endif //LABWORK4_STRINGARGUMENTS_H
