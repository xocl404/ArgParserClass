#ifndef LABWORK4_INTARGUMENTS_H
#define LABWORK4_INTARGUMENTS_H

#include "ArgParser.h"

class ArgumentParser::ArgParser::IntArgument {
private:
    std::string name;
    char short_name = ' ';
    int value;
    bool is_value = false;
    std::vector<int> values;
    std::vector<int>* store_values = &values;
    size_t min_args_count = 0;
    bool is_multi_value = false;
    bool is_positional = false;
    std::string help_info = " ";
public:
    IntArgument(const std::string& name);
    IntArgument(const std::string& name, char short_name);
    IntArgument(const std::string& name, const std::string& info);
    IntArgument(const std::string& name, char short_name, const std::string& info);
    const std::string& GetName () const;
    char GetShortName () const;
    int GetValue () const;
    int GetMultiValue (size_t index) const;
    size_t GetSize () const;
    size_t GetMinArgsCount () const;
    bool GetPositional() const;
    const std::string& GetHelpInfo() const;
    bool IsValue() const;
    void WriteValue (int argument);
    IntArgument& MultiValue();
    IntArgument& MultiValue(size_t minimum);
    IntArgument& Positional();
    IntArgument& Default(int argument);
    IntArgument& StoreValues (std::vector<int>& store);
};

#endif //LABWORK4_INTARGUMENTS_H
