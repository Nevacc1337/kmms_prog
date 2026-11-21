#pragma once

#include "full_box.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtFullBox : public FullBox, public QtUIObjectRectAdapter {
		public:
			QtFullBox(
				const Coord& top_left,
				const int width, const int height,
				UIFactory* ui_factory
			);

			int get_layer() const noexcept override;
			void paint(QPainter&) const override;
	};
}
