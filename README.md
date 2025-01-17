
# StarField Skirmish

A dynamic space combat simulator featuring progressive difficulty scaling, real-time combat mechanics, and dynamic enemy generation. Built in C++, the game combines object-oriented design with robust game architecture to create an engaging space warfare experience.

## Overview

StarField Skirmish challenges players to navigate through an increasingly difficult cosmic battlefield. As players progress, they face evolving challenges through:
- Dynamic difficulty adjustments based on player performance
- Progressively complex enemy patterns and behaviors
- Real-time combat with responsive controls
- Resource and health management systems

## Features

### Combat System
- Real-time projectile mechanics with precise collision detection
- Multiple enemy types with distinct attack patterns
- Dynamic weapon system with upgrades and special abilities
- Progressive difficulty scaling tied to player performance

### Enemy AI
- Advanced enemy ship generation with level-based scaling
- Dynamic movement patterns that evolve with game progression
- Intelligent targeting and attack coordination
- Adaptive difficulty adjustment based on player performance

### Game Progression
- Experience-based leveling system
- Unlockable abilities and ship upgrades
- Score multiplier system for skilled play
- Performance tracking and statistics

### Technical Implementation
- Custom game engine built in C++
- Efficient collision detection algorithms
- Thread-safe resource management
- Optimized rendering and update cycles

## Getting Started

### Prerequisites
- C++ Compiler (GCC 7.0+)
- Make build system

### Installation

1. Clone the repository
```bash
git clone https://github.com/GabrielPerezCSDev/starfield-skirmish.git
cd starfield-skirmish
```

2. Build the project
```bash
make clean
make
```

3. Run the game
```bash
./bin/starfield-skirmish
```

## Game Controls

### Basic Controls
- **←/→**: Move ship left/right
- **Spacebar**: Fire weapon
- **ESC**: Pause game/Access menu

### Advanced Mechanics
- **Double tap ←/→**: Quick dodge
- **Hold Spacebar**: Charge shot
- **P**: Quick pause

## Development

### Architecture
The game is built using a component-based architecture:
- Core game loop with fixed update timing
- Event-driven input handling
- Entity component system for game objects
- Resource management system

### Performance Optimization
- Efficient collision detection using spatial partitioning
- Object pooling for projectiles and particles
- Optimized rendering pipeline
- Memory management systems

## Known Issues & Future Improvements

### Current Limitations
- Occasional static behavior in alien ship movement
- Rare projectile rendering artifacts
- Performance degradation at high enemy counts

### Planned Enhancements
- Additional enemy types with unique behaviors
- Power-up system with temporary abilities
- Local multiplayer support
- Enhanced visual effects and particle systems

