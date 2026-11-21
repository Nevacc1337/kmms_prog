/**
	- Как объекты раскладываются по контейнерам?
*/

#pragma once

#include <vector>

#include "carrier.hpp"
#include "collisionable.hpp"
#include "map_movable.hpp"
#include "mario.hpp"
#include "movable.hpp"
#include "rect.hpp"

namespace biv {
	class Game {
		private:
			std::vector<Carrier*> carrier_objs;
			std::vector<MapMovable*> map_movable_objs;
			std::vector<Rect*> static_objs;
			std::vector<Collisionable*> collisionable_objs;
			std::vector<Movable*> movable_objs;
			
			Mario* mario = nullptr;
			
			int score = 0;
			int level_start_score = 0;
			
			bool is_finished_ = false;
			bool is_level_end_ = false;
			
		public:
			Game();
			
			void add_carrier(Carrier*);
			void add_collisionable(Collisionable*);
			void add_map_movable(MapMovable*);
			void add_mario(Mario*);
			void add_movable(Movable*);
			void add_static_obj(Rect*);
			
			void check_horizontally_static_collisions() noexcept;
			void check_mario_collision();
			bool check_static_collisions(Collisionable* obj) const noexcept;
			void check_vertically_static_collisions() noexcept;
			
			void finish() noexcept;
			
			int get_score() const noexcept;
			
			bool is_finished() const noexcept;
			bool is_level_end() const noexcept;
			
			void move_map_left() noexcept;
			void move_map_right() noexcept;
			void move_objs_horizontally() noexcept;
			void move_objs_vertically() noexcept;
			
			void remove_carrier(Carrier*);
			void remove_collisionable(Collisionable*);
			void remove_map_movable(MapMovable*);
			void remove_mario() noexcept;
			void remove_movable(Movable*);
			void remove_objs();
			void remove_static_obj(Rect*);
			
			void start_level() noexcept;

		private:
			Carrier* find_mario_carrier() const noexcept;

			template<class T>
			void remove_obj(std::vector<T*>& container, T* obj);
	};
}
