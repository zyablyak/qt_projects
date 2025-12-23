cmake_minimum_required(VERSION 3.16)
project(keyboard VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Поиск Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Все исходные файлы
set(SOURCES
    src/main.cpp
    src/keyboard_window.cpp
    src/keyboard.cpp
    src/keyboard_button.cpp
    src/keyboard_data.cpp
)

# Все заголовочные файлы
set(HEADERS
    src/keyboard_window.hpp
    src/keyboard.hpp
    src/keyboard_button.hpp
    src/keyboard_data.hpp
    src/key_data.hpp
)

# Создание исполняемого файла
add_executable(keyboard ${SOURCES} ${HEADERS})

# Подключение Qt библиотек
target_link_libraries(keyboard Qt${QT_VERSION_MAJOR}::Widgets)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Создание папки для изображений и копирование файлов
add_custom_command(TARGET keyboard POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/img"
    COMMENT "Создание папки для изображений"
)

# Копирование изображения при его наличии
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/img/doudou.png")
    add_custom_command(TARGET keyboard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/img/doudou.png"
            "${CMAKE_BINARY_DIR}/img/doudou.png"
        COMMENT "Копирование изображения"
    )
else()
    message(WARNING "Изображение img/doudou.png не найдено!")
endif()


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/build.sh")
    add_custom_command(TARGET keyboard POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/build.sh"
            "${CMAKE_BINARY_DIR}/build.sh"
        COMMENT "Копирование build.sh"
    )
endif()

# Настройка для Windows
if(WIN32)
    set_target_properties(keyboard PROPERTIES
        WIN32_EXECUTABLE TRUE
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

# Опционально: настройка для релизной сборки
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Тип сборки" FORCE)
endif()
