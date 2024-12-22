#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <sstream>
#include <algorithm>
#include <optional>

using namespace std;

constexpr bool debug = true;
constexpr bool within_vs =
#ifdef WITHIN_VS
true;
#else
false;
#endif

class game_t;
struct action_t;

struct xy
{
	int x = -1;
	int y = -1;
};

enum class organ_type_t
{
	// costs 1A 1B 1C 1D
	root,

	// costs 1A
	basic,

	// costs 1B 1C
	tentacle,

	// costs 1C
	harvester,

	// costs 1B 1D
	sporer

	// costs ?
	// wall
};

string to_string(organ_type_t value)
{
	switch (value)
	{
	case organ_type_t::root: return "ROOT";
	case organ_type_t::basic: return "BASIC";
	case organ_type_t::tentacle: return "TENTACLE";
	case organ_type_t::harvester: return "HARVESTER";
	case organ_type_t::sporer: return "SPORER";
	}
	throw exception();
}

enum class dir_t
{
	up, down, left, right
};

enum class protein_type_t
{
	// provides 3 A if eaten
	A = 0,

	B,

	C,

	D
};

using id_player_t = int;
using id_organ_t = int;

class organ_t
{
public:
	id_player_t owner = -1;
	id_organ_t id = -1;
	id_organ_t parentId = -1;
	organ_type_t type{};
	xy position{};
	dir_t direction{};
	id_organ_t rootId = -1;

	optional<action_t> grow(game_t const& game) const;
};

struct cell_t
{
	bool isWall = false;
	optional<organ_t> organ;
	optional<protein_type_t> protein;

	bool empty() const
	{
		return
			isWall == false
			&& organ.has_value() == false
			&& protein.has_value() == false;
	}
};

struct player_t
{
	vector<organ_t> roots;
	vector<organ_t> organs; // including roots
	map<protein_type_t, int> proteins;
	id_organ_t nextId = 1;
};

class inputs
{
	queue<string> m_replay;

public:
#ifdef WITHIN_VS
	inputs(vector<string> replay)
	{
		for (auto const& it : replay)
		{
			m_replay.push(it);
		}
	}
#else
	inputs() = default;
#endif

	string get_next()
	{
		if (within_vs == false)
		{
			string input;
			getline(cin, input);

			if (debug)
				cerr << input << endl;

			return input;
		}

		string input = m_replay.front();
		m_replay.pop();
		return input;
	}
};

class game_t
{
public:
	explicit game_t(inputs& inputs, int height, int width);

	map<id_player_t, player_t> const& players() const { return m_players; }
	map<id_player_t, player_t> & players() { return m_players; }

	int requiredActionsCount() const { return m_requiredActionsCount; }

	vector<vector<cell_t>>& grid() { return m_grid; }
	vector<vector<cell_t>> const& grid() const { return m_grid; }

	map<protein_type_t, vector<xy>> const& proteins() const { return m_proteins; }

	static constexpr id_player_t me_id = 1;
	static constexpr id_player_t opp_id = 0;

private:
	vector<vector<cell_t>> m_grid;
	map<id_player_t, player_t> m_players;
	map<protein_type_t, vector<xy>> m_proteins;
	int m_requiredActionsCount = 0;
};

struct move_t
{
	xy dst;
	organ_type_t type;
};

