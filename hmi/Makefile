#hmi: ./src/main.cpp
#	g++ -o $@ ./framework/OBJLoader.cpp ./src/SceneElements/Mesh.cpp ./src/SceneElements/Renderable.cpp ./src/SceneElements/Transform.cpp $< -lEGL -lGLESv2 -lX11 -lGLEW -lpng

#minimalGLESv2: ./src/main.cpp
#	g++ -o $@ ./src/SceneElements/Renderable.cpp ./src/SceneElements/Mesh.cpp ./src/SceneElements/Transform.cpp $< -lEGL -lGLESv2 -lX11 -lGLEW -lpng

test: 
	g++ -o test ./src/main.cpp ./framework/OBJLoader.cpp ./src/SceneElements/Camera.cpp ./src/SceneElements/Renderable.cpp ./src/SceneElements/Mesh.cpp ./src/SceneElements/Transform.cpp $< -lEGL -lGLESv2 -lX11 -lpng