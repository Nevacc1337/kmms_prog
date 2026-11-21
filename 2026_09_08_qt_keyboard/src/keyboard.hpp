#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

#include <QGridLayout>
#include <QString>
#include <QWidget>

#include "keyboard_button.hpp"
#include "keyboard_data.hpp"
#include "key_data.hpp"

namespace biv {
	class KeyBoard : public QWidget {
		Q_OBJECT

		private:
			const int button_width;
			std::unordered_map<int, KeyBoardButton*> buttons;
			
			KeyBoardData keyboard_data;

			KeyBoardButton* backspace_btn = nullptr;
			KeyBoardButton* enter_btn = nullptr;
			KeyBoardButton* space_btn = nullptr;
		
		public:
			KeyBoard(const int width, QWidget* parent = nullptr);
			
			void animate_button(const int code);
			void animate_backspace();
			void animate_enter();
			void animate_space();

			bool is_key_allowed(const int code) const noexcept;

		signals:
			// Испускаются при нажатии на кнопку: и мышкой, и физической клавишей
			void symbol_pressed(const QString& symbol);
			void backspace_pressed();
			void enter_pressed();
			
		private:
			void create_buttons(
				const std::vector<KeyData>& data, 
				QGridLayout* layout, 
				const int line,
				const int start_position
			);
	};
}
