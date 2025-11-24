# PACMAN
A modern **Pac-Man style game** built in **C++ using SFML**, featuring:

✅ Random-moving ghosts  
✅ Collectable dots  
✅ Speed boosters  
✅ Lives system with heart icons  
✅ Sound effects & background music  
✅ Win & Game Over screens  
✅ Respawn mechanic

This project demonstrates object-oriented game design and real-time rendering using SFML.

---

## 🎮 Gameplay Preview

> Pac-Man collects dots while avoiding ghosts.  
> Boosters temporarily increase speed, allowing fast movement and escape.

🟡 Collect dots to increase score  
👻 Avoid ghosts  
⚡ Pick up boosters for speed boost  
❤️ You have 3 lives  
🏁 Collect all dots to win

---

## 🧩 Core Features

### 👻 Ghost AI
- Moves randomly in four directions
- Changes direction every few seconds
- Detects walls and bounces
- Collides with player

### 🟡 Player
- WASD movement
- Rotates based on movement direction
- Can pick up boosters
- Respawn after death

### ⚡ Booster System
- Temporary speed boost
- Deactivates after use
- Visual feedback
- Plays sound on pickup

### 🔊 Audio
- Background music
- Dot pickup sound
- Booster sound
- Death sound

### ❤️ UI & HUD
- Score display
- Heart icons representing lives
- Win/Game Over message overlays

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| R | Restart Game |
| ESC | Exit Game |

---

## 🛠️ Technologies Used

- C++
- SFML (Graphics, Audio, System)
- Object-Oriented Programming
- Collision Detection
- Game Loop Architecture

---

## 🗂️ Project Structure

src/
│
├── main.cpp
├── game.cpp / game.hpp
├── player.cpp / player.hpp
├── ghost.cpp / ghost.hpp
├── wall.cpp / wall.hpp
├── dot.cpp / dot.hpp
├── booster.cpp / booster.hpp
├── map.cpp / map.hpp
│
assets/
├── images/
│ ├── pacman.png
│ ├── heart.png
├── sounds/
├── pickup.wav
├── booster.wav
├── death.wav
├── background.wav


---

## 🚀 How to Build & Run

### ✅ Requirements
- C++ Compiler (GCC / MSVC / Clang)
- SFML 2.5+ installed

### ✅ Build (Windows MinGW Example)

g++ main.cpp game.cpp player.cpp ghost.cpp wall.cpp dot.cpp booster.cpp map.cpp -o pacman -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

arduino
Copy code

Then run:

./pacman


---

## 🧠 Object-Oriented Design

The game is divided into reusable classes:

- `Game` → Main loop, input, UI
- `Player` → Movement, booster, lives
- `Ghost` → AI movement + collision
- `Map` → Walls, dots, boosters, ghost placement
- `Dot` → Collectables
- `Booster` → Speed power-up
- `Wall` → Collision boundaries

---

## 🏆 Win & Game Over Logic

✅ Win when all dots are collected  
❌ Lose when lives reach zero  

Both states display:

- Overlay message
- Instructions to restart/exit

---

## 🔮 Future Improvements

- Smarter ghost AI (pathfinding)
- Animated sprites
- Menu screen
- High score system
- Level progression

---

## 📜 License

This project is open-source and free to use for learning and development.
