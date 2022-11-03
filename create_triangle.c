#include<stdio.h>
#include<stdlib.h>
#include<glad/glad.h>
#include<glfw3.h>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600

// Callback fn that adjusts OpenGL viewport whenever GLFW window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Get input
void processInput(GLFWwindow* window);

int checkCompileStatus(int shaderID);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n" 
    "void main()\n" 
    "{\n" 
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" 
    "}\0";
       
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

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
  
  // Create vertexShader object and compile
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Check vertexShader compile status
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("Error: Shader compilation failed\n%s", infoLog);
  }

  // Create fragmentShader object and compile
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Check fragmentShader compile status
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("Error: Shader compilation failed\n%s", infoLog);
  }

  // Link all the shaders into a Shader program object
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  
  // Check if linking the shaders was successful
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("Error: Shader program linking failed\n%s", infoLog);
  }

  // Delete previous shader programs
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Create vertices
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
  }; // Points are ordered clockwise direction
  
  // Store vertex data in GPU memory as VBO
  unsigned int VAO, VBO; // hold 1 buffer id
  glGenBuffers(1, &VBO); // generate 1 buffer id
  glGenVertexArrays(1, &VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindVertexArray(VAO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);

  // Render loop
  while (!glfwWindowShouldClose(window))
  {
    processInput(window); // Processes the last reported input states
    
    // Rendering
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // Sets the state
    glClear(GL_COLOR_BUFFER_BIT); // Uses the state

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

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

int checkCompileStatus(int shaderID)
{
  int success;
  char infoLog[512];
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
    printf("Shader compilation failed\n%s",infoLog);
  }
}
