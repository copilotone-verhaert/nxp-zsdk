# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(pbp_broadcast_sink)

zephyr_library_include_directories(${ZEPHYR_BASE}/samples/bluetooth)

FILE(GLOB app_sources ${ZEPHYR_BASE}/samples/bluetooth/pbp_public_broadcast_sink/src/*.c)
target_sources(app PRIVATE ${app_sources})