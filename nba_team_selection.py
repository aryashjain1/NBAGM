import tkinter as tk
from tkinter import ttk

selected_team = None

def submit_selection():
    global selected_team
    selected_team = team_combobox.get()
    print(f"Selected team: {selected_team}")  # Print the selected team
    root.quit()

# Create the main window
root = tk.Tk()
root.title("Select NBA Team")

# Create a label
label = tk.Label(root, text="Select your favorite NBA team:")
label.pack(pady=10)

# Create a dropdown menu with NBA teams
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

team_combobox = ttk.Combobox(root, values=nba_teams)
team_combobox.set("Select a team")
team_combobox.pack(pady=10)

# Create a button to submit the selection
submit_button = tk.Button(root, text="Submit", command=submit_selection)
submit_button.pack(pady=20)

# Start the Tkinter event loop
root.mainloop()

# After the GUI closes, the selected team is printed to the console
if selected_team:
    print(f"Selected team: {selected_team}")
else:
    print("No team selected.")
