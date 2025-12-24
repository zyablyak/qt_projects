#include "os_control_settings.hpp"
#include <cstdio>

void biv::os::init_settings() {
    // В Linux консоль по умолчанию обычно не показывает курсор
    // Но можно скрыть его явно через escape-последовательности
    printf("\033[?25l");  // Скрыть курсор
    fflush(stdout);
}

void biv::os::set_cursor_start_position() {
    // Перемещение курсора в начало (0,0)
    printf("\033[H");
    fflush(stdout);
}