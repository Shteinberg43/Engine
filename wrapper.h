#pragma once
#include <map>
#include <functional>
#include <string>
#include <iostream>

using ArgsMap = std::map<std::string, std::string>;

class Wrapper {
public:
	template<typename Subject>
	Wrapper(Subject* subject, std::string(Subject::* method)(const ArgsMap&), const ArgsMap& default_args) {
		defaultArgs = default_args;
		function = [subject, method](const ArgsMap& args) {
			return (subject->*method)(args);
			};
	}

	std::string execute(const ArgsMap& args_map) {
		if (args_map.size() != defaultArgs.size()) {
			std::cerr << "ERROR: Wrong number of arguments." << std::endl;
			return {};
		}

		ArgsMap mergedArgs = defaultArgs;
		for (const auto& pair : args_map) {
			mergedArgs[pair.first] = pair.second;
		}
		return function(mergedArgs);
	}

private:
	std::function<std::string(const ArgsMap&)> function;
	ArgsMap defaultArgs;
};
