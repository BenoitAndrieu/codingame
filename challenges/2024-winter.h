#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#include <optional>

#include <sstream>
#include <algorithm>

#include <limits>

#include <cassert>

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

enum class dir_t
{
	up, down, left, right
};

enum class organ_type_t
{
	// costs 1A 1B 1C 1D
	root,

	// costs 1A
	basic,

	// costs 1B 1C
	tentacle,

	// costs 1C 1D
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

string to_string(dir_t value)
{
	switch (value)
	{
	case dir_t::up: return "N";
	case dir_t::down: return "S";
	case dir_t::left: return "W";
	case dir_t::right: return "E";
	}
	throw exception();
}

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

struct xy
{
	int x = -1;
	int y = -1;

	auto operator<=>(const xy&) const = default;

	dir_t operator -(xy other) const
	{
		if (x == -1 || y == -1)
			throw exception();
		if (other.x == -1 || other.y == -1)
			throw exception();

		const int d_x = x - other.x;
		const int d_y = y - other.y;

		switch (d_x)
		{
		case -1:
			if (d_y != 0) throw exception();
			return dir_t::left;
		case 1:
			if (d_y != 0) throw exception();
			return dir_t::right;
		}

		switch (d_y)
		{
		case -1:
			if (d_x != 0) throw exception();
			return dir_t::up;
		case 1:
			if (d_x != 0) throw exception();
			return dir_t::down;
		}

		throw exception();
	}

	xy operator + (dir_t dir) const
	{
		if (x == -1 || y == -1)
			throw exception();

		switch (dir)
		{
		case dir_t::up: return xy{ .x = x, .y = y - 1 };
		case dir_t::down:return xy{ .x = x, .y = y + 1 };
		case dir_t::left:return xy{ .x = x - 1 , .y = y };
		case dir_t::right:return xy{ .x = x + 1, .y = y };
		}

		throw exception();
	}
};

class organ_t
{
public:
	id_player_t owner = -1;
	id_organ_t id = -1;
	id_organ_t parentId = -1;
	organ_type_t type{};
	xy position{};
	optional<dir_t> direction{};
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
	set<xy> harvesters_targets;
};

class inputs
{
	queue<string> m_replay;

public:
#ifdef WITHIN_VS
	inputs(vector<string> replay)
	{
		for (string const& it : replay)
		{
			m_replay.push(it);
		}
	}
#else
	inputs() = default;
#endif

	string get_next()
	{
		if constexpr (within_vs == false)
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
private:
	vector<vector<cell_t>> m_grid;
	map<id_player_t, player_t> m_players;
	map<protein_type_t, vector<xy>> m_proteins;
	int m_requiredActionsCount = 0;
	id_organ_t m_nextId = 1;

public:
	explicit game_t(inputs& inputs, int height, int width);

	void update();
	void gather_resources();

	map<id_player_t, player_t> const& players() const { return m_players; }
	map<id_player_t, player_t>& players() { return m_players; }

	int requiredActionsCount() const { return m_requiredActionsCount; }

	vector<vector<cell_t>>& grid() { return m_grid; }
	vector<vector<cell_t>> const& grid() const { return m_grid; }

	map<protein_type_t, vector<xy>> const& proteins() const { return m_proteins; }
	map<protein_type_t, vector<xy>>& proteins() { return m_proteins; }

	int& nextId() { return m_nextId; }

	static constexpr id_player_t me_id = 1;
	static constexpr id_player_t opp_id = 0;
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
						return dir_t::right;
					if (organDir == "W")
						return dir_t::left;

					cerr << organDir << endl;
					throw exception();
				}();

			organ_t organ{
				.owner = owner,
				.id = organId,
				.parentId = organParentId,
				.type = organ_type,
				.position = xy{ x,y },
				.direction = dir,
				.rootId = organRootId,
			};

			m_players[owner].organs.insert({ organId, organ });
			m_nextId++;

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

