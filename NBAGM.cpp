#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

// Define the Player structure
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

// Define the DraftPick structure
struct DraftPick {
    int pickNumber;
    string teamName;
    string playerName;
    string college;
    string attributeUsed;
};

// Function to read NBA data from a CSV file
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

    // Read each line and parse player data
    while (getline(file, line)) {
        istringstream s(line);
        Player player;
        string value;

        getline(s, player.name, ',');
        getline(s, player.position, ',');

        getline(s, value, ',');
        player.height = stoi(value);

        getline(s, value, ',');
        player.weight = stoi(value);

        getline(s, player.college, ',');

        getline(s, value, ',');
        player.mid_Range_Shot = stoi(value);

        getline(s, value, ',');
        player.three_Point_Shot = stoi(value);

        getline(s, value, ',');
        player.speed = stoi(value);

        getline(s, value, ',');
        player.pass_Accuracy = stoi(value);

        getline(s, value, ',');
        player.defending = stoi(value);

        getline(s, value, ',');
        player.rebounding = stoi(value);

        NBA_players.push_back(player);
    }

    return NBA_players;
}

// Helper function to check for valid attributes
bool is_valid_attribute(const string& attribute) {
    const vector<string> valid_attributes = {
        "height", "weight", "mid_Range_Shot", "three_Point_Shot",
        "speed", "passing", "defending", "rebounding"
    };
    return find(valid_attributes.begin(), valid_attributes.end(), attribute) != valid_attributes.end();
}

// Helper function to get attribute value from a player
int get_attribute_value(const Player& player, const string& attribute) {
    if (attribute == "height") return player.height;
    if (attribute == "weight") return player.weight;
    if (attribute == "mid_Range_Shot") return player.mid_Range_Shot;
    if (attribute == "three_Point_Shot") return player.three_Point_Shot;
    if (attribute == "speed") return player.speed;
    if (attribute == "passing") return player.pass_Accuracy;
    if (attribute == "defending") return player.defending;
    if (attribute == "rebounding") return player.rebounding;
    return 0; // Default case (should not occur)
}

// Sort players by chosen attribute using insertion sort
void sortPlayersByAttribute(vector<Player>& players, const string& attribute) {
    int n = players.size();

    for (int i = 1; i < n; ++i) {
        Player keyPlayer = players[i];
        int keyAttribute = get_attribute_value(keyPlayer, attribute);
        int j = i - 1;

        // Move elements that are less than keyAttribute
        while (j >= 0 && get_attribute_value(players[j], attribute) < keyAttribute) {
            players[j + 1] = players[j];
            --j;
        }
        players[j + 1] = keyPlayer;
    }
}

// Print top 15 players based on selected attribute
void print_top_players(const vector<Player>& players, const string& attribute, int N) {
    cout << "\nTop " << N << " players based on " << attribute << ":\n";
    for (int i = 0; i < N && i < players.size(); ++i) {
        const Player& p = players[i];
        cout << i + 1 << ". " << p.name << " - " << get_attribute_value(p, attribute)
             << " (" << p.college << ")\n";
    }
}

// Create the draft order
vector<string> createDraftOrder(const vector<string>& teams) {
    unordered_map<string, int> drafts_per_team;
    vector<string> draft_order;

    while (draft_order.size() < 60) { // 60 picks total (2 rounds)
        int random_index = rand() % teams.size();
        const string& team = teams[random_index];
        if (drafts_per_team[team] < 2) {
            draft_order.push_back(team);
            drafts_per_team[team]++;
        }
    }

    return draft_order;
}

// Function to convert a string to uppercase
string to_uppercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Assign random attributes to teams
vector<pair<string, string>> assignAttributesToTeams(const vector<string>& draftOrder, const vector<string>& attributes) {
    vector<pair<string, string>> draftOrderWithAttributes;
    for (const auto& team : draftOrder) {
        int random_attr_index = rand() % attributes.size();
        string team_attribute = attributes[random_attr_index];
        draftOrderWithAttributes.push_back(make_pair(team, team_attribute));
    }
    return draftOrderWithAttributes;
}

// Function for user's pick
void userMakesPick(const string& team, vector<Player>& available_players, vector<DraftPick>& draftResults, int pickNumber) {
    cout << "\nIt's your turn to pick for " << team << "!\n";

    // Prompt the user to choose an attribute
    string user_attribute;
    cout << "Enter an attribute to sort players by "
         << "(e.g., height, weight, mid_Range_Shot, three_Point_Shot, speed, passing, defending, rebounding):\n";
    cin >> user_attribute;

    // Validate the attribute
    while (!is_valid_attribute(user_attribute)) {
        cout << "Invalid attribute. Please enter a valid attribute: ";
        cin >> user_attribute;
    }

    // Sort the available players based on user's chosen attribute
    vector<Player> sorted_players = available_players;
    sortPlayersByAttribute(sorted_players, user_attribute);

    const int N = 15;
    print_top_players(sorted_players, user_attribute, N);

    // Let the user select a player by number
    int player_choice;
    cout << "Enter the number of the player you want to draft: ";
    cin >> player_choice;

    while (player_choice < 1 || player_choice > N || player_choice > sorted_players.size()) {
        cout << "Invalid choice. Please enter a number between 1 and " << N << ": ";
        cin >> player_choice;
    }

    // Get the selected player
    Player drafted_player = sorted_players[player_choice - 1];

    // Remove the player from available_players
    auto it = find_if(available_players.begin(), available_players.end(),
                      [&](const Player& p) { return p.name == drafted_player.name; });
    if (it != available_players.end()) {
        available_players.erase(it);
    }

    // Output the pick
    cout << "\nYou selected " << drafted_player.name << " from " << drafted_player.college << "!\n";

    // Store the pick in draftResults
    draftResults.push_back({ pickNumber, team, drafted_player.name, drafted_player.college, user_attribute });
}

