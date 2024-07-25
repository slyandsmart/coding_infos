#pragma once

#include <string>

namespace BuildStructureAnalyzer {

struct CMakeGraphvizOutputCreator {

private:

	const std::string target_dir_name;
	const std::string output_dir_name;
	const std::string output_file_name;

public:

	CMakeGraphvizOutputCreator() = delete;

	CMakeGraphvizOutputCreator(const std::string& s, const std::string& t = "", const std::string& u = "cmake_structure") :
			target_dir_name(s), output_dir_name(t), output_file_name(u)  {}

	void operator()();

};

} // end namespace BuildStructureAnalyzer