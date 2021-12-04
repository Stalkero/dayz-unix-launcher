set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Svg CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp *.h *.hpp *.qrc *.ui)

add_executable(dayz-unix-launcher MACOSX_BUNDLE ${SOURCES})
target_include_directories(dayz-unix-launcher PRIVATE .)
target_link_libraries(dayz-unix-launcher PRIVATE
    dayz-unix-launcher-library
    common
    steam-integration
    argparse::argparse
    fmt::fmt-header-only
    nlohmann::json
    pugixml::pugixml
    rihab::scope_guard
    Qt5::Widgets
    Qt5::Svg
    spdlog::spdlog
    )
install(TARGETS dayz-unix-launcher
        BUNDLE DESTINATION . COMPONENT Runtime
        RUNTIME DESTINATION bin COMPONENT Runtime)

if (NOT APPLE)
    install(FILES blagoicons/dayz.png
            DESTINATION share/icons/hicolor/256x256/apps
            RENAME -launcher.png)
    install(FILES dayz-unix-launcher.desktop
            DESTINATION share/applications)
endif()

if (APPLE)
    find_package(Qt5Widgets CONFIG REQUIRED)
    get_target_property(WIDGETS_LOCATION Qt5::Widgets IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${WIDGETS_LOCATION}" DIRECTORY)
    find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${QT_BIN_DIR}")
    
    add_custom_command(TARGET dayz-unix-launcher POST_BUILD
        COMMAND "${MACDEPLOYQT_EXECUTABLE}"
            "$<TARGET_FILE_DIR:dayz-unix-launcher>/../.."
            -always-overwrite
        COMMENT "Running macdeployqt...")

    set(CPACK_GENERATOR "DragNDrop")
    include(CPack)

    set(MACOSX_BUNDLE_ICON_FILE -launcher.icns)
    set(ICON_FILE ${CMAKE_CURRENT_SOURCE_DIR}/blagoicons/-launcher.icns)
    set_source_files_properties(${ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(dayz-unix-launcher PRIVATE ${ICON_FILE})

    set_target_properties(dayz-unix-launcher PROPERTIES OUTPUT_NAME "DayZ Unix Launcher")

    if (STEAMWORKS_SDK_DETECTED)
        add_custom_command(TARGET dayz-unix-launcher POST_BUILD
                          COMMAND ${CMAKE_COMMAND} -E copy "${STEAMWORKS_LIB_PATH}" "$<TARGET_FILE_DIR:dayz-unix-launcher>/libsteam_api.dylib"
                          COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/external/steamworks-LICENSE.txt" "$<TARGET_FILE_DIR:dayz-unix-launcher>/steamworks-LICENSE.txt"
                          COMMENT "Copying Steamworks SDK")
   endif()
elseif (STEAMWORKS_SDK_DETECTED)
    install(FILES "${STEAMWORKS_LIB_PATH}"
                  "${CMAKE_SOURCE_DIR}/external/steamworks-LICENSE.txt"
            DESTINATION share/dayz-unix-launcher/lib)
endif()
