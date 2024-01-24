# Style Guidelines

Code style will be enforced by clang-format which takes care of the standard formatting conventions. A few examples:
- Indentation and alignment are tab based
- One space around math and assignment operators 
- Pointer and reference operators are affixed to the variable, not the type name

## Using clang-format locally
This project currently uses **clang-format 13** to be compatible with godot.

### Installation
- Linux: Often comes out of the box with your distribution. Can also download precompiled binaries from the [LLVM website](https://releases.llvm.org/download.html).
- MacOS and Windows: Download precompiled binaries from the [LLVM website](https://releases.llvm.org/download.html).

### Usage
To apply clang-format:
```
clang-format -i <path/to/file(s)>
```
- `-i` applies the changes directly to the file
- The path can point to several files, either using wildcards or listing them one after the other