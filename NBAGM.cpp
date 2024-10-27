#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // For system() and python
#include <fstream>
#include <sstream>

using namespace std;

// Define a structure to store the team name and abbreviation
struct NBATeam {
    string name;
    string abbreviation;
};

struct Player {
    string name;
    string position;
    int height;
    int weight;
    string college;
    int mid_Range_Shot;
    int three_Point_Shot;
    int speed;
    int pass_Accuracy;
    int defending;
    int rebounding;
};

// Read NBA data from a CSV file
vector<Player> read_NBA_Data(const string& filename) {
    ifstream file(filename);
    vector<Player> NBA_players;
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return NBA_players;
    }

    getline(file, line);  // Skip header line

    while (getline(file, line)) {
        istringstream s(line);
        Player player;
        string player_value;

        getline(s, player.name, ',');
        getline(s, player.position, ',');

        getline(s, player_value, ',');
        player.height = stoi(player_value);

        getline(s, player_value, ',');
        player.weight = stoi(player_value);

        getline(s, player.college, ',');

        getline(s, player_value, ',');
        player.mid_Range_Shot = stoi(player_value);

        getline(s, player_value, ',');
        player.three_Point_Shot = stoi(player_value);

        getline(s, player_value, ',');
        player.speed = stoi(player_value);

        getline(s, player_value, ',');
        player.pass_Accuracy = stoi(player_value);

        getline(s, player_value, ',');
        player.defending = stoi(player_value);

        getline(s, player_value, ',');
        player.rebounding = stoi(player_value);

        NBA_players.push_back(player);
    }
    return NBA_players;
}

// Sort players by three-point shot rating in descending order using insertion sort
void ThreePointRank(vector<Player>& players) {
    int n = players.size();

    for (int i = 1; i < n; ++i) {
        Player rank = players[i];
        int j = i - 1;

        // Sort in descending order based on three_Point_Shot rating
        while (j >= 0 && players[j].three_Point_Shot < rank.three_Point_Shot) {
            players[j + 1] = players[j];
            --j;
        }
        players[j + 1] = rank;
    }
}

// Display the top 15 players based on their three-point shot rating
void print_top_15(const vector<Player>& players) {
    int count = 0;
    for (const auto& player : players) {
        if (count >= 15)
            break; 
        
        cout << count + 1 << ". " << player.name << " - Three Point Shot: " 
        << player.three_Point_Shot << std::endl;
        count += 1;
    }
}

int main() {
    vector<Player> players = read_NBA_Data("NBA Data.csv");

    ThreePointRank(players);
    print_top_15(players);

    // Create a vector of NBA teams with their abbreviations
    vector<NBATeam> nbaTeams = {
        {"Atlanta Hawks", "ATL"},
        {"Boston Celtics", "BOS"},
        {"Brooklyn Nets", "BKN"},
        {"Charlotte Hornets", "CHA"},
        {"Chicago Bulls", "CHI"},
        {"Cleveland Cavaliers", "CLE"},
        {"Dallas Mavericks", "DAL"},
        {"Denver Nuggets", "DEN"},
        {"Detroit Pistons", "DET"},
        {"Golden State Warriors", "GS"},
        {"Houston Rockets", "HOU"},
        {"Indiana Pacers", "IND"},
        {"Los Angeles Clippers", "LAC"},
        {"Los Angeles Lakers", "LAL"},
        {"Memphis Grizzlies", "MEM"},
        {"Miami Heat", "MIA"},
        {"Milwaukee Bucks", "MIL"},
        {"Minnesota Timberwolves", "MIN"},
        {"New Orleans Pelicans", "NO"},
        {"New York Knicks", "NY"},
        {"Oklahoma City Thunder", "OKC"},
        {"Orlando Magic", "ORL"},
        {"Philadelphia 76ers", "PHI"},
        {"Phoenix Suns", "PHX"},
        {"Portland Trail Blazers", "POR"},
        {"Sacramento Kings", "SAC"},
        {"San Antonio Spurs", "SA"},
        {"Toronto Raptors", "TOR"},
        {"Utah Jazz", "UTA"},
        {"Washington Wizards", "WAS"}
    };

    // Call the Python script using the system() command
//    int selected_team = system("python nba_team_selection.py");

    return 0;
}