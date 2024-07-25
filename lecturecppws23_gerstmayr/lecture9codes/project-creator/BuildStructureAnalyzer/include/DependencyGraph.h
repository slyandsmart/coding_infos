#pragma once

#include <vector>
#include <string>
#include <map>
#include <ostream>
#include <filesystem>
#include <utility>

namespace BuildStructureAnalyzer
{

using Path = std::filesystem::path;

using Source = Path;
using Sources = std::vector<Source>;

using Flag = std::pair<std::string, std::string>;
using Flags = std::vector<Flag>;

using LinkLibrary = std::pair<std::string, std::string>;
using LinkLibraries = std::vector<LinkLibrary>;

using TargetName = std::string;
using TargetType = std::string;
using OutputName = std::string;

using IncludeDir = std::string;
using IncludeDirs = std::vector<IncludeDir>;

struct Target
{
    std::map<std::string, std::vector<std::string>> properties;

    std::vector<std::string> getProperty(const std::string&);
    void addProperty(const std::string&, const std::string&);
    void addProperty(const std::string&, const std::vector<std::string>&);
};

struct Library : public Target
{

    enum class Output_t
    {
        OBJECT_lib,
        STATIC_lib,
        SHARED_lib
    };

    Output_t lib_out_t;

    void setOutputType(const Output_t &);
    Output_t &getOutputType();
    const Output_t &getOutputType() const;
};

using Libraries = std::vector<Library>;

struct Executable : public Target
{
};

using Executables = std::vector<Executable>;

struct DependencyGraph
{
    Libraries libs_vec;
    Executables exec_vec;

    bool empty();

    void addLibraries(const Library &);
    Libraries &getLibraries();
    const Libraries &getLibraries() const;

    void addExecutables(const Executable &);
    Executables &getExecutables();
    const Executables &getExecutables() const;
};

} // end namespace BuildStructureAnalyzer

std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Flag &f);
std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Flags &f);
std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Target &t);
std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Library::Output_t &t);
std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Library &l);
std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Executable &e);
std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::DependencyGraph &d);
