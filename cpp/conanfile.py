from conans import ConanFile, CMake


class bitwyresdkCpp(ConanFile):
    name = "bitwyresdk"
    version = "1.0"
    url = "https://github.com/bitwyre/bitwyre_sdk_cpp"
    description = "The official C++ SDK to connect with Bitwyre's REST, WS and FIX API"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "build_test": [True, False], "build_doc": [True, False]}
    default_options = {"shared": False, "build_test": False, "build_doc": False}
    generators = "cmake"
    exports_sources = ("source/details/*", "source/rest/*", "source/CMakeLists.txt",
                       "source/version.h", "source/version.cpp.in", "CMakeLists.txt", "cmake/*")

    requires = [
        "fmt/6.2.0@bitwyre/stable",
        "spdlog/1.6.0rc@bitwyre/stable",
        "nlohmann_json/3.9.1@bitwyre/stable",
        "cpr/1.6.2@bitwyre/stable",
        "cryptopp/8.5.0@bitwyre/stable",
        "namedtype/20190324@bitwyre/stable",
    ]

    def requirements(self):
        if self.options.build_test:
            self.requires("catch2/2.13.6@bitwyre/stable")
            self.requires("gtest/cci.20210126@bitwyre/stable")


    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_TESTING"] = self.options.build_test
        cmake.definitions["BITWYRE_INSTALL_DOCS"] = self.options.build_doc
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

        # Explicit way:
        # self.run('cmake "%s/src" %s' % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.hpp", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["bitwyre"]
