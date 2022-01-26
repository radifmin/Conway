#include "Field.h"
#include <random>
#include <iostream>

Field::Field(int width, int height) :width(width), height(height)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int x = j - width / 2;
			int y = height / 2 - i;
			cells.emplace_back(x, y, false);
		}
	}
	// set neighbours
	for (size_t i = 0; i < cells.size(); i++) {
		cells[i]().push_back(&get(cells[i].x - 1, cells[i].y + 1));
		cells[i]().push_back(&get(cells[i].x - 1, cells[i].y));
		cells[i]().push_back(&get(cells[i].x - 1, cells[i].y - 1));
		cells[i]().push_back(&get(cells[i].x, cells[i].y - 1));
		cells[i]().push_back(&get(cells[i].x + 1, cells[i].y - 1));
		cells[i]().push_back(&get(cells[i].x + 1, cells[i].y));
		cells[i]().push_back(&get(cells[i].x + 1, cells[i].y + 1));
		cells[i]().push_back(&get(cells[i].x, cells[i].y + 1));
	}
}
void Field::change()
{
	std::vector<Cell> next_generation;
	for (size_t i = 0; i < cells.size(); i++) {
		int alive_neighbours_count = cells[i].alive_neighbours();
		next_generation.push_back(cells[i]);
		if (cells[i].is_alive()) {
			if (alive_neighbours_count < 2 || alive_neighbours_count > 3) {
				next_generation[i].kill();
			}
		}
		else if (alive_neighbours_count == 3) {
			next_generation[i].revive();
		}
	}
	cells = next_generation;
}
Field::Cell& Field::get(int x, int y)
{
	int beg = width * height / 2;
	int x_new = x;
	if (abs(x) > width / 2) {
		x_new = x % (width / 2) + (x > 0 ? -1 : 1) * (width / 2 + (width % 2 != 0));
	}
	int y_new = -y * (width);
	if (abs(y) > height / 2) {
		y_new = (y - y % (height / 2)) * (width);
	}
	return cells[beg + x_new + y_new];
}
void Field::fill(int x, int y)
{
	get(x, y) = pixel;
}
void Field::create_glider(int x, int y)
{
	fill(x, y);
	fill(x - 1, y - 1);
	fill(x + 1, y - 2);
	fill(x, y - 2);
	fill(x - 1, y - 2);
}
void Field::create_random_field()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	for (size_t i = 0; i < cells.size(); i++) {
		std::uniform_int_distribution<std::mt19937::result_type> num(1, 7);
		if (num(rng) > 6) {
			cells[i].revive();
		}
	}
}
void Field::print() const
{
	for (size_t i = 0; i < cells.size(); i++)
		std::cout << cells[i];
}