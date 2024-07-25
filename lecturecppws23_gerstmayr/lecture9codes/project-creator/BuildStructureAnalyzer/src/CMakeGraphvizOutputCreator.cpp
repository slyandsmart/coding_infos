#include <CMakeGraphvizOutputCreator.h>

#include <iostream>
#include <sys/stat.h>

using namespace BuildStructureAnalyzer;

inline bool exists(const std::string &name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void CMakeGraphvizOutputCreator::operator()()
{

	// ************************
	// create the graphviz file
	// ************************

	// create the file names
	std::string output_name;
	std::string command;

	const std::string output_name_ext = output_file_name + ".dot";

	if (output_dir_name != "")
	{
		output_name = output_dir_name + "/" + output_name_ext;
		command = "cd " + output_dir_name + " && cmake --graphviz=" + output_name_ext + " . ";
	}
	else
	{
		output_name = output_name_ext;
		command = "cmake --graphviz=" + output_name_ext + " . ";
	}

	// execute the command
	std::cout << "command : " << command << std::endl;
	auto res = system(command.c_str());

	// check if the call was ok and the output file exists
	if (res != 0)
	{
		std::cerr << "CMakeGraphvizOutputCreator : " << res << " return from system-call!\n";
		exit(1);
	}

	if (!exists(output_name))
	{
		std::cerr << "CMakeGraphvizOutputCreator : file " << output_name << " has not been created!\n";
		exit(1);
	}
}