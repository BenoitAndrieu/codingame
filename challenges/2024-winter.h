#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <sstream>
#include <algorithm>
#include <optional>
#include <limits>

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

	auto operator<=>(const xy&) const = default;
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
using distance_t = int;

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
	map<id_organ_t, organ_t> organs; // including roots
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
	map<id_player_t, player_t>& players() { return m_players; }

	int requiredActionsCount() const { return m_requiredActionsCount; }

	vector<vector<cell_t>>& grid() { return m_grid; }
	vector<vector<cell_t>> const& grid() const { return m_grid; }

	map<protein_type_t, vector<xy>> const& proteins() const { return m_proteins; }
	map<protein_type_t, vector<xy>> & proteins() { return m_proteins; }

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
	xy from;
	xy to;
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

			m_players[owner].organs.insert({ organId, organ });
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
		{
			switch (cell.protein.value())
			{
			case protein_type_t::A:
				game.players().at(owner).proteins[protein_type_t::A] += 3;
				break;
			default:
				throw exception();
			}

			std::erase(game.proteins()[cell.protein.value()], target);

			cell.protein.reset();
		}

		cell_t new_cell;
		new_cell.isWall = false;
		new_cell.organ = organ;
		new_cell.protein.reset();
		swap(cell, new_cell);

		game.players().at(owner).organs.insert({ organ.id, organ });
		if (organ_type_to_grow == organ_type_t::root)
			game.players().at(owner).roots.push_back(organ);

#endif

		cout << "GROW" << ' ' << fromId << ' ' << target.x << ' ' << target.y << ' ' << to_string(organ_type_to_grow) << endl;
	}
};

using score_t = int;

optional<action_t> organ_t::grow(game_t const& game) const
{
	map<score_t, action_t> actions;

	game_t clone = game;

	struct bfs_cell_t
	{
		bool visited{};
		optional<distance_t> distance;
	};

	vector<vector<bfs_cell_t>> bfs(game.grid().size(), vector<bfs_cell_t>(game.grid()[0].size()));
	multimap<distance_t, xy> remaining;
	for (auto const& it_organ : game.players().at(owner).organs)
	{
		if (it_organ.second.rootId != id)
			continue;

		bfs[it_organ.second.position.y][it_organ.second.position.x].distance = 0;

		remaining.insert({ 0, it_organ.second.position });
	}

	while (remaining.empty() == false)
	{
		xy it_position;
		{
			auto const it = remaining.cbegin();
			it_position = it->second;
			remaining.erase(it);
		}

		bfs_cell_t& bfs_cell = bfs[it_position.y][it_position.x];
		if (bfs_cell.visited)
			continue;

		bfs_cell.visited = true;

		cell_t const& cell = clone.grid()[it_position.y][it_position.x];
		if (cell.isWall == true)
			continue;

		vector<xy> neighbours;
		neighbours.push_back(xy{ it_position.x + 1, it_position.y + 0 });
		neighbours.push_back(xy{ it_position.x - 0, it_position.y - 1 });
		neighbours.push_back(xy{ it_position.x + 0, it_position.y + 1 });
		neighbours.push_back(xy{ it_position.x - 1, it_position.y + 0 });
		for (auto const& it : neighbours)
		{
			cell_t const& it_neighbour_grid = clone.grid()[it.y][it.x];
			if (it_neighbour_grid.isWall)
				continue;

			auto& it_neighbour = bfs[it.y][it.x];
			if (it_neighbour.distance.has_value() == true && it_neighbour.distance.value() <= bfs_cell.distance.value() + 1)
			{
				continue;
			}

			it_neighbour.distance = bfs_cell.distance.value() + 1;
			remaining.insert({ it_neighbour.distance.value(), it });
		}
	}

	struct data
	{
		xy position;
		protein_type_t protein;
	};

	multimap<distance_t, data> mmap_distance_to_protein;
	for (auto const& it_protein_type : game.proteins())
	{
		for (auto const& it_protein_target : it_protein_type.second)
		{
			auto const& bfs_cell = bfs[it_protein_target.y][it_protein_target.x];
			data d;
			d.position = it_protein_target;
			d.protein = it_protein_type.first;
			mmap_distance_to_protein.insert({ bfs_cell.distance.value(), d });
		}
	}

	if (mmap_distance_to_protein.empty() == true)
		return {};

	const decltype(mmap_distance_to_protein)::const_iterator nearest = mmap_distance_to_protein.cbegin();

	vector<xy> backtrack;
	backtrack.push_back(nearest->second.position);
	for (xy it_position = nearest->second.position;
		bfs[it_position.y][it_position.x].distance.value() > 0;
		)
	{
		vector<xy> neighbours;
		neighbours.push_back(xy{ it_position.x + 1, it_position.y + 0 });
		neighbours.push_back(xy{ it_position.x - 0, it_position.y - 1 });
		neighbours.push_back(xy{ it_position.x + 0, it_position.y + 1 });
		neighbours.push_back(xy{ it_position.x - 1, it_position.y + 0 });

		distance_t min_distance = numeric_limits<distance_t>::max();
		xy min_position;
		for (auto const& it_neighbour : neighbours)
		{
			cell_t const& it_neighbour_grid = clone.grid()[it_neighbour.y][it_neighbour.x];
			if (it_neighbour_grid.isWall)
				continue;

			auto const& bfs_cell = bfs[it_neighbour.y][it_neighbour.x];
			if (bfs_cell.distance.value() < min_distance)
			{
				min_distance = bfs_cell.distance.value();
				min_position = it_neighbour;
			}
		}

		if (min_distance >= numeric_limits<distance_t>::max())
			throw exception();

		backtrack.push_back(min_position);

		it_position = min_position;
	}

	if (backtrack.size() <= 1)
		throw exception();

	action_t action;
	action.owner = owner;
	action.rootId = rootId;
	action.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id;
	action.source = *backtrack.rbegin();
	action.target = *(backtrack.rbegin() + 1);
	action.organ_type_to_grow = organ_type_t::basic;

	return action;
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
