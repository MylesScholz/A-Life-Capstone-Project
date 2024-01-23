# Windows Development Environment Set-up Guide

## Overview
This document provides instructions to set up the development environment on a Windows computer.

## Cloning the Git Repository
1. Check that Git is installed on your computer
   1. Open the Command Prompt (if it is not already open)
   2. Run `git --version`
   3. If the command returns an error,
      1. Go to this link in your browser: https://git-scm.com/download/win
      2. Click "64-bit Git for Windows Setup" to download the installer
      3. In the directory where the file downloaded, run the installer
      4. Follow the installer instructions; the default options should work
      5. Run `git --version` in the Command Prompt again to confirm that the installation worked
   4. Otherwise, continue to step 2.
2. Clone the repository from GitHub
   1. Open the Command Prompt in the folder where your want the repository (or navigate there with `cd [file path]`)
   2. Run `git clone https://github.com/MylesScholz/A-Life-Capstone-Project.git`
   3. Navigate into the new directory with `cd ./A-Life-Capstone-Project`
   4. Run `git submodule update --init --recursive`

## Installing the Build System (SConstruct)
1. Check that Python is installed on your computer
   1. Open the Command Prompt (if it is not already open)
   2. Run `python --version`
   3. If the command returns an error or a version less than 3.6,
      1. Go to this link in your browser: https://www.python.org/downloads/
      2. Click "Download Python 3.*" to download the installer
      3. In the directory where the file downloaded, run the installer
      4. Follow the installer instructions; the default options should work, but check the box labelled "Add python.exe to PATH"
      5. Run `python --version` in the Command Prompt again to confirm that the installation worked
   4. Otherwise, continue to step 2.
2. Install SCons with pip
   1. Open the Command Prompt (if it is not already open)
   2. Run `pip install scons`
   3. Run `scons --version` to confirm the installation

## Installing a C/C++ Compiler (MSYS2)
1. Check that gcc or g++ is installed on your computer
   1. Open the Command Prompt (if it is not already open)
   2. Run `gcc --version`
   3. If the command returns an error, go to this link and follow all its installation instructions: https://www.msys2.org/

## Installing the Godot Editor
1. Check that Godot is installed on your computer
   1. Press the Windows key and search "Godot"
   2. If no app (executable) shows up,
      1. Go to this link in your browser: https://godotengine.org/download/archive/4.2-stable/
      2. Click the "Standard" button next to "Windows" to download a ZIP file containing the Godot editor
      3. In the directory where the file downloaded, unzip the file
         1. Right click the ZIP file
         2. Click "Extract All..."
         3. In the window that appears, click "Extract"
      4. The Godot editor executable is in the uncompressed directory; move this wherever you want to store the editor (but not within the repository directory)

## Building godot-cpp and the Project
1. Open the Command Prompt in /A-Life-Capstone-Project/godot-cpp/ (or navigate there with `cd [file path]`)
2. Run `scons platform=windows` (this may take a while to complete)
3. When the command line returns, navigate to the repository directory with `cd ..`
4. Run `scons` (this may also take a while)
5. Check that the project built correctly by opening it in the Godot editor
   1. Open the Godot editor
   2. Click "Import"
   3. In the window that appears, navigate to the A-Life-Capstone-Project directory
   4. Click "Select Current Folder"
   5. The project should open without error and be able to run

## Installing Clang-Format
1. Go to this link in your browser: https://github.com/llvm/llvm-project/releases/tag/llvmorg-13.0.1
2. Click "LLVM-13.0.1-win64.exe" to download the installer
3. In the directory where the file downloaded, run the installer
4. If the installer asks to uninstall an existing version of LLVM, click "Yes"
5. Follow the installer instructions; use the default options, except click "Add LLVM to the system PATH for all users"
6. Check that clang-format is installed properly
   1. Open the Command Prompt (if it is not already open)
   2. Run `clang-format --version`
   3. If the command returns an error,
      1. Press the Windows key, type "Edit the system environment variables", and select the option of the same name
      2. In the "System Properties" window, click "Environment Variables..."
      3. In the "Environment Variables" window, under "User Variables for [User]", click the "Path" entry
      4. Click "Edit"
      5. In the "Edit Environment Variable" window, click "New" and type "C:\Program Files\LLVM\bin\" (excluding the quotation marks)
      6. Click "OK" in each of the three windows in reverse order to close them
   4. Run `clang-format --version` again to confirm the change

## Setting Up Visual Studio Code
1. Check that Visual Studio Code is installed on your computer
   1. Press the Windows key and search "Visual Studio Code" or "VS Code"
   2. If no app shows up,
      1. Go to this link in your browser: https://code.visualstudio.com/
      2. Click "Download for Windows" to download the installer
      3. In the directory where the file downloaded, run the installer
      4. Follow the installer instructions; the default options should work
2. Open Visual Studio Code
3. In the "Extensions" tab on the right, search for and install, at minimum, the following extensions:
   - C/C++
   - C/C++ Extension Pack
   - Clang-Format
   - godot-tools
   - Python
4. Open "Settings" by navigating through the top menu bar ("File" > "Preferences" > "Settings")
5. Under the "User" tab, navigate to C/C++ formatting ("Extensions" > "C/C++" > "Formatting")
6. Set the following settings:
   - C_Cpp: Clang_format_fallback Style:  LLVM
   - C_Cpp: Clang_format_path:            C:\Program Files\LLVM\bin\clang-format.exe
   - C_Cpp: Clang_format_style:           file
   - C_Cpp: Formatting:                   clangFormat
7. Under the "User" tab, navigate to text editor formatting ("Text Editor" > "Formatting")
8. Set the following settings:
   - Format On Paste:      Checked
   - Format On Save:       Checked
   - Format On Save Mode:  file
