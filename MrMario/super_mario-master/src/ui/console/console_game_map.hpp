#pragma once

#include <vector>

#include "game_map.hpp"
#include "console_ui_obj.hpp"

namespace biv {
	class ConsoleGameMap : public GameMap {
		private:
			static constexpr int SCORE_X = 5;
			static constexpr int SCORE_Y = 1;
			
			char** map;
			int score = 0;
			
			std::vector<ConsoleUIObject*> objs;
			
		public:
			ConsoleGameMap(const int height, const int width);
			~ConsoleGameMap();
			
			void add_obj(ConsoleUIObject*);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(ConsoleUIObject*);
			void set_score(const int score) noexcept override;
			void remove_objs() override;
			void show() const noexcept override;
	};
}
