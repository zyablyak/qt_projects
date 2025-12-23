#pragma once

#include <cstddef>

#include <QPushButton>
#include <QString>
#include <QWidget>

namespace biv {
	class KeyBoardButton : public QPushButton {
		public:
			KeyBoardButton(const QString& text = "", QWidget* parent = nullptr);
            
        protected:
            void focusOutEvent(QFocusEvent* event) override;
            void keyPressEvent(QKeyEvent* event) override;
	};
}