import tkinter as tk
from tkinter import ttk
import pandas as pd

# Global variable for selected team
selected_team = None

# Function to display the top 15 players from 'top_15_players.csv'
def display_top_15_players():
    try:
        top_15_data = pd.read_csv("top_15_players.csv")
    except FileNotFoundError:
        print("Error: 'top_15_players.csv' file not found.")
        return

    top_15_window = tk.Toplevel()
    top_15_window.title("Top 15 NBA Players by Three-Point Shot Rating")

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

    frame = tk.Frame(player_window)
    frame.pack(expand=True, fill='both')

    tree = ttk.Treeview(frame, columns=list(player_data.columns), show="headings")
    tree.pack(side='left', expand=True, fill='both')

    scrollbar = tk.Scrollbar(frame, orient="vertical", command=tree.yview)
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

    # Welcome message
    welcome_label = tk.Label(team_window, text="Welcome to the NBA GM program!\nNow choose the team you will become the GM of.")
    welcome_label.pack(pady=10)

    # Team selection label and dropdown
    label = tk.Label(team_window, text="Select your favorite NBA team:")
    label.pack(pady=10)

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
    team_combobox = ttk.Combobox(team_window, values=nba_teams)
    team_combobox.pack(pady=10)
    
    global selected_team
    selected_team = team_combobox.get()

    def submit_selection():
        global selected_team
        selected_team = team_combobox.get()
        if selected_team:
            with open("selected_team.txt", "w") as f:
                f.write(selected_team)  # Write the selected team to a file
            team_window.destroy()
            show_main_menu()  # Display main menu once a team is selected
        else:
            print("Please select a team before proceeding.")

    submit_button = tk.Button(team_window, text="Submit", command=submit_selection)
    submit_button.pack(pady=10)


def show_main_menu():
    main_menu = tk.Tk()
    main_menu.title(f"{selected_team} - NBA GM Program")

    # Adding buttons for viewing options
    btn_top_15 = tk.Button(main_menu, text="Show Top 15 Players by Three-Point Shot", command=display_top_15_players)
    btn_top_15.pack(pady=10)

    btn_all_players = tk.Button(main_menu, text="Show All Players", command=display_all_players)
    btn_all_players.pack(pady=10)

    # Exit button to end the program and return to C++
    btn_exit = tk.Button(main_menu, text="Exit the Program", command=main_menu.quit)
    btn_exit.pack(pady=10)

    main_menu.mainloop()

# Start with the initial team selection window
root = tk.Tk()
root.withdraw()  # Hide the initial Tkinter root window
initial_team_selection()  # Launch team selection as the entry point
root.mainloop()