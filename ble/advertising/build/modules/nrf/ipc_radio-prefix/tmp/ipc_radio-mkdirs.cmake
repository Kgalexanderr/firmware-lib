# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/opt/nordic/ncs/v3.4.1/nrf/applications/ipc_radio")
  file(MAKE_DIRECTORY "/opt/nordic/ncs/v3.4.1/nrf/applications/ipc_radio")
endif()
file(MAKE_DIRECTORY
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/ipc_radio"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix/tmp"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix/src/ipc_radio-stamp"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix/src"
  "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix/src/ipc_radio-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix/src/ipc_radio-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/kevinguerrero/dev/GitHub/learn/nrf-learning/ble/advertising/build/modules/nrf/ipc_radio-prefix/src/ipc_radio-stamp${cfgdir}") # cfgdir has leading slash
endif()
