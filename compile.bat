g++ -Isrc/include -c main.cpp game.cpp booster.cpp map.cpp wall.cpp player.cpp ghost.cpp dot.cpp
g++ main.o game.o booster.o map.o wall.o player.o ghost.o dot.o -o sfml-app -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
sfml-app.exe