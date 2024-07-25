#pragma once

#include <filesystem>

#include <DependencyGraph.h>

namespace BuildStructureAnalyzer
{

struct DependencyFileParser
{
    static DependencyGraph parseJSON(const Path &);
};

} // end namespace BuildStructureAnalyzer