#include "keyboard_window.hpp"
 
#include <algorithm>
 
#include <QHBoxLayout>
#include <QVBoxLayout>
 
using biv::KeyBoardWindow;
 
namespace {
	const int MAX_MOOD = 30;
}
 
KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Грустная Клавиатура");
	
	// Клавик и его реплики
	face = new MoodFace();
	face->setFixedSize(200, 200);
 
	phrase = new QLabel();
	phrase->setFont(QFont("Roboto", 24));
	phrase->setWordWrap(true);
 
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(face);
	smail_layout->addWidget(phrase, 1);
 
    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setFocusPolicy(Qt::NoFocus);
	display->setPlaceholderText("Помоги мне заработать лучше...");
 
	keyboard = new KeyBoard(keyboard_width);
 
    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
 
	// Сигналы клавиатуры -> слоты окна
	connect(keyboard, &KeyBoard::symbol_pressed, this, &KeyBoardWindow::on_symbol_pressed);
	connect(keyboard, &KeyBoard::backspace_pressed, this, &KeyBoardWindow::on_backspace_pressed);
	connect(keyboard, &KeyBoard::enter_pressed, this, &KeyBoardWindow::on_enter_pressed);
 
	change_mood(0);
}
 
// Физическая реализуется как при клике мышкой clicked -> сигнал -> слот.
void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
		case Qt::Key_Backspace:
			keyboard->animate_backspace();
			return;
		case Qt::Key_Return:
		case Qt::Key_Enter:
			keyboard->animate_enter();
			return;
		case Qt::Key_Space:
			keyboard->animate_space();
			return;
		default:
			break;
	}
 
	const int code = event->nativeVirtualKey();
	if (keyboard->is_key_allowed(code)) {
		keyboard->animate_button(code);
	}
}
 
//SLOTS
void KeyBoardWindow::on_symbol_pressed(const QString& symbol) {
	display->setText(display->text() + symbol);
	change_mood(1);
}
 
void KeyBoardWindow::on_backspace_pressed() {
	QString text = display->text();
	if (text.isEmpty()) {
		return;
	}
	text.chop(1);
	display->setText(text);
	change_mood(-1);
}
 
void KeyBoardWindow::on_enter_pressed() {
	if (display->text().isEmpty()) {
		return;
	}
	display->clear();
	change_mood(3);
}
 
//PRIVATE
void KeyBoardWindow::change_mood(const int delta) {
	mood_points = std::clamp(mood_points + delta, 0, MAX_MOOD);
	face->set_mood(static_cast<double>(mood_points) / MAX_MOOD);
	phrase->setText(get_phrase());
}
 
QString KeyBoardWindow::get_phrase() const {
	if (mood_points == 0) {
		return "Мне грустно... Пожалуйста, потыкай по моим клавишам.";
	}
	if (mood_points < 10) {
		return "Ой, мне уже чуточку лучше!";
	}
	if (mood_points < 20) {
		return "Продолжай, мне нравится!";
	}
	if (mood_points < MAX_MOOD) {
		return "Кажется, я начинаю улыбаться :)";
	}
	return "Ура! Я счастлив! Спасибо тебе!";
}