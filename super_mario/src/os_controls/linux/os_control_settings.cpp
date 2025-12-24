#include "os_control_settings.hpp"
#include <cstdio>

void biv::os::init_settings() {
    printf("\033[?25l");
    fflush(stdout);
}

void biv::os::set_cursor_start_position() {
    printf("\033[H");
    fflush(stdout);
}