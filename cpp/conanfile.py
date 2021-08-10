from conans import ConanFile, CMake


class bitwyresdkCpp(ConanFile):
    name = "bitwyresdk"
    version = "1.0"
    url = "https://github.com/bitwyre/bitwyre_sdk_cpp"
    description = "The official Software Development Kit to connect with Bitwyre's REST, WS and FIX API"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "source/*"
    requires = [
        "catch2/2.13.6",
        "fmt/6.2.0@bitwyre/stable",
        "spdlog/1.6.0rc@bitwyre/stable",
        "nlohmann_json/3.9.1",
        "cpr/1.6.2",
        "gtest/cci.20210126",
        "cryptopp/8.5.0",
        "namedtype/20190324",
    ]

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="source")
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