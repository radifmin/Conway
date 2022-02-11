#pragma once
#include <vector>
#include <ostream>
#include <string>
#include <iostream>

#define pix char('@')
#define empty_pix char(' ')

class GameField
{
	class Generation
	{
		class Cell
		{
			std::vector<Cell*> neighbours;
			bool alive;
		public:
			const int x;
			const int y;
			Cell(const int _x, const int _y, const bool _alive) :x(_x), y(_y), alive(_alive) {}
			//Cell copy() const { return Cell(x, y, alive); }
			bool is_alive() const { return alive; }
			void push_back(Cell& cell) { neighbours.emplace_back(&cell); }
			int alive_neighbours() const {
				int count = 0;
				for (size_t i = 0; i < neighbours.size(); i++)
					if (neighbours[i]->is_alive()) count++;
				return count;
			}
			void kill() { alive = false; }
			void reproduce() { alive = true; }
			Cell& operator=(const Cell& other) {
				*const_cast<int*>(&x) = other.x;
				*const_cast<int*>(&y) = other.y;
				alive = other.alive;
				return *this;
			}
			//Cell& operator[](int i) { return *neighbours[i]; }
		}; // Cell

		std::vector<Cell> cells;
		const int width;
		const int height;
		void initialize_neighbours();

	public:
		Generation(int _width, int _height);
		//void emplace_back(int x, int y, bool alive);
		void change();
		int size() const;
		Cell& get(int x, int y);
		void fill(int x, int y);
		void create_glider(int x, int y);
		void create_random_field();
		//Cell& operator[](int i);
		void print() const;
		void save_as_ppm(const std::string& filename) const;
	}; // Generation

	const int width;
	const int height;
	std::vector<Generation> generations;

public:
	GameField(int _width, int _height);
	void change();
	void fill(int x, int y);
	void create_glider(int x, int y);
	void create_random_field();
	int size() const;
	Generation& current();
	Generation& operator[](int i) { return generations[i]; }
	void print() const;
	void save_as_gif(const std::string& directory) const;
}; // GameField


class test
{
public:
	static void _GameField()
	{
		const int width = 121;
		const int height = 31;
		const int generations = 1000;

		//GameField field(width, height);
		//field.create_glider(0, 0);
		//field.create_glider(-2, 3);
		//field.fill(0, 1);
		//field.fill(-1, 2);
		auto gen = GameField(width, height)[0];
		//gen.create_glider(0, 0);
		//gen.create_random_field();
		//gen.fill(-1, 1);
		//gen.fill(-1, 0);
		//gen.fill(0, 0);
		//gen.fill(0, 1);

		gen.fill(0, 0);
		gen.fill(-3, -1);
		gen.fill(-2, -1);
		gen.fill(-2, 1);
		gen.fill(1, -1);
		gen.fill(2, -1);
		gen.fill(3, -1);


		//field.fill(0, 0);

		//field.print();
		gen.print();

		for (int i = 0; i < generations; i++) {
			getchar();
			//Sleep(200);
			//field.change();
			//field.print();
			gen.change();
			gen.print();
		}
	}
	static void _save_as_ppm()
	{
		const int width = 1001;
		const int height = 1001;
		const int generations = 600;
		auto gen = GameField(width, height)[0];
		//field.create_glider(0, 0);
		//gen.create_glider(0, 0);
		gen.fill(0, 0);
		//gen.fill(-3, -1);
		//gen.fill(-2, -1);
		//gen.fill(-2, 1);
		//gen.fill(1, -1);
		//gen.fill(2, -1);
		//gen.fill(3, -1);
		//gen.create_random_field();
		for (int i = 0; i < generations; i++) {
			std::cout << std::to_string(i + 1) + "/" + std::to_string(generations) + "\n";
			gen.change();
		}

		gen.save_as_ppm("C:\\out");
	}
	static void _save_as_gif() {
		const int width = 21;
		const int height = 21;
		const int generations = 10;
		GameField field(width, height);
		field.create_glider(0, 0);

		for (int i = 0; i < generations; i++) {
			field.change();
		}

		field.save_as_gif("C:\\1gif");
	}
};