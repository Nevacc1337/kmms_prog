#pragma once

#include <QObject>

#include "keyboard.hpp"

class QEvent;
class QKeyEvent;

namespace biv {
	class QtKeyboard : public QObject, public KeyBoard {
		private:
			bool left_pressed = false;
			bool right_pressed = false;
			bool jump_pressed = false;
			bool exit_requested = false;

		public:
			UserInput get_user_input() override;
			void off() override;
			void on() override;

		protected:
			bool eventFilter(QObject* watched, QEvent* event) override;

		private:
			void process_key(const QKeyEvent* event, const bool is_pressed);
	};
}
