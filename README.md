# A-Life-Capstone-Project
An artificial life simulator by Maxwell Cole, Ethan Doll, Wyatt Holliday, Sasha Rosenthal, and Myles Scholz.

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

## Exporting the project

In order to export the project as a whole, first all the platforms that will be exported need to have the gdextesion built. To do this, execute the following command for each of the desired target platforms:
```
scons platform=<PLATFORM> target=template_release
```
Note: If you're building for a platform that is not the platform you're building on, there may be some extra cross compiling steps needed. In the [godot building documentation](https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#building-for-target-platforms) there's some information about this. Beyond what's provided there, for windows the simplest way to build linux seems to be with [WSL](https://learn.microsoft.com/en-us/windows/wsl/install).

Then opening the project in the editor, go to Project>Editor and there are the currently available presets. From there, you can either export all presets or export a specific preset using "Export All..." or "Export Project..." respectively. The default export path points to the `build/` folder. When godot exports it will output both the main executable for the respective platform, as well as the necessary gdextension library file.

### Licensing

This project is distrubited under the GNU GENERAL PUBLIC LICENSE version 3. Please read [LICENSE](/LICENSE) for more information. This project also uses third party libraries which are distributed using their own terms. Please read [3RD-PARTY-LICENSE](/3RD-PARTY-LICENSE) for more information.