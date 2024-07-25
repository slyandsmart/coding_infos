#include <fstream>
#include <iostream>
#include <filesystem>
#include <cassert>

#include <nlohmann/json.hpp>

#include <DependencyFileParser.h>
#include <DependencyGraph.h>
#include <CMakeProperties.h>



using Json = nlohmann::json;
namespace fs = std::filesystem;
using namespace BuildStructureAnalyzer;

void parseTargetElement(const Json &j, Target &res, const std::string& property)
{
    // get target_name
    if (j.contains(property))
    {
        if (j[property].size() == 1)
        {
            res.addProperty(property, j[property][0].get<std::string>());
        }
        else
        {
            res.addProperty(property, j[property].get<std::vector<std::string>>());            
        }
    }
}

void parseTargetElements(const Json &j, Target &res)
{
   for(const auto& property : CMakeProperties::p)
   {
       parseTargetElement(j, res, property);
   }
}

Target parseNewTarget(const Json &j)
{
    // get info from json file
    Target res;
    parseTargetElements(j, res);
    return res;
}

void parseTarget(const Json &j, Target &res)
{
    parseTargetElements(j, res);
}

Target parseNewTarget(const Path &p)
{
    // load the file
    std::ifstream stream(p);
    auto j = Json::parse(stream);

    auto res = parseNewTarget(j);

    stream.close();

    return res;
}

void parseLibrary(const Json &j, Library &lib)
{
    // parse the Target
    parseTarget(j, lib);

    // parse Library specific stuff
    if (lib.properties["TYPE"][0] == "SHARED_LIBRARY")
    {
        lib.setOutputType(Library::Output_t::SHARED_lib);
    }
    else if (lib.properties["TYPE"][0] == "STATIC_LIBRARY")
    {
        lib.setOutputType(Library::Output_t::STATIC_lib);
    }
    else if (lib.properties["TYPE"][0] == "OBJECT_LIBRARY")
    {
        lib.setOutputType(Library::Output_t::OBJECT_lib);
    }
}

Library parseNewLibrary(const Json &j)
{
    // create temporary Library entry
    Library res;
    parseLibrary(j, res);
    return res;
}

void parseExecutable(const Json &j, Executable &exe)
{
    // parse the rest of the Target
    parseTarget(j, exe);
}

Executable parseNewExecutable(const Json &j)
{
    // create temporary Executable entry
    Executable res;
    parseExecutable(j, res);
    return res;
}

DependencyGraph DependencyFileParser::parseJSON(const Path &p)
{
    DependencyGraph res;

    // lookup json files
    for (const auto &p : fs::directory_iterator(p))
    {
        if (p.path().extension() != ".dat")
            continue;

        // open file
        std::ifstream in(p.path());

        auto j = Json::parse(in);

        // check type and call function
        auto type = j["TYPE"][0].get<std::string>();
        if (type == "EXECUTABLE")
        {
            auto exe = parseNewExecutable(j);
            res.addExecutables(exe);
        }
        else
        {
            auto lib = parseNewLibrary(j);
            res.addLibraries(lib);
        }
    }

    return res;
}
