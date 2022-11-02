OpenGL tutorial:

I am following "learnopengl.com"

Compiling GLFW:
Compiling GLFW and OpenGL applications is a bit tricky. You will have to link the required libraries.
I am using msys64's mingw64 for compiling on windows. The following command worked for me

gcc create_window.c libglfw3.a -lgdi32 glad.c
