file(GLOB_RECURSE SOURCES *.cpp *.hpp)

add_library(dayz-unix-launcher-library STATIC ${SOURCES})
target_include_directories(dayz-unix-launcher-library INTERFACE .)
target_link_libraries(dayz-unix-launcher-library PRIVATE common fmt::fmt-header-only nlohmann::json spdlog::spdlog)
