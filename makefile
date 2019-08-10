GLMFLAGS=`pkg-config --cflags --libs /usr/local/Cellar/glm/0.9.9.5/lib/pkgconfig/glm.pc`
SDL2FLAGS=`pkg-config --cflags --libs /usr/local/Cellar/sdl2/2.0.9_1/lib/pkgconfig/sdl2.pc`
OPENGL=-framework OpenGL
ALLFLAGS=$(GLMFLAGS) $(SDL2FLAGS) $(OPENGL)

main: Window.o main.cpp
	g++ main.cpp -o main Window.o $(ALLFLAGS)

Window.o: Window.cpp Window.hpp
	g++ -c Window.cpp $(ALLFLAGS)
