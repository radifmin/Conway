#include <iostream>
#include <vector>
#include <random>
#include "Field.h"

#define pixel char('*')

int main()
{
	const int width = 121;
	const int height = 31;
	const int generations = 100;

	Field field(width, height);
	//field.create_random_field();
	field.create_glider(0, 0);
	field.fill(0, 1);

	field.print();
	for (int i = 0; i < generations; i++) {
		getchar();
		//Sleep(200);
		field.change();
		field.print();
	}

	return 0;
}