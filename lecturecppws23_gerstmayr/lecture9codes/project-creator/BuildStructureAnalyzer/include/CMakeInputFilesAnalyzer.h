#pragma once

#include <string>
#include <filesystem>

#include <DependencyGraph.h>

namespace BuildStructureAnalyzer {

struct CMakeInputFilesAnalyzer {

    DependencyGraph g;
    void operator()(const std::filesystem::path&);

};

} // end namespace BuildStructureAnalyzer   