// Function for other teams' picks (Greedy Algorithm)
void teamMakesPick(const string& team, const string& team_attribute, vector<Player>& available_players, vector<DraftPick>& draftResults, int pickNumber) {
    // Sort the available players based on team's top attribute
    vector<Player> sorted_players = available_players;
    sortPlayersByAttribute(sorted_players, team_attribute);

    if (!sorted_players.empty()) {
        // The team picks the top player
        Player drafted_player = sorted_players.front();

        // Remove the player from available_players
        auto it = find_if(available_players.begin(), available_players.end(), [&](const Player& p) { return p.name == drafted_player.name; });
        if (it != available_players.end()) {
            available_players.erase(it);
        }

        // Output the pick
        cout << "Pick " << pickNumber << ": " << team << " selects " << drafted_player.name
             << " from " << drafted_player.college << " based on top attribute: " << team_attribute << endl;

        // Store the pick in draftResults
        draftResults.push_back({ pickNumber, team, drafted_player.name, drafted_player.college, team_attribute });
        usleep(750000); // Delay for dramatic effect
    } else {
        cout << "No more players available to draft.\n";
    }
}

// Function to save draft results to a CSV file
bool saveDraftResults(const string& filename, const vector<DraftPick>& draftResults) {
    ofstream draftFile(filename);
    if (!draftFile.is_open()) {
        cerr << "Error: Could not open file to write the final draft order.\n";
        return false;
    }

    draftFile << "Pick,Team,Name,College,Attribute Used\n";

    // Write each draft pick
    for (const auto& pick : draftResults) {
        draftFile << pick.pickNumber << ","
                  << pick.teamName << ","
                  << pick.playerName << ","
                  << pick.college << ","
                  << pick.attributeUsed << "\n";
    }

    draftFile.close();
    return true;
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Read player data from CSV file
    vector<Player> players = read_NBA_Data("NBA_Data.csv");
    if (players.empty()) {
        return 1; // Exit if no players are loaded
    }

    // List of NBA teams
    vector<string> nbaTeams = {
        "ATLANTA HAWKS", "BOSTON CELTICS", "BROOKLYN NETS", "CHARLOTTE HORNETS",
        "CHICAGO BULLS", "CLEVELAND CAVALIERS", "DALLAS MAVERICKS", "DENVER NUGGETS",
        "DETROIT PISTONS", "GOLDEN STATE WARRIORS", "HOUSTON ROCKETS", "INDIANA PACERS",
        "LOS ANGELES CLIPPERS", "LOS ANGELES LAKERS", "MEMPHIS GRIZZLIES", "MIAMI HEAT",
        "MILWAUKEE BUCKS", "MINNESOTA TIMBERWOLVES", "NEW ORLEANS PELICANS", "NEW YORK KNICKS",
        "OKLAHOMA CITY THUNDER", "ORLANDO MAGIC", "PHILADELPHIA 76ERS", "PHOENIX SUNS",
        "PORTLAND TRAIL BLAZERS", "SACRAMENTO KINGS", "SAN ANTONIO SPURS", "TORONTO RAPTORS",
        "UTAH JAZZ", "WASHINGTON WIZARDS"
    };

    cout << "Welcome to the NBA GM program!\n";

    // Display available teams
    cout << "Available NBA Teams:\n";
    for (const auto& team : nbaTeams) {
        cout << "- " << team << endl;
    }

    // User selects a team
    string team_selection;
    cout << "\nChoose your team to become the GM of:\n";
    while (true) {
        getline(cin, team_selection);
        team_selection = to_uppercase(team_selection);

        // Check if the team_selection is valid
        auto it_team = find(nbaTeams.begin(), nbaTeams.end(), team_selection);
        if (it_team != nbaTeams.end()) {
            break; // Valid team selected
        } else {
            cout << "Invalid team selection. Please enter a valid NBA team name:\n";
        }
    }

    // List of valid NBA attributes
    vector<string> attributes = {
        "height", "weight", "mid_Range_Shot", "three_Point_Shot",
        "speed", "passing", "defending", "rebounding"
    };

    // Generate the draft order
    vector<string> draftOrder = createDraftOrder(nbaTeams);

    // Assign random attributes to teams
    vector<pair<string, string>> draftOrderWithAttributes = assignAttributesToTeams(draftOrder, attributes);

    // Create a copy of available players
    vector<Player> available_players = players;

    // Vector to store draft results
    vector<DraftPick> draftResults;

    // Simulate the draft picks
    cout << "\nStarting the NBA Draft!\n";
    for (size_t i = 0; i < draftOrderWithAttributes.size(); ++i) {
        const string& team = draftOrderWithAttributes[i].first;
        const string& team_attribute = draftOrderWithAttributes[i].second;

        int pickNumber = static_cast<int>(i + 1);

        // Check if it's the user's team
        if (team == team_selection) {
            userMakesPick(team, available_players, draftResults, pickNumber);
        } else {
            teamMakesPick(team, team_attribute, available_players, draftResults, pickNumber);
        }
    }

    // Save the final draft order to a CSV file
    if (!saveDraftResults("final_draft_order.csv", draftResults)) {
        return 1;
    }

    cout << "\nDraft completed!\n";
   
    system("python3 nba_team_selection.py");

    return 0;
}