#include "GameField.h"
#include <random>
#include <fstream>

GameField::GameField(int _width, int _height) :width(_width), height(_height)
{
	Generation gen(width, height);
	generations.emplace_back(gen);
}
void GameField::fill(int x, int y)
{
	current().fill(x, y);
}
void GameField::create_glider(int x, int y)
{
	current().create_glider(x, y);
}
void GameField::create_random_field()
{
	current().create_random_field();
}
void GameField::change()
{
	Generation next_gen = current();
	next_gen.change();
	generations.emplace_back(next_gen);
}
int GameField::size() const
{
	return generations.size();
}
GameField::Generation& GameField::current()
{
	return generations[size() - 1];
}
void GameField::print() const
{
	generations[size()-1].print();
}
void GameField::save_as_gif(const std::string& directory) const
{
	//for (size_t i = 0; i < generations.size(); i++) {
	//	std::cout << std::to_string(i+1) + "/" + std::to_string(generations.size())+"\n";
	//	generations[i].save_as_ppm(directory + "\\" + std::to_string(i + 1));
	//}
	//std::vector<Magick::Image> frames;
	//Image image(Geometry(width, height), Color(255, 255, 255));
	//image.write("C:\\out.png");
}

GameField::Generation::Generation(int _width, int _height) :width(_width), height(_height)
{
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			int x = j - width / 2;
			int y = height / 2 - i;
			cells.emplace_back(x, y, false);
		}
	}

	initialize_neighbours();
}
void GameField::Generation::initialize_neighbours()
{
	//for (size_t i = 0; i < cells.size(); i++) {
	//	cells[i].push_back(get(cells[i].x - 1, cells[i].y + 1));
	//	cells[i].push_back(get(cells[i].x - 1, cells[i].y    ));
	//	cells[i].push_back(get(cells[i].x - 1, cells[i].y - 1));
	//	cells[i].push_back(get(cells[i].x    , cells[i].y - 1));
	//	cells[i].push_back(get(cells[i].x + 1, cells[i].y - 1));
	//	cells[i].push_back(get(cells[i].x + 1, cells[i].y    ));
	//	cells[i].push_back(get(cells[i].x + 1, cells[i].y + 1));
	//	cells[i].push_back(get(cells[i].x    , cells[i].y + 1));
	//}
}
void GameField::Generation::change()
{
	//initialize_neighbours();
	//std::vector<Cell> next_generation;
	//for (size_t i = 0; i < cells.size(); i++) {
	//	int count = cells[i].alive_neighbours();
	//	next_generation.emplace_back(cells[i].x, cells[i].y, cells[i].is_alive());
	//	if (cells[i].is_alive()) {
	//		if (count < 2 || count > 3) {
	//			next_generation[i].kill();
	//		}
	//	}
	//	else if (count == 3) {
	//		next_generation[i].reproduce();
	//	}
	//}
	//cells.clear();
	//cells = next_generation;
	std::vector<std::pair<int, bool>> updates;
	for (int i = 0; i < cells.size(); i++)
	{
		auto &cell = cells[i];
		int count = 0;
		//int count = cell.alive_neighbours();
		for (int nX = -1; nX <= 1; nX++) {
			int newX = nX + cell.x;
			for (int nY = -1; nY <= 1; nY++)
			{
				int newY = nY + cell.y;

				if ((nX == 0 && nY == 0)) //Cell itself 
					continue;

				if (get(newX, newY).is_alive())
					count++;
			}
		}
		if (cell.is_alive()) {
			if (count<4)
				updates.push_back({ i, false }); // kill
		}
		else if (count == 1||count==2||count==4||count==7) {
			updates.push_back({ i,true }); // reproduce
		}
	}
	for (int i = 0; i < updates.size(); i++)
		if (updates[i].second)
			cells[updates[i].first].reproduce();
		else cells[updates[i].first].kill();
}
int GameField::Generation::size() const
{
	return cells.size();
}
GameField::Generation::Cell& GameField::Generation::get(int x, int y)
{
	int newX = x;
	if (abs(x) > width / 2)
		newX = x % (width / 2) + (x > 0 ? -1 : 1) * (width / 2 + /*(width % 2 != 0)*/1);
	int newY = -y * (width);
	if (abs(y) > height / 2)
		newY = (y - y % (height / 2)) * (width);
	return cells[width * height / 2+newX+newY];
}
void GameField::Generation::fill(int x, int y)
{
	get(x, y).reproduce();
}
void GameField::Generation::create_glider(int x, int y)
{
	fill(x, y);
	fill(x - 1, y - 1);
	fill(x + 1, y - 2);
	fill(x, y - 2);
	fill(x - 1, y - 2);
}
void GameField::Generation::create_random_field()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	for (size_t i = 0; i < cells.size(); i++) {
		std::uniform_int_distribution<std::mt19937::result_type> num(1, 7);
		if (num(rng) > 6) {
			cells[i].reproduce();
		}
	}
}
void GameField::Generation::print() const
{
	for (size_t i = 0; i < size(); i++)
		if (cells[i].is_alive()) std::cout << pix;
		else std::cout << empty_pix;
}
void GameField::Generation::save_as_ppm(const std::string &filename) const
{
	std::ofstream fout;
	fout.open(filename+".ppm");
	fout << "P3\n" + std::to_string(height) + " " + std::to_string(width) + "\n1\n";

	for (int i = 0; i < cells.size(); i++) {
		if (cells[i].is_alive())fout << "1 1 1 ";
		else fout << "0 0 0 ";
	}

	fout.close();
}