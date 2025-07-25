constexpr bool debug = true;
constexpr bool within_vs =
#ifdef WITHIN_VS
true;
#else
false;
#endif

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

struct Agent {
    int id;
    int player;
    int x, y;
    int cooldown;
    int splash_bombs;
    int wetness;
    int optimal_range;
    int soaking_power;
};

int manhattan(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

using agent_id_t = int;
using player_id_t = int;

int main()
{
    int my_id;
    cin >> my_id; cin.ignore();

    int agent_data_count;
    cin >> agent_data_count; cin.ignore();

    // Données initiales (caractéristiques des agents)
    map<agent_id_t, tuple<player_id_t, int, int>> agent_specs; // agent_id -> (player, optimal_range, soaking_power)

    for (int i = 0; i < agent_data_count; i++) {
        agent_id_t agent_id;
        player_id_t player;
        int shoot_cooldown, optimal_range, soaking_power, splash_bombs;
        cin >> agent_id >> player >> shoot_cooldown >> optimal_range >> soaking_power >> splash_bombs; cin.ignore();
        agent_specs[agent_id] = {player, optimal_range, soaking_power};
    }

    int width, height;
    cin >> width >> height; cin.ignore();
    for (int i = 0; i < height * width; i++) {
        int x, y, tile_type;
        cin >> x >> y >> tile_type; cin.ignore();
    }

    // game loop
    while (1) {
        int agent_count;
        cin >> agent_count; cin.ignore();

        vector<Agent> all_agents;
        vector<Agent> my_agents;
        vector<Agent> enemy_agents;

        for (int i = 0; i < agent_count; i++) {
            int agent_id, x, y, cooldown, splash_bombs, wetness;
            cin >> agent_id >> x >> y >> cooldown >> splash_bombs >> wetness; cin.ignore();

            auto [player, optimal_range, soaking_power] = agent_specs[agent_id];

            Agent a = {agent_id, player, x, y, cooldown, splash_bombs, wetness, optimal_range, soaking_power};
            all_agents.push_back(a);
            if (my_id == player)
                my_agents.push_back(a);
            else
                enemy_agents.push_back(a);
        }

        int my_agent_count;
        cin >> my_agent_count; cin.ignore();

        // Pour chaque agent, tirer sur l’ennemi le plus mouillé
        for (Agent &my_agent : my_agents) {
            if (my_agent.cooldown > 0 || enemy_agents.empty()) {
                cout << my_agent.id << ";HUNKER_DOWN" << endl;
                continue;
            }

            // Trouver l’ennemi le plus mouillé
            Agent *target = nullptr;
            int max_wetness = -1;

            for (Agent &enemy : enemy_agents) {
                int dist = manhattan(my_agent.x, my_agent.y, enemy.x, enemy.y);
                if (dist <= my_agent.optimal_range * 2) {
                    if (enemy.wetness > max_wetness) {
                        max_wetness = enemy.wetness;
                        target = &enemy;
                    }
                }
            }

            if (target != nullptr) {
                cout << my_agent.id << ";SHOOT " << target->id << endl;
            } else {
                cout << my_agent.id << ";HUNKER_DOWN" << endl;
            }
        }
    }
}
