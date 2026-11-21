#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			static constexpr float H_SPEED = 0.25f;
			static constexpr int REWARD = 50;

			float left_bound;
			float right_bound;

		public:
			FlyingEnemy(
				const Coord& top_left, const int width, const int height,
				const int patrol_range
			);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;
			int get_reward() const noexcept override;

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void move_map_horizontally(const float offset) noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
	};
}
