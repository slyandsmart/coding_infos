#include <gtest/gtest.h>

#include <CMakeInputFilesAnalyzer.h>

using namespace BuildStructureAnalyzer;

TEST(CMakeInputFilesAnalyzer, Basic) {
    CMakeInputFilesAnalyzer a;
    a("test_files/Basic");

    // check the output
    std::cout << a.g << std::endl;

}
