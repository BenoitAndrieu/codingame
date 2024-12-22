#include "gtest/gtest.h"

#define WITHIN_VS

#include "2024-winter.h"

TEST(_2024_WINTER, VERY_EASY)
{
	vector<string> replay =
	{
"18 9",
"81",
"0 0 WALL - 1 0 X 0 0",
"1 0 WALL - 1 0 X 0 0",
"2 0 WALL - 1 0 X 0 0",
"3 0 WALL - 1 0 X 0 0",
"4 0 WALL - 1 0 X 0 0",
"5 0 WALL - 1 0 X 0 0",
"6 0 WALL - 1 0 X 0 0",
"7 0 WALL - 1 0 X 0 0",
"8 0 WALL - 1 0 X 0 0",
"9 0 WALL - 1 0 X 0 0",
"10 0 WALL - 1 0 X 0 0",
"11 0 WALL - 1 0 X 0 0",
"12 0 WALL - 1 0 X 0 0",
"13 0 WALL - 1 0 X 0 0",
"14 0 WALL - 1 0 X 0 0",
"15 0 WALL - 1 0 X 0 0",
"16 0 WALL - 1 0 X 0 0",
"17 0 WALL - 1 0 X 0 0",
"0 1 WALL - 1 0 X 0 0",
"6 1 A - 1 0 X 0 0",
"12 1 A - 1 0 X 0 0",
"15 1 A - 1 0 X 0 0",
"17 1 WALL - 1 0 X 0 0",
"0 2 WALL - 1 0 X 0 0",
"1 2 ROOT 1 1 N 0 1",
"4 2 A - 1 0 X 0 0",
"9 2 A - 1 0 X 0 0",
"17 2 WALL - 1 0 X 0 0",
"0 3 WALL - 1 0 X 0 0",
"7 3 A - 1 0 X 0 0",
"11 3 A - 1 0 X 0 0",
"17 3 WALL - 1 0 X 0 0",
"0 4 WALL - 1 0 X 0 0",
"1 4 WALL - 1 0 X 0 0",
"2 4 WALL - 1 0 X 0 0",
"3 4 WALL - 1 0 X 0 0",
"4 4 WALL - 1 0 X 0 0",
"5 4 WALL - 1 0 X 0 0",
"6 4 WALL - 1 0 X 0 0",
"7 4 WALL - 1 0 X 0 0",
"8 4 WALL - 1 0 X 0 0",
"9 4 WALL - 1 0 X 0 0",
"10 4 WALL - 1 0 X 0 0",
"11 4 WALL - 1 0 X 0 0",
"12 4 WALL - 1 0 X 0 0",
"13 4 WALL - 1 0 X 0 0",
"14 4 WALL - 1 0 X 0 0",
"15 4 WALL - 1 0 X 0 0",
"17 4 WALL - 1 0 X 0 0",
"0 5 WALL - 1 0 X 0 0",
"6 5 A - 1 0 X 0 0",
"12 5 A - 1 0 X 0 0",
"15 5 A - 1 0 X 0 0",
"17 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"1 6 ROOT 0 2 N 0 2",
"4 6 A - 1 0 X 0 0",
"9 6 A - 1 0 X 0 0",
"17 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"7 7 A - 1 0 X 0 0",
"11 7 A - 1 0 X 0 0",
"17 7 WALL - 1 0 X 0 0",
"0 8 WALL - 1 0 X 0 0",
"1 8 WALL - 1 0 X 0 0",
"2 8 WALL - 1 0 X 0 0",
"3 8 WALL - 1 0 X 0 0",
"4 8 WALL - 1 0 X 0 0",
"5 8 WALL - 1 0 X 0 0",
"6 8 WALL - 1 0 X 0 0",
"7 8 WALL - 1 0 X 0 0",
"8 8 WALL - 1 0 X 0 0",
"9 8 WALL - 1 0 X 0 0",
"10 8 WALL - 1 0 X 0 0",
"11 8 WALL - 1 0 X 0 0",
"12 8 WALL - 1 0 X 0 0",
"13 8 WALL - 1 0 X 0 0",
"14 8 WALL - 1 0 X 0 0",
"15 8 WALL - 1 0 X 0 0",
"16 8 WALL - 1 0 X 0 0",
"17 8 WALL - 1 0 X 0 0",
"10 0 0 0",
"10 0 0 0",
"1",
	};

	inputs inputs(replay);

	string input = inputs.get_next();
	int width, height;
	{
		stringstream ss(input);
		ss >> width >> height;
	}

	game_t game(inputs, height, width);
	while (true)
	{
		for (auto const& it_root : game.players().at(game_t::me_id).roots)
		{
			auto action = it_root.grow(game);
			if (!action)
				cout << "WAIT" << endl;
			else
				action->perform(game);
		}
	}
}