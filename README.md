# TOOBAD4ML - TOOl to Buffer overflow Analysis and Description FOR Machine Learning

A tool for extracting features of Buffer Overflow vulnerabilities written in C code in order to further analyze them with Machine Learning techniques.

## Build status

| Branch | CI |
|--------|----|
| master | [![Build Status](http://ciserver.unileon.es:8080/buildStatus/icon?job=secure-coding%2Ftoobad4ml)](http://ciserver.unileon.es:8080/job/secure-coding/job/toobad4ml/) |

## Getting Started

### Prerequisites

* [CMake](https://cmake.org) 3.1 or later is required to build the project.
* In-source builds are not allowed. So before building TOOBAD4ML you *must* create a separate directory for the build files.

### Dependencies

The following libraries are used by TOOBAD4ML:

* [Clang](https://clang.llvm.org) version 5.0.0 or later;
* [Google Test](https://github.com/google/googletest) version 1.8.1 or later (only for testing);

You can optionally use [Conan](https://conan.io) to manage these dependencies. However, please note that Clang is not currently available in the official repositories. To get it, you must add the following remote repository *before* running the `conan install` command:

```
conan remote add roboticsgroup https://ciserver.unileon.es:8082/artifactory/api/conan/conan-dev
```

### Installing dependencies with Conan

If you don't plan to use Conan you can ignore this step. Otherwise, first go to the `build` directory and then type the following command *before* using CMake:

```
conan install .. -s compiler.libcxx=libstdc++11
```

### Building the project

You can build TOOBAD4ML using your preferred generator, just be sure that you run any CMake commands inside the `build` directory. For instance, to build with [Ninja](https://ninja-build.org), type:

```
cmake .. -G "Ninja"
```

Note that CMake automatically searches the system for installed dependencies during the configuration process. However, if you want to force it to use Conan's dependencies, simply add the argument `-DTOOBAD4ML_FORCE_CONAN=ON` to the previous command:

```
cmake .. -G "Ninja" -DTOOBAD4ML_FORCE_CONAN=ON
```

Finally, build the project with:

```
cmake --build .
```

The binary can be found in the `<TOOBAD4ML_ROOT_DIR>/bin` directory.

### Testing the project

Tests can be enabled by adding the argument `-DTOOBAD4ML_ENABLE_TESTING=ON` to the CMake configuration command:

```
cmake .. -G "Ninja" -DTOOBAD4ML_ENABLE_TESTING=ON
```

To build all unit tests, type:

```
cmake --build . --target tests
```

It is recommended to run the unit tests with CTest; although all the tests executables can be found in the `<TOOBAD4ML_ROOT_DIR>/bin/tests` directory. CMake generates the CTest configuration files inside the `build` directory, so in order to run it just type:

```
ctest -VV
```

### Generate documentation

Doxygen documentation can be enabled by adding the argument `-DTOOBAD4ML_GENERATE_DOCS=ON` to the CMake configuration command:

```
cmake .. -G "Ninja" -DTOOBAD4ML_GENERATE_DOCS=ON
```

## Usage

```
./TOOBAD4ML <path_to_file_or_to_multiple_files.c> -f=FORMAT -o=FILENAME --
```

### Flags

* Format:
    * STD: Standard output
    * CSV: CSV format

* Filename:
    * The name of the output file

*NOTE*: if filename is provided and format flag is set to `STD`, filename is ignored.

### Sample tagged source file

TODO

## FAQ

Please check the wiki :-)

## Credits

This tool has been developed by:

* Gonzalo Esteban
* David Fernández
* Razvan Raducu
* Flavio Rodrigues

## License

TBD :-)