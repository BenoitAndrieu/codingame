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

dir_t opposite(dir_t value)
{
	switch (value)
	{
	case dir_t::up: return dir_t::down;
	case dir_t::down: return dir_t::up;
	case dir_t::left: return dir_t::right;
	case dir_t::right: return dir_t::left;
	}

	throw exception();
}

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

using priority_t = int;
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

distance_t distance(xy a, xy b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

bool is_valid(xy position, int grid_width, int grid_height)
{
	if (position.x < 0)
		return false;
	if (position.x >= grid_width)
		return false;
	if (position.y < 0)
		return false;
	if (position.y >= grid_height)
		return false;
	return true;
}

void add_if_valid(xy position, int grid_width, int grid_height, vector<xy>& vector)
{
	if (is_valid(position, grid_width, grid_height) == false)
		return;
	vector.push_back(position);
}

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

	template<typename STREAM>
	STREAM& serialize(STREAM& stream) const;
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
			{
				static int line_index = 1;
				cerr << "\"" << input << "\",";
				if (line_index++ % 10 == 0)
					cerr << endl;
			}

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

	template<typename STREAM>
	STREAM& serialize_grid(STREAM& stream) const;

	map<id_player_t, player_t> const& players() const { return m_players; }
	map<id_player_t, player_t>& players() { return m_players; }

	int requiredActionsCount() const { return m_requiredActionsCount; }

	vector<vector<cell_t>>& grid() { return m_grid; }
	vector<vector<cell_t>> const& grid() const { return m_grid; }

	int grid_width() const { return m_grid[0].size(); }
	int grid_height() const { return m_grid.size(); }

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

			organ_t organ
			{
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
	priority_t priority = -1;
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

		const organ_t organ
		{
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
			it_player.proteins[cell.protein.value()] += 3;

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
		case organ_type_t::sporer:
			it_player.proteins[protein_type_t::B] -= 1;
			it_player.proteins[protein_type_t::D] -= 1;
			break;
		case organ_type_t::root:
			it_player.proteins[protein_type_t::A] -= 1;
			it_player.proteins[protein_type_t::B] -= 1;
			it_player.proteins[protein_type_t::C] -= 1;
			it_player.proteins[protein_type_t::D] -= 1;
			break;
		default:
			throw exception();
		}

		if (it_player.proteins[protein_type_t::A] < 0
			|| it_player.proteins[protein_type_t::B] < 0
			|| it_player.proteins[protein_type_t::C] < 0
			|| it_player.proteins[protein_type_t::D] < 0)
			throw exception();

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
			if (organ_type_to_grow == organ_type_t::root)
				cout << "SPORE" << ' ' << fromId << ' ' << target.x << ' ' << target.y << endl;
			else if (direction.has_value())
				cout << "GROW" << ' ' << fromId << ' ' << target.x << ' ' << target.y << ' ' << to_string(organ_type_to_grow) << ' ' << to_string(direction.value()) << endl;
			else
				cout << "GROW" << ' ' << fromId << ' ' << target.x << ' ' << target.y << ' ' << to_string(organ_type_to_grow) << endl;
		}
	}
};

using score_t = int;

