compile_main:
	g++ -o main.out app/main.cpp -lGLEW -lglfw -lGL -lX11 -lXrandr -lXi -lXinerama -lXxf86vm -lXcursor -ldl -lpthread
