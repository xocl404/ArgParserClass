#ifndef LABWORK4_FLAGARGUMENTS_H
#define LABWORK4_FLAGARGUMENTS_H

#include "ArgParser.h"

class ArgumentParser::ArgParser::FlagArgument {
private:
    std::string name;
    char short_name = ' ';
    bool value = false;
    bool* store_value = &value;
    bool is_default = false;
    std::string help_info = " ";
public:
    FlagArgument(const std::string& name);
    FlagArgument(const std::string& name, char short_name);
    FlagArgument(const std::string& name, char short_name, const std::string& info);
    FlagArgument(const std::string& name, const std::string& info);
    const std::string& GetName () const;
    char GetShortName () const;
    bool GetValue () const;
    const std::string& GetHelpInfo() const;
    bool IsDefault () const;
    void WriteValue ();
    FlagArgument& Default (bool argument);
    FlagArgument& StoreValue (bool& store);
};

#endif //LABWORK4_FLAGARGUMENTS_H