optional<action_t> organ_t::grow(game_t const& game) const
{
	struct bfs_cell_t
	{
		bool visitable = true;
		bool visited = false;
		optional<distance_t> distance;
	};

	vector<vector<bfs_cell_t>> bfs(game.grid().size(), vector<bfs_cell_t>(game.grid()[0].size()));

	for (int y = 0; y < game.grid().size();++y)
	{
		for (int x = 0; x < game.grid()[y].size(); ++x)
		{
			cell_t const& it_cell = game.grid()[y][x];
			if (it_cell.isWall == false)
				continue;
			bfs[y][x].visitable = false;
		}
	}

	multimap<distance_t, xy> bfs_queue; // the multimap allows to process the nearest cells
	for (pair<const id_player_t, player_t> const& it_player : game.players())
	{
		for (pair<const id_organ_t, organ_t> const& it_organ : it_player.second.organs)
		{
			if (it_organ.second.owner == owner)
			{
				if (it_organ.second.rootId != id)
				{
					// we can not grow above another organ
					bfs[it_organ.second.position.y][it_organ.second.position.x].visitable = false;

					continue;
				}

				// we can grow from any organ from the current root
				bfs[it_organ.second.position.y][it_organ.second.position.x].distance = 0;

				bfs_queue.insert({ 0, it_organ.second.position });
			}
			else if (it_organ.second.rootId != id)
			{
				// a tentacle blocks growing on the targeted cell (TODO but a spore could fire) (TODO could be interesting to have defensive tentacles)
				if (it_organ.second.type == organ_type_t::tentacle)
				{
					const auto tentacle_target = it_organ.second.position + it_organ.second.direction.value();
					if (is_valid(tentacle_target, game.grid_width(), game.grid_height()))
						bfs[tentacle_target.y][tentacle_target.x].visitable = false;
				}

				continue;
			}
		}
	}

	const vector<vector<bfs_cell_t>> bfs_init_state = bfs;
	const multimap<distance_t, xy> bfs_queue_init_state = bfs_queue;

	auto fn_compute_bfs = [&game](auto& _bfs, auto& _bfs_queue, set<xy> const& _harvesters_targets)
		{
			while (_bfs_queue.empty() == false)
			{
				const xy it_position = [&]()
					{
						auto const it = _bfs_queue.cbegin();
						const xy position = it->second;
						_bfs_queue.erase(it);
						return position;
					}();

				bfs_cell_t& bfs_cell = _bfs[it_position.y][it_position.x];
				if (bfs_cell.visited)
					continue;
				if (bfs_cell.visitable == false)
					continue;

				bfs_cell.visited = true;

				cell_t const& cell = game.grid()[it_position.y][it_position.x];
				if (cell.isWall == true)
					continue;

				vector<xy> neighbours;
				add_if_valid(it_position + dir_t::right, game.grid_width(), game.grid_height(), neighbours);
				add_if_valid(it_position + dir_t::up, game.grid_width(), game.grid_height(), neighbours);
				add_if_valid(it_position + dir_t::down, game.grid_width(), game.grid_height(), neighbours);
				add_if_valid(it_position + dir_t::left, game.grid_width(), game.grid_height(), neighbours);
				for (xy const& it : neighbours)
				{
					cell_t const& it_neighbour_grid = game.grid()[it.y][it.x];
					if (it_neighbour_grid.isWall)
						continue;

					if (_harvesters_targets.contains(it) == true)
						continue; // target should not be harvested by the root's player

					bfs_cell_t& it_neighbour = _bfs[it.y][it.x];
					if (it_neighbour.visitable == false)
						continue;

					if (it_neighbour.distance.has_value() == true)
					{
						assert(bfs_cell.distance.has_value());
						if (it_neighbour.distance.value() <= bfs_cell.distance.value() + 1)
						{
							// another cell has already computed a shortest distance
							continue;
						}
					}

					assert(bfs_cell.distance.has_value());
					it_neighbour.distance = bfs_cell.distance.value() + 1;
					_bfs_queue.insert({ it_neighbour.distance.value(), it });
				}
			}
		};

	fn_compute_bfs(bfs, bfs_queue, game.players().at(owner).harvesters_targets);

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

	// finds the proteins to grow to
	multimap<distance_t, data_t> mmap_distance_to_target;
	for (pair<const protein_type_t, vector<xy>> const& it_protein_type : game.proteins())
	{
		for (xy const& it_protein_target : it_protein_type.second)
		{
			if (game.players().at(owner).harvesters_targets.contains(it_protein_target) == true)
				continue; // target should not be harvested by the player

			bfs_cell_t const& bfs_cell = bfs[it_protein_target.y][it_protein_target.x];
			if (bfs_cell.visited == false)
				continue;
			if (bfs_cell.distance.has_value() == false)
				continue;

			const data_t d
			{
				.type = action_type_t::grow,
				.position = it_protein_target,
				.protein = it_protein_type.first,
			};
			mmap_distance_to_target.insert({ bfs_cell.distance.value(), d });
		}
	}

	// detect if the organ has harvesters on each protein
	set<protein_type_t> harvesting;
	for (pair<const id_organ_t, organ_t> const& it_organ : game.players().at(owner).organs)
	{
		if (it_organ.second.rootId != id)
			continue;

		if (it_organ.second.type == organ_type_t::harvester)
		{
			const xy harvester_target = it_organ.second.position + it_organ.second.direction.value();
			if (is_valid(harvester_target, game.grid_width(), game.grid_height()) == true)
			{
				cell_t const& cell = game.grid()[harvester_target.y][harvester_target.x];
				if (cell.protein.has_value() == true)
				{
					harvesting.insert(cell.protein.value());
				}
			}
		}
	}

	// finds the organs to attack
	multimap<distance_t, data_t> mmap_distance_to_enemy;
	for (pair<const id_player_t, player_t> const& it_player : game.players())
	{
		if (it_player.first == owner)
			continue;

		for (pair<const id_organ_t, organ_t> const& it_organ : it_player.second.organs)
		{
			bfs_cell_t const& bfs_cell = bfs[it_organ.second.position.y][it_organ.second.position.x];
			if (bfs_cell.visited == false)
				continue;
			if (bfs_cell.distance.has_value() == false)
				continue;

			const data_t d
			{
				.type = action_type_t::attack,
				.position = it_organ.second.position,
				.protein = optional<protein_type_t>{},
			};

			mmap_distance_to_enemy.insert({ bfs_cell.distance.value(), d });
		}
	}

	const bool harvesting_ok_for_tentacles = harvesting.contains(protein_type_t::B) && harvesting.contains(protein_type_t::C);
	const bool way_enough_resources_for_tentacles = game.players().at(owner).proteins.at(protein_type_t::B) >= 5 && game.players().at(owner).proteins.at(protein_type_t::C) >= 5;
	const bool enemy_is_near = mmap_distance_to_enemy.empty() == false && mmap_distance_to_enemy.begin()->first <= 7; // enemy is near

	if (mmap_distance_to_target.empty() == true) // if there is no protein available
	{
		// finds the nearest empty cells
		for (int y = 0; y < game.grid().size(); ++y)
		{
			for (int x = 0; x < game.grid()[y].size(); ++x)
			{
				bfs_cell_t const& bfs_cell = bfs[y][x];
				if (bfs_cell.visited == false)
					continue;
				if (bfs_cell.distance.has_value() == false)
					continue;

				if (bfs_cell.distance.value() != 1)
					continue;

				cell_t const& cell = game.grid()[y][x];
				if (cell.organ.has_value() == true)
					continue;

				const data_t d
				{
					.type = action_type_t::grow,
					.position = xy{ x,y },
					.protein = optional<protein_type_t>{},
				};

				mmap_distance_to_target.insert({ 1, d });
			}
		}
	}

	if (mmap_distance_to_target.empty() == true // if there is no protein available
		|| harvesting_ok_for_tentacles
		|| way_enough_resources_for_tentacles
		|| enemy_is_near)
	{
		// finds the organs to attack
		for (pair<const id_player_t, player_t> const& it_player : game.players())
		{
			if (it_player.first == owner)
				continue;

			for (pair<const id_organ_t, organ_t> const& it_organ : it_player.second.organs)
			{
				bfs_cell_t const& bfs_cell = bfs[it_organ.second.position.y][it_organ.second.position.x];
				if (bfs_cell.visited == false)
					continue;
				if (bfs_cell.distance.has_value() == false)
					continue;

				if (bfs_cell.distance.value() < 2)
					continue; // too near to be attacked

				const data_t d
				{
					.type = action_type_t::attack,
					.position = it_organ.second.position,
					.protein = optional<protein_type_t>{},
				};

				mmap_distance_to_target.insert({ bfs_cell.distance.value(), d });
			}
		}
	}

	priority_t current_prio = 2;

	const priority_t grow_tentacle_prio = current_prio;

	current_prio = 5;
	priority_t grow_harvester_A_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_sporer_A_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_root_A_prio = numeric_limits<priority_t>::max() / 2;
	if (harvesting.contains(protein_type_t::A) == false)
	{
		grow_harvester_A_prio = current_prio++;
		grow_root_A_prio = current_prio++;
		grow_sporer_A_prio = current_prio++;
	}

	current_prio = 5;
	priority_t grow_harvester_B_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_sporer_B_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_root_B_prio = numeric_limits<priority_t>::max() / 2;
	if (harvesting.contains(protein_type_t::B) == false)
	{
		grow_harvester_B_prio = current_prio++;
		grow_root_B_prio = current_prio++;
		grow_sporer_B_prio = current_prio++;
	}

	current_prio = 5;
	priority_t grow_harvester_C_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_sporer_C_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_root_C_prio = numeric_limits<priority_t>::max() / 2;
	if (harvesting.contains(protein_type_t::C) == false)
	{
		grow_harvester_C_prio = current_prio++;
		grow_root_C_prio = current_prio++;
		grow_sporer_C_prio = current_prio++;
	}

	current_prio = 5;
	priority_t grow_harvester_D_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_sporer_D_prio = numeric_limits<priority_t>::max() / 2;
	priority_t grow_root_D_prio = numeric_limits<priority_t>::max() / 2;
	if (harvesting.contains(protein_type_t::D) == false)
	{
		grow_harvester_D_prio = current_prio++;
		grow_root_D_prio = current_prio++;
		grow_sporer_D_prio = current_prio++;
	}

	current_prio += 5;

	multimap<priority_t, action_t> candidates;
	multimap<xy, action_t> mmap_harversters_candidates;

	auto fn_detect_action = [&](vector<xy> const& backtrack, const data_t& it_data)
		{
			if (backtrack.size() == 3 && it_data.type == action_type_t::grow)
			{
				if (game.players().at(owner).proteins.at(protein_type_t::C) < 1
					|| game.players().at(owner).proteins.at(protein_type_t::D) < 1)
				{
					// not enough resources for an harvester
					[[maybe_unused]] const int breakpoint = 1;
				}
				else
				{
					// enough resources for an harvester

					const xy harvester_position = *(backtrack.begin() + 1);
					const xy protein_position = *backtrack.begin();

					// we will perform a distance computation to check if the harvester would be a blocker

					vector<vector<bfs_cell_t>> bfs_harvester = bfs_init_state;
					multimap<distance_t, xy> bfs_queue_harvester = bfs_queue_init_state;
					set<xy> harvesters_targets = game.players().at(owner).harvesters_targets;

					{
						bfs_harvester[harvester_position.y][harvester_position.x].distance = 0;
						bfs_queue_harvester.insert({ 0, harvester_position });
						harvesters_targets.insert(protein_position);
					}

					fn_compute_bfs(bfs_harvester, bfs_queue_harvester, harvesters_targets);

					set<xy> reachable_proteins_before;
					for (pair<const protein_type_t, vector<xy>> const& it : game.proteins())
					{
						for (xy it_protein_position : it.second)
						{
							bfs_cell_t const& bfs_cell = bfs[it_protein_position.y][it_protein_position.x];
							if (bfs_cell.visited == false)
								continue;
							if (bfs_cell.distance.has_value() == false)
								continue;
							reachable_proteins_before.insert(it_protein_position);
						}
					}

					vector<xy> positions_to_check = [&]()
						{
							vector<xy> positions;
							for (int i = -1; i <= 1;++i)
							{
								for (int j = -1; j <= 1;++j)
								{
									if (i == 0 && j == 0)
										continue;
									add_if_valid(xy(protein_position.x + i, protein_position.y + j), game.grid_width(), game.grid_height(), positions);
								}
							}
							return positions;
						}();

					bool blocking = [&]()
						{
							for (const xy it_position : positions_to_check)
							{
								bfs_cell_t const& bfs_cell_harvester = bfs_harvester[it_position.y][it_position.x];
								bfs_cell_t const& bfs_cell = bfs[it_position.y][it_position.x];

								if (bfs_cell.visited == false)
									continue;
								if (bfs_cell.distance.has_value() == false)
									continue;
								if (bfs_cell.distance.value() == 0)
									continue;
								if (bfs_cell_harvester.distance.has_value() == true)
									continue; // not a blocker

								return true; // blocker
							}

							return false;
						}();

					set<xy> reachable_proteins_after;
					for (pair<const protein_type_t, vector<xy>> const& it : game.proteins())
					{
						for (xy it_protein_position : it.second)
						{
							bfs_cell_t const& bfs_cell = bfs_harvester[it_protein_position.y][it_protein_position.x];
							if (bfs_cell.visited == false)
								continue;
							if (bfs_cell.distance.has_value() == false)
								continue;
							reachable_proteins_after.insert(it_protein_position);
						}
					}

					blocking = reachable_proteins_after.size() + 1 != reachable_proteins_before.size();

					if (blocking == true)
					{
						[[maybe_unused]] const int breakpoint = 1;
					}
					else
					{
						cell_t const& cell = game.grid()[protein_position.y][protein_position.x];
						const priority_t grow_harvester_prio = [&]()
							{
								if (cell.protein.has_value())
								{
									return min(min(grow_harvester_A_prio, grow_harvester_B_prio), min(grow_harvester_C_prio, grow_harvester_D_prio));
								}
								else
								{
									return numeric_limits<priority_t>::max() / 2;
								}
							}();

						const xy source = *(backtrack.begin() + 2);
						const action_t grow_harvester
						{
							.priority = grow_harvester_prio,
							.owner = owner,
							.rootId = rootId,
							.fromId = game.grid()[source.y][source.x].organ->id,
							.source = source,
							.target = harvester_position,
							.organ_type_to_grow = organ_type_t::harvester,
							.direction = protein_position - harvester_position,
						};

						candidates.insert({ grow_harvester_prio, grow_harvester });
						mmap_harversters_candidates.insert({ grow_harvester.target, grow_harvester });

						return;
					}
				}
			}

			cell_t const& cell = game.grid()[backtrack.begin()->y][backtrack.begin()->x];
			priority_t priority = [&]()
				{
					if (cell.protein.has_value() == true)
					{
						switch (cell.protein.value())
						{
						case protein_type_t::A: return grow_harvester_A_prio;
						case protein_type_t::B: return grow_harvester_B_prio;
						case protein_type_t::C: return grow_harvester_C_prio;
						case protein_type_t::D: return grow_harvester_D_prio;
						}
						throw exception();
					}
					else
					{
						return numeric_limits<priority_t>::max() / 2;
					}
				}();

			if (it_data.type == action_type_t::attack)
			{
				const bool tentacle_enough_resources =
					game.players().at(owner).proteins.at(protein_type_t::B) >= 1
					&& game.players().at(owner).proteins.at(protein_type_t::C) >= 1;

				if (backtrack.size() != 3 && backtrack.size() != 4)
				{
					if (tentacle_enough_resources)
					{
						priority = grow_tentacle_prio;
						if (backtrack.size() >= 10)
						{
							priority += 10;
						}
					}
				}
				else
				{
					if (tentacle_enough_resources)
					{
						const xy source = *backtrack.rbegin();
						const action_t grow_tentacle
						{
							.priority = grow_tentacle_prio,
							.owner = owner,
							.rootId = rootId,
							.fromId = game.grid()[source.y][source.x].organ->id,
							.source = source,
							.target = *(backtrack.rbegin() + 1),
							.organ_type_to_grow = organ_type_t::tentacle,
							.direction = *backtrack.begin() - *(backtrack.begin() + 1),
						};
						candidates.insert({ grow_tentacle_prio, grow_tentacle });

						return;
					}
					else
						priority = grow_tentacle_prio;
				}
			}

			auto fn_from_direction = [&](int size_required, int delta_begin)
				{
					optional<dir_t> from_direction;
					for (int i = 2; i < backtrack.size() - delta_begin; ++i)
					{
						if (from_direction.has_value() == false)
						{
							from_direction = backtrack[i] - backtrack[i - 1];
							continue;
						}

						if (from_direction != backtrack[i] - backtrack[i - 1])
						{
							from_direction.reset();
							return optional<dir_t>();
						}
					}

					return from_direction;
				};

			// can we grow a root ?
			constexpr int size_required_for_root = 4; // sporer root organ target
			if (backtrack.size() >= size_required_for_root)
			{
				// enough resources for a root ? (TODO and an harvester or a tentacle)
				if (game.players().at(owner).proteins.at(protein_type_t::A) == 0
					|| game.players().at(owner).proteins.at(protein_type_t::B) == 0
					|| game.players().at(owner).proteins.at(protein_type_t::C) == 0
					|| game.players().at(owner).proteins.at(protein_type_t::D) == 0)
				{
					[[maybe_unused]] const int breakpoint = 1;
				}
				else
				{
					cell_t const& src_cell = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x];
					if (src_cell.organ.has_value() == false)
					{
						[[maybe_unused]] const int breakpoint = 1;
					}
					else if (src_cell.organ->type != organ_type_t::sporer)
					{
						[[maybe_unused]] const int breakpoint = 1;
					}
					else if (const optional<dir_t> fire_from_direction = fn_from_direction(size_required_for_root, 0); fire_from_direction.has_value() == true)
					{
						if (fire_from_direction.value() == opposite(src_cell.organ.value().direction.value()))
						{
							cell_t const& target_cell = game.grid()[backtrack.begin()->y][backtrack.begin()->x];
							priority_t grow_root_prio = [&]()
								{
									if (target_cell.protein.has_value())
									{
										switch (target_cell.protein.value())
										{
										case protein_type_t::A: return grow_sporer_A_prio;
										case protein_type_t::B: return grow_sporer_B_prio;
										case protein_type_t::C: return grow_sporer_C_prio;
										case protein_type_t::D: return grow_sporer_D_prio;
										}
										throw exception();
									}
									else
									{
										return numeric_limits<priority_t>::max() / 2;
									}
								}();

							const distance_t sporer_fire_distance = distance(backtrack[0], *(backtrack.rbegin() + 2));
							const distance_t saving = (distance_t(backtrack.size()) - 2) - sporer_fire_distance;
							if (saving >= 1)
								grow_root_prio -= saving - 1;

							const xy new_root_position = *(backtrack.begin() + 2);

							// we want harvesters instead of roots
							for (auto [it, range_end] = mmap_harversters_candidates.equal_range(new_root_position);
								it != range_end;
								++it)
							{
								if (it->second.priority >= grow_root_prio)
									grow_root_prio = max(grow_root_prio, it->second.priority + 1);
							}

							const action_t grow_root
							{
								.priority = grow_root_prio,
								.owner = owner,
								.rootId = rootId,
								.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
								.source = *backtrack.rbegin(),
								.target = new_root_position,
								.organ_type_to_grow = organ_type_t::root,
							};

							candidates.insert({ grow_root_prio, grow_root });
						}
					}
					else
					{
						[[maybe_unused]] const int breakpoint = 1;
					}
				}
			}

			// can we grow a sporer ?
			constexpr int size_required_for_sporer = 5; // organ sporer root organ target
			if (backtrack.size() >= size_required_for_sporer)
			{
				// enough resources for a sporer and a root after and an harvester or a tentacle
				if (game.players().at(owner).proteins.at(protein_type_t::A) < 1
					|| game.players().at(owner).proteins.at(protein_type_t::B) < 3
					|| game.players().at(owner).proteins.at(protein_type_t::C) < 2
					|| game.players().at(owner).proteins.at(protein_type_t::D) < 3)
				{
					// not enough resources
					[[maybe_unused]] const int breakpoint = 1;
				}
				else if (game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->type == organ_type_t::sporer)
				{
					// don't grow a sporer from a sporer
					[[maybe_unused]] const int breakpoint = 1;
				}
				else
				{
					// clear path ?
					const optional<dir_t> fire_from_direction = fn_from_direction(size_required_for_sporer, 1);

					if (fire_from_direction.has_value() == true)
					{
						cell_t const& target_cell = game.grid()[backtrack.begin()->y][backtrack.begin()->x];
						priority_t grow_sporer_prio = [&]()
							{
								if (target_cell.protein.has_value())
								{
									switch (target_cell.protein.value())
									{
									case protein_type_t::A: return grow_sporer_A_prio;
									case protein_type_t::B: return grow_sporer_B_prio;
									case protein_type_t::C: return grow_sporer_C_prio;
									case protein_type_t::D: return grow_sporer_D_prio;
									}
									throw exception();
								}
								else
								{
									return numeric_limits<priority_t>::max() / 2;
								}
							}();

						const distance_t sporer_fire_distance = distance(backtrack[1], *(backtrack.rbegin() + 2));
						const distance_t saving = (distance_t(backtrack.size()) - 2) - sporer_fire_distance;
						if (saving >= 1)
							grow_sporer_prio -= saving - 1;

						const xy new_sporer_position = *(backtrack.rbegin() + 1);

						// we want harvesters instead of sporers
						for (auto [it, range_end] = mmap_harversters_candidates.equal_range(new_sporer_position);
							it != range_end;
							++it)
						{
							if (it->second.priority >= grow_sporer_prio)
								grow_sporer_prio = max(grow_sporer_prio, it->second.priority + 1);
						}

						const action_t grow_sporer
						{
							.priority = grow_sporer_prio,
							.owner = owner,
							.rootId = rootId,
							.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
							.source = *backtrack.rbegin(),
							.target = new_sporer_position,
							.organ_type_to_grow = organ_type_t::sporer,
							.direction = opposite(fire_from_direction.value()),
						};

						candidates.insert({ grow_sporer_prio, grow_sporer });
					}
				}
			}

			priority_t grow_basic_priority = priority + 2;
			const xy new_basic_position = *(backtrack.rbegin() + 1);

			// we want harvesters instead of basics
			for (auto [it, range_end] = mmap_harversters_candidates.equal_range(new_basic_position);
				it != range_end;
				++it)
			{
				if (it->second.priority >= grow_basic_priority)
					grow_basic_priority = max(grow_basic_priority, it->second.priority + 1);
			}

			cell_t const& target_cell = game.grid()[new_basic_position.y][new_basic_position.x];
			if (target_cell.protein.has_value() == true)
				grow_basic_priority += 2;

			if (game.players().at(owner).proteins.at(protein_type_t::A) > 0)
			{
				const action_t grow_basic
				{
					.priority = grow_basic_priority,
					.owner = owner,
					.rootId = rootId,
					.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
					.source = *backtrack.rbegin(),
					.target = new_basic_position,
					.organ_type_to_grow = organ_type_t::basic,
				};

				candidates.insert({ grow_basic_priority, grow_basic });

				return;
			}

			// grow a tentacle instead ?
			if (game.players().at(owner).proteins.at(protein_type_t::B) > 0
				&& game.players().at(owner).proteins.at(protein_type_t::C) > 0)
			{
				const action_t grow_tentacle
				{
					.priority = grow_basic_priority,
					.owner = owner,
					.rootId = rootId,
					.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
					.source = *backtrack.rbegin(),
					.target = new_basic_position,
					.organ_type_to_grow = organ_type_t::tentacle,
					.direction = grow_tentacle.target - grow_tentacle.source,
				};

				candidates.insert({ grow_basic_priority, grow_tentacle });

				return;
			}

			// grow an harvester instead ?
			if (game.players().at(owner).proteins.at(protein_type_t::C) > 0
				&& game.players().at(owner).proteins.at(protein_type_t::D) > 0)
			{
				const action_t grow_harvester
				{
					.priority = grow_basic_priority,
					.owner = owner,
					.rootId = rootId,
					.fromId = game.grid()[backtrack.rbegin()->y][backtrack.rbegin()->x].organ->id,
					.source = *backtrack.rbegin(),
					.target = new_basic_position,
					.organ_type_to_grow = organ_type_t::harvester,
					.direction = grow_harvester.target - grow_harvester.source,
				};

				candidates.insert({ grow_basic_priority, grow_harvester });

				return;
			}
		};

	for (auto const& [it_distance, it_data] : mmap_distance_to_target)
	{
		auto fn_backtrack = [&](optional<dir_t> start)
			{
				vector<xy> backtrack;
				backtrack.push_back(it_data.position);
				assert(bfs[it_data.position.y][it_data.position.x].distance.value());
				for (xy it_position = it_data.position;
					bfs[it_position.y][it_position.x].distance.value() > 0;
					)
				{
					vector<xy> neighbours;
					if (backtrack.size() == 1)
					{
						if (!start || start == dir_t::left)
							add_if_valid(it_position + dir_t::left, game.grid_width(), game.grid_height(), neighbours);
						if (!start || start == dir_t::up)
							add_if_valid(it_position + dir_t::up, game.grid_width(), game.grid_height(), neighbours);
						if (!start || start == dir_t::down)
							add_if_valid(it_position + dir_t::down, game.grid_width(), game.grid_height(), neighbours);
						if (!start || start == dir_t::right)
							add_if_valid(it_position + dir_t::right, game.grid_width(), game.grid_height(), neighbours);
					}
					else
					{
						// trying to stay in the same direction to favor spore fire
						const dir_t dir = *backtrack.rbegin() - *(backtrack.rbegin() + 1);
						if (dir == dir_t::down || dir == dir_t::up)
						{
							add_if_valid(it_position + dir, game.grid_width(), game.grid_height(), neighbours);
							add_if_valid(it_position + opposite(dir), game.grid_width(), game.grid_height(), neighbours);
							add_if_valid(it_position + dir_t::left, game.grid_width(), game.grid_height(), neighbours);
							add_if_valid(it_position + dir_t::right, game.grid_width(), game.grid_height(), neighbours);
						}
						else
						{
							add_if_valid(it_position + dir, game.grid_width(), game.grid_height(), neighbours);
							add_if_valid(it_position + opposite(dir), game.grid_width(), game.grid_height(), neighbours);
							add_if_valid(it_position + dir_t::down, game.grid_width(), game.grid_height(), neighbours);
							add_if_valid(it_position + dir_t::up, game.grid_width(), game.grid_height(), neighbours);
						}
					}

					distance_t min_distance = numeric_limits<distance_t>::max();
					xy min_position;
					for (xy const& it_neighbour : neighbours)
					{
						// avoid to go on the same cells over and over
						if (find(backtrack.crbegin(), backtrack.crend(), it_neighbour) != backtrack.crend())
							continue;

						cell_t const& it_neighbour_grid = game.grid()[it_neighbour.y][it_neighbour.x];
						if (it_neighbour_grid.isWall)
							continue;
						if (it_neighbour_grid.organ && it_neighbour_grid.organ->owner != owner)
							continue;

						bfs_cell_t const& bfs_cell = bfs[it_neighbour.y][it_neighbour.x];
						if (bfs_cell.visited == false)
							continue;
						if (bfs_cell.distance.has_value() == false)
							continue; // could be an harvested protein

						if (bfs_cell.distance.value() > min_distance)
							continue;

						if (bfs_cell.distance.value() == min_distance)
						{
							cell_t const& it_min_position_grid = game.grid()[min_position.y][min_position.x];
							if (it_min_position_grid.protein.has_value() == false)
								continue; // the current minima does not go through a protein, it is better

							[[maybe_unused]] const int breakpoint = 1;
						}

						min_distance = bfs_cell.distance.value();
						min_position = it_neighbour;
					}

					if (min_distance >= numeric_limits<distance_t>::max())
						return vector<xy>{};

					backtrack.push_back(min_position);

					it_position = min_position;
					assert(bfs[it_data.position.y][it_data.position.x].distance.value());
				}

				return backtrack;
			};

		const vector<xy> backtrack = fn_backtrack(optional<dir_t>());

		if (backtrack.size() < 2)
			continue;

		fn_detect_action(backtrack, it_data);

		// we may be missing harvesters or tentacles if target is too near, there could be another path
		if (backtrack.size() == 2)
		{
			const dir_t dir = backtrack[0] - backtrack[1];

			if (dir != dir_t::left)
			{
				const vector<xy> left = fn_backtrack(dir_t::left);
				if (left.size() >= 3)
					fn_detect_action(left, it_data);
			}

			if (dir != dir_t::right)
			{
				const vector<xy> right = fn_backtrack(dir_t::right);
				if (right.size() >= 3)
					fn_detect_action(right, it_data);
			}

			if (dir != dir_t::up)
			{
				const vector<xy> up = fn_backtrack(dir_t::up);
				if (up.size() >= 3)
					fn_detect_action(up, it_data);
			}

			if (dir != dir_t::down)
			{
				const vector<xy> down = fn_backtrack(dir_t::down);
				if (down.size() >= 3)
					fn_detect_action(down, it_data);
			}
		}
	}

	static xy debug_xy;
	static organ_type_t debug_organ;
	if (is_valid(debug_xy, game.grid_width(), game.grid_height()))
	{
		for (pair<const priority_t, action_t> const& it : candidates)
		{
			if (it.second.target != debug_xy)
				continue;
			if (it.second.organ_type_to_grow != debug_organ)
				continue;
			[[maybe_unused]] const int breakpoint = 1;
		}
	}

	for (pair<const priority_t, action_t> const& it : candidates)
		return it.second;
	return {};
}