game_t::game_t(inputs& inputs, int height, int width)
{
	m_grid.resize(height, vector<cell_t>(width));
	m_players.insert({ me_id, player_t{} }); // me
	m_players.insert({ opp_id, player_t{} }); // opponent

	int entityCount;
	{
		string input = inputs.get_next();
		stringstream ss(input);
		ss >> entityCount;
	}

	for (int i = 0; i < entityCount; ++i)
	{
		string input = inputs.get_next();
		int x, y, organId, organParentId, organRootId;
		id_player_t owner;
		string type, organDir;
		{
			stringstream ss(input);
			ss >> x >> y >> type >> owner >> organId >> organDir >> organParentId >> organRootId;
		}

		if (type == "WALL")
		{
			m_grid[y][x].isWall = true;
		}
		else if (type == "A" || type == "B" || type == "C" || type == "D")
		{
			protein_type_t protein = static_cast<protein_type_t>(type[0] - 'A');
			m_grid[y][x].protein = protein;
			m_proteins[protein].push_back(xy{ x,y });
		}
		else
		{
			organ_type_t organ_type = [=]()
				{
					if (type == "ROOT")
						return organ_type_t::root;
					if (type == "BASIC")
						return organ_type_t::basic;
					if (type == "TENTACLE")
						return organ_type_t::tentacle;
					if (type == "HARVESTER")
						return organ_type_t::harvester;
					if (type == "SPORER")
						return organ_type_t::sporer;

					cerr << type << endl;
					throw exception();
				}();

			dir_t dir = [=]()
				{
					if (organDir == "N")
						return dir_t::up;
					if (organDir == "S")
						return dir_t::down;
					if (organDir == "E")
						return dir_t::left;
					if (organDir == "W")
						return dir_t::right;

					cerr << organDir << endl;
					throw exception();
				}();

			organ_t organ;
			organ.type = organ_type;
			organ.id = organId;
			organ.position = xy{ x,y };
			organ.owner = owner;
			organ.direction = dir;
			organ.parentId = organParentId;
			organ.rootId = organRootId;

			m_players[owner].organs.push_back(organ);
			m_players[owner].nextId = max(m_players[owner].nextId - 1, static_cast<int>(m_players[owner].organs.size())) + 1;

			if (organ_type == organ_type_t::root)
				m_players[owner].roots.push_back(organ);

			m_grid[y][x].organ = organ;
		}
	}

	{
		string input = inputs.get_next();
		stringstream ss(input);
		int myA, myB, myC, myD;
		ss >> myA >> myB >> myC >> myD;
		m_players[me_id].proteins[protein_type_t::A] = myA;
		m_players[me_id].proteins[protein_type_t::B] = myB;
		m_players[me_id].proteins[protein_type_t::C] = myC;
		m_players[me_id].proteins[protein_type_t::D] = myD;
	}

	{
		string input = inputs.get_next();
		stringstream ss(input);
		int oppA, oppB, oppC, oppD;
		ss >> oppA >> oppB >> oppC >> oppD;
		m_players[opp_id].proteins[protein_type_t::A] = oppA;
		m_players[opp_id].proteins[protein_type_t::B] = oppB;
		m_players[opp_id].proteins[protein_type_t::C] = oppC;
		m_players[opp_id].proteins[protein_type_t::D] = oppD;
	}

	int requiredActionsCount;
	{
		string input = inputs.get_next();
		stringstream ss(input);
		ss >> requiredActionsCount;
		m_requiredActionsCount = requiredActionsCount;
	}
}

struct action_t
{
	id_player_t owner = -1;
	id_organ_t rootId = -1;
	id_organ_t fromId = -1;
	xy source;
	xy target;
	organ_type_t organ_type_to_grow{};

	void perform(game_t& game) const
	{
#ifdef WITHIN_VS
		auto& cell = game.grid()[target.y][target.x];
		if (cell.isWall == true)
			throw exception();
		if (cell.organ.has_value() == true)
			throw exception();

		organ_t organ;
		organ.owner = owner;
		organ.id = game.players().at(owner).nextId++;
		organ.parentId = game.grid()[source.y][source.x].organ->id;
		organ.type = organ_type_to_grow;
		organ.position = target;
		organ.direction = dir_t();
		organ.rootId = rootId;

		if (cell.protein)
			throw exception(); // TODO add resources to player

		cell_t new_cell;
		new_cell.isWall = false;
		new_cell.organ = organ;
		new_cell.protein.reset();
		swap(cell, new_cell);
		
		game.players().at(owner).organs.push_back(organ);
		if (organ_type_to_grow == organ_type_t::root)
			game.players().at(owner).roots.push_back(organ);

#else
		cout << "GROW" << ' ' << fromId << ' ' << target.x << ' ' << target.y << ' ' << to_string(organ_type_to_grow) << endl;
#endif
	}
};

