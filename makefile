SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

bin/main : src/main.cpp
	g++ -o bin/main src/main.cpp $(SFML)

run : bin/main
	./bin/main