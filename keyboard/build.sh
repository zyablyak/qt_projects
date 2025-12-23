#!/bin/bash

BUILD_TYPE="Ninja"
BUILD_SUFFIX="ninja"

BUILD_FOLDER="build_${BUILD_SUFFIX}"
SOURCE_FOLDER="."
IMG_FOLDER="img"

echo "=== Сборка виртуальной клавиатуры ==="

# Проверяем, существует ли папка с исходниками
if [ ! -d "src" ]; then
    echo "Ошибка: папка 'src' не найдена!"
    echo "Создайте структуру проекта:"
    echo "  mkdir -p src img"
    echo "  cp *.cpp *.hpp src/ 2>/dev/null || true"
    exit 1
fi

# Создаем папку сборки
if [ ! -d "$BUILD_FOLDER" ]; then
    echo "Создаю папку сборки: $BUILD_FOLDER"
    mkdir -p "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER" || exit

echo "Конфигурация CMake..."
cmake -G "$BUILD_TYPE" -DCMAKE_BUILD_TYPE=Release "../$SOURCE_FOLDER"

if [ $? -ne 0 ]; then
    echo "Ошибка конфигурации CMake!"
    exit 1
fi

echo "Сборка проекта..."
cmake --build . --config Release

if [ $? -ne 0 ]; then
    echo "Ошибка сборки!"
    exit 1
fi

if [ -f "keyboard" ]; then
    echo ""
    echo " Сборка успешно завершена!"
    echo "  Исполняемый файл: $(pwd)/keyboard"
    echo ""
    echo "Для запуска выполните:"
    echo "  ./keyboard"
elif [ -f "keyboard.exe" ]; then
    echo " Сборка успешно завершена!"
    echo "  Исполняемый файл: $(pwd)/keyboard.exe"
else
    echo " Ошибка: исполняемый файл не найден!"
    exit 1
fi