void game_t::update()
{
	for (pair<const id_player_t, player_t>& it_player : players())
	{
		it_player.second.harvesters_targets.clear();

		for (pair<const id_organ_t, organ_t> const& it_organ : it_player.second.organs)
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
	for (pair<const id_player_t, player_t>& it_player : players())
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

template<typename STREAM>
STREAM& game_t::serialize_grid(STREAM& stream) const
{
	for (vector<cell_t> const& it_row : m_grid)
	{
		for (cell_t const& it_cell : it_row)
		{
			it_cell.serialize(stream);
		}

		stream << endl;
	}
	return stream;
}

template<typename STREAM>
STREAM& cell_t::serialize(STREAM& stream) const
{
	if (protein)
	{
		switch (protein.value())
		{
		case protein_type_t::A: stream << 'A'; return stream;
		case protein_type_t::B: stream << 'B'; return stream;
		case protein_type_t::C: stream << 'C'; return stream;
		case protein_type_t::D: stream << 'D'; return stream;
		default: throw exception();
		}
	}

	if (organ)
	{
		switch (organ.value().type)
		{
		case organ_type_t::root: stream << 'R'; return stream;
		case organ_type_t::basic: stream << 'O'; return stream;
		case organ_type_t::tentacle: stream << 'T'; return stream;
		case organ_type_t::harvester: stream << 'H'; return stream;
		case organ_type_t::sporer: stream << 'S'; return stream;
		default: throw exception();
		}
	}

	if (empty())
	{
		stream << '.';
		return stream;
	}

	if (isWall)
	{
		stream << 'X';
		return stream;
	}

	throw exception();
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

		vector<optional<action_t>> actions;
		for (auto const& it_root : game.players().at(game_t::me_id).roots)
		{
			auto action = it_root.grow(game);
			actions.push_back(action);
		}

		int requiredActionsCount = game.requiredActionsCount();
		for (optional<action_t> const& it_action : actions)
		{
			if (requiredActionsCount == 0)
				break;
			else
				requiredActionsCount--;

			if (!it_action)
				cout << "WAIT" << endl;
			else
				it_action->perform(game);
		}
		for (;requiredActionsCount > 0; --requiredActionsCount)
			cout << "WAIT" << endl;
	}
}
#endif
