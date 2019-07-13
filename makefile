OBJECTS = main.o
EXEC = test

#build executable program
$(EXEC): $(OBJECTS)
	g++ $^ -o $@ `Magick++-config --cppflags --cxxflags --ldflags --libs`

#build objective files from source files
%.o: source/%.cpp # $(HEADERS)
	g++ -c $< -o $@ `Magick++-config --cppflags --cxxflags --ldflags --libs`

#clean up the mess
clean:
	rm -i `find ./ -type f -executable`
	rm -i *.o

