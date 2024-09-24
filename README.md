
# StarField Skirmish

"**StarField Skirmish**" is a dynamic, space-themed shooter game that challenges players to navigate through levels of increasing difficulty, managing alien encounters and enhancing their spaceship capabilities. Developed with engaging mechanics and a user-friendly interface, the game offers an immersive experience in space combat.

## Table of Contents
- [Key Features](#key-features)
- [Running the Game](#running-the-game)
- [Game Controls](#game-controls)
- [Bugs](#bugs)
- [Contributing](#contributing)
- [License](#license)

## Key Features

### Alien Ship Management
- **Dynamic Alien Ship Creation**: The game dynamically generates alien ships, with the number and difficulty of ships scaling with the player's current level.
- **Level-Adjusted Ships**: Alien ships' fire rate and speed increase with the game level, introducing progressively challenging encounters.

### Game Level Dynamics
- **Ship Scrolling**: Alien ships move vertically down the screen at a pace determined by the `shipScrollerSpeed`, which increases as the player advances through levels.
- **Level-Based Ship Addition**: New lines of alien ships are added at intervals corresponding to the current level, making the game progressively more complex.

### New Screens and User Interface
- **Main Menu**: The `MainMenuView` class provides a main menu screen, offering options to start the game, view instructions, or exit.
- **Information Screen**: The `InfoView` class displays game instructions and controls, aiding player interaction and understanding.

### Game Controls and Interaction
- **Key Handling in Game Loop**: The `runGameLoop()` function listens for key inputs, allowing players to control their spaceship (movement and shooting) and manage game states (exit or restart).

### Game Information Display
- **Real-Time Info Updates**: The `printGameInfo()` function continuously displays important game-related information, such as the number of active alien ships, player health, and score, ensuring players are well-informed throughout gameplay.

## Running the Game

To start playing "**StarField Skirmish**," follow these steps:

### 1. **Compile the Game**
Run `make` in the project root directory to compile the game.

### 2. **Launch the Game**
- Navigate to the `bin` directory and execute `./starfield_skirmish`.
- Alternatively, you can run `./run.sh` from the root directory for convenience.

### 3. **Game Controls**
- Use the **arrow keys** (left and right) to move your spaceship.
- Press the **spacebar** to shoot.
- To exit the game at any time, press **ESC**.

## Bugs

- **Static Ships**: Sometimes alien ships may stop scrolling. This issue can often be fixed by fully exiting the game and restarting.
- **Frozen Bullet**: Occasionally, a bullet from the player's ship might freeze in place. This is a rare occurrence and typically resolves after the next shot.

