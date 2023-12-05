# A-Life-Capstone-Project
An artificial life simulator by Maxwell Cole, Ethan Doll, Wyatt Holliday, Henry Pfluke, Sasha Rosenthal, and Myles Scholz.

## Build instructions
- Install scons: `pip install scons` (you will need python version 3.6+)
- Install additional requirements for the platform you are building on: https://docs.godotengine.org/en/stable/contributing/development/compiling/index.html#building-for-target-platforms
- In the repo, cd into godot-cpp and run `scons platform=<platform>` to build godot-cpp
- cd back out to the main folder, and run `scons platform=<platform>` to build our project's cpp source files
- In Godot, click import and navigate to where the repo is cloned, and open project.godot