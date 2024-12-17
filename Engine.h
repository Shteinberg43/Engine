#pragma once
#include "wrapper.h"

class Engine {
public:
    void register_command(const std::string& name, Wrapper* wrapper) {
        commands[name] = wrapper;
    };
    std::string execute(const std::string& name, const  ArgsMap& args) {
        if (commands.find(name) != commands.end()) {
            return commands[name]->execute(args);
        }
        return "Command not found";

    };

private:
    std::map<std::string, Wrapper*> commands;
};
