from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.files import copy, get
from conan.tools.layout import basic_layout
from conan.tools.microsoft import is_msvc
from conan.tools.scm import Version
import os


class confu_algorithm(ConanFile):
    name = "confu_algorithm"
    version = "0.0.0"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "CMakeLists.txt", "confu_algorithm/*", "cmake/*"
    generators = "CMakeDeps", "CMakeToolchain"
    package_type = "header-library"
    no_copy_source = True

    def package(self):
        copy(self, "*.h*", src=os.path.join(self.source_folder, "confu_algorithm"),
             dst=os.path.join(self.package_folder, "include", "confu_algorithm"))
