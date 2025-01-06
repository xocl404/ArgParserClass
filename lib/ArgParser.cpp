#include "ArgParser.h"
#include "StringArguments.h"
#include "IntArguments.h"
#include "FlagArguments.h"

std::vector<std::string> ArgumentParser::ArgParser::ToString (int argc, char** argv) {
    std::vector<std::string> arguments;
    for (int i = 1; i < argc; ++i) {
        std::string str;
        for (int j = 0; j < strlen(argv[i]); ++j) {
            str.push_back(argv[i][j]);
        }
        arguments.push_back(str);
    }

    return arguments;
};

bool ArgumentParser::ArgParser::IsDigit(const std::string &str) {
    for (int i = 0; i < str.length(); ++i) {
        if (static_cast<int>(str[i]) < 48 || static_cast<int>(str[i]) > 57) {
            return false;
        }
    }

    return true;
}

ArgumentParser::ArgParser::ArgParser(const std::string& name): name(name) {}

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& arguments) {
    if (arguments[0] != "app") {
        return false;
    }

    if (!flag_arguments.empty()) {
        for (int i = 1; i < arguments.size(); ++i) {
            if (arguments[i][1] == '-') {
                std::string arg_name = arguments[i].substr(2);
                for (int j = 0; j < flag_arguments.size(); ++j) {
                    if (flag_arguments[j]->GetName() == arg_name) {
                        flag_arguments[j]->WriteValue();
                        break;
                    }
                }
            } else {
                for (int l = 1; l < arguments[i].size(); ++l) {
                    for (int j = 0; j < flag_arguments.size(); ++j) {
                        if (flag_arguments[j]->GetShortName() == arguments[i][l]) {
                            flag_arguments[j]->WriteValue();
                            break;
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i < arguments.size(); ++i) {
        if (IsDigit(arguments[i])) {
            for (int j = 0; j < int_arguments.size(); ++j) {
                if (int_arguments[j]->GetPositional()) {
                    int_arguments[j]->WriteValue(std::stoi(arguments[i]));
                }
            }

            continue;
        }
        size_t pos = arguments[i].find('=');
        if (arguments[i][1] == '-') {
            std::string arg_name = arguments[i].substr(2, pos - 2);
            std::string arg = arguments[i].substr(pos + 1);
            for (int j = 0; j < string_arguments.size(); ++j) {
                if (string_arguments[j]->GetName() == arg_name) {
                    string_arguments[j]->WriteValue(arg);
                    break;
                }
            }
            for (int j = 0; j < int_arguments.size(); ++j) {
                if (int_arguments[j]->GetName() == arg_name) {
                    int_arguments[j]->WriteValue(std::stoi(arg));
                    break;
                }
            }
        } else {
            char arg_name = arguments[i][1];
            std::string arg = arguments[i].substr(pos + 1);
            for (int j = 0; j < string_arguments.size(); ++j) {
                if (string_arguments[j]->GetShortName() == arg_name) {
                    string_arguments[j]->WriteValue(arg);
                    break;
                }
            }
            for (int j = 0; j < int_arguments.size(); ++j) {
                if (int_arguments[j]->GetShortName() == arg_name) {
                    int_arguments[j]->WriteValue(std::stoi(arg));
                    break;
                }
            }
        }
    }

    if (help_name != " " || short_help_name != ' ') {
        for (int i = 1; i < arguments.size(); ++i) {
            if (arguments[i][1] == '-') {
                std::string arg_name = arguments[i].substr(2);
                if (help_name == arg_name) {
                    is_help = true;
                }
            } else {
                if (short_help_name == arguments[i][1]) {
                    is_help = true;
                }
            }
        }
        if (is_help) {
            return true;
        }
    }

    for (int i = 0; i < string_arguments.size(); ++i) {
        if (string_arguments[i]->GetMinArgsCount() > string_arguments[i]->GetSize() || !string_arguments[i]->IsValue()) {
            return false;
        }
    }

    for (int i = 0; i < int_arguments.size(); ++i) {
        if (int_arguments[i]->GetMinArgsCount() > int_arguments[i]->GetSize() || !int_arguments[i]->IsValue()) {
            return false;
        }
    }

    return true;
}

bool ArgumentParser::ArgParser::Parse (int argc, char** argv) {
    return Parse(ToString(argc, argv));
}

ArgumentParser::ArgParser& ArgumentParser::ArgParser::AddHelp(char short_name, const std::string& long_name, const std::string& info) {
    short_help_name = short_name;
    help_name = long_name;
    help_info = info;

    return *this;
}

bool ArgumentParser::ArgParser::Help() {
    return is_help;
}

std::string ArgumentParser::ArgParser::HelpDescription() const {
    std::string info = name + "\n" + help_info + "\n\n";
    for (int i = 0; i < string_arguments.size(); ++i) {
        if (string_arguments[i]->GetShortName() != ' ') {
            info.push_back('-');
            info.push_back(string_arguments[i]->GetShortName());
            info.push_back(',');
        } else {
            info += "   ";
        }
        info += "  --" + string_arguments[i]->GetName() + "=<string>,  " + string_arguments[i]->GetHelpInfo();
        if (string_arguments[i]->IsValue()) {
            info +=  " [default = " + string_arguments[i]->GetValue();
            info.push_back(']');
        }
        if (string_arguments[i]->GetMinArgsCount() != 0) {
            info += " [min args = ";
            info += std::to_string(string_arguments[i]->GetMinArgsCount());
            info.push_back(']');
        }
        info += "\n";
    }
    for (int i = 0; i < flag_arguments.size(); ++i) {
        if (flag_arguments[i]->GetShortName() != ' ') {
            info.push_back('-');
            info.push_back(flag_arguments[i]->GetShortName());
            info.push_back(',');
        } else {
            info += "   ";
        }
        info += "  --" + flag_arguments[i]->GetName() + ",  " + flag_arguments[i]->GetHelpInfo();
        if (flag_arguments[i]->IsDefault()) {
            info +=  " [default = ";
            if (flag_arguments[i]->GetValue()) {
                info += "true]";
            } else {
                info += "false]";
            }
        }
        info += "\n";
    }
    for (int i = 0; i < int_arguments.size(); ++i) {
        if (int_arguments[i]->GetShortName() != ' ') {
            info.push_back('-');
            info.push_back(int_arguments[i]->GetShortName());
            info.push_back(',');
        } else {
            info += "   ";
        }
        info += "  --" + int_arguments[i]->GetName() + "=<int>,  " + int_arguments[i]->GetHelpInfo();
        if (int_arguments[i]->IsValue()) {
            info +=  " [default = " + std::to_string(int_arguments[i]->GetValue());
            info.push_back(']');
        }
        if (int_arguments[i]->GetMinArgsCount() != 0) {
            info += " [min args = ";
            info += std::to_string(int_arguments[i]->GetMinArgsCount());
            info.push_back(']');
        }
        info += "\n";
    }
    info += "\n";
    if (short_help_name != ' ') {
        info.push_back('-');
        info.push_back(short_help_name);
        info.push_back(',');
    } else {
        info += "   ";
    }
    info += "  --" + help_name + "\n";

    return info;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument (const std::string& arg_name) {
    ArgumentParser::ArgParser::StringArgument* arg = new ArgumentParser::ArgParser::StringArgument (arg_name);
    string_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument (char short_arg_name,
        const std::string& arg_name) {
    ArgumentParser::ArgParser::StringArgument* arg = new ArgumentParser::ArgParser::StringArgument (arg_name,
        short_arg_name);
    string_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument (const std::string& arg_name,
        const std::string& help) {
    ArgumentParser::ArgParser::StringArgument* arg = new ArgumentParser::ArgParser::StringArgument (arg_name,help);
    string_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::StringArgument& ArgumentParser::ArgParser::AddStringArgument (char short_arg_name,
        const std::string& arg_name, const std::string& help) {
    ArgumentParser::ArgParser::StringArgument* arg = new ArgumentParser::ArgParser::StringArgument (arg_name,
        short_arg_name, help);
    string_arguments.push_back(arg);

    return *arg;
}

const std::string& ArgumentParser::ArgParser::GetStringValue(const std::string& arg_name) const {
    for (int i = 0; i < string_arguments.size(); ++i) {
        if (string_arguments[i]->GetName() == arg_name) {
            return string_arguments[i]->GetValue();
        }
    }
}

const std::string& ArgumentParser::ArgParser::GetStringValue(const std::string& arg_name, int index) const {
    for (int i = 0; i < string_arguments.size(); ++i) {
        if (string_arguments[i]->GetName() == arg_name) {
            return string_arguments[i]->GetMultiValue(index);
        }
    }
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument (const std::string& arg_name) {
    ArgumentParser::ArgParser::IntArgument* arg = new ArgumentParser::ArgParser::IntArgument (arg_name);
    int_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument (char short_arg_name, const std::string& arg_name) {
    ArgumentParser::ArgParser::IntArgument* arg = new ArgumentParser::ArgParser::IntArgument (arg_name, short_arg_name);
    int_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument (const std::string& arg_name,
        const std::string& help) {
    ArgumentParser::ArgParser::IntArgument* arg = new ArgumentParser::ArgParser::IntArgument (arg_name,help);
    int_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::IntArgument& ArgumentParser::ArgParser::AddIntArgument (char short_arg_name, const std::string& arg_name,
        const std::string& help) {
    ArgumentParser::ArgParser::IntArgument* arg = new ArgumentParser::ArgParser::IntArgument (arg_name,
        short_arg_name, help);
    int_arguments.push_back(arg);

    return *arg;
}

int ArgumentParser::ArgParser::GetIntValue(const std::string& arg_name) const {
    for (int i = 0; i < int_arguments.size(); ++i) {
        if (int_arguments[i]->GetName() == arg_name) {
            return int_arguments[i]->GetValue();
        }
    }
}

int ArgumentParser::ArgParser::GetIntValue(const std::string& arg_name, int index) const {
    for (int i = 0; i < int_arguments.size(); ++i) {
        if (int_arguments[i]->GetName() == arg_name) {
            return int_arguments[i]->GetMultiValue(index);
        }
    }
}

ArgumentParser::ArgParser::FlagArgument& ArgumentParser::ArgParser::AddFlag (const std::string& arg_name) {
    ArgumentParser::ArgParser::FlagArgument* arg = new ArgumentParser::ArgParser::FlagArgument (arg_name);
    flag_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::FlagArgument& ArgumentParser::ArgParser::AddFlag (char short_arg_name, const std::string& arg_name) {
    ArgumentParser::ArgParser::FlagArgument* arg = new ArgumentParser::ArgParser::FlagArgument (arg_name,
        short_arg_name);
    flag_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::FlagArgument& ArgumentParser::ArgParser::AddFlag (const std::string& arg_name, const std::string& help) {
    ArgumentParser::ArgParser::FlagArgument* arg = new ArgumentParser::ArgParser::FlagArgument (arg_name,help);
    flag_arguments.push_back(arg);

    return *arg;
}

ArgumentParser::ArgParser::FlagArgument& ArgumentParser::ArgParser::AddFlag (char short_arg_name, const std::string& arg_name,
        const std::string& help) {
    ArgumentParser::ArgParser::FlagArgument* arg = new ArgumentParser::ArgParser::FlagArgument (arg_name,
        short_arg_name, help);
    flag_arguments.push_back(arg);

    return *arg;
}

bool ArgumentParser::ArgParser::GetFlag (const std::string& arg_name) const {
    for (int i = 0; i < flag_arguments.size(); ++i) {
        if (flag_arguments[i]->GetName() == arg_name) {
            return flag_arguments[i]->GetValue();
        }
    }
}

ArgumentParser::ArgParser::~ArgParser() {
    for (int i = 0; i < string_arguments.size(); ++i) {
        delete string_arguments[i];
    }
    for (int i = 0; i < int_arguments.size(); ++i) {
        delete int_arguments[i];
    }
    for (int i = 0; i < flag_arguments.size(); ++i) {
        delete flag_arguments[i];
    }
}
