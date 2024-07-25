# project-creator

Oh yeah.
There it is.
The magical tool, which makes it easy for non-computer-scientists to create projects in C/C++ without hesitating with compiler calls and/or `make` files.
This tool gives you the opportunity to create new projects and modify existing projects created with this tool.

## Introduction

The **project-creator** is intended to create new projects with an already
existing CMake structure.
A second option is to extend the existing project by some new modules.

When a new project is created, the **project-creator** is creating a `CMakeLists.txt` file in the root folder and a folder called `cmake` including a bunch of files including cmake-macros and code, helping to integrate other projects (GTest).

The main `CMakeLists.txt` in the root folder is responsible for all general project properties.
Inside this file we can manually add linking-libraries for the whole project, add and/or demand for already existing libraries and change much more.
There is already an existing example on how to include a package from an other source (GTest) and one example on how to demand for an existing package (Boost).

Further it gives the opportunity to add individual compiler- and linker-flags to the compiler used in the project.

The next important thing is, that all sub-folders beginning with a capital letter will be recognized as `Module`.
All files ending with `.h`, `.hpp`, `.def` or `.inc` inside the `Module/include` will be made globally visible inside the project.
This means that you can include each header file `header.h` with this style `#include <header.h>`.

Each of these folders will be called with `add_subfolder()`.
This will invoke the `CmakeLists.txt` of the subfolder.

Each of these `Module/CmakeLists.txt` can be modified.
At the beginning of these files we can add specific linker flags to the `module_link_libs` variable.
All source files ending with `.c` or `.cpp` inside the `Module/src` folder and all header files inside the `Module/include` will compiled together to a module library.
There will be a shared library called **libModule.so** and a static library named **libModule_static.a**.
The next thing happening is, that all files inside the `Module/test/test_files` folder are copied to the build folder.
This is done, so no original file will be modified.
Each test inside the `Module/test/` folder will have access to the copied files.
In the end for each file ending with `.cc` inside the `Module/test` folder an executable is created which is automatically linked to `-lgtest` and the module library `-lModule`.

At the end of the main `CmakeLists.txt` file two macros are called:
- `lib_create()`
- `bin_create()`

`lib_create()` will make a shared and static library out of all libraries in the
modules.
These libraries are linked to all components given by `${GLOBAL_LINKING_FLAGS}`.
This library is then put in a `lib` folder inside the build folder.

`bin_create()` will create an executable out of all files ending with `.cpp`
or `.cxx`inside the `bin` folder. Each executable will be linked automatically
to the main library inside the `lib` folder and the flags defined in `${GLOBAL_LINKING_FLAGS}`.

The **project-creator** can also be used to create new modules.

---

## Build and Installation

The build and installation procedure is rather standard:

Download the project, open a terminal and switch to the
**project-creator**-folder. Then execute the following commands:

```
mkdir build && cd build
cmake ..
make
```

After this, the project should be built and in the **bin** folder there should
be the executable **project-creator**. To install it either
- add the path to the **bin** folder to the `$PATH` variable
- copy the **project-creator** executable to `/usr/bin` or any other folder
referenced by the `$PATH` variable

---

## Usage

Executing the `project-creator` with no flag will do exactly what you tell the executable to do... nothing.

To create a new project you need to call `project-creator -p PNAME`.
This will create the initial structure (main-`CMakeLists.txt`, the cmake-floder with some macros and a module called `Module`).
If you want to give the Module a different name `Test` you have to add the `-m` flag with a following name of the module.

The execution of `project-creator -m Name` will first check, if the initial structure is already existing.
If so, then a new module with the name `Name` will be created.
Otherwise the execution will stop.
As explained in section **Introduction** the modules are recognized by a folder name starting with a capital letter.
If you try to create a module with the name `islower` the **project-creator** is creating a module with the name `Islower` instead.

---
