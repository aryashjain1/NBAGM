#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  // For system()

using namespace std;

// Define a structure to store the team name and abbreviation
struct NBATeam {
    string name;
    string abbreviation;
};

int main() {
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
    int selected_team = system("python nba_team_selection.py");

    return 0;
}