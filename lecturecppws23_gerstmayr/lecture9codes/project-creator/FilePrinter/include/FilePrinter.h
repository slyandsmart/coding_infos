#pragma once

#include <string>
#include <filesystem>

namespace Fileprinter {

  struct FilePrinter {

      void printProject(const std::string& project_name, const std::string& module_name = "");
      void printModule(const std::string& module_name);
      void printCMakeInterceptionScript(const std::string& dir, const std::string& code_sub_dir);

  private:

      void printMainCMakeLists(const std::string& project_name);
      void createFolder(const std::string& dir_name);
      void printBinCreateScript();
      void printLibCreate();
      void printScriptCMakeLists();
      void printGtestFiles();
      void printMacroScript();
      void printCMakeScriptFiles();
      void printSharedLibUtils();
      void printModuleCMakeLists(const std::string& module_name);
      void printModuleInitHeader(const std::string& module_name);
      void printModuleInitCPP(const std::string& module_name);
      void printModuleInitTest(const std::string& module_name);

      bool checkFolderExistence(const std::string& dir_name);
      bool checkFileExistence(const std::string& file_name);
  };

} // end namespace FilePrinter