using score_t = int;

optional<action_t> organ_t::grow(game_t const& game) const
{
	map<score_t, action_t> actions;

	for (auto const& it_protein_type : game.proteins())
	{
		for (auto const& it_protein_target : it_protein_type.second)
		{
			game_t clone = game;

			struct move_t
			{
				xy from{};
				xy to{};
			};

			struct bfs_data_t
			{
				bool visited = false;
				optional<move_t> move;
			};

			vector<vector<bfs_data_t>> bfs(game.grid().size(), vector<bfs_data_t>(game.grid()[0].size()));

			queue<move_t> move_queue;
			move_queue.push(move_t{ xy{}, position });

			vector<move_t> path_to_target;

			while (move_queue.empty() == false)
			{
				auto const it_move = move_queue.front();
				move_queue.pop();

				bfs_data_t& bfs_cell = bfs[it_move.to.y][it_move.to.x];
				cell_t& cell = clone.grid()[it_move.to.y][it_move.to.x];
				if (bfs_cell.visited)
					continue;
				if (cell.isWall == true)
					continue;

				// enough resources ?
				const int proteins = clone.players().at(owner).proteins.at(protein_type_t::A);
				const int required = abs(position.x - it_move.to.x) + abs(position.y - it_move.to.y);
				if (required > proteins)
					continue;

				bfs_cell.visited = true;
				bfs_cell.move = it_move;

				if (it_protein_target.x == it_move.to.x && it_protein_target.y == it_move.to.y)
					// found
					break;

				move_queue.push(move_t{ it_move.to,xy{ it_move.to.x + 1, it_move.to.y + 0 } });
				move_queue.push(move_t{ it_move.to,xy{ it_move.to.x - 0, it_move.to.y - 1 } });
				move_queue.push(move_t{ it_move.to,xy{ it_move.to.x + 0, it_move.to.y + 1 } });
				move_queue.push(move_t{ it_move.to,xy{ it_move.to.x - 1, it_move.to.y + 0 } });
			}

			bfs_data_t const& bfs_cell = bfs[it_protein_target.y][it_protein_target.x];
			if (bfs_cell.visited == true)
			{
				vector<move_t> backtrack;
				for (move_t move = bfs_cell.move.value();
					move.from.x != -1;
					move = bfs[move.from.y][move.from.x].move.value())
				{
					backtrack.push_back(move);
				}

				auto first_move = backtrack.back();

				action_t action;
				action.owner = owner;
				action.rootId = rootId;
				action.fromId = game.grid()[first_move.from.y][first_move.from.x].organ->id;
				action.source = first_move.from;
				action.target = first_move.to;
				action.organ_type_to_grow = organ_type_t::basic;

				actions.insert({ 0, action });
			}
		}
	}

	if (actions.empty() == true)
		return {};

	const auto it_best_action = actions.rbegin();
	return it_best_action->second;
}

#ifndef WITHIN_VS
int main()
{
	inputs inputs;

	string input = inputs.get_next();
	int width, height;
	{
		stringstream ss(input);
		ss >> width >> height;
	}

	while (true)
	{
		game_t game(inputs, height, width);
		int requiredActionsCount = game.requiredActionsCount();
		for (auto const& it_root : game.players().at(game_t::me_id).roots)
		{
			if (requiredActionsCount == 0)
				break;
			else
				requiredActionsCount--;

			auto action = it_root.grow(game);
			if (!action)
				cout << "WAIT" << endl;
			else
				action->perform(game);
		}
		for (;requiredActionsCount > 0; --requiredActionsCount)
			cout << "WAIT" << endl;
	}
}
#endif
