#!/bin/bash

echo "Установка зависимостей для Linux (Arch Linux)..."
echo "================================================"

# Проверяем, запущен ли pacman
if [ -f "/var/lib/pacman/db.lck" ]; then
    echo "Обнаружена блокировка базы pacman."
    echo "Возможно, другой процесс pacman уже запущен."
    echo "Дождитесь его завершения или выполните:"
    echo "sudo rm /var/lib/pacman/db.lck"
    echo ""
    echo "Продолжить установку вручную? (y/n)"
    read -r answer
    if [ "$answer" != "y" ] && [ "$answer" != "Y" ]; then
        exit 1
    fi
fi

# Устанавливаем зависимости для Arch Linux
echo "1. Установка базовых инструментов сборки..."
sudo pacman -S --needed --noconfirm base-devel cmake ninja 2>/dev/null || echo "Не удалось установить base-devel, возможно уже установлен"

echo "2. Установка Qt6..."
sudo pacman -S --needed --noconfirm qt6-base 2>/dev/null

echo "3. Установка шрифта Roboto..."
sudo pacman -S --needed --noconfirm ttf-roboto 2>/dev/null || {
    echo "Шрифт Roboto не найден в официальных репозиториях."
    echo "Альтернативные варианты:"
    echo "  a) Установите из AUR: yay -S ttf-roboto"
    echo "  b) Используйте другой шрифт (измените в коде)"
}

echo "4. Проверка установленных пакетов..."
echo "================================================"
echo "CMake: $(cmake --version 2>/dev/null | head -n1 || echo 'Не установлен')"
echo "Ninja: $(ninja --version 2>/dev/null || echo 'Не установлен')"
echo "Qt6: $(pkg-config --modversion Qt6Core 2>/dev/null || echo 'Не установлен')"
echo "================================================"

echo "Зависимости установлены или проверены!"
echo ""
echo "Если какие-то пакеты не установились, установите их вручную:"
echo "  sudo pacman -S --needed cmake ninja qt6-base"
echo ""
echo "Для шрифта Roboto из AUR:"
echo "  yay -S ttf-roboto"
echo "Или замените шрифт в коде на 'DejaVu Sans' или другой доступный"
