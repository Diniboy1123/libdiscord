cmake_minimum_required(VERSION 3.0)
project(libdiscord VERSION 0.3.0 LANGUAGES C)

## Library info
set(PACKAGE libdiscord)
set(CPACK_PACKAGE_NAME libdiscord)

set(LD_VERSION_MAJOR 0)
set(LD_VERSION_MINOR .3)
set(LD_VERSION_PATCH )
set(LD_VERSION "${LD_VERSION_MAJOR}${LD_VERSION_MINOR}${LD_VERSION_PATCH}")

## libdiscord options
set(LD_RINGBUFFER_DEFAULT_SIZE 16)

## Discord-specific options
set(LD_API_URL "\"https://discordapp.com/api\"")
set(LD_REST_API_VERSION "\"/v6\"")
set(LD_WS_API_VERSION 6)
#set(LD_GATEWAY_API_VERSION 3 "Only version 3 of the gateway API is supported")
set(LD_GITHUB_URL "\"https://github.com/dxing97/libdiscord\"") # do we need this?


## Compilation
set(CMAKE_C_STANDARD 99)

## Include directories
IF (CYGWIN)
    SET (CMAKE_FIND_LIBRARY_PREFIXES "")
    SET (CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".LIB" ".dll" ".DLL")
ELSE()
    SET (CMAKE_FIND_LIBRARY_PREFIXES "lib")
    SET (CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")
ENDIF (CYGWIN)

include_directories(/usr/local/lib /usr/local/include)
include_directories(example_bots lib cmake)

#homebrew on macOS
include_directories(/usr/local/opt/curl/include)
include_directories(/usr/local/opt/openssl/include)



include_directories("${PROJECT_BINARY_DIR}")
# If libwebsockets was compiled and installed in Cygwin:
include_directories(/usr/local/lib/include)

set(LD_LIBS websockets jansson curl crypto)

## Sources and headers
configure_file(
        "${PROJECT_SOURCE_DIR}/cmake/libdiscord_config.h.in"
        "${PROJECT_BINARY_DIR}/libdiscord_config.h"
)

set(LD_SOURCE lib/libdiscord.h lib/libdiscord.c lib/REST.h lib/REST.c lib/log.c lib/log.h lib/json.c lib/json.h lib/utils.c lib/utils.h lib/status.h)
add_library(discord SHARED ${LD_SOURCE})


## Targets
## Library
target_link_libraries(discord ${LD_LIBS})
set_target_properties(discord PROPERTIES VERSION ${PROJECT_VERSION})
target_compile_options(discord PRIVATE "-Wall")
target_compile_options(discord PRIVATE "-Werror")
target_compile_options(discord PRIVATE "-Wno-unknown-pragmas")
target_compile_options(discord PRIVATE "-g")


## Example Bots
set(BOT_AYY_SOURCE example_bots/example-ayylmao.c cmake/libdiscord_config.h.in)
add_executable(example-bot-ayylmao ${BOT_AYY_SOURCE})
target_link_libraries(example-bot-ayylmao discord)

set(BOT_PING_SOURCE example_bots/example-ping.c cmake/libdiscord_config.h.in)
add_executable(example-bot-ping ${BOT_PING_SOURCE})
target_link_libraries(example-bot-ping discord)

set(BOT_COUNTER_SOURCE example_bots/example-counter.c cmake/libdiscord_config.h.in)
add_executable(example-bot-counter ${BOT_COUNTER_SOURCE})
target_link_libraries(example-bot-counter discord)

set(EXAMPLE_SIMPLEPOST_SOURCE cmake/libdiscord_config.h.in example_bots/example-simplepost.c)
add_executable(example-simplepost ${EXAMPLE_SIMPLEPOST_SOURCE})
target_link_libraries(example-simplepost discord)

set(BOT_HASH_SOURCE cmake/libdiscord_config.h.in example_bots/example-hash.c)
add_executable(example-bot-hash ${BOT_HASH_SOURCE})
target_link_libraries(example-bot-hash discord)

## Tests
set(TESTS_JSON_SOURCE cmake/libdiscord_config.h.in tests/tests-json.c)
add_executable(tests-json ${TESTS_JSON_SOURCE})
target_link_libraries(tests-json discord)