#include "keyboard_window.hpp"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QTextCursor>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent), caps_lock_enabled(false), shift_pressed(false) {
    const int keyboard_width = 1160;
    resize(keyboard_width, 710);
    setWindowTitle("Лучшая Клавиатура");
    
    QPixmap pixmap("img/doudou.png");
    if (pixmap.isNull()) {
        pixmap = QPixmap("../img/doudou.png");
    }
    
    QLabel* image = new QLabel(this);
    image->setFixedSize(200, 200);
    image->setPixmap(pixmap);
    image->setScaledContents(true);
    
    QHBoxLayout* smail_layout = new QHBoxLayout();
    smail_layout->addWidget(image);

    display = new QTextEdit();
    display->setMinimumHeight(200);
    display->setFont(QFont("DejaVu Sans", 40));
    display->setReadOnly(true);
    display->setFocusPolicy(Qt::NoFocus);
    display->setText("Теперь я работаю идеально");

    keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);

    setFocusPolicy(Qt::ClickFocus);
    
    connect(keyboard, &KeyBoard::keyPressed, this, &KeyBoardWindow::onKeyPressed);
}

int KeyBoardWindow::normalize_key(int key) {
    switch (key) {
        case 0x0419: return Qt::Key_Q;
        case 0x0426: return Qt::Key_W;
        case 0x0423: return Qt::Key_E;
        case 0x041a: return Qt::Key_R;
        case 0x0415: return Qt::Key_T;
        case 0x041d: return Qt::Key_Y;
        case 0x0413: return Qt::Key_U;
        case 0x0428: return Qt::Key_I;
        case 0x0429: return Qt::Key_O;
        case 0x0417: return Qt::Key_P;
        case 0x0425: return Qt::Key_BracketLeft;
        case 0x042a: return Qt::Key_BracketRight;
        case 0x0424: return Qt::Key_A;
        case 0x042b: return Qt::Key_S;
        case 0x0412: return Qt::Key_D;
        case 0x0410: return Qt::Key_F;
        case 0x041f: return Qt::Key_G;
        case 0x0420: return Qt::Key_H;
        case 0x041e: return Qt::Key_J;
        case 0x041b: return Qt::Key_K;
        case 0x0414: return Qt::Key_L;
        case 0x0416: return Qt::Key_Semicolon;
        case 0x042d: return Qt::Key_Apostrophe;
        case 0x042f: return Qt::Key_Z;
        case 0x0427: return Qt::Key_X;
        case 0x0421: return Qt::Key_C;
        case 0x041c: return Qt::Key_V;
        case 0x0418: return Qt::Key_B;
        case 0x0422: return Qt::Key_N;
        case 0x042c: return Qt::Key_M;
        case 0x0411: return Qt::Key_Comma;
        case 0x042e: return Qt::Key_Period;
        case 0x0401: return Qt::Key_QuoteLeft;
        case Qt::Key_Space: return Qt::Key_Space;
        case Qt::Key_Tab: return Qt::Key_Tab;
        case Qt::Key_Shift: return Qt::Key_Shift;
        default: return key;
    }
}

void KeyBoardWindow::process_key(int key, const QString& sys_text) {
    if (keyboard->is_key_allowed(key) || key == Qt::Key_Delete || key == Qt::Key_Tab || 
        key == Qt::Key_CapsLock || key == Qt::Key_Backspace || key == Qt::Key_Space ||
        key == Qt::Key_Return || key == Qt::Key_Enter || key == Qt::Key_Shift) {
        
        if (key == Qt::Key_Backspace || key == Qt::Key_Delete) {
            QString text = display->toPlainText();
            if (!text.isEmpty()) {
                text.chop(1);
                display->setText(text);
                display->moveCursor(QTextCursor::End);
            }
            keyboard->animate_button(Qt::Key_Backspace);
        } else if (key == Qt::Key_Space) {
            display->setText(display->toPlainText() + " ");
            display->moveCursor(QTextCursor::End);
            keyboard->animate_button(key);
        } else if (key == Qt::Key_Tab) {
            display->setText(display->toPlainText() + "    ");
            display->moveCursor(QTextCursor::End);
            keyboard->animate_button(key);
        } else if (key == Qt::Key_CapsLock) {
            caps_lock_enabled = !caps_lock_enabled;
            keyboard->animate_button(key);
        } else if (key == Qt::Key_Return || key == Qt::Key_Enter) {
            display->setText(display->toPlainText() + "\n");
            display->moveCursor(QTextCursor::End);
            keyboard->animate_button(key);
        } else if (key == Qt::Key_Shift) {
            shift_pressed = true;
        } else {
            QString text = keyboard->get_key_text(key);

            if (!text.isEmpty()) {
                bool should_be_upper = caps_lock_enabled;
 
                if (shift_pressed && text.length() == 1 && text[0].isLetter()) {
                    should_be_upper = !should_be_upper;
                }

                if (text.length() == 1 && text[0].isLetter()) {
                    if (should_be_upper) {
                        text = text.toUpper();
                    } else {
                        text = text.toLower();
                    }
                }
                
                display->setText(display->toPlainText() + text);
                display->moveCursor(QTextCursor::End);
                keyboard->animate_button(key);
            }
        }

        if (key != Qt::Key_Shift) {
            shift_pressed = false;
        }
    }
}

void KeyBoardWindow::onKeyPressed(int key) {
    process_key(key);
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    const int key = normalize_key(event->key());

    if (key == Qt::Key_Tab) {
        event->accept();
        process_key(key, event->text());
    } else if (key == Qt::Key_Space) {
        event->accept();
        process_key(key, event->text());
    } else {
        process_key(key, event->text());
        QWidget::keyPressEvent(event);
    }
}

void KeyBoardWindow::keyReleaseEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Shift) {
        shift_pressed = false;
    }
    QWidget::keyReleaseEvent(event);
}