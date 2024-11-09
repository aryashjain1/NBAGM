import tkinter as tk
from tkinter import ttk
import pandas as pd

# Set common geometry and font settings
WINDOW_GEOMETRY = "960x540"
FONT_LARGE = ("Arial", 16)
FONT_MEDIUM = ("Arial", 14)
FONT_SMALL = ("Arial", 12)

# Function to display the draft results
def display_draft_results():
    """
    Opens a new window displaying draft results from 'final_draft_order.csv'.
    If the file is not found, it displays an error message.
    """
    try:
        draft_data = pd.read_csv("final_draft_order.csv")
    except FileNotFoundError:
        print("Error: 'final_draft_order.csv' file not found.")
        return

    draft_window = tk.Toplevel()
    draft_window.title("Draft Results")
    draft_window.geometry(WINDOW_GEOMETRY)

    # Treeview to display draft data
    tree = ttk.Treeview(draft_window, columns=list(draft_data.columns), show="headings")
    tree.pack(expand=True, fill='both')

    # Add vertical scrollbar
    scrollbar = tk.Scrollbar(draft_window, orient="vertical", command=tree.yview)
    scrollbar.pack(side='right', fill='y')
    tree.configure(yscroll=scrollbar.set)

    # Configure Treeview columns
    for col in draft_data.columns:
        tree.heading(col, text=col)
        tree.column(col, anchor='center', width=120)

    # Populate Treeview with draft data
    for _, row in draft_data.iterrows():
        tree.insert("", "end", values=list(row))

# Function to display all players
def display_all_players():
    """
    Opens a new window displaying all players' data from 'NBA_Data.csv'.
    If the file is not found, it displays an error message.
    """
    try:
        player_data = pd.read_csv("NBA_Data.csv")
    except FileNotFoundError:
        print("Error: 'NBA_Data.csv' file not found.")
        return

    player_window = tk.Toplevel()
    player_window.title("All NBA Players and Attributes")
    player_window.geometry(WINDOW_GEOMETRY)

    # Treeview to display player data
    tree = ttk.Treeview(player_window, columns=list(player_data.columns), show="headings")
    tree.pack(expand=True, fill='both')

    # Add vertical scrollbar
    scrollbar = tk.Scrollbar(player_window, orient="vertical", command=tree.yview)
    scrollbar.pack(side='right', fill='y')
    tree.configure(yscroll=scrollbar.set)

    # Configure Treeview columns
    for col in player_data.columns:
        tree.heading(col, text=col)
        tree.column(col, anchor='center', width=100)

    # Populate Treeview with player data
    for _, row in player_data.iterrows():
        tree.insert("", "end", values=list(row))

# Display main menu
def show_main_menu():
    """
    Launches the main menu window with options to view draft results,
    view all players, or exit the program.
    """
    main_menu = tk.Tk()
    main_menu.title("NBA GM Program")
    main_menu.geometry(WINDOW_GEOMETRY)

    # Create buttons for the main menu
    tk.Button(main_menu, text="Show Draft Results", font=FONT_MEDIUM,
              command=display_draft_results, width=40, height=2).pack(pady=20)
    tk.Button(main_menu, text="Show All Players", font=FONT_MEDIUM, command=display_all_players,
              width=40, height=2).pack(pady=20)
    tk.Button(main_menu, text="Exit the Program", font=FONT_MEDIUM, command=main_menu.quit,
              width=40, height=2).pack(pady=20)

    main_menu.mainloop()

# Start the main menu directly
if __name__ == "__main__":
    show_main_menu()