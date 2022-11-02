#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<glfw3.h>

// Callback fn that adjusts OpenGL viewport whenever GLFW window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Get input
void processInput(GLFWwindow* window);

int main()
{
  // Initialize GLFW
  if (!glfwInit())
  {
    exit(EXIT_FAILURE);
  }
  
  // GLFW window creation 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
  if(!window)
  {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  // Make context and set framebuffer callback fn for the GLFW window
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD\n");   
    return -1;
  }
    
  // Set OpenGL viewport
  glViewport(0, 0, 800, 600);
  

  // Render loop
  while (!glfwWindowShouldClose(window))
  {
    processInput(window); // Processes the last reported input states
    
    // Rendering
    glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents(); // Obtains the input states 
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}
