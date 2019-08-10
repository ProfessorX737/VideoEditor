GLMFLAGS=`pkg-config --cflags --libs /usr/local/Cellar/glm/0.9.9.5/lib/pkgconfig/glm.pc`
SDL2FLAGS=`pkg-config --cflags --libs /usr/local/Cellar/sdl2/2.0.9_1/lib/pkgconfig/sdl2.pc`
OPENGL=-framework OpenGL

main: Test.o main.cpp
	g++ main.cpp -o main Test.o $(GLMFLAGS) $(SDL2FLAGS) $(OPENGL)

Test.o: Test.cpp Test.hpp
	g++ -c Test.cpp $(GLMFLAGS)
