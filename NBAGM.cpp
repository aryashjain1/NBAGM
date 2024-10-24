#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

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

    string NBA_team;
    cout << "Welcome to NBA GM!" 
         << "\nTo begin, write the abbreviation of your favorite NBA franchise to become their General Manager." << endl;
    sleep(2);
    // Print all the teams and their abbreviations
    for (const NBATeam& team : nbaTeams) {
        cout << team.name << " (" << team.abbreviation << ")" << endl;
    }
    cout << endl;
    cin >> NBA_team;

    return 0;
}