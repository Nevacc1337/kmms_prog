#include "console_game_map.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>

#ifdef WINDOWS_CONSOLE
	#define NOMINMAX
	#include <windows.h>
#endif

#ifdef LINUX_CONSOLE
	#include <ncurses.h>
#endif

using biv::ConsoleGameMap;

ConsoleGameMap::ConsoleGameMap(const int height, const int width) 
	: GameMap(height, width) {

	map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width + 1];
	}
		
	clear();
}

ConsoleGameMap::~ConsoleGameMap() {
	for (int i = 0; i < height; i++) {
		delete [] map[i];
	}
	delete [] map;
}

void ConsoleGameMap::add_obj(ConsoleUIObject* obj) {
	objs.push_back(obj);
}

void ConsoleGameMap::clear() noexcept {
	// Воздух
	for (int i = 0; i < width; i++) {
		map[0][i] = ' ';
	}
	map[0][width] = '\0';
	
	for (int i = 1; i < height - 3; i++) {
		std::sprintf(map[i], "%s", map[0]);
	}
	
	// Вода
	for (int i = 0; i < width; i++) {
		map[height - 3][i] = '~';
	}
	map[height - 3][width] = '\0';
	
	for (int i = height - 2; i < height; i++) {
		std::sprintf(map[i], "%s", map[height - 3]);
	}
}

void ConsoleGameMap::refresh() noexcept {
	clear();
	
	for (ConsoleUIObject* obj: objs) {
		int left = obj->get_left();
		int top = obj->get_top();
		int right = obj->get_right();
		int bottom = obj->get_bottom();
		
		char brush = obj->get_brush();
		
		for (int i = left; i < right; i++) {
			for (int j = top; j < bottom; j++) {
				if (is_on_map(i, j)) {
					map[j][i] = brush;
				}
			}
		}
	}
	
	char text[32];
	std::snprintf(text, sizeof(text), "Score: %d", score);
	for (int i = 0; text[i] != '\0'; i++) {
		if (is_on_map(SCORE_X + i, SCORE_Y)) {
			map[SCORE_Y][SCORE_X + i] = text[i];
		}
	}
}

void ConsoleGameMap::set_score(const int score) noexcept {
	this->score = score;
}

void ConsoleGameMap::remove_obj(ConsoleUIObject* obj) {
	objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void ConsoleGameMap::remove_objs() {
	objs.clear();
}

void ConsoleGameMap::show() const noexcept {
	#ifdef WINDOWS_CONSOLE
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < height; i++) {
			COORD coord;
			coord.X = 0;
			coord.Y = static_cast<SHORT>(i);
			SetConsoleCursorPosition(handle, coord);
			DWORD written = 0;
			WriteConsoleA(handle, map[i], static_cast<DWORD>(width), &written, NULL);
		}
	#elif defined(LINUX_CONSOLE)
		for (int i = 0; i < height; i++) {
			//printw("%s", map[i]);
			move(i, 0); 
			addstr(map[i]);
		}
		::refresh();
	#endif
}
