Código referencia do tutorial https://learnopengl.com


```
sudo apt-get install cmake xorg-dev

mkdir build
	cd build
	cmake ..
	make
	./openglexample
	```
	
	If you're using mac, uncomment line 35 in game/src/main.cpp file:
	
	```
	34     // Mac OS only
	35     //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); <--- uncomment this
