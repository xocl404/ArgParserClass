#pragma once
#include <vector>
#include <string>
#include <cstring>

namespace ArgumentParser {
    class ArgParser {
    private:
        class StringArgument;
        class IntArgument;
        class FlagArgument;

        std::string name;
        std::string help_name = " ";
        char short_help_name = ' ';
        std::string help_info = " ";
        bool is_help = false;
        std::vector<StringArgument*> string_arguments;
        std::vector<IntArgument*> int_arguments;
        std::vector<FlagArgument*> flag_arguments;
        std::vector<std::string> ToString (int argc, char** argv);
        bool IsDigit (const std::string& str);
    public:
        ArgParser (const std::string& name);
        bool Parse (const std::vector<std::string>& arguments);
        bool Parse (int argc, char** argv);
        ArgParser& AddHelp (char short_name, const std::string& long_name, const std::string& info);
        bool Help();
        std::string HelpDescription () const;
        StringArgument& AddStringArgument (const std::string& arg_name);
        StringArgument& AddStringArgument (char short_arg_name, const std::string& arg_name);
        StringArgument& AddStringArgument (const std::string& arg_name, const std::string& info);
        StringArgument& AddStringArgument (char short_arg_name, const std::string& arg_name, const std::string& info);
        const std::string& GetStringValue(const std::string& arg_name) const;
        const std::string& GetStringValue(const std::string& arg_name, int index) const;
        IntArgument& AddIntArgument (const std::string& arg_name);
        IntArgument& AddIntArgument (char short_arg_name, const std::string& arg_name);
        IntArgument& AddIntArgument (const std::string& arg_name, const std::string& info);
        IntArgument& AddIntArgument (char short_arg_name, const std::string& arg_name, const std::string& info);
        int GetIntValue(const std::string& arg_name) const;
        int GetIntValue(const std::string& arg_name, int index) const;
        FlagArgument& AddFlag (const std::string& arg_name);
        FlagArgument& AddFlag(char short_arg_name, const std::string& arg_name);
        FlagArgument& AddFlag(const std::string& arg_name, const std::string& info);
        FlagArgument& AddFlag(char short_arg_name, const std::string& arg_name, const std::string& info);
        bool GetFlag (const std::string& arg_name) const;
        ~ArgParser();
    };
} // namespace ArgumentParser
