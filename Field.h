#pragma once
#include <vector>
#include <ostream>

#define pixel char('*')

class Field
{
	class Cell
	{
		char p;
		std::vector<Cell*> neighbours;
	public:
		const int x;
		const int y;
		Cell(int _x, int _y, bool alive) :x(_x), y(_y)
		{
			if (alive) p = pixel;
			else p = ' ';
		}
		bool is_alive() const { return p != ' '; }
		int alive_neighbours() const
		{
			int count = 0;
			for (size_t i = 0; i < neighbours.size(); i++)
				if (neighbours[i]->is_alive()) count++;
			return count;
		}
		void kill() { p = ' '; }
		void revive() { p = pixel; }
		Cell& operator=(const Cell& other)
		{
			*const_cast<int*>(&x) = other.x;
			*const_cast<int*>(&y) = other.y;
			p = other.p;
			return *this;
		}
		Cell& operator=(const char& other) {
			p = other;
			return *this;
		}
		Cell& operator[](int i) { return *neighbours[i]; }
		std::vector<Cell*>& operator()() { return neighbours; }
		friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
			return os << cell.p;
		}
	}; // Cell
	
	const int width;
	const int height;
	std::vector<Cell> cells;
	Cell& get(int x, int y);

public:
	Field(int width, int height);
	void change();
	void fill(int x, int y);
	void create_glider(int x, int y);
	void create_random_field();
	Cell& operator[](int i) { return cells[i]; }
	std::vector<Cell>& operator()() { return cells; }
	void print() const;
};

