#!/bin/bash


echo "=== Начало сборки calculator ==="

# Проверка наличия CMake
if ! command -v cmake &> /dev/null; then
    echo "Ошибка: CMake не установлен. Установите его:"
    echo "  Ubuntu/Debian: sudo apt install cmake"
    echo "  Fedora/RHEL: sudo dnf install cmake"
    echo "  Arch: sudo pacman -S cmake"
    exit 1
fi

# Проверка наличия Qt6
if ! pkg-config --exists Qt6Widgets 2>/dev/null && ! pkg-config --exists Qt6Core 2>/dev/null; then
    echo "Ошибка: Qt6 не установлен или pkg-config не видит его."
    echo "Установите Qt6 и Qt6-dev пакеты:"
    echo "  Ubuntu/Debian: sudo apt install qt6-base-dev qt6-declarative-dev"
    echo "  Fedora/RHEL: sudo dnf install qt6-qtbase-devel qt6-qtdeclarative-devel"
    echo "  Arch: sudo pacman -S qt6-base qt6-declarative"
    exit 1
fi

# Проверка наличия компилятора C++
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "Ошибка: Компилятор C++ не найден. Установите g++ или clang++"
    echo "  Ubuntu/Debian: sudo apt install g++"
    echo "  Fedora/RHEL: sudo dnf install gcc-c++"
    echo "  Arch: sudo pacman -S gcc"
    exit 1
fi

# Создаем директорию для сборки если её нет
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
    echo "Создаю директорию сборки: $BUILD_DIR"
    mkdir -p "$BUILD_DIR"
fi

# Переходим в директорию сборки
cd "$BUILD_DIR" || exit

echo "=== Запуск CMake ==="

# Запускаем CMake для генерации Makefile
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_COMPILER=$(which g++ 2>/dev/null || which clang++ 2>/dev/null) \
    -DCMAKE_PREFIX_PATH=$(pkg-config --variable=prefix Qt6Core 2>/dev/null || echo "/usr") \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

if [ $? -ne 0 ]; then
    echo "Ошибка при выполнении CMake!"
    exit 1
fi

echo "=== Сборка проекта ==="

# Определяем количество ядер для параллельной сборки
CORES=$(nproc 2>/dev/null || echo 2)
echo "Использую $CORES ядер для сборки"

# Собираем проект
make -j"$CORES"

if [ $? -ne 0 ]; then
    echo "Ошибка при сборке!"
    exit 1
fi

chmod +x calculator

echo "=== Сборка завершена успешно! ==="
echo ""
echo "Исполняемый файл создан: $(pwd)/calculator"
echo ""
echo "Для запуска калькулятора выполните:"
echo "  ./calculator"
echo ""
echo "Тестовые учетные данные:"
echo "  Логин: login"
echo "  Пароль: admin"
echo ""
echo "Альтернативный запуск:"
echo "  cd $(pwd) && ./calculator"

# Возвращаемся в исходную директорию
cd ..
