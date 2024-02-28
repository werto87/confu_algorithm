#
# Copyright (c) 2024 Waldemar Schneider (w-schneider1987 at web dot de)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

add_library(confu_algorithm INTERFACE)

add_library(myproject::confu_algorithm ALIAS confu_algorithm)

find_package(Boost)

target_link_libraries(confu_algorithm INTERFACE Boost::headers)

target_include_directories(
  confu_algorithm INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(confu_algorithm INTERFACE cxx_std_20)

set_target_properties(
  confu_algorithm
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

install(FILES createChainViews.hxx stableUniqueElements.hxx
        DESTINATION include/confu_algorithm)
install(TARGETS confu_algorithm DESTINATION lib)
