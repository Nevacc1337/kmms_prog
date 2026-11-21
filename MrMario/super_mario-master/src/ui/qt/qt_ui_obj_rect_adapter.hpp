#pragma once

#include <QPixmap>
#include <QRect>

#include "qt_ui_obj.hpp"
#include "rect.hpp"

namespace biv {
	class QtUIObjectRectAdapter : virtual public Rect, public QtUIObject {
		public:
			int get_bottom() const noexcept override;
			int get_left() const noexcept override;
			int get_right() const noexcept override;
			int get_top() const noexcept override;

		protected:
			void paint_sprite(QPainter&, const QPixmap& sprite) const;
			void paint_tiles(QPainter&, const QPixmap& tile) const;
			void paint_tiles(
				QPainter&, const QPixmap& top_tile, const QPixmap& tile
			) const;

		private:
			QRect get_pixel_rect() const noexcept;
	};
}
