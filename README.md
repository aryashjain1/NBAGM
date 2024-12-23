NBA GM Project

Welcome to the NBA GM project! This program allows users to step into the shoes of an NBA General Manager (GM) and make draft picks for a chosen team during the NBA draft. Users can select players based on various attributes, simulate the drafting process, and view detailed results for each pick.

Project Overview

The NBA GM project is designed to simulate the NBA draft experience. It provides a list of players with attributes and allows users to select players based on different criteria like height, speed, or shooting accuracy. Users can also view the draft results and all players' data in an organized graphical interface. This project includes both a C++ program for simulating the draft and a Python program with a graphical interface for displaying draft results and players.

Features
1.	Simulate NBA Draft: Users can select a team, choose players based on their preferred attributes, and make picks for that team.
2.	Attribute-Based Sorting: Choose attributes like height, speed, or shooting accuracy to filter top players.
3.	Interactive GUI: A Python GUI allows users to view draft results and all player data in an organized format.
4.	Comprehensive Draft Results: Save the draft results to a CSV file for easy access and analysis.

Setup Instructions

Requirements
1.	C++ Compiler: The draft simulation program is written in C++. You will need a compiler like GCC.
2.	Python 3: The GUI is built in Python using the tkinter and pandas libraries.
3.	Python Libraries: Ensure pandas and tkinter are installed.

File Requirements
1.	NBA_Data.csv: This file should contain the NBA player data, including attributes like height, speed, college, etc. Ensure it is in the same directory or folder as the C++ and Python files.
2.	final_draft_order.csv: The C++ program will generate this file after the draft. It contains the results of the draft and is used by the Python GUI to display the draft picks.

Usage Instructions
Running the Draft Simulation (C++)
1.	Choose Your Team: The program will display a list of NBA teams. Enter the name of the team you wish to manage.
2.	Make Draft Picks: As the draft progresses, you will be prompted to pick players based on an attribute of your choice (e.g., height, weight, speed).
3.	Draft Results: The program saves the draft results in final_draft_order.csv upon completion.
Viewing Draft Results and Player Data (Python GUI)
1.	Show Draft Results: After running the draft, open the Python GUI and click "Show Draft Results" to view the draft picks.
2.	View All Players: To view a full list of available NBA players and their attributes, click "Show All Players."
3.	Exit the Program: Click "Exit the Program" in the main menu to close the application.

File Descriptions
1.	NBAGM.cpp: The main C++ program for simulating the NBA draft. Users interact with this file to manage their chosen team and make draft selections.
2.	nba_team_selection.py: The Python program providing a graphical user interface to display draft results and player data.
3.	NBA_Data.csv: Input data file containing NBA players' information and attributes (required for the C++ simulation).
4.	final_draft_order.csv: Output file generated by the C++ program that records the draft results and is used by the Python GUI for display.
