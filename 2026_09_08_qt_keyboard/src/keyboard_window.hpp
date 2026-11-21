#pragma once
 
#include <cstddef>
 
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QWidget>
 
#include "keyboard.hpp"
#include "mood_face.hpp"
 
namespace biv {
	class KeyBoardWindow : public QWidget {
		Q_OBJECT
 
		private:
			QLineEdit* display;
			QLabel* phrase;
			MoodFace* face;
			KeyBoard* keyboard;
 
			int mood_points = 0;
 
		public:
			KeyBoardWindow(QWidget* parent = nullptr);
			
		protected:
			void keyPressEvent(QKeyEvent* event) override;
 
		private slots:
			void on_symbol_pressed(const QString& symbol);
			void on_backspace_pressed();
			void on_enter_pressed();
 
		private:
			void change_mood(const int delta);
			QString get_phrase() const;
	};
}