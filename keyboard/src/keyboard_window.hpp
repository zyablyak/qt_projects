#pragma once

#include <cstddef>

#include <QKeyEvent>
#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
    class KeyBoardWindow : public QWidget {
        Q_OBJECT
        
        private:
            QTextEdit* display;
            KeyBoard* keyboard;
            bool caps_lock_enabled;
            bool shift_pressed;

        public:
            KeyBoardWindow(QWidget* parent = nullptr);
            
        private:
            int normalize_key(int key);
            void process_key(int key, const QString& sys_text = QString());
            
        private slots:
            void onKeyPressed(int key);
            
        protected:
            void keyPressEvent(QKeyEvent* event) override;
            void keyReleaseEvent(QKeyEvent* event) override;
    };
}