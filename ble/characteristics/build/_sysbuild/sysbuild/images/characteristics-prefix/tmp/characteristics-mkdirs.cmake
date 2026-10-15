# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics")
  file(MAKE_DIRECTORY "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics")
endif()
file(MAKE_DIRECTORY
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/characteristics"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix/tmp"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix/src/characteristics-stamp"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix/src"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix/src/characteristics-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix/src/characteristics-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/characteristics/build/_sysbuild/sysbuild/images/characteristics-prefix/src/characteristics-stamp${cfgdir}") # cfgdir has leading slash
endif()
