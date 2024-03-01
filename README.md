# A-Life-Capstone-Project
An artificial life simulator by Maxwell Cole, Ethan Doll, Wyatt Holliday, Henry Pfluke, Sasha Rosenthal, and Myles Scholz.

## Repository Overview
The repository incorporates multiple external systems that have their own associated files and directories. For the most part, these do not need to be edited. The most important directories for development are /src/, /tests/, and /docs/, which contain source files, unit testing files, and documentation, respectively. There are also multiple Godot project files that are important for development, but these are best used through the Godot Editor.

For instructions on setting up the development environment on a Windows computer, see [/docs/windows_dev_env_setup_guide.md](/docs/windows_dev_env_setup_guide.md).

### File Structure
```
A-Life-Capstone-Project/: The repository directory
|
├──.github/: GitHub management files
|
├──bin/: GDExtension configuration files
|
├──docs/: Documentation
|  |
│  ├──src/: Source file documentation
|  |
│  └──(General project documentation)
│
├──godot-cpp/: The GDExtension submodule
|
├──src/: Source files
|
├──tests/: Testing files
|
├──.clang-format: Clang-Format configuration file
|
├──(.git*): Git configuration files
|
├──README.md: This file
|
├──SConstruct: SConstruct build file
|
├──(Godot project files)
|
└──...
```