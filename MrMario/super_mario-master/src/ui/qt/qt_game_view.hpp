#pragma once

#include <QImage>
#include <QWidget>

class QPaintEvent;

namespace biv {
	class QtGameView : public QWidget {
		private:
			QImage frame;

		public:
			QtGameView(const int frame_width, const int frame_height);

			void show_frame(const QImage& frame);

		protected:
			void paintEvent(QPaintEvent*) override;
	};
}
