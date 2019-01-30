# TOOBAD4ML - TOOl to Buffer overflow Analysis and Description FOR Machine Learning

A tool for describing buffer overflow vulnerabilities (previously tagged in C source code), in order to further analyze them with Machine Learning techniques.

## Getting Started

### Dependencies

The following dependencies are required to build TOOBAD4ML:

* [Clang](https://clang.llvm.org) - 5.0.0 or later
* [Google Test](https://github.com/google/googletest) - 1.8.1 (only for testing)

### Setting the build directory

In-source builds are not allowed. So before building TOOBAD4ML, you must create a separate directory for the build files. This command will do the task:

```
mkdir build && cd build
```

### Installing dependencies using Conan (optional)

If you are missing any dependencies, you can use [Conan](https://conan.io). However, please note that Clang is not currently available in the official repositories. To get it, you must add the following remote repository *before* running the `conan install` command:

```
conan remote add manu343726 https://api.bintray.com/conan/manu343726/conan-packages
```

Then, just install the dependencies:

```
conan install .. --build=missing -s compiler.libcxx=libstdc++11
```

### Building the project

Use CMake with your preferred generator to build the tool:

```
cmake ..
cmake --build .
```

The binary can be found in the `<TooBad4ML_ROOT_DIR>/bin/` directory.

## Tests

Unit testing can be enabled by adding the argument `-DTOOBAD4ML_ENABLE_TESTING=ON` to the CMake build command:

```
cmake .. -DTOOBAD4ML_ENABLE_TESTING=ON
cmake --build .
```

TODO: test execution

## Usage

```
./TooBad4ML <path_to_file_or_to_multiple_files.c>
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
