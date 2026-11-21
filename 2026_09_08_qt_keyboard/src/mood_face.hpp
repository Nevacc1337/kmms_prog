#pragma once

#include <QPaintEvent>
#include <QWidget>

namespace biv {
	// mood = 0.0 -> грустный, mood = 1.0 -> счастливый
	class MoodFace : public QWidget {
		private:
			double mood;

		public:
			MoodFace(QWidget* parent = nullptr);

			void set_mood(const double value);

		protected:
			void paintEvent(QPaintEvent* event) override;
	};
}
