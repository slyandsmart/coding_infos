#include <gtest/gtest.h>

#include <DependencyFileParser.h>

using namespace BuildStructureAnalyzer;

TEST(DependencyFileParser, Basic)
{

}

TEST(DependencyFileParser, Target)
{
    Path input_file_path("test_files/test_target.dat");
    auto res = DependencyFileParser().parseJSON(input_file_path);

    std::cout << "this is a result :\n" << res << "\n";
}