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
		for (organ_t const& it_root : game.players().at(game_t::me_id).roots)
		{
			optional<action_t> action = it_root.grow(game);
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
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
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
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
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
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
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
	return;
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

			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
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

TEST(_2024_WINTER, _5_SPORERS)
{
	return;
	vector<string> replay =
	{
"18 9",
"69",
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
"16 2 A - 1 0 X 0 0",
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
"16 6 A - 1 0 X 0 0",
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
"6 2 2 3",
"6 2 2 3",
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
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
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

TEST(_2024_WINTER, _6_BRONZE)
{
	return;
	vector<string> replay =
	{
"22 11",
"56",
"0 0 WALL - 1 0 X 0 0",
"1 0 ROOT 1 1 N 0 1",
"5 0 WALL - 1 0 X 0 0",
"9 0 D - 1 0 X 0 0",
"12 0 B - 1 0 X 0 0",
"17 0 WALL - 1 0 X 0 0",
"18 0 B - 1 0 X 0 0",
"0 1 WALL - 1 0 X 0 0",
"2 1 WALL - 1 0 X 0 0",
"8 1 WALL - 1 0 X 0 0",
"15 1 A - 1 0 X 0 0",
"19 1 WALL - 1 0 X 0 0",
"0 2 C - 1 0 X 0 0",
"8 2 WALL - 1 0 X 0 0",
"11 2 WALL - 1 0 X 0 0",
"18 2 WALL - 1 0 X 0 0",
"19 2 WALL - 1 0 X 0 0",
"2 3 D - 1 0 X 0 0",
"16 3 A - 1 0 X 0 0",
"17 3 WALL - 1 0 X 0 0",
"19 3 C - 1 0 X 0 0",
"21 3 WALL - 1 0 X 0 0",
"1 4 WALL - 1 0 X 0 0",
"3 4 WALL - 1 0 X 0 0",
"6 4 WALL - 1 0 X 0 0",
"9 4 WALL - 1 0 X 0 0",
"12 4 WALL - 1 0 X 0 0",
"3 5 WALL - 1 0 X 0 0",
"18 5 WALL - 1 0 X 0 0",
"9 6 WALL - 1 0 X 0 0",
"12 6 WALL - 1 0 X 0 0",
"15 6 WALL - 1 0 X 0 0",
"18 6 WALL - 1 0 X 0 0",
"20 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"2 7 C - 1 0 X 0 0",
"4 7 WALL - 1 0 X 0 0",
"5 7 A - 1 0 X 0 0",
"19 7 D - 1 0 X 0 0",
"2 8 WALL - 1 0 X 0 0",
"3 8 WALL - 1 0 X 0 0",
"10 8 WALL - 1 0 X 0 0",
"13 8 WALL - 1 0 X 0 0",
"21 8 C - 1 0 X 0 0",
"2 9 WALL - 1 0 X 0 0",
"6 9 A - 1 0 X 0 0",
"13 9 WALL - 1 0 X 0 0",
"19 9 WALL - 1 0 X 0 0",
"21 9 WALL - 1 0 X 0 0",
"3 10 B - 1 0 X 0 0",
"4 10 WALL - 1 0 X 0 0",
"9 10 B - 1 0 X 0 0",
"12 10 D - 1 0 X 0 0",
"16 10 WALL - 1 0 X 0 0",
"20 10 ROOT 0 2 N 0 2",
"21 10 WALL - 1 0 X 0 0",
"9 4 7 6",
"9 4 7 6",
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
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _7_BRONZE)
{
	return;
	vector<string> replay =
	{
"16 8",
"46",
"0 0 WALL - 1 0 X 0 0",
"4 0 WALL - 1 0 X 0 0",
"6 0 WALL - 1 0 X 0 0",
"8 0 A - 1 0 X 0 0",
"11 0 WALL - 1 0 X 0 0",
"14 0 WALL - 1 0 X 0 0",
"15 0 WALL - 1 0 X 0 0",
"1 1 WALL - 1 0 X 0 0",
"2 1 C - 1 0 X 0 0",
"5 1 A - 1 0 X 0 0",
"7 1 WALL - 1 0 X 0 0",
"8 1 WALL - 1 0 X 0 0",
"14 1 C - 1 0 X 0 0",
"15 1 WALL - 1 0 X 0 0",
"0 2 ROOT 1 1 N 0 1",
"8 2 A - 1 0 X 0 0",
"9 2 WALL - 1 0 X 0 0",
"11 2 B - 1 0 X 0 0",
"13 2 B - 1 0 X 0 0",
"0 3 D - 1 0 X 0 0",
"4 3 D - 1 0 X 0 0",
"7 3 WALL - 1 0 X 0 0",
"14 3 WALL - 1 0 X 0 0",
"1 4 WALL - 1 0 X 0 0",
"8 4 WALL - 1 0 X 0 0",
"11 4 D - 1 0 X 0 0",
"15 4 D - 1 0 X 0 0",
"2 5 B - 1 0 X 0 0",
"4 5 B - 1 0 X 0 0",
"6 5 WALL - 1 0 X 0 0",
"7 5 A - 1 0 X 0 0",
"15 5 ROOT 0 2 N 0 2",
"0 6 WALL - 1 0 X 0 0",
"1 6 C - 1 0 X 0 0",
"7 6 WALL - 1 0 X 0 0",
"8 6 WALL - 1 0 X 0 0",
"10 6 A - 1 0 X 0 0",
"13 6 C - 1 0 X 0 0",
"14 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"1 7 WALL - 1 0 X 0 0",
"4 7 WALL - 1 0 X 0 0",
"7 7 A - 1 0 X 0 0",
"9 7 WALL - 1 0 X 0 0",
"11 7 WALL - 1 0 X 0 0",
"15 7 WALL - 1 0 X 0 0",
"9 5 8 9",
"9 5 8 9",
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
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _8_BRONZE)
{
	return;
	vector<string> replay =
	{
"18 9",
"108",
"1 0 WALL - 1 0 X 0 0",
"2 0 WALL - 1 0 X 0 0",
"3 0 WALL - 1 0 X 0 0",
"4 0 WALL - 1 0 X 0 0",
"5 0 BASIC 1 35 N 18 1",
"6 0 BASIC 1 36 N 35 1",
"7 0 BASIC 1 38 N 36 1",
"8 0 BASIC 1 40 N 38 1",
"13 0 WALL - 1 0 X 0 0",
"4 1 WALL - 1 0 X 0 0",
"5 1 HARVESTER 1 18 E 16 1",
"6 1 C - 1 0 X 0 0",
"7 1 WALL - 1 0 X 0 0",
"8 1 BASIC 1 43 N 40 1",
"9 1 BASIC 1 44 N 43 1",
"10 1 WALL - 1 0 X 0 0",
"11 1 WALL - 1 0 X 0 0",
"13 1 WALL - 1 0 X 0 0",
"17 1 WALL - 1 0 X 0 0",
"0 2 HARVESTER 1 3 E 1 1",
"1 2 A - 1 0 X 0 0",
"2 2 BASIC 1 9 N 7 1",
"3 2 SPORER 1 11 E 9 1",
"4 2 HARVESTER 1 14 S 11 1",
"5 2 SPORER 1 16 E 14 1",
"6 2 ROOT 1 20 N 0 20",
"7 2 HARVESTER 1 23 E 20 20",
"8 2 D - 1 0 X 0 0",
"9 2 BASIC 1 46 N 44 1",
"10 2 SPORER 1 48 E 46 1",
"11 2 HARVESTER 1 50 E 48 1",
"12 2 B - 1 0 X 0 0",
"13 2 C - 1 0 X 0 0",
"16 2 WALL - 1 0 X 0 0",
"17 2 WALL - 1 0 X 0 0",
"0 3 ROOT 1 1 N 0 1",
"1 3 BASIC 1 5 N 1 1",
"2 3 BASIC 1 7 N 5 1",
"3 3 WALL - 1 0 X 0 0",
"4 3 B - 1 0 X 0 0",
"5 3 BASIC 1 29 N 26 20",
"6 3 BASIC 1 26 N 20 20",
"7 3 WALL - 1 0 X 0 0",
"9 3 WALL - 1 0 X 0 0",
"10 3 HARVESTER 1 55 S 48 1",
"11 3 HARVESTER 1 52 E 50 1",
"12 3 A - 1 0 X 0 0",
"13 3 HARVESTER 0 22 W 19 2",
"14 3 WALL - 1 0 X 0 0",
"1 4 BASIC 1 21 N 5 1",
"2 4 WALL - 1 0 X 0 0",
"3 4 WALL - 1 0 X 0 0",
"5 4 WALL - 1 0 X 0 0",
"6 4 WALL - 1 0 X 0 0",
"7 4 D - 1 0 X 0 0",
"8 4 TENTACLE 0 53 E 51 2",
"9 4 BASIC 0 51 N 49 2",
"10 4 D - 1 0 X 0 0",
"11 4 WALL - 1 0 X 0 0",
"12 4 WALL - 1 0 X 0 0",
"13 4 BASIC 0 19 N 17 2",
"14 4 WALL - 1 0 X 0 0",
"15 4 WALL - 1 0 X 0 0",
"1 5 BASIC 1 24 N 21 1",
"2 5 BASIC 1 27 N 24 1",
"3 5 WALL - 1 0 X 0 0",
"5 5 A - 1 0 X 0 0",
"9 5 BASIC 0 49 N 41 2",
"10 5 WALL - 1 0 X 0 0",
"11 5 BASIC 0 28 N 25 2",
"12 5 BASIC 0 25 N 17 2",
"13 5 BASIC 0 17 N 15 2",
"14 5 WALL - 1 0 X 0 0",
"15 5 BASIC 0 10 N 6 2",
"16 5 BASIC 0 6 N 2 2",
"17 5 ROOT 0 2 N 0 2",
"0 6 WALL - 1 0 X 0 0",
"1 6 WALL - 1 0 X 0 0",
"2 6 BASIC 1 30 N 27 1",
"3 6 HARVESTER 1 32 E 30 1",
"4 6 C - 1 0 X 0 0",
"5 6 B - 1 0 X 0 0",
"9 6 BASIC 0 41 N 37 2",
"10 6 BASIC 0 37 N 33 2",
"11 6 BASIC 0 33 N 28 2",
"12 6 BASIC 0 31 N 25 2",
"13 6 BASIC 0 15 N 13 2",
"14 6 BASIC 0 13 N 12 2",
"15 6 BASIC 0 12 N 10 2",
"16 6 BASIC 0 8 N 6 2",
"17 6 HARVESTER 0 4 W 2 2",
"0 7 WALL - 1 0 X 0 0",
"4 7 WALL - 1 0 X 0 0",
"6 7 WALL - 1 0 X 0 0",
"7 7 WALL - 1 0 X 0 0",
"10 7 WALL - 1 0 X 0 0",
"11 7 BASIC 0 39 N 33 2",
"12 7 BASIC 0 34 N 31 2",
"13 7 WALL - 1 0 X 0 0",
"14 7 BASIC 0 42 N 13 2",
"17 7 TENTACLE 0 54 E 4 2",
"4 8 WALL - 1 0 X 0 0",
"11 8 BASIC 0 47 N 39 2",
"12 8 BASIC 0 45 N 34 2",
"13 8 WALL - 1 0 X 0 0",
"14 8 WALL - 1 0 X 0 0",
"15 8 WALL - 1 0 X 0 0",
"16 8 WALL - 1 0 X 0 0",
"21 26 30 12",
"10 5 6 8",
"2",
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
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _9_BRONZE)
{
	return;
	vector<string> replay =
	{
"20 10",
"82",
"0 0 B - 1 0 X 0 0",
"4 0 WALL - 1 0 X 0 0",
"9 0 D - 1 0 X 0 0",
"10 0 C - 1 0 X 0 0",
"12 0 WALL - 1 0 X 0 0",
"13 0 A - 1 0 X 0 0",
"1 1 ROOT 0 1 N 0 1",
"3 1 WALL - 1 0 X 0 0",
"4 1 WALL - 1 0 X 0 0",
"13 1 B - 1 0 X 0 0",
"19 1 WALL - 1 0 X 0 0",
"0 2 WALL - 1 0 X 0 0",
"1 2 WALL - 1 0 X 0 0",
"2 2 B - 1 0 X 0 0",
"9 2 D - 1 0 X 0 0",
"12 2 WALL - 1 0 X 0 0",
"13 2 WALL - 1 0 X 0 0",
"16 2 WALL - 1 0 X 0 0",
"18 2 WALL - 1 0 X 0 0",
"0 3 A - 1 0 X 0 0",
"1 3 WALL - 1 0 X 0 0",
"5 3 WALL - 1 0 X 0 0",
"6 3 A - 1 0 X 0 0",
"8 3 WALL - 1 0 X 0 0",
"9 3 WALL - 1 0 X 0 0",
"10 3 WALL - 1 0 X 0 0",
"11 3 WALL - 1 0 X 0 0",
"12 3 WALL - 1 0 X 0 0",
"13 3 WALL - 1 0 X 0 0",
"15 3 WALL - 1 0 X 0 0",
"16 3 C - 1 0 X 0 0",
"18 3 D - 1 0 X 0 0",
"3 4 WALL - 1 0 X 0 0",
"4 4 WALL - 1 0 X 0 0",
"5 4 C - 1 0 X 0 0",
"8 4 WALL - 1 0 X 0 0",
"12 4 A - 1 0 X 0 0",
"13 4 A - 1 0 X 0 0",
"16 4 C - 1 0 X 0 0",
"17 4 B - 1 0 X 0 0",
"18 4 D - 1 0 X 0 0",
"1 5 D - 1 0 X 0 0",
"2 5 B - 1 0 X 0 0",
"3 5 C - 1 0 X 0 0",
"6 5 A - 1 0 X 0 0",
"7 5 A - 1 0 X 0 0",
"11 5 WALL - 1 0 X 0 0",
"14 5 C - 1 0 X 0 0",
"15 5 WALL - 1 0 X 0 0",
"16 5 WALL - 1 0 X 0 0",
"1 6 D - 1 0 X 0 0",
"3 6 C - 1 0 X 0 0",
"4 6 WALL - 1 0 X 0 0",
"6 6 WALL - 1 0 X 0 0",
"7 6 WALL - 1 0 X 0 0",
"8 6 WALL - 1 0 X 0 0",
"9 6 WALL - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"11 6 WALL - 1 0 X 0 0",
"13 6 A - 1 0 X 0 0",
"14 6 WALL - 1 0 X 0 0",
"18 6 WALL - 1 0 X 0 0",
"19 6 A - 1 0 X 0 0",
"1 7 WALL - 1 0 X 0 0",
"3 7 WALL - 1 0 X 0 0",
"6 7 WALL - 1 0 X 0 0",
"7 7 WALL - 1 0 X 0 0",
"10 7 D - 1 0 X 0 0",
"17 7 B - 1 0 X 0 0",
"18 7 WALL - 1 0 X 0 0",
"19 7 WALL - 1 0 X 0 0",
"0 8 WALL - 1 0 X 0 0",
"6 8 B - 1 0 X 0 0",
"15 8 WALL - 1 0 X 0 0",
"16 8 WALL - 1 0 X 0 0",
"18 8 ROOT 1 2 N 0 2",
"6 9 A - 1 0 X 0 0",
"7 9 WALL - 1 0 X 0 0",
"9 9 C - 1 0 X 0 0",
"10 9 D - 1 0 X 0 0",
"15 9 WALL - 1 0 X 0 0",
"19 9 B - 1 0 X 0 0",
"3 8 3 9",
"3 8 3 9",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _A_BRONZE)
{
	return;
	vector<string> replay =
	{
"18 9",
"79",
"2 0 BASIC 1 31 N 30 18",
"3 0 BASIC 1 30 N 29 18",
"4 0 BASIC 1 29 N 26 18",
"5 0 BASIC 1 26 N 24 18",
"6 0 BASIC 1 24 N 21 18",
"10 0 BASIC 1 22 N 19 14",
"11 0 WALL - 1 0 X 0 0",
"16 0 WALL - 1 0 X 0 0",
"3 1 WALL - 1 0 X 0 0",
"4 1 BASIC 0 45 N 12 1",
"5 1 BASIC 0 47 N 45 1",
"6 1 BASIC 1 21 N 18 18",
"7 1 ROOT 1 18 N 0 18",
"10 1 BASIC 1 19 N 15 14",
"11 1 SPORER 1 15 W 14 14",
"3 2 SPORER 0 3 E 1 1",
"4 2 BASIC 0 12 N 5 1",
"5 2 BASIC 1 39 N 32 18",
"6 2 BASIC 1 32 N 21 18",
"7 2 WALL - 1 0 X 0 0",
"10 2 WALL - 1 0 X 0 0",
"11 2 ROOT 1 14 N 0 14",
"12 2 SPORER 1 44 E 14 14",
"13 2 D - 1 0 X 0 0",
"15 2 ROOT 1 49 N 0 49",
"17 2 WALL - 1 0 X 0 0",
"1 3 WALL - 1 0 X 0 0",
"2 3 WALL - 1 0 X 0 0",
"3 3 ROOT 0 1 N 0 1",
"4 3 BASIC 0 5 N 1 1",
"5 3 WALL - 1 0 X 0 0",
"6 3 BASIC 1 33 N 32 18",
"10 3 BASIC 1 28 N 25 14",
"11 3 BASIC 1 25 N 14 14",
"15 3 WALL - 1 0 X 0 0",
"16 3 D - 1 0 X 0 0",
"0 4 WALL - 1 0 X 0 0",
"3 4 BASIC 0 7 N 1 1",
"4 4 SPORER 0 9 E 7 1",
"6 4 BASIC 1 34 N 33 18",
"7 4 BASIC 1 40 N 34 18",
"8 4 WALL - 1 0 X 0 0",
"9 4 WALL - 1 0 X 0 0",
"10 4 BASIC 1 23 N 20 2",
"17 4 WALL - 1 0 X 0 0",
"1 5 D - 1 0 X 0 0",
"2 5 WALL - 1 0 X 0 0",
"3 5 BASIC 0 48 N 7 1",
"6 5 BASIC 1 35 N 34 18",
"9 5 BASIC 1 27 N 20 2",
"10 5 BASIC 1 20 N 13 2",
"11 5 SPORER 1 13 N 10 2",
"12 5 WALL - 1 0 X 0 0",
"14 5 ROOT 1 2 N 0 2",
"15 5 WALL - 1 0 X 0 0",
"16 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"1 6 HARVESTER 1 50 N 46 18",
"2 6 BASIC 1 46 N 43 18",
"3 6 BASIC 1 43 N 42 18",
"4 6 BASIC 1 42 N 41 18",
"5 6 BASIC 1 41 N 36 18",
"6 6 BASIC 1 36 N 35 18",
"7 6 WALL - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"11 6 BASIC 1 10 N 8 2",
"12 6 BASIC 1 8 N 6 2",
"13 6 BASIC 1 6 N 4 2",
"14 6 BASIC 1 4 N 2 2",
"15 6 BASIC 1 16 N 4 2",
"6 7 BASIC 1 37 N 36 18",
"7 7 BASIC 1 38 N 37 18",
"11 7 HARVESTER 1 11 S 10 2",
"14 7 WALL - 1 0 X 0 0",
"15 7 HARVESTER 1 17 S 16 2",
"1 8 WALL - 1 0 X 0 0",
"6 8 WALL - 1 0 X 0 0",
"11 8 A - 1 0 X 0 0",
"15 8 B - 1 0 X 0 0",
"1 34 9 1",
"1 8 3 4",
"4",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _B_BRONZE)
{
	return;
	vector<string> replay =
	{
"16 8",
"38",
"0 0 C - 1 0 X 0 0",
"6 0 B - 1 0 X 0 0",
"8 0 A - 1 0 X 0 0",
"9 0 C - 1 0 X 0 0",
"12 0 D - 1 0 X 0 0",
"0 1 ROOT 1 1 N 0 1",
"7 1 C - 1 0 X 0 0",
"9 1 D - 1 0 X 0 0",
"13 1 C - 1 0 X 0 0",
"6 2 A - 1 0 X 0 0",
"9 2 D - 1 0 X 0 0",
"12 2 WALL - 1 0 X 0 0",
"13 2 B - 1 0 X 0 0",
"3 3 D - 1 0 X 0 0",
"4 3 WALL - 1 0 X 0 0",
"6 3 A - 1 0 X 0 0",
"7 3 B - 1 0 X 0 0",
"10 3 A - 1 0 X 0 0",
"13 3 B - 1 0 X 0 0",
"2 4 B - 1 0 X 0 0",
"5 4 A - 1 0 X 0 0",
"8 4 B - 1 0 X 0 0",
"9 4 A - 1 0 X 0 0",
"11 4 WALL - 1 0 X 0 0",
"12 4 D - 1 0 X 0 0",
"2 5 B - 1 0 X 0 0",
"3 5 WALL - 1 0 X 0 0",
"6 5 D - 1 0 X 0 0",
"9 5 A - 1 0 X 0 0",
"2 6 C - 1 0 X 0 0",
"6 6 D - 1 0 X 0 0",
"8 6 C - 1 0 X 0 0",
"15 6 ROOT 0 2 N 0 2",
"3 7 D - 1 0 X 0 0",
"6 7 C - 1 0 X 0 0",
"7 7 A - 1 0 X 0 0",
"9 7 B - 1 0 X 0 0",
"15 7 C - 1 0 X 0 0",
"9 10 3 7",
"9 10 3 7",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _0_SILVER)
{
	return;
	vector<string> replay =
	{
"22 11",
"66",
"5 0 WALL - 1 0 X 0 0",
"16 0 WALL - 1 0 X 0 0",
"0 1 C - 1 0 X 0 0",
"2 1 ROOT 0 1 N 0 1",
"5 1 WALL - 1 0 X 0 0",
"9 1 WALL - 1 0 X 0 0",
"12 1 WALL - 1 0 X 0 0",
"16 1 WALL - 1 0 X 0 0",
"19 1 ROOT 1 2 N 0 2",
"21 1 C - 1 0 X 0 0",
"2 2 WALL - 1 0 X 0 0",
"3 2 WALL - 1 0 X 0 0",
"18 2 WALL - 1 0 X 0 0",
"19 2 WALL - 1 0 X 0 0",
"1 3 WALL - 1 0 X 0 0",
"2 3 WALL - 1 0 X 0 0",
"3 3 C - 1 0 X 0 0",
"6 3 WALL - 1 0 X 0 0",
"15 3 WALL - 1 0 X 0 0",
"18 3 C - 1 0 X 0 0",
"19 3 WALL - 1 0 X 0 0",
"20 3 WALL - 1 0 X 0 0",
"3 4 D - 1 0 X 0 0",
"8 4 WALL - 1 0 X 0 0",
"13 4 WALL - 1 0 X 0 0",
"18 4 D - 1 0 X 0 0",
"5 5 WALL - 1 0 X 0 0",
"10 5 WALL - 1 0 X 0 0",
"11 5 WALL - 1 0 X 0 0",
"16 5 WALL - 1 0 X 0 0",
"1 6 WALL - 1 0 X 0 0",
"2 6 WALL - 1 0 X 0 0",
"4 6 WALL - 1 0 X 0 0",
"5 6 WALL - 1 0 X 0 0",
"9 6 WALL - 1 0 X 0 0",
"12 6 WALL - 1 0 X 0 0",
"16 6 WALL - 1 0 X 0 0",
"17 6 WALL - 1 0 X 0 0",
"19 6 WALL - 1 0 X 0 0",
"20 6 WALL - 1 0 X 0 0",
"4 7 WALL - 1 0 X 0 0",
"5 7 WALL - 1 0 X 0 0",
"9 7 A - 1 0 X 0 0",
"12 7 A - 1 0 X 0 0",
"16 7 WALL - 1 0 X 0 0",
"17 7 WALL - 1 0 X 0 0",
"1 8 WALL - 1 0 X 0 0",
"6 8 WALL - 1 0 X 0 0",
"7 8 WALL - 1 0 X 0 0",
"14 8 WALL - 1 0 X 0 0",
"15 8 WALL - 1 0 X 0 0",
"20 8 WALL - 1 0 X 0 0",
"0 10 WALL - 1 0 X 0 0",
"2 10 WALL - 1 0 X 0 0",
"3 10 B - 1 0 X 0 0",
"4 10 WALL - 1 0 X 0 0",
"5 10 WALL - 1 0 X 0 0",
"6 10 B - 1 0 X 0 0",
"9 10 A - 1 0 X 0 0",
"12 10 A - 1 0 X 0 0",
"15 10 B - 1 0 X 0 0",
"16 10 WALL - 1 0 X 0 0",
"17 10 WALL - 1 0 X 0 0",
"18 10 B - 1 0 X 0 0",
"19 10 WALL - 1 0 X 0 0",
"21 10 WALL - 1 0 X 0 0",
"8 8 6 3",
"8 8 6 3",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _1_SILVER)
{
	return;
	vector<string> replay =
	{
"22 11",
"119",
"5 0 WALL - 1 0 X 0 0",
"16 0 WALL - 1 0 X 0 0",
"0 1 C - 1 0 X 0 0",
"1 1 HARVESTER 0 3 W 1 1",
"2 1 ROOT 0 1 N 0 1",
"3 1 BASIC 0 10 N 1 1",
"4 1 BASIC 0 12 N 10 1",
"5 1 WALL - 1 0 X 0 0",
"9 1 WALL - 1 0 X 0 0",
"12 1 WALL - 1 0 X 0 0",
"16 1 WALL - 1 0 X 0 0",
"17 1 BASIC 1 7 N 5 2",
"18 1 BASIC 1 5 N 2 2",
"19 1 ROOT 1 2 N 0 2",
"20 1 HARVESTER 1 4 E 2 2",
"21 1 C - 1 0 X 0 0",
"0 2 BASIC 0 8 N 6 1",
"1 2 BASIC 0 6 N 3 1",
"2 2 WALL - 1 0 X 0 0",
"3 2 WALL - 1 0 X 0 0",
"4 2 BASIC 0 14 N 12 1",
"17 2 BASIC 1 9 N 7 2",
"18 2 WALL - 1 0 X 0 0",
"19 2 WALL - 1 0 X 0 0",
"1 3 WALL - 1 0 X 0 0",
"2 3 WALL - 1 0 X 0 0",
"3 3 C - 1 0 X 0 0",
"4 3 HARVESTER 0 15 W 14 1",
"6 3 WALL - 1 0 X 0 0",
"15 3 WALL - 1 0 X 0 0",
"17 3 HARVESTER 1 11 E 9 2",
"18 3 C - 1 0 X 0 0",
"19 3 WALL - 1 0 X 0 0",
"20 3 WALL - 1 0 X 0 0",
"2 4 TENTACLE 0 25 N 23 1",
"3 4 D - 1 0 X 0 0",
"4 4 HARVESTER 0 17 W 15 1",
"8 4 WALL - 1 0 X 0 0",
"9 4 TENTACLE 0 70 E 69 1",
"10 4 TENTACLE 0 71 E 70 1",
"11 4 TENTACLE 0 72 E 71 1",
"12 4 TENTACLE 0 73 S 72 1",
"13 4 WALL - 1 0 X 0 0",
"15 4 BASIC 1 18 N 16 2",
"16 4 BASIC 1 16 N 13 2",
"17 4 HARVESTER 1 13 E 11 2",
"18 4 D - 1 0 X 0 0",
"2 5 BASIC 0 23 N 21 1",
"3 5 TENTACLE 0 21 N 19 1",
"4 5 BASIC 0 19 N 17 1",
"5 5 WALL - 1 0 X 0 0",
"8 5 TENTACLE 0 68 E 64 1",
"9 5 TENTACLE 0 69 N 68 1",
"10 5 WALL - 1 0 X 0 0",
"11 5 WALL - 1 0 X 0 0",
"12 5 TENTACLE 0 74 E 73 1",
"13 5 TENTACLE 0 75 E 74 1",
"15 5 BASIC 1 20 N 18 2",
"16 5 WALL - 1 0 X 0 0",
"17 5 BASIC 1 56 N 13 2",
"1 6 WALL - 1 0 X 0 0",
"2 6 WALL - 1 0 X 0 0",
"3 6 BASIC 0 27 N 21 1",
"4 6 WALL - 1 0 X 0 0",
"5 6 WALL - 1 0 X 0 0",
"8 6 TENTACLE 0 64 N 58 1",
"9 6 WALL - 1 0 X 0 0",
"12 6 WALL - 1 0 X 0 0",
"14 6 TENTACLE 1 77 W 22 2",
"15 6 BASIC 1 22 N 20 2",
"16 6 WALL - 1 0 X 0 0",
"17 6 WALL - 1 0 X 0 0",
"19 6 WALL - 1 0 X 0 0",
"20 6 WALL - 1 0 X 0 0",
"3 7 HARVESTER 0 29 N 27 1",
"4 7 WALL - 1 0 X 0 0",
"5 7 WALL - 1 0 X 0 0",
"8 7 TENTACLE 0 58 N 55 1",
"9 7 A - 1 0 X 0 0",
"15 7 SPORER 1 24 W 22 2",
"16 7 WALL - 1 0 X 0 0",
"17 7 WALL - 1 0 X 0 0",
"1 8 WALL - 1 0 X 0 0",
"3 8 HARVESTER 0 31 N 29 1",
"6 8 WALL - 1 0 X 0 0",
"7 8 WALL - 1 0 X 0 0",
"8 8 TENTACLE 0 55 N 48 1",
"14 8 WALL - 1 0 X 0 0",
"15 8 WALL - 1 0 X 0 0",
"20 8 WALL - 1 0 X 0 0",
"3 9 HARVESTER 0 33 S 31 1",
"4 9 TENTACLE 0 35 N 33 1",
"5 9 HARVESTER 0 37 N 35 1",
"6 9 HARVESTER 0 39 S 37 1",
"7 9 TENTACLE 0 41 N 39 1",
"8 9 TENTACLE 0 48 N 41 1",
"9 9 TENTACLE 0 52 N 48 1",
"10 9 ROOT 1 65 N 0 65",
"14 9 BASIC 1 67 N 62 53",
"15 9 HARVESTER 1 62 S 59 53",
"16 9 BASIC 1 59 N 53 53",
"17 9 ROOT 1 53 N 0 53",
"18 9 HARVESTER 1 57 S 53 53",
"0 10 WALL - 1 0 X 0 0",
"2 10 WALL - 1 0 X 0 0",
"3 10 B - 1 0 X 0 0",
"4 10 WALL - 1 0 X 0 0",
"5 10 WALL - 1 0 X 0 0",
"6 10 B - 1 0 X 0 0",
"7 10 TENTACLE 0 43 N 41 1",
"8 10 HARVESTER 0 45 E 43 1",
"9 10 A - 1 0 X 0 0",
"12 10 A - 1 0 X 0 0",
"15 10 B - 1 0 X 0 0",
"16 10 WALL - 1 0 X 0 0",
"17 10 WALL - 1 0 X 0 0",
"18 10 B - 1 0 X 0 0",
"19 10 WALL - 1 0 X 0 0",
"21 10 WALL - 1 0 X 0 0",
"0 25 65 20",
"17 31 47 25",
"3",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _2_SILVER)
{
	return;
	vector<string> replay =
	{
"24 12",
"102",
"0 0 WALL - 1 0 X 0 0",
"2 0 WALL - 1 0 X 0 0",
"3 0 WALL - 1 0 X 0 0",
"5 0 D - 1 0 X 0 0",
"7 0 D - 1 0 X 0 0",
"9 0 WALL - 1 0 X 0 0",
"14 0 WALL - 1 0 X 0 0",
"16 0 D - 1 0 X 0 0",
"18 0 D - 1 0 X 0 0",
"20 0 WALL - 1 0 X 0 0",
"21 0 WALL - 1 0 X 0 0",
"23 0 WALL - 1 0 X 0 0",
"2 1 WALL - 1 0 X 0 0",
"10 1 WALL - 1 0 X 0 0",
"13 1 WALL - 1 0 X 0 0",
"21 1 WALL - 1 0 X 0 0",
"1 2 B - 1 0 X 0 0",
"2 2 WALL - 1 0 X 0 0",
"5 2 B - 1 0 X 0 0",
"8 2 WALL - 1 0 X 0 0",
"9 2 WALL - 1 0 X 0 0",
"11 2 D - 1 0 X 0 0",
"12 2 D - 1 0 X 0 0",
"14 2 WALL - 1 0 X 0 0",
"15 2 WALL - 1 0 X 0 0",
"18 2 B - 1 0 X 0 0",
"21 2 WALL - 1 0 X 0 0",
"22 2 B - 1 0 X 0 0",
"0 3 WALL - 1 0 X 0 0",
"1 3 ROOT 1 1 N 0 1",
"2 3 WALL - 1 0 X 0 0",
"3 3 C - 1 0 X 0 0",
"7 3 D - 1 0 X 0 0",
"10 3 WALL - 1 0 X 0 0",
"11 3 D - 1 0 X 0 0",
"12 3 D - 1 0 X 0 0",
"13 3 WALL - 1 0 X 0 0",
"16 3 D - 1 0 X 0 0",
"20 3 C - 1 0 X 0 0",
"21 3 WALL - 1 0 X 0 0",
"22 3 ROOT 0 2 N 0 2",
"23 3 WALL - 1 0 X 0 0",
"0 4 B - 1 0 X 0 0",
"1 4 A - 1 0 X 0 0",
"2 4 WALL - 1 0 X 0 0",
"6 4 WALL - 1 0 X 0 0",
"7 4 C - 1 0 X 0 0",
"9 4 C - 1 0 X 0 0",
"14 4 C - 1 0 X 0 0",
"16 4 C - 1 0 X 0 0",
"17 4 WALL - 1 0 X 0 0",
"21 4 WALL - 1 0 X 0 0",
"22 4 A - 1 0 X 0 0",
"23 4 B - 1 0 X 0 0",
"10 5 C - 1 0 X 0 0",
"11 5 WALL - 1 0 X 0 0",
"12 5 WALL - 1 0 X 0 0",
"13 5 C - 1 0 X 0 0",
"1 6 A - 1 0 X 0 0",
"3 6 WALL - 1 0 X 0 0",
"9 6 A - 1 0 X 0 0",
"14 6 A - 1 0 X 0 0",
"20 6 WALL - 1 0 X 0 0",
"22 6 A - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"3 7 A - 1 0 X 0 0",
"20 7 A - 1 0 X 0 0",
"23 7 WALL - 1 0 X 0 0",
"1 8 D - 1 0 X 0 0",
"3 8 WALL - 1 0 X 0 0",
"4 8 WALL - 1 0 X 0 0",
"6 8 A - 1 0 X 0 0",
"17 8 A - 1 0 X 0 0",
"19 8 WALL - 1 0 X 0 0",
"20 8 WALL - 1 0 X 0 0",
"22 8 D - 1 0 X 0 0",
"0 9 D - 1 0 X 0 0",
"1 9 A - 1 0 X 0 0",
"5 9 C - 1 0 X 0 0",
"6 9 B - 1 0 X 0 0",
"10 9 C - 1 0 X 0 0",
"11 9 C - 1 0 X 0 0",
"12 9 C - 1 0 X 0 0",
"13 9 C - 1 0 X 0 0",
"17 9 B - 1 0 X 0 0",
"18 9 C - 1 0 X 0 0",
"22 9 A - 1 0 X 0 0",
"23 9 D - 1 0 X 0 0",
"2 10 B - 1 0 X 0 0",
"8 10 B - 1 0 X 0 0",
"9 10 A - 1 0 X 0 0",
"11 10 A - 1 0 X 0 0",
"12 10 A - 1 0 X 0 0",
"14 10 A - 1 0 X 0 0",
"15 10 B - 1 0 X 0 0",
"21 10 B - 1 0 X 0 0",
"2 11 C - 1 0 X 0 0",
"3 11 B - 1 0 X 0 0",
"10 11 B - 1 0 X 0 0",
"13 11 B - 1 0 X 0 0",
"20 11 B - 1 0 X 0 0",
"21 11 C - 1 0 X 0 0",
"4 9 8 6",
"4 9 8 6",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _3_SILVER)
{
	return;
	vector<string> replay =
	{
"16 8",
"52",
"0 0 WALL - 1 0 X 0 0",
"7 0 WALL - 1 0 X 0 0",
"10 0 WALL - 1 0 X 0 0",
"11 0 WALL - 1 0 X 0 0",
"15 0 WALL - 1 0 X 0 0",
"2 1 WALL - 1 0 X 0 0",
"4 1 D - 1 0 X 0 0",
"5 1 WALL - 1 0 X 0 0",
"6 1 A - 1 0 X 0 0",
"11 1 WALL - 1 0 X 0 0",
"13 1 D - 1 0 X 0 0",
"15 1 A - 1 0 X 0 0",
"5 2 WALL - 1 0 X 0 0",
"7 2 WALL - 1 0 X 0 0",
"9 2 WALL - 1 0 X 0 0",
"10 2 B - 1 0 X 0 0",
"11 2 WALL - 1 0 X 0 0",
"12 2 WALL - 1 0 X 0 0",
"15 2 WALL - 1 0 X 0 0",
"2 3 WALL - 1 0 X 0 0",
"3 3 ROOT 1 1 N 0 1",
"6 3 C - 1 0 X 0 0",
"7 3 B - 1 0 X 0 0",
"11 3 WALL - 1 0 X 0 0",
"14 3 C - 1 0 X 0 0",
"15 3 WALL - 1 0 X 0 0",
"0 4 WALL - 1 0 X 0 0",
"1 4 C - 1 0 X 0 0",
"4 4 WALL - 1 0 X 0 0",
"8 4 B - 1 0 X 0 0",
"9 4 C - 1 0 X 0 0",
"12 4 ROOT 0 2 N 0 2",
"13 4 WALL - 1 0 X 0 0",
"0 5 WALL - 1 0 X 0 0",
"3 5 WALL - 1 0 X 0 0",
"4 5 WALL - 1 0 X 0 0",
"5 5 B - 1 0 X 0 0",
"6 5 WALL - 1 0 X 0 0",
"8 5 WALL - 1 0 X 0 0",
"10 5 WALL - 1 0 X 0 0",
"0 6 A - 1 0 X 0 0",
"2 6 D - 1 0 X 0 0",
"4 6 WALL - 1 0 X 0 0",
"9 6 A - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"11 6 D - 1 0 X 0 0",
"13 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"4 7 WALL - 1 0 X 0 0",
"5 7 WALL - 1 0 X 0 0",
"8 7 WALL - 1 0 X 0 0",
"15 7 WALL - 1 0 X 0 0",
"7 10 9 5",
"7 10 9 5",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _4_SILVER)
{
	return;
	vector<string> replay =
	{
"16 8",
"36",
"6 0 D - 1 0 X 0 0",
"10 0 WALL - 1 0 X 0 0",
"13 0 D - 1 0 X 0 0",
"14 0 B - 1 0 X 0 0",
"3 1 ROOT 0 1 N 0 1",
"4 1 WALL - 1 0 X 0 0",
"6 1 A - 1 0 X 0 0",
"8 1 WALL - 1 0 X 0 0",
"9 1 C - 1 0 X 0 0",
"12 1 A - 1 0 X 0 0",
"0 2 B - 1 0 X 0 0",
"3 2 A - 1 0 X 0 0",
"9 2 D - 1 0 X 0 0",
"11 2 B - 1 0 X 0 0",
"12 2 WALL - 1 0 X 0 0",
"2 3 A - 1 0 X 0 0",
"11 3 C - 1 0 X 0 0",
"14 3 C - 1 0 X 0 0",
"1 4 C - 1 0 X 0 0",
"4 4 C - 1 0 X 0 0",
"13 4 A - 1 0 X 0 0",
"3 5 WALL - 1 0 X 0 0",
"4 5 B - 1 0 X 0 0",
"6 5 D - 1 0 X 0 0",
"12 5 A - 1 0 X 0 0",
"15 5 B - 1 0 X 0 0",
"3 6 A - 1 0 X 0 0",
"6 6 C - 1 0 X 0 0",
"7 6 WALL - 1 0 X 0 0",
"9 6 A - 1 0 X 0 0",
"11 6 WALL - 1 0 X 0 0",
"12 6 ROOT 1 2 N 0 2",
"1 7 B - 1 0 X 0 0",
"2 7 D - 1 0 X 0 0",
"5 7 WALL - 1 0 X 0 0",
"9 7 D - 1 0 X 0 0",
"3 9 5 8",
"3 9 5 8",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _5_SILVER)
{
	return;
	vector<string> replay =
	{
"24 12",
"38",
"1 0 ROOT 1 1 N 0 1",
"2 0 B - 1 0 X 0 0",
"6 0 WALL - 1 0 X 0 0",
"7 0 A - 1 0 X 0 0",
"8 0 C - 1 0 X 0 0",
"12 0 WALL - 1 0 X 0 0",
"2 1 D - 1 0 X 0 0",
"18 1 WALL - 1 0 X 0 0",
"23 1 WALL - 1 0 X 0 0",
"2 2 WALL - 1 0 X 0 0",
"3 2 A - 1 0 X 0 0",
"11 2 D - 1 0 X 0 0",
"5 3 B - 1 0 X 0 0",
"11 3 WALL - 1 0 X 0 0",
"15 3 C - 1 0 X 0 0",
"17 3 WALL - 1 0 X 0 0",
"22 3 WALL - 1 0 X 0 0",
"1 4 WALL - 1 0 X 0 0",
"21 4 WALL - 1 0 X 0 0",
"2 7 WALL - 1 0 X 0 0",
"22 7 WALL - 1 0 X 0 0",
"1 8 WALL - 1 0 X 0 0",
"6 8 WALL - 1 0 X 0 0",
"8 8 C - 1 0 X 0 0",
"12 8 WALL - 1 0 X 0 0",
"18 8 B - 1 0 X 0 0",
"12 9 D - 1 0 X 0 0",
"20 9 A - 1 0 X 0 0",
"21 9 WALL - 1 0 X 0 0",
"0 10 WALL - 1 0 X 0 0",
"5 10 WALL - 1 0 X 0 0",
"21 10 D - 1 0 X 0 0",
"11 11 WALL - 1 0 X 0 0",
"15 11 C - 1 0 X 0 0",
"16 11 A - 1 0 X 0 0",
"17 11 WALL - 1 0 X 0 0",
"21 11 B - 1 0 X 0 0",
"22 11 ROOT 0 2 N 0 2",
"6 10 8 4",
"6 10 8 4",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _6_SILVER)
{
	return;
	vector<string> replay =
	{
"18 9",
"70",
"1 0 ROOT 0 1 N 0 1",
"3 0 WALL - 1 0 X 0 0",
"5 0 WALL - 1 0 X 0 0",
"12 0 WALL - 1 0 X 0 0",
"13 0 WALL - 1 0 X 0 0",
"15 0 WALL - 1 0 X 0 0",
"16 0 C - 1 0 X 0 0",
"1 1 A - 1 0 X 0 0",
"4 1 D - 1 0 X 0 0",
"7 1 WALL - 1 0 X 0 0",
"9 1 WALL - 1 0 X 0 0",
"10 1 WALL - 1 0 X 0 0",
"12 1 WALL - 1 0 X 0 0",
"15 1 WALL - 1 0 X 0 0",
"17 1 WALL - 1 0 X 0 0",
"2 2 A - 1 0 X 0 0",
"5 2 WALL - 1 0 X 0 0",
"6 2 B - 1 0 X 0 0",
"11 2 C - 1 0 X 0 0",
"12 2 WALL - 1 0 X 0 0",
"17 2 WALL - 1 0 X 0 0",
"1 3 WALL - 1 0 X 0 0",
"6 3 WALL - 1 0 X 0 0",
"7 3 A - 1 0 X 0 0",
"9 3 WALL - 1 0 X 0 0",
"12 3 WALL - 1 0 X 0 0",
"13 3 WALL - 1 0 X 0 0",
"16 3 WALL - 1 0 X 0 0",
"17 3 WALL - 1 0 X 0 0",
"0 4 WALL - 1 0 X 0 0",
"1 4 WALL - 1 0 X 0 0",
"2 4 WALL - 1 0 X 0 0",
"3 4 D - 1 0 X 0 0",
"5 4 WALL - 1 0 X 0 0",
"8 4 WALL - 1 0 X 0 0",
"9 4 WALL - 1 0 X 0 0",
"12 4 WALL - 1 0 X 0 0",
"14 4 D - 1 0 X 0 0",
"15 4 WALL - 1 0 X 0 0",
"16 4 WALL - 1 0 X 0 0",
"17 4 WALL - 1 0 X 0 0",
"0 5 WALL - 1 0 X 0 0",
"1 5 WALL - 1 0 X 0 0",
"4 5 WALL - 1 0 X 0 0",
"5 5 WALL - 1 0 X 0 0",
"8 5 WALL - 1 0 X 0 0",
"10 5 A - 1 0 X 0 0",
"11 5 WALL - 1 0 X 0 0",
"16 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"5 6 WALL - 1 0 X 0 0",
"6 6 C - 1 0 X 0 0",
"11 6 B - 1 0 X 0 0",
"12 6 WALL - 1 0 X 0 0",
"15 6 A - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"2 7 WALL - 1 0 X 0 0",
"5 7 WALL - 1 0 X 0 0",
"7 7 WALL - 1 0 X 0 0",
"8 7 WALL - 1 0 X 0 0",
"10 7 WALL - 1 0 X 0 0",
"13 7 D - 1 0 X 0 0",
"16 7 A - 1 0 X 0 0",
"1 8 C - 1 0 X 0 0",
"2 8 WALL - 1 0 X 0 0",
"4 8 WALL - 1 0 X 0 0",
"5 8 WALL - 1 0 X 0 0",
"12 8 WALL - 1 0 X 0 0",
"14 8 WALL - 1 0 X 0 0",
"16 8 ROOT 1 2 N 0 2",
"5 8 7 9",
"5 8 7 9",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _7_SILVER)
{
	return;
	vector<string> replay =
	{
"24 12",
"162",
"5 0 WALL - 1 0 X 0 0",
"6 0 WALL - 1 0 X 0 0",
"7 0 WALL - 1 0 X 0 0",
"8 0 WALL - 1 0 X 0 0",
"11 0 C - 1 0 X 0 0",
"12 0 A - 1 0 X 0 0",
"13 0 WALL - 1 0 X 0 0",
"18 0 WALL - 1 0 X 0 0",
"19 0 A - 1 0 X 0 0",
"21 0 WALL - 1 0 X 0 0",
"2 1 WALL - 1 0 X 0 0",
"3 1 WALL - 1 0 X 0 0",
"6 1 WALL - 1 0 X 0 0",
"13 1 D - 1 0 X 0 0",
"16 1 WALL - 1 0 X 0 0",
"17 1 D - 1 0 X 0 0",
"18 1 A - 1 0 X 0 0",
"19 1 WALL - 1 0 X 0 0",
"21 1 B - 1 0 X 0 0",
"0 2 C - 1 0 X 0 0",
"1 2 WALL - 1 0 X 0 0",
"2 2 ROOT 0 1 N 0 1",
"4 2 WALL - 1 0 X 0 0",
"6 2 WALL - 1 0 X 0 0",
"11 2 C - 1 0 X 0 0",
"12 2 A - 1 0 X 0 0",
"13 2 C - 1 0 X 0 0",
"14 2 D - 1 0 X 0 0",
"16 2 WALL - 1 0 X 0 0",
"17 2 WALL - 1 0 X 0 0",
"18 2 B - 1 0 X 0 0",
"20 2 WALL - 1 0 X 0 0",
"21 2 WALL - 1 0 X 0 0",
"22 2 A - 1 0 X 0 0",
"23 2 B - 1 0 X 0 0",
"0 3 C - 1 0 X 0 0",
"3 3 WALL - 1 0 X 0 0",
"6 3 WALL - 1 0 X 0 0",
"7 3 B - 1 0 X 0 0",
"8 3 A - 1 0 X 0 0",
"9 3 WALL - 1 0 X 0 0",
"11 3 WALL - 1 0 X 0 0",
"14 3 WALL - 1 0 X 0 0",
"16 3 WALL - 1 0 X 0 0",
"17 3 WALL - 1 0 X 0 0",
"18 3 WALL - 1 0 X 0 0",
"19 3 A - 1 0 X 0 0",
"20 3 WALL - 1 0 X 0 0",
"21 3 WALL - 1 0 X 0 0",
"23 3 C - 1 0 X 0 0",
"1 4 WALL - 1 0 X 0 0",
"2 4 WALL - 1 0 X 0 0",
"5 4 C - 1 0 X 0 0",
"6 4 C - 1 0 X 0 0",
"8 4 A - 1 0 X 0 0",
"9 4 WALL - 1 0 X 0 0",
"11 4 A - 1 0 X 0 0",
"12 4 WALL - 1 0 X 0 0",
"13 4 D - 1 0 X 0 0",
"14 4 B - 1 0 X 0 0",
"15 4 WALL - 1 0 X 0 0",
"16 4 WALL - 1 0 X 0 0",
"17 4 D - 1 0 X 0 0",
"18 4 D - 1 0 X 0 0",
"20 4 WALL - 1 0 X 0 0",
"21 4 D - 1 0 X 0 0",
"22 4 B - 1 0 X 0 0",
"23 4 WALL - 1 0 X 0 0",
"5 5 WALL - 1 0 X 0 0",
"6 5 WALL - 1 0 X 0 0",
"10 5 D - 1 0 X 0 0",
"11 5 B - 1 0 X 0 0",
"12 5 WALL - 1 0 X 0 0",
"13 5 WALL - 1 0 X 0 0",
"15 5 WALL - 1 0 X 0 0",
"16 5 WALL - 1 0 X 0 0",
"17 5 WALL - 1 0 X 0 0",
"18 5 B - 1 0 X 0 0",
"20 5 WALL - 1 0 X 0 0",
"22 5 WALL - 1 0 X 0 0",
"23 5 WALL - 1 0 X 0 0",
"0 6 WALL - 1 0 X 0 0",
"1 6 WALL - 1 0 X 0 0",
"3 6 WALL - 1 0 X 0 0",
"5 6 B - 1 0 X 0 0",
"6 6 WALL - 1 0 X 0 0",
"7 6 WALL - 1 0 X 0 0",
"8 6 WALL - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"11 6 WALL - 1 0 X 0 0",
"12 6 B - 1 0 X 0 0",
"13 6 D - 1 0 X 0 0",
"17 6 WALL - 1 0 X 0 0",
"18 6 WALL - 1 0 X 0 0",
"0 7 WALL - 1 0 X 0 0",
"1 7 B - 1 0 X 0 0",
"2 7 D - 1 0 X 0 0",
"3 7 WALL - 1 0 X 0 0",
"5 7 D - 1 0 X 0 0",
"6 7 D - 1 0 X 0 0",
"7 7 WALL - 1 0 X 0 0",
"8 7 WALL - 1 0 X 0 0",
"9 7 B - 1 0 X 0 0",
"10 7 D - 1 0 X 0 0",
"11 7 WALL - 1 0 X 0 0",
"12 7 A - 1 0 X 0 0",
"14 7 WALL - 1 0 X 0 0",
"15 7 A - 1 0 X 0 0",
"17 7 C - 1 0 X 0 0",
"18 7 C - 1 0 X 0 0",
"21 7 WALL - 1 0 X 0 0",
"22 7 WALL - 1 0 X 0 0",
"0 8 C - 1 0 X 0 0",
"2 8 WALL - 1 0 X 0 0",
"3 8 WALL - 1 0 X 0 0",
"4 8 A - 1 0 X 0 0",
"5 8 WALL - 1 0 X 0 0",
"6 8 WALL - 1 0 X 0 0",
"7 8 WALL - 1 0 X 0 0",
"9 8 WALL - 1 0 X 0 0",
"12 8 WALL - 1 0 X 0 0",
"14 8 WALL - 1 0 X 0 0",
"15 8 A - 1 0 X 0 0",
"16 8 B - 1 0 X 0 0",
"17 8 WALL - 1 0 X 0 0",
"20 8 WALL - 1 0 X 0 0",
"23 8 C - 1 0 X 0 0",
"0 9 B - 1 0 X 0 0",
"1 9 A - 1 0 X 0 0",
"2 9 WALL - 1 0 X 0 0",
"3 9 WALL - 1 0 X 0 0",
"5 9 B - 1 0 X 0 0",
"6 9 WALL - 1 0 X 0 0",
"7 9 WALL - 1 0 X 0 0",
"9 9 D - 1 0 X 0 0",
"10 9 C - 1 0 X 0 0",
"11 9 A - 1 0 X 0 0",
"12 9 C - 1 0 X 0 0",
"17 9 WALL - 1 0 X 0 0",
"19 9 WALL - 1 0 X 0 0",
"21 9 ROOT 1 2 N 0 2",
"22 9 WALL - 1 0 X 0 0",
"23 9 C - 1 0 X 0 0",
"2 10 B - 1 0 X 0 0",
"4 10 WALL - 1 0 X 0 0",
"5 10 A - 1 0 X 0 0",
"6 10 D - 1 0 X 0 0",
"7 10 WALL - 1 0 X 0 0",
"10 10 D - 1 0 X 0 0",
"17 10 WALL - 1 0 X 0 0",
"20 10 WALL - 1 0 X 0 0",
"21 10 WALL - 1 0 X 0 0",
"2 11 WALL - 1 0 X 0 0",
"4 11 A - 1 0 X 0 0",
"5 11 WALL - 1 0 X 0 0",
"10 11 WALL - 1 0 X 0 0",
"11 11 A - 1 0 X 0 0",
"12 11 C - 1 0 X 0 0",
"15 11 WALL - 1 0 X 0 0",
"16 11 WALL - 1 0 X 0 0",
"17 11 WALL - 1 0 X 0 0",
"18 11 WALL - 1 0 X 0 0",
"3 10 7 6",
"3 10 7 6",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _01_GOLD)
{
	return;
	vector<string> replay =
	{
"20 10",
"74",
"1 0 D - 1 0 X 0 0",
"2 0 WALL - 1 0 X 0 0",
"3 0 WALL - 1 0 X 0 0",
"5 0 WALL - 1 0 X 0 0",
"6 0 C - 1 0 X 0 0",
"12 0 WALL - 1 0 X 0 0",
"15 0 D - 1 0 X 0 0",
"16 0 WALL - 1 0 X 0 0",
"1 1 ROOT 1 1 N 0 1",
"5 1 WALL - 1 0 X 0 0",
"6 1 WALL - 1 0 X 0 0",
"7 1 WALL - 1 0 X 0 0",
"10 1 WALL - 1 0 X 0 0",
"12 1 WALL - 1 0 X 0 0",
"14 1 WALL - 1 0 X 0 0",
"16 1 WALL - 1 0 X 0 0",
"18 1 WALL - 1 0 X 0 0",
"6 2 WALL - 1 0 X 0 0",
"7 2 B - 1 0 X 0 0",
"9 2 WALL - 1 0 X 0 0",
"14 2 B - 1 0 X 0 0",
"3 3 WALL - 1 0 X 0 0",
"4 3 WALL - 1 0 X 0 0",
"6 3 C - 1 0 X 0 0",
"9 3 WALL - 1 0 X 0 0",
"10 3 WALL - 1 0 X 0 0",
"13 3 WALL - 1 0 X 0 0",
"14 3 WALL - 1 0 X 0 0",
"15 3 WALL - 1 0 X 0 0",
"16 3 WALL - 1 0 X 0 0",
"18 3 WALL - 1 0 X 0 0",
"7 4 WALL - 1 0 X 0 0",
"12 4 A - 1 0 X 0 0",
"15 4 WALL - 1 0 X 0 0",
"16 4 WALL - 1 0 X 0 0",
"18 4 WALL - 1 0 X 0 0",
"19 4 WALL - 1 0 X 0 0",
"0 5 WALL - 1 0 X 0 0",
"1 5 WALL - 1 0 X 0 0",
"3 5 WALL - 1 0 X 0 0",
"4 5 WALL - 1 0 X 0 0",
"7 5 A - 1 0 X 0 0",
"12 5 WALL - 1 0 X 0 0",
"1 6 WALL - 1 0 X 0 0",
"3 6 WALL - 1 0 X 0 0",
"4 6 WALL - 1 0 X 0 0",
"5 6 WALL - 1 0 X 0 0",
"6 6 WALL - 1 0 X 0 0",
"9 6 WALL - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"13 6 C - 1 0 X 0 0",
"15 6 WALL - 1 0 X 0 0",
"16 6 WALL - 1 0 X 0 0",
"5 7 B - 1 0 X 0 0",
"10 7 WALL - 1 0 X 0 0",
"12 7 B - 1 0 X 0 0",
"13 7 WALL - 1 0 X 0 0",
"1 8 WALL - 1 0 X 0 0",
"3 8 WALL - 1 0 X 0 0",
"5 8 WALL - 1 0 X 0 0",
"7 8 WALL - 1 0 X 0 0",
"9 8 WALL - 1 0 X 0 0",
"12 8 WALL - 1 0 X 0 0",
"13 8 WALL - 1 0 X 0 0",
"14 8 WALL - 1 0 X 0 0",
"18 8 ROOT 0 2 N 0 2",
"3 9 WALL - 1 0 X 0 0",
"4 9 D - 1 0 X 0 0",
"7 9 WALL - 1 0 X 0 0",
"13 9 C - 1 0 X 0 0",
"14 9 WALL - 1 0 X 0 0",
"16 9 WALL - 1 0 X 0 0",
"17 9 WALL - 1 0 X 0 0",
"18 9 D - 1 0 X 0 0",
"4 9 6 7",
"4 9 6 7",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _02_GOLD)
{
	return;
	vector<string> replay =
	{
"24 12",
"134",
"0 0 WALL - 1 0 X 0 0",
"1 0 WALL - 1 0 X 0 0",
"2 0 WALL - 1 0 X 0 0",
"4 0 WALL - 1 0 X 0 0",
"5 0 WALL - 1 0 X 0 0",
"6 0 WALL - 1 0 X 0 0",
"10 0 WALL - 1 0 X 0 0",
"11 0 WALL - 1 0 X 0 0",
"12 0 B - 1 0 X 0 0",
"13 0 WALL - 1 0 X 0 0",
"14 0 WALL - 1 0 X 0 0",
"15 0 WALL - 1 0 X 0 0",
"16 0 WALL - 1 0 X 0 0",
"17 0 WALL - 1 0 X 0 0",
"19 0 WALL - 1 0 X 0 0",
"0 1 WALL - 1 0 X 0 0",
"1 1 WALL - 1 0 X 0 0",
"2 1 D - 1 0 X 0 0",
"4 1 WALL - 1 0 X 0 0",
"5 1 WALL - 1 0 X 0 0",
"6 1 WALL - 1 0 X 0 0",
"8 1 WALL - 1 0 X 0 0",
"10 1 WALL - 1 0 X 0 0",
"12 1 B - 1 0 X 0 0",
"17 1 WALL - 1 0 X 0 0",
"19 1 WALL - 1 0 X 0 0",
"21 1 WALL - 1 0 X 0 0",
"0 2 WALL - 1 0 X 0 0",
"1 2 WALL - 1 0 X 0 0",
"6 2 WALL - 1 0 X 0 0",
"10 2 WALL - 1 0 X 0 0",
"11 2 WALL - 1 0 X 0 0",
"15 2 WALL - 1 0 X 0 0",
"18 2 A - 1 0 X 0 0",
"1 3 WALL - 1 0 X 0 0",
"2 3 A - 1 0 X 0 0",
"3 3 ROOT 0 1 N 0 1",
"5 3 WALL - 1 0 X 0 0",
"6 3 WALL - 1 0 X 0 0",
"7 3 WALL - 1 0 X 0 0",
"8 3 WALL - 1 0 X 0 0",
"9 3 B - 1 0 X 0 0",
"11 3 WALL - 1 0 X 0 0",
"13 3 WALL - 1 0 X 0 0",
"18 3 WALL - 1 0 X 0 0",
"20 3 WALL - 1 0 X 0 0",
"21 3 WALL - 1 0 X 0 0",
"22 3 WALL - 1 0 X 0 0",
"23 3 WALL - 1 0 X 0 0",
"1 4 C - 1 0 X 0 0",
"2 4 WALL - 1 0 X 0 0",
"6 4 WALL - 1 0 X 0 0",
"7 4 WALL - 1 0 X 0 0",
"8 4 WALL - 1 0 X 0 0",
"9 4 C - 1 0 X 0 0",
"12 4 A - 1 0 X 0 0",
"14 4 WALL - 1 0 X 0 0",
"15 4 WALL - 1 0 X 0 0",
"18 4 D - 1 0 X 0 0",
"0 5 WALL - 1 0 X 0 0",
"4 5 WALL - 1 0 X 0 0",
"7 5 WALL - 1 0 X 0 0",
"8 5 WALL - 1 0 X 0 0",
"9 5 WALL - 1 0 X 0 0",
"13 5 WALL - 1 0 X 0 0",
"17 5 WALL - 1 0 X 0 0",
"20 5 WALL - 1 0 X 0 0",
"3 6 WALL - 1 0 X 0 0",
"6 6 WALL - 1 0 X 0 0",
"10 6 WALL - 1 0 X 0 0",
"14 6 WALL - 1 0 X 0 0",
"15 6 WALL - 1 0 X 0 0",
"16 6 WALL - 1 0 X 0 0",
"19 6 WALL - 1 0 X 0 0",
"23 6 WALL - 1 0 X 0 0",
"5 7 D - 1 0 X 0 0",
"8 7 WALL - 1 0 X 0 0",
"9 7 WALL - 1 0 X 0 0",
"11 7 A - 1 0 X 0 0",
"14 7 C - 1 0 X 0 0",
"15 7 WALL - 1 0 X 0 0",
"16 7 WALL - 1 0 X 0 0",
"17 7 WALL - 1 0 X 0 0",
"21 7 WALL - 1 0 X 0 0",
"22 7 C - 1 0 X 0 0",
"0 8 WALL - 1 0 X 0 0",
"1 8 WALL - 1 0 X 0 0",
"2 8 WALL - 1 0 X 0 0",
"3 8 WALL - 1 0 X 0 0",
"5 8 WALL - 1 0 X 0 0",
"10 8 WALL - 1 0 X 0 0",
"12 8 WALL - 1 0 X 0 0",
"14 8 B - 1 0 X 0 0",
"15 8 WALL - 1 0 X 0 0",
"16 8 WALL - 1 0 X 0 0",
"17 8 WALL - 1 0 X 0 0",
"18 8 WALL - 1 0 X 0 0",
"20 8 ROOT 1 2 N 0 2",
"21 8 A - 1 0 X 0 0",
"22 8 WALL - 1 0 X 0 0",
"5 9 A - 1 0 X 0 0",
"8 9 WALL - 1 0 X 0 0",
"12 9 WALL - 1 0 X 0 0",
"13 9 WALL - 1 0 X 0 0",
"17 9 WALL - 1 0 X 0 0",
"22 9 WALL - 1 0 X 0 0",
"23 9 WALL - 1 0 X 0 0",
"2 10 WALL - 1 0 X 0 0",
"4 10 WALL - 1 0 X 0 0",
"6 10 WALL - 1 0 X 0 0",
"11 10 B - 1 0 X 0 0",
"13 10 WALL - 1 0 X 0 0",
"15 10 WALL - 1 0 X 0 0",
"17 10 WALL - 1 0 X 0 0",
"18 10 WALL - 1 0 X 0 0",
"19 10 WALL - 1 0 X 0 0",
"21 10 D - 1 0 X 0 0",
"22 10 WALL - 1 0 X 0 0",
"23 10 WALL - 1 0 X 0 0",
"4 11 WALL - 1 0 X 0 0",
"6 11 WALL - 1 0 X 0 0",
"7 11 WALL - 1 0 X 0 0",
"8 11 WALL - 1 0 X 0 0",
"9 11 WALL - 1 0 X 0 0",
"10 11 WALL - 1 0 X 0 0",
"11 11 B - 1 0 X 0 0",
"12 11 WALL - 1 0 X 0 0",
"13 11 WALL - 1 0 X 0 0",
"17 11 WALL - 1 0 X 0 0",
"18 11 WALL - 1 0 X 0 0",
"19 11 WALL - 1 0 X 0 0",
"21 11 WALL - 1 0 X 0 0",
"22 11 WALL - 1 0 X 0 0",
"23 11 WALL - 1 0 X 0 0",
"7 9 10 10",
"7 9 10 10",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _03_GOLD)
{
	return;
	vector<string> replay =
	{
		"18 9",
		"70",
		"1 0 A -1 0 X 0 0",
		"5 0 WALL -1 0 X 0 0",
		"8 0 D -1 0 X 0 0",
		"1 1 WALL -1 0 X 0 0",
		"2 1 WALL -1 0 X 0 0",
		"7 1 A -1 0 X 0 0",
		"13 1 WALL -1 0 X 0 0",
		"0 2 D -1 0 X 0 0",
		"3 2 SPORER 1 13 E 1 1",
		"7 2 C -1 0 X 0 0",
		"8 2 WALL -1 0 X 0 0",
		"15 2 A -1 0 X 0 0",
		"0 3 HARVESTER 1 11 N 7 1",
		"1 3 HARVESTER 1 7 S 3 1",
		"2 3 SPORER 1 3 S 1 1",
		"3 3 ROOT 1 1 N 0 1",
		"4 3 SPORER 1 15 E 1 1",
		"5 3 HARVESTER 1 18 E 15 1",
		"6 3 B -1 0 X 0 0",
		"9 3 B -1 0 X 0 0",
		"12 3 C -1 0 X 0 0",
		"13 3 WALL -1 0 X 0 0",
		"15 3 HARVESTER 0 17 N 6 2",
		"1 4 A -1 0 X 0 0",
		"2 4 HARVESTER 1 5 E 3 1",
		"3 4 B -1 0 X 0 0",
		"5 4 HARVESTER 1 19 E 18 1",
		"6 4 C -1 0 X 0 0",
		"7 4 D -1 0 X 0 0",
		"10 4 D -1 0 X 0 0",
		"11 4 C -1 0 X 0 0",
		"12 4 HARVESTER 0 16 N 14 2",
		"13 4 BASIC 0 14 N 12 2",
		"14 4 B -1 0 X 0 0",
		"15 4 HARVESTER 0 6 W 4 2",
		"16 4 A -1 0 X 0 0",
		"2 5 HARVESTER 1 9 S 5 1",
		"4 5 WALL -1 0 X 0 0",
		"5 5 BASIC 1 21 N 19 1",
		"6 5 BASIC 1 23 N 21 1",
		"8 5 B -1 0 X 0 0",
		"11 5 B -1 0 X 0 0",
		"12 5 HARVESTER 0 20 W 12 2",
		"13 5 BASIC 0 12 N 2 2",
		"14 5 ROOT 0 2 N 0 2",
		"15 5 BASIC 0 4 N 2 2",
		"16 5 HARVESTER 0 8 N 4 2",
		"2 6 A -1 0 X 0 0",
		"6 6 BASIC 1 25 N 23 1",
		"9 6 WALL -1 0 X 0 0",
		"10 6 C -1 0 X 0 0",
		"12 6 TENTACLE 0 22 W 20 2",
		"14 6 TENTACLE 0 33 S 32 2",
		"15 6 TENTACLE 0 32 W 10 2",
		"16 6 HARVESTER 0 10 E 8 2",
		"17 6 D -1 0 X 0 0",
		"4 7 WALL -1 0 X 0 0",
		"6 7 BASIC 1 27 N 25 1",
		"7 7 BASIC 1 29 N 27 1",
		"8 7 BASIC 1 31 N 29 1",
		"9 7 TENTACLE 1 34 E 31 1",
		"10 7 TENTACLE 1 36 E 34 1",
		"11 7 TENTACLE 1 38 N 36 1",
		"14 7 TENTACLE 0 35 S 33 2",
		"15 7 WALL -1 0 X 0 0",
		"16 7 WALL -1 0 X 0 0",
		"9 8 D -1 0 X 0 0",
		"12 8 WALL -1 0 X 0 0",
		"14 8 TENTACLE 0 37 E 35 2",
		"16 8 A -1 0 X 0 0",
		"35 30 13 12",
		"36 29 14 17",
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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}

TEST(_2024_WINTER, _04_GOLD)
{
	vector<string> replay =
	{
"24 12","110",
"0 0 WALL -1 0 X 0 0","1 0 C -1 0 X 0 0","2 0 HARVESTER 0 16 W 3 1","4 0 WALL -1 0 X 0 0","6 0 A -1 0 X 0 0","9 0 C -1 0 X 0 0","13 0 B -1 0 X 0 0","17 0 A -1 0 X 0 0","18 0 A -1 0 X 0 0","23 0 B -1 0 X 0 0",
"0 1 BASIC 0 5 W 1 1","1 1 ROOT 0 1 N 0 1","2 1 HARVESTER 0 3 N 1 1","3 1 TENTACLE 0 26 E 3 1","4 1 TENTACLE 0 28 E 26 1","5 1 TENTACLE 0 30 E 28 1","6 1 HARVESTER 0 32 N 30 1","7 1 TENTACLE 0 34 E 32 1","0 2 HARVESTER 0 7 E 5 1","1 2 C -1 0 X 0 0",
"2 2 HARVESTER 0 9 S 3 1","6 2 TENTACLE 0 72 S 32 1","7 2 TENTACLE 0 69 S 34 1","18 2 D -1 0 X 0 0","20 2 D -1 0 X 0 0","23 2 D -1 0 X 0 0","0 3 B -1 0 X 0 0","1 3 HARVESTER 0 22 W 11 1","2 3 HARVESTER 0 11 S 9 1","3 3 HARVESTER 0 13 E 11 1",
"4 3 C -1 0 X 0 0","6 3 TENTACLE 0 73 E 72 1","12 3 A -1 0 X 0 0","15 3 C -1 0 X 0 0","19 3 D -1 0 X 0 0","20 3 A -1 0 X 0 0","21 3 HARVESTER 1 25 W 23 2","1 4 B -1 0 X 0 0","2 4 HARVESTER 0 20 W 11 1","3 4 HARVESTER 0 18 E 13 1",
"4 4 D -1 0 X 0 0","6 4 TENTACLE 0 74 S 73 1","7 4 TENTACLE 0 75 E 74 1","16 4 A -1 0 X 0 0","19 4 D -1 0 X 0 0","20 4 B -1 0 X 0 0","21 4 HARVESTER 1 23 E 21 2","22 4 D -1 0 X 0 0","3 5 TENTACLE 0 24 S 18 1","5 5 WALL -1 0 X 0 0",
"7 5 TENTACLE 0 76 E 75 1","17 5 BASIC 1 29 N 27 2","18 5 BASIC 1 27 N 19 2","19 5 HARVESTER 1 19 N 17 2","20 5 HARVESTER 1 17 N 15 2","21 5 SPORER 1 21 N 17 2","3 6 HARVESTER 0 39 S 24 1","7 6 TENTACLE 0 77 E 76 1","8 6 TENTACLE 0 78 N 77 1","14 6 BASIC 1 37 N 35 2",
"15 6 BASIC 1 35 N 33 2","16 6 BASIC 1 33 N 31 2","17 6 BASIC 1 31 N 29 2","18 6 WALL -1 0 X 0 0","20 6 BASIC 1 15 N 14 2","1 7 D -1 0 X 0 0","2 7 HARVESTER 0 43 W 41 1","3 7 HARVESTER 0 41 E 39 1","4 7 D -1 0 X 0 0","7 7 A -1 0 X 0 0",
"8 7 TENTACLE 0 79 N 78 1","9 7 TENTACLE 0 80 N 79 1","10 7 TENTACLE 0 82 N 80 1","11 7 TENTACLE 0 84 N 82 1","12 7 TENTACLE 0 85 N 84 1","13 7 TENTACLE 0 87 N 85 1","19 7 D -1 0 X 0 0","20 7 HARVESTER 1 14 W 12 2","21 7 C -1 0 X 0 0","22 7 B -1 0 X 0 0",
"3 8 A -1 0 X 0 0","4 8 D -1 0 X 0 0","8 8 C -1 0 X 0 0","9 8 HARVESTER 0 81 W 80 1","10 8 HARVESTER 0 83 E 82 1","11 8 A -1 0 X 0 0","12 8 TENTACLE 0 86 S 85 1","19 8 C -1 0 X 0 0","20 8 HARVESTER 1 12 W 8 2","21 8 HARVESTER 1 8 N 6 2",
"22 8 HARVESTER 1 10 N 8 2","23 8 B -1 0 X 0 0","0 9 D -1 0 X 0 0","3 9 D -1 0 X 0 0","5 9 D -1 0 X 0 0","21 9 HARVESTER 1 6 E 4 2","22 9 C -1 0 X 0 0","14 10 C -1 0 X 0 0","21 10 HARVESTER 1 4 S 2 2","22 10 ROOT 1 2 N 0 2",
"0 11 B -1 0 X 0 0","5 11 A -1 0 X 0 0","6 11 A -1 0 X 0 0","10 11 B -1 0 X 0 0","14 11 C -1 0 X 0 0","17 11 A -1 0 X 0 0","19 11 WALL -1 0 X 0 0","21 11 B -1 0 X 0 0","22 11 C -1 0 X 0 0","23 11 WALL -1 0 X 0 0",
"38 147 136 129","55 77 132 99","1", };

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
		cout << string(game.grid_width(), '_') << endl;
		game.serialize_grid(cout);

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == game_t::opp_id)
				continue;

			vector<optional<action_t>> actions;
			for (organ_t const& it_root : it_player.second.roots)
			{
				optional<action_t> action = it_root.grow(game);
				actions.push_back(action);
			}

			for (optional<action_t> const& it_action : actions)
			{
				if (!it_action)
				{
					if (it_player.first == game_t::me_id)
						cout << "WAIT" << endl;
				}
				else
					it_action->perform(game);
			}
		}
	}
}