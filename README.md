you must have g++ and sfml library

g++ -std=c++20 -c main.cpp Resourse/Node.cpp Resourse/Graph.cpp Resourse/FindPathStrategy.cpp Resourse/Strategys.cpp Resourse/GraphWindow.cpp

then 

g++ -o GraphApp main.o Node.o Graph.o FindPathStrategy.o Strategys.o GraphWindow.o -lsfml-graphics -lsfml-window -lsfml-system

then 

./GraphApp
