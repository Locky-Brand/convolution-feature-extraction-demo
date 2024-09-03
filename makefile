gl330:
	g++ -Wall -g -DGL330 ./main.cpp ./engine/core/gl_api/GLAD/glad330.c ./engine/core/gl_api/api_tools.c ./engine/core/gl_api/textures.c ./engine/core/gl_api/stb_implementation.c ./engine/core/utils/gbl_utils.c ./engine/core/gfx3D_330/*.c ./engine/core/objects/*.c ./engine/entities/*.c ./engine/core/math/*.c -I"./engine/core/dependancies/include/" -L"./engine/core/dependancies/libs/" -lglfw -lm -lassimp -lzlibstatic

gl210:
	gcc -DGL210 ./main.c ./gl_api/GLAD/glad210.c ./gl_api/api_tools.c ./gfx3D_210/gfx3D_210.c ./objects/*.c ./math/*.c -I"./engine/core/dependancies/include/" -L"./engine/core/dependancies/libs/" -lglfw -lm

soft:
	gcc -DSOFT ./main.c

embedded:

