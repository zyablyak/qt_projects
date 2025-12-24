#!/bin/bash

BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="src"

# Создаем папку для сборки если ее нет
if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

# Генерируем проект
cmake -G "$BUILD_TYPE" "../$SOURCE_FOLDER"

# Собираем проект
cmake --build .

cd ..