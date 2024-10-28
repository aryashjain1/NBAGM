#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Player {
    string name;
    string position;
    int height;
    int weight;
    int potential;
    string college;
    int mid_Range_Shot;
    int three_Point_Shot;
    int speed;
    int pass_Accuracy;
    int defending;
    int rebounding;
};

// Define a structure to store the team name and abbreviation
struct NBATeam {
    string name;
    string abbreviation;
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

    // Skip the header line
    getline(file, line);

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

// Helper function to check for valid attribute
bool is_valid_attribute(const string& attribute) {
    const vector<string> valid_attributes = {
        "height", "weight", "mid_Range_Shot", "three_Point_Shot", 
        "speed", "passing", "defending", "rebounding"
    };
    return find(valid_attributes.begin(), valid_attributes.end(), attribute) != valid_attributes.end();
}

// Sort players by chosen attribute using insertion sort
string sortPlayersByAttribute(vector<Player>& players) {
    int n = players.size();
    string attribute_selection;

    cout << "By which attribute would you like to rank these players?\n";
    cout << "Options: height, weight, mid_Range_Shot, three_Point_Shot, speed, passing, defending, rebounding\n";
    cin >> attribute_selection;

    while (!is_valid_attribute(attribute_selection)) {
        cout << "Invalid attribute. Please enter a valid attribute: ";
        cin >> attribute_selection;
    }

    for (int i = 1; i < n; ++i) {
        Player rank = players[i];
        int j = i - 1;

        if (attribute_selection == "height") {
            while (j >= 0 && players[j].height < rank.height) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "weight") {
            while (j >= 0 && players[j].weight < rank.weight) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "mid_Range_Shot") {
            while (j >= 0 && players[j].mid_Range_Shot < rank.mid_Range_Shot) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "three_Point_Shot") {
            while (j >= 0 && players[j].three_Point_Shot < rank.three_Point_Shot) {
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "speed") {
            while (j >= 0 && players[j].speed < rank.speed) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "passing") {
            while (j >= 0 && players[j].pass_Accuracy < rank.pass_Accuracy) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "defending") {
            while (j >= 0 && players[j].defending < rank.defending) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        } else if (attribute_selection == "rebounding") {
            while (j >= 0 && players[j].rebounding < rank.rebounding) { 
                players[j + 1] = players[j]; 
                --j; 
            }
        }
        players[j + 1] = rank;
    }
    return attribute_selection;
}

// Print top 15 players based on selected attribute
void print_top_15(const vector<Player>& players, const string& attribute_selection) {
    ofstream outFile("top_15_players.csv");
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file to write top 15 players." << endl;
        return;
    }

    outFile << "Rank,Name," << attribute_selection << "\n";
    int count = 0;

    for (const auto& player : players) {
        if (count >= 15) break;

        outFile << count + 1 << "," << player.name << ",";
        
        if (attribute_selection == "height") outFile << player.height;
        else if (attribute_selection == "weight") outFile << player.weight;
        else if (attribute_selection == "mid_Range_Shot") outFile << player.mid_Range_Shot;
        else if (attribute_selection == "three_Point_Shot") outFile << player.three_Point_Shot;
        else if (attribute_selection == "speed") outFile << player.speed;
        else if (attribute_selection == "passing") outFile << player.pass_Accuracy;
        else if (attribute_selection == "defending") outFile << player.defending;
        else if (attribute_selection == "rebounding") outFile << player.rebounding;

        outFile << "\n";
        ++count;
    }
    outFile.close();
}

string get_selected_team() {
    ifstream file("selected_team.txt");
    string team;
    if (file.is_open()) {
        getline(file, team);
    } else {
        cerr << "Error: Could not open selected_team.txt" << endl;
    }
    return team;
}

int main() {
    vector<Player> players = read_NBA_Data("NBA Data.csv");

    // Sort players by selected attribute and print top 15
    string attribute = sortPlayersByAttribute(players);
    print_top_15(players, attribute);

    system("python3 nba_team_selection.py");

    string team = get_selected_team();
    if (!team.empty()) {
        cout << "You selected: " << team << endl;
    } else {
        cout << "No team selected." << endl;
    }

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

    return 0;
}