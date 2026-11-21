#include "qt_keyboard.hpp"

#include <QCoreApplication>
#include <QEvent>
#include <QKeyEvent>
#include <QWidget>

using biv::QtKeyboard;
using biv::UserInput;

namespace {
	enum class Key {
		NONE,
		LEFT,
		RIGHT,
		JUMP,
		EXIT
	};

	constexpr int CYRILLIC_EF = 0x424;
	constexpr int CYRILLIC_VE = 0x412;
	constexpr int CYRILLIC_SHORT_I = 0x419;

	Key get_key(const QKeyEvent* event) {
		switch (event->key()) {
			case Qt::Key_A:
			case Qt::Key_Left:
			case CYRILLIC_EF:
				return Key::LEFT;
			case Qt::Key_D:
			case Qt::Key_Right:
			case CYRILLIC_VE:
				return Key::RIGHT;
			case Qt::Key_Space:
			case Qt::Key_Up:
				return Key::JUMP;
			case Qt::Key_Q:
			case Qt::Key_Escape:
			case CYRILLIC_SHORT_I:
				return Key::EXIT;
		}

		#ifdef Q_OS_WIN
			switch (event->nativeVirtualKey()) {
				case 'A':
					return Key::LEFT;
				case 'D':
					return Key::RIGHT;
				case 'Q':
					return Key::EXIT;
			}
		#endif

		return Key::NONE;
	}
}

UserInput QtKeyboard::get_user_input() {
	QCoreApplication::processEvents();

	if (exit_requested) {
		return UserInput::EXIT;
	}

	if (left_pressed) {
		return jump_pressed ? UserInput::MAP_RIGHT_AND_JUMP : UserInput::MAP_RIGHT;
	} else if (right_pressed) {
		return jump_pressed ? UserInput::MAP_LEFT_AND_JUMP : UserInput::MAP_LEFT;
	} else if (jump_pressed) {
		return UserInput::MARIO_JUMP;
	}
	return UserInput::NO_INPUT;
}

void QtKeyboard::off() {
	left_pressed = false;
	right_pressed = false;
	jump_pressed = false;
}

void QtKeyboard::on() {
	QCoreApplication::instance()->installEventFilter(this);
}

bool QtKeyboard::eventFilter(QObject* watched, QEvent* event) {
	switch (event->type()) {
		case QEvent::KeyPress:
			process_key(static_cast<QKeyEvent*>(event), true);
			break;
		case QEvent::KeyRelease:
			process_key(static_cast<QKeyEvent*>(event), false);
			break;
		case QEvent::WindowDeactivate:
			off();
			break;
		case QEvent::Close:
			if (watched->isWidgetType() && static_cast<QWidget*>(watched)->isWindow()) {
				exit_requested = true;
			}
			break;
		default:
			break;
	}
	return false;
}

void QtKeyboard::process_key(const QKeyEvent* event, const bool is_pressed) {
	if (event->isAutoRepeat()) {
		return;
	}

	switch (get_key(event)) {
		case Key::LEFT:
			left_pressed = is_pressed;
			break;
		case Key::RIGHT:
			right_pressed = is_pressed;
			break;
		case Key::JUMP:
			jump_pressed = is_pressed;
			break;
		case Key::EXIT:
			exit_requested = exit_requested || is_pressed;
			break;
		case Key::NONE:
			break;
	}
}