	{
		string input = inputs.get_next();
		stringstream ss(input);
		int requiredActionsCount;
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
	optional<dir_t> direction{};

	void perform(game_t& game) const
	{
#ifdef WITHIN_VS
		cell_t& cell = game.grid()[target.y][target.x];
		if (cell.isWall == true)
			throw exception();
		if (cell.organ.has_value() == true)
			throw exception();

		player_t& it_player = game.players().at(owner);
		if (it_player.harvesters_targets.contains(target))
			throw exception();

		organ_t organ{
			.owner = owner,
			.id = game.nextId()++,
			.parentId = game.grid()[source.y][source.x].organ->id,
			.type = organ_type_to_grow,
			.position = target,
			.direction = direction,
			.rootId = rootId,
		};

		if (cell.protein)
		{
			switch (cell.protein.value())
			{
			case protein_type_t::A:
				it_player.proteins[protein_type_t::A] += 3;
				break;
			default:
				throw exception();
			}

			std::erase(game.proteins()[cell.protein.value()], target);

			cell.protein.reset();
		}

		switch (organ.type)
		{
		case organ_type_t::basic:
			it_player.proteins[protein_type_t::A] -= 1;
			break;
		case organ_type_t::harvester:
			it_player.proteins[protein_type_t::C] -= 1;
			it_player.proteins[protein_type_t::D] -= 1;
			break;
		case organ_type_t::tentacle:
			it_player.proteins[protein_type_t::B] -= 1;
			it_player.proteins[protein_type_t::C] -= 1;
			break;
		default:
			throw exception();
		}

		cell_t new_cell
		{
			.isWall = false,
			.organ = optional(organ),
			.protein = optional<protein_type_t>(),
		};
		swap(cell, new_cell);

		it_player.organs.insert({ organ.id, organ });
		if (organ_type_to_grow == organ_type_t::root)
			it_player.roots.push_back(organ);

#endif

		if (owner == game_t::me_id)
		{
			if (direction.has_value())
				cout << "GROW" << ' ' << fromId << ' ' << target.x << ' ' << target.y << ' ' << to_string(organ_type_to_grow) << ' ' << to_string(direction.value()) << endl;
			else
				cout << "GROW" << ' ' << fromId << ' ' << target.x << ' ' << target.y << ' ' << to_string(organ_type_to_grow) << endl;
		}
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

	for (pair<const int, player_t> const& it_player : game.players())
	{
		for (pair<const int, organ_t> const& it_organ : it_player.second.organs)
		{
			if (it_player.first != owner)
				bfs[it_organ.second.position.y][it_organ.second.position.x].visited = true;

			if (it_organ.second.rootId != id)
				continue;

			bfs[it_organ.second.position.y][it_organ.second.position.x].distance = 0;

			remaining.insert({ 0, it_organ.second.position });
		}
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
		neighbours.push_back(it_position + dir_t::right);
		neighbours.push_back(it_position + dir_t::up);
		neighbours.push_back(it_position + dir_t::down);
		neighbours.push_back(it_position + dir_t::left);
		for (xy const& it : neighbours)
		{
			cell_t const& it_neighbour_grid = clone.grid()[it.y][it.x];
			if (it_neighbour_grid.isWall)
				continue;

			if (game.players().at(owner).harvesters_targets.contains(it) == true)
				continue; // target should not be harvested by the player

			bfs_cell_t& it_neighbour = bfs[it.y][it.x];
			if (it_neighbour.distance.has_value() == true)
			{
				assert(bfs_cell.distance.has_value());
				if (it_neighbour.distance.value() <= bfs_cell.distance.value() + 1)
				{
					continue;
				}
			}

			assert(bfs_cell.distance.has_value());
			it_neighbour.distance = bfs_cell.distance.value() + 1;
			remaining.insert({ it_neighbour.distance.value(), it });
		}
	}

	enum class action_type_t
	{
		grow,
		attack,
	};

	struct data_t
	{
		action_type_t type{};
		xy position;
		optional<protein_type_t> protein;
	};

	multimap<distance_t, data_t> mmap_distance_to_protein;
	for (pair<const protein_type_t, vector<xy>> const& it_protein_type : game.proteins())
	{
		for (xy const& it_protein_target : it_protein_type.second)
		{
			if (game.players().at(owner).harvesters_targets.contains(it_protein_target) == true)
				continue; // target should not be harvested by the player

			bfs_cell_t const& bfs_cell = bfs[it_protein_target.y][it_protein_target.x];
			if (bfs_cell.distance.has_value() == false)
				continue;

			data_t d{
				.type = action_type_t::grow,
				.position = it_protein_target,
				.protein = it_protein_type.first,
			};
			mmap_distance_to_protein.insert({ bfs_cell.distance.value(), d });
		}
	}

	// if there is no protein available
	if (mmap_distance_to_protein.empty() == true)
	{
		for (int y = 0; y < game.grid().size(); ++y)
		{
			for (int x = 0; x < game.grid()[y].size(); ++x)
			{
				bfs_cell_t const& bfs_cell = bfs[y][x];
				if (bfs_cell.distance.has_value() == false)
					continue;

				if (bfs_cell.distance.value() != 1)
					continue;

				cell_t const& cell = game.grid()[y][x];
				if (cell.organ.has_value() == true)
					continue;

				data_t d
				{
					.type = action_type_t::grow,
					.position = xy{ x,y },
					.protein = optional<protein_type_t>{},
				};

				mmap_distance_to_protein.insert({ 1, d });
			}
		}

		for (pair<const int, player_t> const& it_player : game.players())
		{
			if (it_player.first == owner)
				continue;

			for (pair<const int, organ_t> const& it_organ : it_player.second.organs)
			{
				bfs_cell_t const& bfs_cell = bfs[it_organ.second.position.y][it_organ.second.position.x];
				if (bfs_cell.distance.has_value() == false)
					continue;

				if (bfs_cell.distance.value() < 2)
					continue;

				data_t d
				{
					.type = action_type_t::attack,
					.position = it_organ.second.position,
					.protein = optional<protein_type_t>{},
				};

				mmap_distance_to_protein.insert({ bfs_cell.distance.value(), d });
			}
		}
	}

	using priority_t = int;
	int current_prio = 0;
	const priority_t grow_tentacle_prio = current_prio++;
	const priority_t grow_harvester_prio = current_prio++;
	const priority_t grow_basic_prio = current_prio++;
	multimap<priority_t, action_t> candidates;

	for (auto const& [it_distance, it_data] : mmap_distance_to_protein)
	{
		vector<xy> backtrack;
		backtrack.push_back(it_data.position);
		assert(bfs[it_data.position.y][it_data.position.x].distance.value());
		for (xy it_position = it_data.position;
			bfs[it_position.y][it_position.x].distance.value() > 0;
			)
		{
			vector<xy> neighbours;
			neighbours.push_back(it_position + dir_t::left);
			neighbours.push_back(it_position + dir_t::up);
			neighbours.push_back(it_position + dir_t::down);
			neighbours.push_back(it_position + dir_t::right);

			distance_t min_distance = numeric_limits<distance_t>::max();
			xy min_position;
			for (xy const& it_neighbour : neighbours)
			{
				cell_t const& it_neighbour_grid = clone.grid()[it_neighbour.y][it_neighbour.x];
				if (it_neighbour_grid.isWall)
					continue;

				bfs_cell_t const& bfs_cell = bfs[it_neighbour.y][it_neighbour.x];
				if (bfs_cell.distance.has_value() == false)
					continue; // could be an harvested protein

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
			assert(bfs[it_data.position.y][it_data.position.x].distance.value());
		}

		if (backtrack.size() <= 1)
			throw exception();

		if (backtrack.size() == 3 && it_data.type == action_type_t::grow)
		{
			if (game.players().at(owner).proteins.at(protein_type_t::C) > 0
				&& game.players().at(owner).proteins.at(protein_type_t::D) > 0)
			{
				action_t grow_harvester
				{
					.owner = owner,
					.rootId = rootId,
					.fromId = id,
					.source = *(backtrack.begin() + 2),
					.target = *(backtrack.begin() + 1),
					.organ_type_to_grow = organ_type_t::harvester,
					.direction = grow_harvester.target - grow_harvester.source,
				};
				candidates.insert({ grow_harvester_prio, grow_harvester });

				continue;
			}
		}

		priority_t priority = grow_basic_prio;

		if (it_data.type == action_type_t::attack)
		{
			const bool tentacle_enough_resources =
				game.players().at(owner).proteins.at(protein_type_t::B) > 0
				&& game.players().at(owner).proteins.at(protein_type_t::C) > 0;

			if (backtrack.size() != 3)
			{
				if (tentacle_enough_resources)
					priority = grow_tentacle_prio;
			}
			else
			{
				if (tentacle_enough_resources)
				{
					action_t grow_tentacle
					{
						.owner = owner,
						.rootId = rootId,
						.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
						.source = *(backtrack.begin() + 2),
						.target = *(backtrack.begin() + 1),
						.organ_type_to_grow = organ_type_t::tentacle,
						.direction = grow_tentacle.target - grow_tentacle.source,
					};
					candidates.insert({ grow_tentacle_prio, grow_tentacle });

					continue;
				}
				else
					priority = grow_tentacle_prio;
			}
		}

		if (game.players().at(owner).proteins.at(protein_type_t::A) == 0)
			continue;

		action_t grow_basic
		{
			.owner = owner,
			.rootId = rootId,
			.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
			.source = *backtrack.rbegin(),
			.target = *(backtrack.rbegin() + 1),
			.organ_type_to_grow = organ_type_t::basic,
		};
		candidates.insert({ priority, grow_basic });
	}

	for (pair<const int, action_t> const& it : candidates)
		return it.second;
	return {};
}

void game_t::update()
{
	for (pair<const int, player_t>& it_player : players())
	{
		it_player.second.harvesters_targets.clear();

		for (pair<const int, organ_t> const& it_organ : it_player.second.organs)
		{
			if (it_organ.second.type != organ_type_t::harvester)
				continue;

			assert(it_organ.second.direction.has_value());
			it_player.second.harvesters_targets.insert(it_organ.second.position + it_organ.second.direction.value());
		}
	}
}

void game_t::gather_resources()
{
	for (pair<const int, player_t>& it_player : players())
	{
		for (xy const& it_target : it_player.second.harvesters_targets)
		{
			cell_t const& cell = grid()[it_target.y][it_target.x];
			if (cell.protein.has_value() == false)
				continue; // no proteins here

			protein_type_t type = cell.protein.value();

			it_player.second.proteins[type] += 1;
		}
	}
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
		game.update();

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
