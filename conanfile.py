######################################################################
#
#   conanfile.py
#
#   Conan recipe for building toobad4ml or managing its dependencies.
#
######################################################################

import os

from conans import ConanFile, CMake, tools
from conans.tools import SystemPackageTool

class Toobad4mlConan(ConanFile):
    name = "toobad4ml"
    version = "0.1.0"
    license = "MIT"
    author = "Robotics Group - Universidad de León"
    url = "https://niebla.unileon.es/securecoding/toobad4ml"
    description = "A tool for extracting features of Buffer Overflow \
        vulnerabilities written in C code in order to further analyze \
        them with Machine Learning techniques"
    topics = ("buffer overflow", "feature extraction", "machine learning")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared":      [True, False], "fPIC": [True, False],
               "build_tests": [True, False],
               "build_docs":  [True, False]}
    default_options = {"shared":      False, "fPIC": True,
                       "build_tests": False,
                       "build_docs":  False}
    generators = "cmake"
    exports_sources = ("LICENSE", "CMakeLists.txt", "cmake/*", "data/*", "docs/*", "src/*")
    _cmake = None

    @property
    def _build_subfolder(self):
        return "build_subfolder"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def requirements(self):
        self.requires("libclang/6.0.1@Manu343726/testing")
        #if self.options.build_tests:
        self.requires("gtest/1.10.0")
        #if self.options.build_docs:
        self.requires("doxygen/1.8.20")

    def _configure_cmake(self):
        if not self._cmake:
            self._cmake = CMake(self)
        # setup user options
        self._cmake.definitions['TOOBAD4ML_GENERATE_DOCS'] = self.options.build_docs
        self._cmake.definitions['TOOBAD4ML_ENABLE_TESTING'] = self.options.build_tests
        self._cmake.configure(build_folder=self._build_subfolder)
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        # run tests on demand
        if self.options.build_tests:
            cmake.test(output_on_failure=True)

    def package(self):
        self.copy("LICENSE",
            dst="licenses",
            src=self.source_folder,
            keep_path=False
        )
        # executable & library
        self.copy("toobad4ml_exe",
            dst="bin",
            src=os.path.join(self._build_subfolder, "bin"),
            keep_path=False
        )
        self.copy("*toobad4ml*",
            dst="lib",
            src=os.path.join(self._build_subfolder, "lib"),
            keep_path=False
        )
        # headers
        self.copy("*.h",
            dst="include",
            src=os.path.join(self.source_folder, "src", "library")
        )
        self.copy("*.h",
            dst="include",
            src=os.path.join(self.source_folder, "src", "app")
        )
        # doxygen
        if self.options.build_docs:
            self.copy("*",
                dst="docs",
                src=os.path.join(self._build_subfolder, "doxygen")
            )

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)

    def deploy(self):
        # binaries
        self.copy("*", dst="bin", src="bin")
        # docs
        if self.options.build_docs:
            self.copy("*", dst="docs", src="docs")