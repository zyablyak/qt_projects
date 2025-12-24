#include "keyboard.hpp"
#include <QTimer>
#include <QStyle>

using biv::KeyBoard;

KeyBoard::KeyBoard(const int width, QWidget* parent) 
    : button_width(width / 29), QWidget(parent) {

    keyboard_data = new KeyBoardData();
    
    QGridLayout* keys_layout = new QGridLayout(this);
    keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);
    
    // 1-я линия
    create_buttons(keyboard_data->get_line1(), keys_layout, 0, 0);
    
    KeyBoardButton* backspace_btn = new KeyBoardButton("Удалить");
    backspace_btn->setMinimumSize(2 * button_width, button_width);
    backspace_btn->setAutoExclusive(false);
    backspace_btn->setCheckable(false);
    keys_layout->addWidget(backspace_btn, 0, 26, 2, 3);
    
    connect(backspace_btn, &QPushButton::clicked, this, [this]() {
        emit keyPressed(Qt::Key_Backspace);
    });

    // 2-я линия
    KeyBoardButton* tab_btn = new KeyBoardButton("Tab");
    tab_btn->setMinimumSize(2 * button_width, button_width);
    tab_btn->setAutoExclusive(false);
    tab_btn->setCheckable(false);
    keys_layout->addWidget(tab_btn, 2, 0, 2, 3);
    
    connect(tab_btn, &QPushButton::clicked, this, [this]() {
        emit keyPressed(Qt::Key_Tab);
    });
    
    create_buttons(keyboard_data->get_line2(), keys_layout, 2, 3);
    
    // 3-я линия
    KeyBoardButton* caps_btn = new KeyBoardButton("Caps");
    caps_btn->setMinimumSize(2 * button_width, button_width);
    caps_btn->setCheckable(true);
    caps_btn->setAutoExclusive(false);
    keys_layout->addWidget(caps_btn, 4, 0, 2, 4);
    
    connect(caps_btn, &QPushButton::clicked, this, [this]() {
        emit keyPressed(Qt::Key_CapsLock);
    });
    
    create_buttons(keyboard_data->get_line3(), keys_layout, 4, 4);
    
    KeyBoardButton* enter_btn = new KeyBoardButton("Enter");
    enter_btn->setMinimumSize(2 * button_width, button_width);
    enter_btn->setAutoExclusive(false);
    enter_btn->setCheckable(false);
    keys_layout->addWidget(enter_btn, 4, 26, 2, 3);
    
    connect(enter_btn, &QPushButton::clicked, this, [this]() {
        emit keyPressed(Qt::Key_Return);
    });
    
    // 4-я линия - Левый Shift
    KeyBoardButton* left_shift_btn = new KeyBoardButton("Shift");
    left_shift_btn->setMinimumSize(2 * button_width, button_width);
    left_shift_btn->setAutoExclusive(false);
    left_shift_btn->setCheckable(true); // Делаем checkable для визуальной обратной связи
    keys_layout->addWidget(left_shift_btn, 6, 0, 2, 5);
    
    connect(left_shift_btn, &QPushButton::pressed, this, [this, left_shift_btn]() {
        left_shift_btn->setChecked(true);
        emit keyPressed(Qt::Key_Shift);
    });
    
    connect(left_shift_btn, &QPushButton::released, this, [left_shift_btn]() {
        left_shift_btn->setChecked(false);
    });
    
    create_buttons(keyboard_data->get_line4(), keys_layout, 6, 5);
    
    // 4-я линия - Правый Shift
    KeyBoardButton* right_shift_btn = new KeyBoardButton("Shift");
    right_shift_btn->setMinimumSize(2 * button_width, button_width);
    right_shift_btn->setAutoExclusive(false);
    right_shift_btn->setCheckable(true); // Делаем checkable для визуальной обратной связи
    keys_layout->addWidget(right_shift_btn, 6, 25, 2, 4);

    connect(right_shift_btn, &QPushButton::pressed, this, [this, right_shift_btn]() {
        right_shift_btn->setChecked(true);
        emit keyPressed(Qt::Key_Shift);
    });
    
    connect(right_shift_btn, &QPushButton::released, this, [right_shift_btn]() {
        right_shift_btn->setChecked(false);
    });

    // 5-я линия
    KeyBoardButton* space = new KeyBoardButton(" ");
    space->setMinimumSize(8 * button_width, button_width);
    space->setAutoExclusive(false);
    space->setCheckable(false);
    keys_layout->addWidget(space, 8, 7, 2, 16);

    connect(space, &QPushButton::clicked, this, [this]() {
        emit keyPressed(Qt::Key_Space);
    });

    buttons[Qt::Key_Space] = space;
    buttons[Qt::Key_Shift] = left_shift_btn;
}

void KeyBoard::animate_button(const int code) {
    auto it = buttons.find(code);
    if (it != buttons.end()) {
        QPushButton* btn = it->second;
        btn->setDown(true);
        QTimer::singleShot(100, btn, [btn]() {
            btn->setDown(false);
        });
    }
}

QString KeyBoard::get_key_text(const int code) const {
    auto it = buttons.find(code);
    if (it != buttons.end()) {
        if (code == Qt::Key_Space) {
            return " ";
        }
        return it->second->text();
    }

    if (code == Qt::Key_Space) {
        return " ";
    }
    
    return QString();
}

bool KeyBoard::is_key_allowed(const int code) const noexcept {
    if (code == Qt::Key_Space) {
        return true;
    }
    return keyboard_data->is_key_allowed(code);
}

// ----------------------------------------------------------------------------
//                                  PRIVATE
// ----------------------------------------------------------------------------
void KeyBoard::create_buttons(
    const std::vector<KeyData>& data, 
    QGridLayout* layout, 
    const int line,
    const int start_position
) {
    for (int i = 0; i < data.size(); i++) {
        KeyBoardButton* btn = new KeyBoardButton(data[i].text);
        btn->setMinimumSize(button_width, button_width);
        btn->setAutoExclusive(false);
        btn->setCheckable(false);
        
        layout->addWidget(btn, line, i * 2 + start_position, 2, 2);
        
        buttons[data[i].code] = btn;
        
        connect(btn, &QPushButton::clicked, this, [this, code = data[i].code]() {
            emit keyPressed(code);
        });
    }
}