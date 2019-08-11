GLMFLAGS=`pkg-config --cflags --libs /usr/local/Cellar/glm/0.9.9.5/lib/pkgconfig/glm.pc`
VULKAN=-I/usr/local/Caskroom/vulkan-sdk/1.1.114.0/macOS/include -L/usr/local/Caskroom/vulkan-sdk/1.1.114.0/macOS/lib -lvulkan
GLFW=`pkg-config --cflags --libs /usr/local/Cellar/glfw/3.3/lib/pkgconfig/glfw3.pc` 
ALLFLAGS=$(GLMFLAGS) $(VULKAN) $(GLFW)

main: main.cpp
	g++ -std=c++11 main.cpp -o main $(ALLFLAGS)

