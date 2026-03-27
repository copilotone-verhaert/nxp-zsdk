# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(shell_nxp_vendor_commands_extension)

if(CONFIG_OPENTHREAD)
  # Low-level Spinel communication (openthread-radio-spinel)
  target_sources(openthread-radio-spinel PRIVATE
    src/nxp_vendor_spinel.cpp
  )

  target_include_directories(openthread-radio-spinel PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  )

  target_sources(app PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/nxp_vendor_commands.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/nxp_vendor_cli.cpp
  )

  target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src
  )

  set_property(TARGET app PROPERTY CXX_STANDARD 14)
  set_property(TARGET app PROPERTY CXX_STANDARD_REQUIRED ON)
endif()
