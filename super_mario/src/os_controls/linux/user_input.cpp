#include "user_input.hpp"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>

using biv::os::UserInput;

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

    if (ch == 27) { // ESC
        if (!kbhit()) {
            return UserInput::EXIT;
        }
        
        ch = getchar();
        if (ch == '[') {
            if (!kbhit()) {
                return UserInput::NO_INPUT;
            }
            ch = getchar();

            switch (ch) {
                default:
                    return UserInput::NO_INPUT;
            }
        } else {
            ungetc(ch, stdin);
            return UserInput::EXIT;
        }
    }

    switch (ch) {
        case 'a':
        case 'A':
            return UserInput::MAP_RIGHT;
        case 'd':
        case 'D':
            return UserInput::MAP_LEFT;
        case ' ':
            return UserInput::MARIO_JUMP;
        case 'q':
        case 'Q':
            return UserInput::EXIT;
        default:
            return UserInput::NO_INPUT;
    }
}