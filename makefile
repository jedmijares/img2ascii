OBJECTS = main.o
EXEC = img2ascii

#build executable program
$(EXEC): $(OBJECTS)
	g++ $^ -o $@ `Magick++-config --cppflags --cxxflags --ldflags --libs`

#build objective files from source files
%.o: source/%.cpp # $(HEADERS)
	g++ -c $< -o $@ `Magick++-config --cppflags --cxxflags --ldflags --libs`

#clean up the mess
clean:
	rm `find ./ -type f -executable`
	rm *.o

