cmake_minimum_required(VERSION 3.11)
project(TasqEngineLua VERSION 1.0 LANGUAGES CXX)

# Procurar pkg-config
find_package(PkgConfig REQUIRED)

# Procurar SDL2
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(LUA REQUIRED lua)  # ou "lua" dependendo do sistema

# Adicionar o executável
add_executable(tLauncher 
    ./src/main.cpp
    ./src/Platform/Platform.cpp
    ./src/Renderer/Renderer.cpp
)

# Incluir diretórios encontrados
target_include_directories(tLauncher PRIVATE
    ./include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIRS}
)

# Ligar com as bibliotecas
target_link_libraries(tLauncher PRIVATE
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${LUA_LIBRARIES}
)

# Instalar o binário em dist/bin
install(TARGETS tLauncher
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/dist/bin
)

# Instalar headers (suponha que seus headers estão em ./include)
install(DIRECTORY include/
    DESTINATION ${CMAKE_SOURCE_DIR}/dist/include
    FILES_MATCHING PATTERN "*.h"
)
