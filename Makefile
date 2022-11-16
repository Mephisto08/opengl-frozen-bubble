minimalGLESv2: minimalGLESv2.cpp
	g++ -o $@ $< -lEGL -lGLESv2 -lX11 -lpng
	