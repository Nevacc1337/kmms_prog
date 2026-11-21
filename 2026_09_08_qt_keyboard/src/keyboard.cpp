#include "keyboard.hpp"

using biv::KeyBoard;

KeyBoard::KeyBoard(const int width, QWidget* parent) 
	: QWidget(parent), button_width(width / 29) {
	
    QGridLayout* keys_layout = new QGridLayout(this);
	keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);
	
	// 1-я линия
	create_buttons(keyboard_data.get_line1(), keys_layout, 0, 0);
	
	backspace_btn = new KeyBoardButton("Удалить");
	backspace_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(backspace_btn, 0, 26, 2, 3);
	connect(backspace_btn, &QPushButton::clicked, this, &KeyBoard::backspace_pressed);

	// 2-я линия
	KeyBoardButton* tab_btn = new KeyBoardButton("Tab");
	tab_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(tab_btn, 2, 0, 2, 3);
	
	create_buttons(keyboard_data.get_line2(), keys_layout, 2, 3);
	
	// 3-я линия
	KeyBoardButton* caps_btn = new KeyBoardButton("Caps");
	caps_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(caps_btn, 4, 0, 2, 4);
	
	create_buttons(keyboard_data.get_line3(), keys_layout, 4, 4);
	
	enter_btn = new KeyBoardButton("Enter");
	enter_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(enter_btn, 4, 26, 2, 3);
	connect(enter_btn, &QPushButton::clicked, this, &KeyBoard::enter_pressed);
	
	// 4-я линия
	KeyBoardButton* left_shift_btn = new KeyBoardButton("Shift");
	left_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(left_shift_btn, 6, 0, 2, 5);
	
	create_buttons(keyboard_data.get_line4(), keys_layout, 6, 5);
	
	KeyBoardButton* right_shift_btn = new KeyBoardButton("Shift");
	right_shift_btn->setMinimumSize(2 * button_width, button_width);
	keys_layout->addWidget(right_shift_btn, 6, 25, 2, 4);

	// 5-я линия
	space_btn = new KeyBoardButton();
	space_btn->setMinimumSize(8 * button_width, button_width);
	keys_layout->addWidget(space_btn, 8, 7, 2, 16);
	connect(space_btn, &QPushButton::clicked, this, [this]() {
		emit symbol_pressed(" ");
	});
}

void KeyBoard::animate_button(const int code) {
	const auto it = buttons.find(code);
	if (it != buttons.end()) {
		it->second->animateClick();
	}
}

void KeyBoard::animate_backspace() {
	backspace_btn->animateClick();
}

void KeyBoard::animate_enter() {
	enter_btn->animateClick();
}

void KeyBoard::animate_space() {
	space_btn->animateClick();
}

bool KeyBoard::is_key_allowed(const int code) const noexcept {
	return buttons.count(code) > 0;
}

//PRIVATE
void KeyBoard::create_buttons(
	const std::vector<KeyData>& data, 
	QGridLayout* layout, 
	const int line,
	const int start_position
) {
	for (int i = 0; i < static_cast<int>(data.size()); i++) {
        KeyBoardButton* btn = new KeyBoardButton(data[i].text);
		btn->setMinimumSize(button_width, button_width);
        
		layout->addWidget(btn, line, i * 2 + start_position, 2, 2);
		
		buttons[data[i].code] = btn;

		// Клик по кнопке мышкой или через animateClick дает сигнал с символом
		const QString symbol = data[i].text;
		connect(btn, &QPushButton::clicked, this, [this, symbol]() {
			emit symbol_pressed(symbol);
		});
	}
}
