#include <DependencyGraph.h>

using namespace BuildStructureAnalyzer;

// Target implementation
std::vector<std::string> Target::getProperty(const std::string &p)
{
    return properties[p];
}

void Target::addProperty(const std::string &p, const std::string &val)
{
    properties[p].push_back(val);
}

void Target::addProperty(const std::string &p, const std::vector<std::string> &val)
{
    for(const auto& elem : val)
    {
        addProperty(p,elem);
    }
}

// Library implementation

void Library::setOutputType(const Library::Output_t &t)
{
    lib_out_t = t;
}

Library::Output_t &Library::getOutputType()
{
    return lib_out_t;
}

const Library::Output_t &Library::getOutputType() const
{
    return lib_out_t;
}

bool DependencyGraph::empty()
{
    return libs_vec.empty() && exec_vec.empty();
}

void DependencyGraph::addLibraries(const Library &l)
{
    libs_vec.push_back(l);
}

Libraries &DependencyGraph::getLibraries()
{
    return libs_vec;
}

const Libraries &DependencyGraph::getLibraries() const
{
    return libs_vec;
}

void DependencyGraph::addExecutables(const Executable &e)
{
    exec_vec.push_back(e);
}

Executables &DependencyGraph::getExecutables()
{
    return exec_vec;
}

const Executables &DependencyGraph::getExecutables() const
{
    return exec_vec;
}

std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Flag &f)
{
    o << std::get<0>(f) << " : " << std::get<1>(f);
    return o;
}

std::ostream &operator<<(std::ostream &o, const BuildStructureAnalyzer::Flags &f)
{
    for (const auto &flag : f)
    {
        o << "\"" << std::get<0>(flag) << " : " << std::get<1>(flag) << "\"";
    }
    return o;
}

std::ostream &operator<<(std::ostream &o, const Target &t)
{
    for(const auto& elem : t.properties)
    {
        const auto& target_name = elem.first;
        const auto& target_values = elem.second;

        o << target_name << " : [";
        for(const auto& prop : target_values)
        {
            o << prop << ", ";
        }
        o << "]" << std::endl;
    }

    return o;
}

std::ostream &operator<<(std::ostream &o, const Library::Output_t &t)
{
    switch (t)
    {
    case Library::Output_t::OBJECT_lib:
        return o << "OBJECT";
    case Library::Output_t::SHARED_lib:
        return o << "SHARED";
    case Library::Output_t::STATIC_lib:
        return o << "STATIC";
    }

    return o;
}

std::ostream &operator<<(std::ostream &o, const Library &l)
{
    o << "Library : " << std::endl;
    o << std::endl;

    const Target tmp = l;
    o << tmp << std::endl;

    return o;
}

std::ostream &operator<<(std::ostream &o, const Executable &e)
{
    o << "Executable : " << std::endl;
    o << std::endl;

    const Target tmp = e;
    o << tmp << std::endl;

    return o;
}

std::ostream &operator<<(std::ostream &o, const DependencyGraph &d)
{
    o << "DependencyGraph : " << std::endl;
    o << std::endl;

    o << "Libraries :" << std::endl;
    o << std::endl;

    for (const auto &lib : d.getLibraries())
    {
        o << lib << std::endl;
    }
    o << std::endl;

    o << "Executables:" << std::endl;
    o << std::endl;
    for (const auto &exe : d.getExecutables())
    {
        o << exe << std::endl;
    }
    o << std::endl;

    return o;
}
