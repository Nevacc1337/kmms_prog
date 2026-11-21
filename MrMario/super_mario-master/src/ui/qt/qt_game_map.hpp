#pragma once

#include <vector>

#include <QImage>

#include "game_map.hpp"
#include "qt_game_view.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
	class QtGameMap : public GameMap {
		private:
			QtGameView* view;
			QImage frame;
			int visible_cols;
			int score = 0;

			std::vector<QtUIObject*> objs;

		public:
			QtGameMap(const int height, const int width);
			~QtGameMap();

			void add_obj(QtUIObject*);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(QtUIObject*);
			void set_score(const int score) noexcept override;
			void remove_objs() override;
			void show() const noexcept override;

		private:
			void paint_score(QPainter&) const;
	};
}
