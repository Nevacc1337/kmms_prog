#pragma once

#include "carrier.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {
	class MovingPlatform : public RectMapMovableAdapter, public Movable, public Carrier {
		private:
			static constexpr float PLATFORM_SPEED = 0.4f;

			float left_bound;
			float right_bound;
			float last_shift = 0;

		public:
			MovingPlatform(
				const Coord& top_left, const int width, const int height,
				const int patrol_range
			);

			bool is_carrying(const Rect& obj) const noexcept override;
			float get_last_shift() const noexcept override;

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_horizontally(const float offset) noexcept override;
	};
}
