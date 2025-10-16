# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(bap_unicast_client)

FILE(GLOB app_sources ${ZEPHYR_BASE}/samples/bluetooth/bap_unicast_client/src/main.c)
target_sources(app PRIVATE ${app_sources})

zephyr_sources_ifdef(CONFIG_LIBLC3 ${ZEPHYR_BASE}/samples/bluetooth/bap_unicast_client/src/stream_lc3.c)
zephyr_sources_ifdef(CONFIG_BT_AUDIO_TX ${ZEPHYR_BASE}/samples/bluetooth/bap_unicast_client/src/stream_tx.c)

#if(CONFIG_LIBLC3)
#  FILE(GLOB liblc3_sources ${ZEPHYR_BASE}/samples/bluetooth/bap_unicast_client/src/stream_lc3.c)
#  target_sources(app PRIVATE ${liblc3_sources})
#endif()

#if(CONFIG_BT_AUDIO_TX)
#  FILE(GLOB tx_sources ${ZEPHYR_BASE}/samples/bluetooth/bap_unicast_client/src/stream_tx.c)
#  target_sources(app PRIVATE ${tx_sources})
#endif()

zephyr_library_include_directories(${ZEPHYR_BASE}/samples/bluetooth)
