#include <CMakeInputFilesAnalyzer.h>

#include <sys/stat.h>

#include <iostream>
#include <string>
#include <algorithm>

#include <FilePrinter.h>
#include <DependencyFileParser.h>

using namespace BuildStructureAnalyzer;
using namespace Fileprinter;

namespace fs = std::filesystem;

std::string random_string( size_t length ) {
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ std::rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

std::string createUniqueFolderName() {
    
    bool found = false;
    std::string result;

    while(!found) {

        auto tmp_str = random_string(10);
        fs::path folder(tmp_str);

        if(!fs::exists(folder)) {
            found = true;
            result = tmp_str;
        }
    }

    return result;
}

void CMakeInputFilesAnalyzer::operator()(const fs::path& dir) {

    // create new testing foldername
    fs::path folder(createUniqueFolderName());
    fs::path code_folder ("code");

    // create new testing folder
    if(!fs::create_directories(folder)) {
        std::cout << "Test directory can't be created. Aborting!\n";
        return;
    };

    if(!fs::create_directories(folder / code_folder)) {
        std::cout << "Test directory can't be created. Aborting!\n";
        return;
    };

    // copy all code elements
    fs::copy(dir, folder / code_folder, fs::copy_options::overwrite_existing | fs::copy_options::recursive);

    // create CMake-interception-function-file
    FilePrinter fp;
    fp.printCMakeInterceptionScript(folder, "code");

    // run intercepted CMake script
    std::string command =   "cd " + folder.string() + " && "
                            "cmake -Wno-dev . && cd -";

    auto res = system(command.c_str());

	// check if the call was ok and the output file exists
	if (res != 0) {
		std::cerr << "CMakeGraphvizOutputCreator : " << res << " return from system-call!\n";
		return;
	}

    // read the stored data and create structure graph
    g = DependencyFileParser::parseJSON(folder / fs::path("results"));
    
    // cleanup
    // fs::remove_all(folder);
}