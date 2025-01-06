# Egg Blitz Game

Egg Blitz is a simple yet engaging game developed using **SFML** for the Programming Fundamentals semester project. Players control a pan to catch falling eggs, with the aim of maximizing their score while avoiding rotten eggs.

---

## Features

1. **Interactive Gameplay**: Move the pan left or right to catch eggs.
2. **Dynamic Difficulty Levels**:
   - Easy (0-15 seconds)
   - Moderate (15-30 seconds)
   - Hard (30+ seconds)
3. **Three Egg Types**:
   - **Good Eggs** (Green): Earn points.
   - **Rotten Eggs** (Red): End the game.
   - **Golden Eggs** (Yellow): Special rewards.
4. **Sound Effects**:
   - Background music.
   - Sound for catching eggs and game events.
5. **Visual Enhancements**:
   - Background transitions from menu to gameplay.
   - Smooth animations and responsive controls.

---

## How to Play

1. **Start the Game**: Click the "Start" button on the menu.
2. **Control the Pan**:
   - Press the **Left Arrow Key** to move left.
   - Press the **Right Arrow Key** to move right.
3. **Catch Eggs**:
   - Green Eggs: Gain points.
   - Yellow Eggs: Special rewards.
   - Avoid Red Eggs: They end the game.
4. **Score and Time**: Keep track of your progress in the top-left corner.
5. **Game Over**: The game ends if you miss too many eggs or catch a red egg.

---

## Installation

### Prerequisites
- SFML Library (2.5.1 or later)
- C++ Compiler supporting C++11 or later

### Steps
1. Clone the repository or download the source code.
2. Ensure SFML is installed and linked to your development environment.
3. Place the required assets (images, sounds, fonts) in the appropriate directories.
4. Compile and run the code:
   ```bash
   g++ -o EggBlitz main.cpp -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
   ./EggBlitz
   ```

---

## Assets

Ensure the following files are in the project directory:

1. **Images**:
   - `sfml_img.png` (Menu background)
   - `rose-petals.png` (Game background)
   - `pan.png` (Pan texture)
2. **Sounds**:
   - `pansound.mp3` (Catching good/golden eggs)
   - `splash.mp3` (Catching rotten eggs)
   - `bgg.mp3` (Background music)
3. **Fonts**:
   - `cccc.ttf` (Game text font)

---

## Future Enhancements

- Add leaderboards to track high scores.
- Include more egg types with unique behaviors.
- Implement power-ups and penalties.
- Introduce multiplayer mode.

---

## Acknowledgments

Special thanks to the Programming Fundamentals course instructors and the SFML community for their support and resources.

---

## License

This project is for educational purposes only. Asset files are used under fair use. Contact the developer for permissions.

