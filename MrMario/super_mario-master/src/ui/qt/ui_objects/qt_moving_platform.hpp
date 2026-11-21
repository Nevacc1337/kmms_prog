#pragma once

#include "moving_platform.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtMovingPlatform : public MovingPlatform, public QtUIObjectRectAdapter {
		public:
			QtMovingPlatform(
				const Coord& top_left, const int width, const int height,
				const int patrol_range
			);

			int get_layer() const noexcept override;
			void paint(QPainter&) const override;
	};
}
