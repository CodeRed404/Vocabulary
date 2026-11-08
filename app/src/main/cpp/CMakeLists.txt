cmake_minimum_required(VERSION 3.22.1)
project("vocabulary")

set(CMAKE_BUILD_TYPE Debug)
# Raylib für Android konfigurieren
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(PLATFORM "Android" CACHE STRING "Target platform" FORCE)

# Raylib als Unterverzeichnis einbinden
add_subdirectory(raylib)

add_library(${CMAKE_PROJECT_NAME} SHARED
        native-lib.cpp
        scripts/Manager.cpp
        scripts/AssetManager.cpp
        #scenes
        scripts/scenes/SceneManager.cpp
        scripts/scenes/Scene.cpp
        scripts/scenes/Opening.cpp
        scripts/scenes/Menu.cpp
        scripts/scenes/TrainMenu.cpp
        scripts/scenes/TemplatesMenu.cpp
        scripts/scenes/VocabsMenu.cpp
        #vocabs
        scripts/vocabs/Templates.cpp
        scripts/vocabs/TrainScene.cpp
        #ui
        scripts/ui/Text.cpp
        scripts/ui/Button.cpp
)

# WICHTIG: Zwingt den Linker, das Android-Einstiegssymbol von Raylib nicht zu verwerfen
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

target_link_libraries(${CMAKE_PROJECT_NAME}
        raylib
        android
        log
        EGL
        GLESv2
        OpenSLES
        z

        # --- HIER NEU HINZUGEFÜGT FÜR CURL ---
        curl
        m
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        raylib/src
        raylib/src/external

        # my
        cpp_libs/include
)

# --- HIER NEU HINZUGEFÜGT: Pfad zur libcurl.a für Android ---
add_library(curl STATIC IMPORTED)
set_target_properties(curl PROPERTIES IMPORTED_LOCATION
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp_libs/libs/${ANDROID_ABI}/libcurl.a)