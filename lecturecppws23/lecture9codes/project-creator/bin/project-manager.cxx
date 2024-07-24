
#include <boost/program_options.hpp>
#include <string>

#include <FilePrinter.h>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, const char* argv[]) {

    std::string project_name, module_name;

    po::options_description desc("Allowed options:");
    desc.add_options()
            ("help", "produce help message")
            ("project,p", po::value<std::string>(&project_name), "name of the project")
            ("module,m", po::value<std::string>(&module_name), "name of the module")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    Fileprinter::FilePrinter fp;

    if (!project_name.empty()) {
        // we need to create a new project
        fp.printProject(project_name, module_name);
    } else if (!module_name.empty()) {
        // we need to create a module
        fp.printModule(module_name);
    } else {
        std::cout << "no options are given, program doesn't know what to do....\n";
    }

    return EXIT_SUCCESS;
}