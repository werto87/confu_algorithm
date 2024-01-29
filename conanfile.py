from conan import ConanFile


class Project(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def configure(self):
        self.options["catch2"].with_main = True
        self.options["catch2"].with_benchmark = True

    def requirements(self):
        self.requires("catch2/2.13.7")

