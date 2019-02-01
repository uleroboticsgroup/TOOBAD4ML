# TOOBAD4ML - TOOl to Buffer overflow Analysis and Description FOR Machine Learning

A tool for describing buffer overflow vulnerabilities (previously tagged in C source code) in order to further analyze them with Machine Learning techniques.

## Getting Started

### Prerequisites

* [CMake](https://cmake.org) 3.1 or later is required to build the project.
* In-source builds are not allowed. So before building TOOBAD4ML you must create a separate directory for the build files.

### Dependencies

The following libraries are used by TOOBAD4ML:

* [Clang](https://clang.llvm.org) version 5.0.0 or later;
* [Google Test](https://github.com/google/googletest) version 1.8.1 or later (only for testing);

You can optionally use [Conan](https://conan.io) to manage these dependencies. However, please note that Clang is not currently available in the official repositories. To get it, you must add the following remote repository *before* running the `conan install` command:

```
conan remote add manu343726 https://api.bintray.com/conan/manu343726/conan-packages
```

### Installing dependencies with Conan

If you don't plan to use Conan, you can ignore this step. Otherwise, first go to the `build` directory and then type the following command *before* using CMake:

```
conan install .. --build=missing -s compiler.libcxx=libstdc++11
```

### Building the project

You can build TOOBAD4ML using your preferred generator; just be sure that you run any CMake commands inside the `build` directory. For instance:

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

The binary can be found in the `<TOOBAD4ML_ROOT_DIR>/bin/` directory.

### Testing the project

Tests can be enabled by adding the argument `-DTOOBAD4ML_ENABLE_TESTING=ON` to the CMake configuration command:

```
cmake .. -G "Ninja" -DTOOBAD4ML_ENABLE_TESTING=ON
cmake --build .
```

The test executables can be found in the `<TOOBAD4ML_ROOT_DIR>/bin/` directory. However, you can use CTest to run the testing process. CMake generates its configuration files inside the `build/tests` directory. So in order to run CTest just type:

```
cd tests && ctest -V
```

## Usage

```
./TOOBAD4ML <path_to_file_or_to_multiple_files.c>
```

### Sample tagged source file

TODO

## FAQ

Please check the wiki :-)

## Credits

This project has been founded by the [Research Institute of Applied Sciences in Cybersecurity](http://riasc.unileon.es) (RIASC) from the [Universidad de León](https://www.unileon.es) and developed by:

* Gonzalo Esteban
* Razvan Raducu
* Flavio Rodrigues

## License

TBD :-)
