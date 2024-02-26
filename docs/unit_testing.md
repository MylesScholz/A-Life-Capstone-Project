# Unit Testing
This project uses [doctest](https://github.com/doctest/doctest) as a testing framework to allow writing unit tests directly in C++ (find the [documentation here](https://github.com/doctest/doctest/blob/master/doc/markdown/readme.md#reference)). These tests reside in the `test/` subdirectory, and tests are then compiled into the extension and run in the godot editor to allow doctest to access classes and functionality managed by the godot engine.

## Building & Running tests

### Building godot-cpp
In order to build the tests first make sure godot-cpp has been built at least once by navigating to the godot-cpp subdirectory and building with:
```
scons platform=<PLATFORM>
```
Where `<PLATFORM>` is the platform you're building for (windows, macos, linux, etc.)

### Building with tests enabled
From there navigate back to the main directory and build with the following options
```
scons platform=<PLATFORM> disable_exceptions=no build_library=no tests=1
```
- There are several macros used for testing with doctest that require exceptions, so to support them `disable_exceptions=no` is used
- However godot-cpp relies on exceptions being disabled, so in order to not rebuild it we build with `build_library=no`
- In order to compile the tests, the custom flag `tests` is used

### Running tests
Next to run the tests, run:
```
/path/to/godot --headless --runTests
```
- `--runTests` can be shortened as `-T`
- Arguments can be forwarded to doctest after all godot engine arguments using `-- --<DOCTEST_ARG1> ...` (ex: `godot --headless --runTests -- --help`). A list of options for doctest can be found here: https://github.com/doctest/doctest/blob/master/doc/markdown/commandline.md

If everything has worked correctly you should see something along the lines of:
```
[doctest] doctest version is "2.4.11"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases: 1 | 1 passed | 0 failed | 0 skipped
[doctest] assertions: 8 | 8 passed | 0 failed |
[doctest] Status: SUCCESS!
```

## Writing tests
All testing files are prefixed with `test_`, and include the `tests/test_header.hpp` header which includes everything needed for writing tests with doctest.

Test cases are written using the `TEST_CASE` macro. Each test must have a brief name/description written as a string in the parenthesis. Optionally, a custom tag can be included to allow tests to be filtered at runtime (ex: `[Cell]`, `[UI]`, etc.). Additionally doctest has several [decorators](https://github.com/doctest/doctest/blob/master/doc/markdown/testcases.md#decorators) that provide additional test definition options.

Doctest has a well featured set of assertions for verifying behavior. See the doctest [assertion documentation](https://github.com/doctest/doctest/blob/master/doc/markdown/assertions.md).

### Filter tests
By passing arguments into doctest (explained in [Running tests](#running-tests)) you can then filter for tests with custom tags like `--test-case="*[UI]*`.