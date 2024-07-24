#include <gtest/gtest.h>

#include <CMakeGraphvizOutputCreator.h>

using namespace BuildStructureAnalyzer;

const std::string test_file_dir = "test_files";

TEST(CMakeGraphvizOutputCreator, Basic) {

	const std::string cmake_test_folder_name = test_file_dir + "/Basic";

    CMakeGraphvizOutputCreator c(cmake_test_folder_name, cmake_test_folder_name);
    c();

}