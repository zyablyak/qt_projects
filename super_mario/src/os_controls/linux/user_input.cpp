#include "user_input.hpp"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>

using biv::os::UserInput;

// Функция для настройки неблокирующего ввода
static void set_nonblocking_mode(bool enable) {
    static struct termios oldt, newt;
    static bool initialized = false;
    
    if (!initialized) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        initialized = true;
    }
    
    if (enable) {
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// Функция проверки нажатия клавиши
static bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    
    return false;
}

UserInput biv::os::get_user_input() {
    if (!kbhit()) {
        return UserInput::NO_INPUT;
    }
    
    int ch = getchar();
    
    // Обработка escape-последовательностей для специальных клавиш
    if (ch == 27) { // ESC
        if (!kbhit()) {
            return UserInput::EXIT; // Обычная клавиша ESC
        }
        
        ch = getchar();
        if (ch == '[') {
            if (!kbhit()) {
                return UserInput::NO_INPUT;
            }
            ch = getchar();
            
            // Стрелки и другие специальные клавиши
            switch (ch) {
                // В этой версии стрелки не используются, но можно добавить при необходимости
                default:
                    return UserInput::NO_INPUT;
            }
        } else {
            // Если после ESC не идет '[', то это просто ESC
            ungetc(ch, stdin);
            return UserInput::EXIT;
        }
    }
    
    // Обработка обычных символов
    switch (ch) {
        case 'a':
        case 'A':
            return UserInput::MAP_RIGHT;
        case 'd':
        case 'D':
            return UserInput::MAP_LEFT;
        case ' ':
            return UserInput::MARIO_JUMP;
        case 'q':  // В Linux часто используют 'q' для выхода
        case 'Q':
            return UserInput::EXIT;
        default:
            return UserInput::NO_INPUT;
    }
}