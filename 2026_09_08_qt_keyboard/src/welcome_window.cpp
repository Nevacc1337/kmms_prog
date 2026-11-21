#include "welcome_window.hpp"

#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "mood_face.hpp"

using biv::WelcomeWindow;

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent) {
	resize(600, 500);
	setWindowTitle("Грустная Клавиатура");

	QLabel* title = new QLabel("Привет! Я Клавик.\nМне очень грустно...");
	title->setFont(QFont("Roboto", 24));
	title->setAlignment(Qt::AlignCenter);

	MoodFace* face = new MoodFace();
	face->setFixedSize(200, 200);

	QPushButton* start_btn = new QPushButton("Перейти к клавиатуре");
	start_btn->setFont(QFont("Roboto", 20));
	start_btn->setMinimumHeight(70);

	connect(start_btn, &QPushButton::clicked, this, &WelcomeWindow::keyboard_requested);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(title);
	layout->addWidget(face, 0, Qt::AlignCenter);
	layout->addWidget(start_btn);
}
