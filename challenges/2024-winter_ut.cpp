#include "gtest/gtest.h"

#define WITHIN_VS

#include "2024-winter.h"

TEST(_2024_WINTER, _0_BASIC)
{
	return;

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

TEST(_2024_WINTER, _1_HARVESTER)
{
	return;
	vector<string> replay =
	{
"	18 9",
"69",
"0 0 WALL -1 0 X 0 0",
"1 0 WALL -1 0 X 0 0",
"2 0 WALL -1 0 X 0 0",
"3 0 WALL -1 0 X 0 0",
"4 0 WALL -1 0 X 0 0",
"5 0 WALL -1 0 X 0 0",
"6 0 WALL -1 0 X 0 0",
"7 0 WALL -1 0 X 0 0",
"8 0 WALL -1 0 X 0 0",
"9 0 WALL -1 0 X 0 0",
"10 0 WALL -1 0 X 0 0",
"11 0 WALL -1 0 X 0 0",
"12 0 WALL -1 0 X 0 0",
"13 0 WALL -1 0 X 0 0",
"14 0 WALL -1 0 X 0 0",
"15 0 WALL -1 0 X 0 0",
"16 0 WALL -1 0 X 0 0",
"17 0 WALL -1 0 X 0 0",
"0 1 WALL -1 0 X 0 0",
"5 2 A -1 0 X 0 0",
"17 1 WALL -1 0 X 0 0",
"0 2 WALL -1 0 X 0 0",
"1 2 ROOT 1 1 N 0 1",
"17 2 WALL -1 0 X 0 0",
"0 3 WALL -1 0 X 0 0",
"17 3 WALL -1 0 X 0 0",
"0 4 WALL -1 0 X 0 0",
"1 4 WALL -1 0 X 0 0",
"2 4 WALL -1 0 X 0 0",
"3 4 WALL -1 0 X 0 0",
"4 4 WALL -1 0 X 0 0",
"5 4 WALL -1 0 X 0 0",
"6 4 WALL -1 0 X 0 0",
"7 4 WALL -1 0 X 0 0",
"8 4 WALL -1 0 X 0 0",
"9 4 WALL -1 0 X 0 0",
"10 4 WALL -1 0 X 0 0",
"11 4 WALL -1 0 X 0 0",
"12 4 WALL -1 0 X 0 0",
"13 4 WALL -1 0 X 0 0",
"14 4 WALL -1 0 X 0 0",
"15 4 WALL -1 0 X 0 0",
"17 4 WALL -1 0 X 0 0",
"0 5 WALL -1 0 X 0 0",
"5 6 A -1 0 X 0 0",
"17 5 WALL -1 0 X 0 0",
"0 6 WALL -1 0 X 0 0",
"1 6 ROOT 0 2 N 0 2",
"17 6 WALL -1 0 X 0 0",
"0 7 WALL -1 0 X 0 0",
"17 7 WALL -1 0 X 0 0",
"0 8 WALL -1 0 X 0 0",
"1 8 WALL -1 0 X 0 0",
"2 8 WALL -1 0 X 0 0",
"3 8 WALL -1 0 X 0 0",
"4 8 WALL -1 0 X 0 0",
"5 8 WALL -1 0 X 0 0",
"6 8 WALL -1 0 X 0 0",
"7 8 WALL -1 0 X 0 0",
"8 8 WALL -1 0 X 0 0",
"9 8 WALL -1 0 X 0 0",
"10 8 WALL -1 0 X 0 0",
"11 8 WALL -1 0 X 0 0",
"12 8 WALL -1 0 X 0 0",
"13 8 WALL -1 0 X 0 0",
"14 8 WALL -1 0 X 0 0",
"15 8 WALL -1 0 X 0 0",
"16 8 WALL -1 0 X 0 0",
"17 8 WALL -1 0 X 0 0",
"10 0 1 1",
"10 0 1 1",
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
		game.update();
		game.gather_resources();

		for (pair<const int, player_t> const& it_player : game.players())
		{
			for (auto const& it_root : it_player.second.roots)
			{
				auto action = it_root.grow(game);
				if (!action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _2_HARVESTER)
{
	return;
	vector<string> replay =
	{
"	18 9",
"77",
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
"17 1 WALL - 1 0 X 0 0",
"0 2 WALL - 1 0 X 0 0",
"1 2 ROOT 1 1 N 0 1",
"2 2 BASIC 1 3 N 1 1",
"3 2 BASIC 1 5 N 3 1",
"4 2 BASIC 1 8 N 5 1",
"5 2 HARVESTER 1 10 E 8 1",
"6 2 A - 1 0 X 0 0",
"17 2 WALL - 1 0 X 0 0",
"0 3 WALL - 1 0 X 0 0",
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
"17 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"1 6 ROOT 0 2 N 0 2",
"2 6 BASIC 0 4 N 2 2",
"3 6 BASIC 0 6 N 4 2",
"4 6 BASIC 0 7 N 6 2",
"5 6 HARVESTER 0 9 E 7 2",
"6 6 A - 1 0 X 0 0",
"17 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
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
"8 0 0 0",
"8 0 0 0",
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
		game.update();
		game.gather_resources();

		for (pair<const int, player_t> const& it_player : game.players())
		{
			for (auto const& it_root : it_player.second.roots)
			{
				auto action = it_root.grow(game);
				if (!action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _3_HARVESTER)
{
	return;
	vector<string> replay =
	{
"	18 9",
"91",
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
"17 1 WALL - 1 0 X 0 0",
"0 2 WALL - 1 0 X 0 0",
"1 2 ROOT 1 1 N 0 1",
"2 2 BASIC 1 3 N 1 1",
"3 2 BASIC 1 5 N 3 1",
"4 2 HARVESTER 1 8 E 5 1",
"5 2 A - 1 0 X 0 0",
"17 2 WALL - 1 0 X 0 0",
"0 3 WALL - 1 0 X 0 0",
"4 3 BASIC 1 9 N 8 1",
"5 3 BASIC 1 12 N 9 1",
"6 3 BASIC 1 14 N 12 1",
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
"1 5 BASIC 0 25 N 24 2",
"2 5 BASIC 0 24 N 4 2",
"3 5 BASIC 0 16 N 6 2",
"4 5 BASIC 0 10 N 7 2",
"5 5 BASIC 0 11 N 10 2",
"6 5 BASIC 0 15 N 11 2",
"7 5 BASIC 0 19 N 15 2",
"8 5 BASIC 0 22 N 19 2",
"17 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"1 6 ROOT 0 2 N 0 2",
"2 6 BASIC 0 4 N 2 2",
"3 6 BASIC 0 6 N 4 2",
"4 6 HARVESTER 0 7 E 6 2",
"5 6 BASIC 0 13 N 11 2",
"6 6 BASIC 0 18 N 15 2",
"7 6 BASIC 0 23 N 19 2",
"17 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"4 7 BASIC 0 21 N 17 2",
"5 7 BASIC 0 17 N 13 2",
"6 7 BASIC 0 20 N 18 2",
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
"35 0 0 0",
"0 0 0 0",
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
		game.update();
		game.gather_resources();

		for (pair<const int, player_t> const& it_player : game.players())
		{
			for (auto const& it_root : it_player.second.roots)
			{
				auto action = it_root.grow(game);
				if (!action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _4_TENTACLE)
{
	vector<string> replay =
	{
"	18 8",
//"104",
"82",
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
"1 1 WALL - 1 0 X 0 0",
"2 1 WALL - 1 0 X 0 0",
"3 1 WALL - 1 0 X 0 0",
"4 1 WALL - 1 0 X 0 0",
"5 1 WALL - 1 0 X 0 0",
"6 1 WALL - 1 0 X 0 0",
"7 1 WALL - 1 0 X 0 0",
"8 1 WALL - 1 0 X 0 0",
"9 1 WALL - 1 0 X 0 0",
"10 1 WALL - 1 0 X 0 0",
"11 1 WALL - 1 0 X 0 0",
"12 1 WALL - 1 0 X 0 0",
"13 1 WALL - 1 0 X 0 0",
"14 1 WALL - 1 0 X 0 0",
"15 1 WALL - 1 0 X 0 0",
"16 1 WALL - 1 0 X 0 0",
"17 1 WALL - 1 0 X 0 0",
"0 2 WALL - 1 0 X 0 0",
"1 2 ROOT 1 1 N 0 1",
/*"2 2 BASIC 1 3 N 1 1",*/
/*"3 2 BASIC 1 5 N 3 1",*/
/*"4 2 BASIC 1 8 N 5 1",*/
/*"5 2 BASIC 1 10 N 8 1",*/
/*"6 2 BASIC 1 12 N 10 1",*/
/*"7 2 BASIC 1 14 N 12 1",*/
/*"8 2 BASIC 1 16 N 14 1",*/
/*"9 2 BASIC 1 18 N 16 1",*/
/*"10 2 BASIC 1 20 N 18 1",*/
/*"11 2 BASIC 1 21 N 20 1",*/
/*"12 2 BASIC 1 24 N 21 1",*/
/*"13 2 BASIC 0 19 N 13 2",*/
/*"14 2 BASIC 0 23 N 11 2",*/
"17 2 WALL - 1 0 X 0 0",
"0 3 WALL - 1 0 X 0 0",
/*"13 3 BASIC 0 13 N 11 2",*/
/*"14 3 BASIC 0 11 N 9 2",*/
/*"15 3 BASIC 0 15 N 7 2",*/
"17 3 WALL - 1 0 X 0 0",
"0 4 WALL - 1 0 X 0 0",
/*"14 4 BASIC 0 9 N 6 2",*/
/*"15 4 BASIC 0 7 N 4 2",*/
"17 4 WALL - 1 0 X 0 0",
"0 5 WALL - 1 0 X 0 0",
/*"12 5 BASIC 0 22 N 17 2",*/
/*"13 5 BASIC 0 17 N 6 2",*/
/*"14 5 BASIC 0 6 N 4 2",*/
/*"15 5 BASIC 0 4 N 2 2",*/
"16 5 ROOT 0 2 N 0 2",
"17 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"1 6 WALL - 1 0 X 0 0",
"2 6 WALL - 1 0 X 0 0",
"3 6 WALL - 1 0 X 0 0",
"4 6 WALL - 1 0 X 0 0",
"5 6 WALL - 1 0 X 0 0",
"6 6 WALL - 1 0 X 0 0",
"7 6 WALL - 1 0 X 0 0",
"8 6 WALL - 1 0 X 0 0",
"9 6 WALL - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"11 6 WALL - 1 0 X 0 0",
"12 6 WALL - 1 0 X 0 0",
"13 6 WALL - 1 0 X 0 0",
"14 6 WALL - 1 0 X 0 0",
"15 6 WALL - 1 0 X 0 0",
"16 6 WALL - 1 0 X 0 0",
"17 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"1 7 WALL - 1 0 X 0 0",
"2 7 WALL - 1 0 X 0 0",
"3 7 WALL - 1 0 X 0 0",
"4 7 WALL - 1 0 X 0 0",
"5 7 WALL - 1 0 X 0 0",
"6 7 WALL - 1 0 X 0 0",
"7 7 WALL - 1 0 X 0 0",
"8 7 WALL - 1 0 X 0 0",
"9 7 WALL - 1 0 X 0 0",
"10 7 WALL - 1 0 X 0 0",
"11 7 WALL - 1 0 X 0 0",
"12 7 WALL - 1 0 X 0 0",
"13 7 WALL - 1 0 X 0 0",
"14 7 WALL - 1 0 X 0 0",
"15 7 WALL - 1 0 X 0 0",
"16 7 WALL - 1 0 X 0 0",
"17 7 WALL - 1 0 X 0 0",
"39 50 50 0",
"39 50 50 0",
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
		game.update();
		game.gather_resources();

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			for (auto const& it_root : it_player.second.roots)
			{
				auto action = it_root.grow(game);
				if (!action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					action->perform(game);
			}
		}
	}
}