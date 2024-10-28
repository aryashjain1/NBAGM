import tkinter as tk
from tkinter import ttk
import pandas as pd

# Global variable for selected team
selected_team = None

# Set common geometry and font settings
WINDOW_GEOMETRY = "960x540"
FONT_LARGE = ("Arial", 16)
FONT_MEDIUM = ("Arial", 14)
FONT_SMALL = ("Arial", 12)

# Function to get the third header
def attribute_name():
    with open("top_15_players.csv", mode="r") as file:
        headers = file.readline().strip().split(",")
        return headers[2].strip() if len(headers) >= 3 else "N/A"

# Function to display the top 15 players
def display_top_15_players(third_header):
    try:
        top_15_data = pd.read_csv("top_15_players.csv")
    except FileNotFoundError:
        print("Error: 'top_15_players.csv' file not found.")
        return

    top_15_window = tk.Toplevel()
    top_15_window.title("Top 15 NBA Players by " + third_header)
    top_15_window.geometry(WINDOW_GEOMETRY)

    tree = ttk.Treeview(top_15_window, columns=list(top_15_data.columns), show="headings")
    for col in top_15_data.columns:
        tree.heading(col, text=col)
        tree.column(col, anchor='center', width=150)

    for _, row in top_15_data.iterrows():
        tree.insert("", "end", values=list(row))

    tree.pack(expand=True, fill='both')

# Function to display all players
def display_all_players():
    try:
        player_data = pd.read_csv("NBA Data.csv")
    except FileNotFoundError:
        print("Error: NBA Data.csv file not found.")
        return

    player_window = tk.Toplevel()
    player_window.title("All NBA Players and Attributes")
    player_window.geometry(WINDOW_GEOMETRY)

    tree = ttk.Treeview(player_window, columns=list(player_data.columns), show="headings")
    tree.pack(expand=True, fill='both')

    scrollbar = tk.Scrollbar(player_window, orient="vertical", command=tree.yview)
    scrollbar.pack(side='right', fill='y')
    tree.configure(yscroll=scrollbar.set)

    for col in player_data.columns:
        tree.heading(col, text=col)
        tree.column(col, anchor='center', width=100)

    for _, row in player_data.iterrows():
        tree.insert("", "end", values=list(row))

# Initial team selection window with welcome message
def initial_team_selection():
    team_window = tk.Toplevel()
    team_window.title("NBA GM Program - Team Selection")
    team_window.geometry(WINDOW_GEOMETRY)

    tk.Label(team_window, text="Welcome to the NBA GM program!\nChoose your team to become the GM of.", font=FONT_LARGE).pack(pady=20)
    tk.Label(team_window, text="Select your favorite NBA team:", font=FONT_MEDIUM).pack(pady=20)

    nba_teams = [
        "Atlanta Hawks", "Boston Celtics", "Brooklyn Nets", "Charlotte Hornets",
        "Chicago Bulls", "Cleveland Cavaliers", "Dallas Mavericks", "Denver Nuggets",
        "Detroit Pistons", "Golden State Warriors", "Houston Rockets", "Indiana Pacers",
        "Los Angeles Clippers", "Los Angeles Lakers", "Memphis Grizzlies", "Miami Heat",
        "Milwaukee Bucks", "Minnesota Timberwolves", "New Orleans Pelicans", "New York Knicks",
        "Oklahoma City Thunder", "Orlando Magic", "Philadelphia 76ers", "Phoenix Suns",
        "Portland Trail Blazers", "Sacramento Kings", "San Antonio Spurs", "Toronto Raptors",
        "Utah Jazz", "Washington Wizards"
    ]

    team_combobox = ttk.Combobox(team_window, values=nba_teams, font=FONT_SMALL)
    team_combobox.pack(pady=20)

    def submit_selection():
        global selected_team
        selected_team = team_combobox.get()
        if selected_team:
            with open("selected_team.txt", "w") as f:
                f.write(selected_team)
            team_window.destroy()
            third_header = attribute_name()
            show_main_menu(third_header)
        else:
            print("Please select a team before proceeding.")

    tk.Button(team_window, text="Submit", command=submit_selection, font=FONT_MEDIUM, width=20, height=2).pack(pady=20)

# Helper function for the "Show Top 15 Players" button action
def show_top_15_players_by_attribute():
    third_header = attribute_name()
    display_top_15_players(third_header)

# Display main menu after team selection
def show_main_menu(third_header):
    main_menu = tk.Tk()
    main_menu.title(f"{selected_team} - NBA GM Program")
    main_menu.geometry(WINDOW_GEOMETRY)

    tk.Button(main_menu, text="Show Top 15 NBA Players by " + third_header, font=FONT_MEDIUM,
              command=show_top_15_players_by_attribute, width=40, height=2).pack(pady=20)

    tk.Button(main_menu, text="Show All Players", font=FONT_MEDIUM, command=display_all_players, width=40, height=2).pack(pady=20)
    tk.Button(main_menu, text="Exit the Program", font=FONT_MEDIUM, command=main_menu.quit, width=40, height=2).pack(pady=20)

    main_menu.mainloop()

# Start with the initial team selection window
root = tk.Tk()
root.withdraw()  # Hide the initial Tkinter root window
initial_team_selection()  # Launch team selection as the entry point
root.mainloop()