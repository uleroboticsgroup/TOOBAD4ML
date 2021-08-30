Build {#build}
=====

[TOC]

## Getting started ##

### Prerequisites ###

| Tool                       | Version | Required | Description            |
|----------------------------|---------|----------|------------------------|
| [CMake](https://cmake.org) | 3.1+    | Yes      | Build automation       |
| [Conan](https://conan.io/) | 1.27+   | No       | C++ dependency manager |
| [Doxygen](https://www.doxygen.nl/) | 1.20.0+ | No | Document generation  |

### Dependencies ###

The following libraries are used by TOOBAD4ML:

* [Clang LibTooling](https://clang.llvm.org/docs/LibTooling.html) version 5.0.0 or later.
* [Google Test](https://github.com/google/googletest) version 1.10.0 or later (only for testing).

You can optionally use [Conan](https://conan.io) to manage these dependencies. However, please note that Clang is not currently available in the official repositories. To get it, you must add the following remote repository *before* running the `conan install` command:

```bash
conan remote add roboticsgroup https://ciserver.unileon.es:8082/artifactory/api/conan/conan-dev
```

## Building the project ##

In order to build the project you have two options: CMake or Conan.

### CMake ###

Before building TOOBAD4ML you must create a separate directory for the build files because in-source builds are not allowed. Then go to that directory (as all the building process must be done inside it) and type:

```bash
mkdir build && cd build
```

If you plan to use Conan only to manage dependencies, type the following command *before* using CMake:

```bash
conan install .. -s compiler.libcxx=libstdc++11
```

Once set, you can build TOOBAD4ML using your preferred generator. For instance, to build with [Ninja](https://ninja-build.org), type:

```bash
cmake .. -G "Ninja"
```

Additionally, you can add the following CMake options to the previous command as compile definitions:

| Option                   | Values    | Description         |
|--------------------------|-----------|---------------------|
| TOOBAD4ML_ENABLE_TESTING | [ON, OFF] | Build unit tests    |
| TOOBAD4ML_GENERATE_DOCS  | [ON, OFF] | Build documentation |

For instance, to build TOOBAD4ML unit tests you should type:

```bash
cmake .. -G "Ninja" -DTOOBAD4ML_ENABLE_TESTING=ON
```

Finally, build the project with:

```bash
cmake --build .
```

If unit tests are built, it is recommended to run them with CTest. CMake generates the CTest configuration files inside the `build` directory, so in order to run it just type:

```bash
ctest -VV
```

### Conan ###

A Conan recipe is included to facilitate the building process. Just type:

```bash
conan create . toobad4ml/0.1.0@ -s compiler.libcxx=libstdc++11
```

You can also build TOOBAD4ML with the following options:

| Option      | Values        | Description         |
|-------------|---------------|---------------------|
| build_tests | [True, False] | Build unit tests    |
| build_docs  | [True, False] | Build documentation |

For instance, to build TOOBAD4ML unit tests you should type:

```bash
conan create . toobad4ml/0.1.0@ -s compiler.libcxx=libstdc++11 -o build_tests=True
```

Please note that Conan will build TOOBAD4ML in the local cache. In order to access the binary, you should deploy it by typing:

```bash
conan install toobad4ml/0.1.0@ -s compiler.libcxx=libstdc++11 -if=bin
```

The tool will be deployed inside `bin` directory.