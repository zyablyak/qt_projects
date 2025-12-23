#include "keyboard_button.hpp"

#include <QSizePolicy>
#include <QStyle>
#include <QStyleOptionButton>
#include <QFocusEvent>
#include <QKeyEvent>

using biv::KeyBoardButton;

KeyBoardButton::KeyBoardButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent) {
	setFont(QFont("Roboto", 20));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setCheckable(false);
	setAutoExclusive(false);

    setFocusPolicy(Qt::NoFocus);

	QStyleOptionButton option;
	initStyleOption(&option);
	option.state &= ~QStyle::State_Sunken;
}

void KeyBoardButton::focusOutEvent(QFocusEvent* event) {
    Q_UNUSED(event);
}

void KeyBoardButton::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Tab || event->key() == Qt::Key_Space) {
        event->ignore();
    } else {
        QPushButton::keyPressEvent(event);
    }
}