SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 

bin/main : src/main.cpp $(wildcard include/*.hpp)
	g++ -o bin/main src/main.cpp $(SFML) -Iinclude

run : bin/main include/*.hpp
	./bin/main