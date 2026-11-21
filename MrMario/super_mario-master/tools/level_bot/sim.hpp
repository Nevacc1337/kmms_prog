#pragma once
#define private public
#define protected public
#include <thread>
#include <cstdio>
#include "console_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "keyboard.hpp"
#undef private
#undef protected

struct Sim {
	biv::Game game;
	biv::UIFactory* f;
	biv::GameMap* map;
	biv::GameLevel* level;
	biv::Mario* mario;
	int deaths = 0, levels_done = 0, frame = 0;
	bool finished = false;
	Sim(biv::GameLevel* (*mk)(biv::UIFactory*)) {
		f = new biv::ConsoleUIFactory(&game);
		map = f->get_game_map(30, 200);
		level = mk(f);
		mario = f->get_mario();
	}
	// one frame of main loop; returns true if game finished
	void step(biv::UserInput in) {
		frame++;
		switch (in) {
			case biv::UserInput::MAP_LEFT:
			case biv::UserInput::MAP_LEFT_AND_JUMP:
				mario->move_map_left();
				if (!game.check_static_collisions(mario)) game.move_map_left();
				mario->move_map_right();
				if (in == biv::UserInput::MAP_LEFT_AND_JUMP) mario->jump();
				break;
			case biv::UserInput::MAP_RIGHT:
			case biv::UserInput::MAP_RIGHT_AND_JUMP:
				mario->move_map_right();
				if (!game.check_static_collisions(mario)) game.move_map_right();
				mario->move_map_left();
				if (in == biv::UserInput::MAP_RIGHT_AND_JUMP) mario->jump();
				break;
			case biv::UserInput::MARIO_JUMP: mario->jump(); break;
			case biv::UserInput::EXIT: game.finish(); break;
			default: break;
		}
		game.move_objs_horizontally();
		game.check_horizontally_static_collisions();
		game.move_objs_vertically();
		game.check_mario_collision();
		game.check_vertically_static_collisions();
		if (map->is_below_map(mario->get_top()) || !mario->is_active()) {
			deaths++; level->restart(); mario = f->get_mario();
		}
		if (game.is_level_end()) {
			levels_done++;
			if (!level->is_final()) { level = level->get_next(); mario = f->get_mario(); game.start_level(); }
			else game.finish();
		}
	}
	void dump(int x0=0,int x1=200) {
		map->refresh();
		auto* m=(biv::ConsoleGameMap*)map;
		for(int i=0;i<30;i++){ printf("%.*s\n", x1-x0, m->map[i]+x0); }
	}
};
