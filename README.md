
# Pacman LandTiger

## Description
This is a Pacman project developed for the LandTiger board. The objective of the game is to collect all the dots while avoiding ghosts. It was designed as an embedded programming exercise to learn the basics of microcontroller development, test C programming skills, and, most importantly, practice optimizing code to use limited resources efficiently. This project focuses on maximizing performance within a constrained environment, a valuable skill for any engineer.
## Project Structure

The project is organized into different branches and folders to separate the core functionality and hardware interactions


Inside the `Source` folder, you will find various subfolders that manage different hardware components and the game mechanics:

- **`joystick/`**: Contains the code to handle the joystick inputs for moving Pacman on the screen.
- **`timer/`**: Manages the game timing and controls the movement of both Pacman and the ghosts. This includes controlling the speed and intervals of game actions.
- **`RIT/`**: Contains code related to Real-Time Interrupts (RIT) for handling time-sensitive events, such as managing the joystick input and handling button presses to avoid debounce issues.
- **`buttons/`**: Contains the logic for handling the pause button and any other button inputs.
- **`TouchPanel/`** and **`GLCD/`**: Manages the LCD display
- **`CAN/`**: Contains code to manage CAN communication, which is used for transmitting game data (such as score, countdown, and lives). The CAN bus is connected in loopback mode on the LandTiger board, meaning the messages are sent and received within the system itself for testing and communication purposes.
- **`music/`**: Contains the code and data to handle musical notes and sound effects in the game.
- **`sample.c/`**: Contains the initialization code for all the different parts of the project. This includes setting up hardware components like the joystick, timer, buttons, and CAN communication, as well as preparing the display and other peripherals for the game. This file also serves as the main entry point for the program, where the main game loop is executed, and all components are initialized before the game begins.
  
Outside the `Source` folder, you will find the following files:

- **`schema.c/`** and **`schema.h/`**: Contains the labyrinth layout and functions for drawing it on the screen.
- **`pacman.c/`** and **`pacman.h/`**: Includes the functions for drawing and clearing Pacman, as well as the logic for managing its movement.
- **`blinky.c/`** and **`blinky.h/`**: Handles the drawing and movement of Blinky, the ghost. Its movement is automatically managed by calculating the Manhattan distance to Pacman and determining the best direction to move towards Pacman.

## Installation

1. Clone the repository
2. You will need a development environment for embedded systems, such as Keil, to build and flash the project onto the LandTiger board.
3. Ensure that you have the LPC1768 LandTiger library installed for compilation.
4. Build and flash the project to the LandTiger board.

For detailed setup instructions on how to configure the environment and compile the project, please refer to the documentation of the LandTiger board and Keil setup guides.

## How to use

1. Build the project using Keil or the chosen development environment.
2. Flash the code onto the LandTiger board using the flashing tool.
3. Start the game on the board and begin playing!
 
You can customize the game by adjusting settings such as the time intervals, the speed of Pacman, and other gameplay parameters to suit your preferences.
