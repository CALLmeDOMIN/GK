#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const GLchar *vertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "layout(location = 1) in vec3 color;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    " vertexColor = color;\n"
    "}\0";

const GLchar *fragmentShaderSource =
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    " fragmentColor = vec4(vertexColor, 1.0);\n"
    "}\0";

const GLchar *secondRecVertexShaderSource =
    "#version 330 core\n"
    "layout(location = 0) in vec3 position;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    " vertexColor = vec3(0.0f, 0.0f, 1.0f);\n"
    "}\0";

const GLchar *secondRecFragmentShaderSource =
    "#version 330 core\n"
    "out vec4 fragmentColor;\n"
    "void main()\n"
    "{\n"
    " fragmentColor = vec4(0.3f, 0.0f, 0.51f, 1.0f);\n"
    "}\0";

int main() {
  // inicjalizacja GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Tworzenie okna
  const unsigned int window_width = 1000;
  const unsigned int window_height = 800;
  GLFWwindow *window = glfwCreateWindow(window_width, window_height,
                                        "grafika komputerowa", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // inicjalizacja GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLint status;
  GLchar error_message[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    glGetShaderInfoLog(vertexShader, 512, NULL, error_message);
    std::cout << "Error (Vertex shader): " << error_message << std::endl;
  }

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, error_message);
    std::cout << "Error (Fragment shader): " << error_message << std::endl;
  }

  GLuint secondRecVertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(secondRecVertexShader, 1, &secondRecVertexShaderSource, NULL);
  glCompileShader(secondRecVertexShader);

  glGetShaderiv(secondRecVertexShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    glGetShaderInfoLog(secondRecVertexShader, 512, NULL, error_message);
    std::cout << "Error (Second rec vertex shader): " << error_message
              << std::endl;
  }

  GLuint secondRecFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(secondRecFragmentShader, 1, &secondRecFragmentShaderSource,
                 NULL);
  glCompileShader(secondRecFragmentShader);
  glGetShaderiv(secondRecFragmentShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    glGetShaderInfoLog(secondRecFragmentShader, 512, NULL, error_message);
    std::cout << "Error (Second rec fragment shader): " << error_message
              << std::endl;
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  GLuint secondRecShaderProgram = glCreateProgram();
  glAttachShader(secondRecShaderProgram, secondRecVertexShader);
  glAttachShader(secondRecShaderProgram, secondRecFragmentShader);
  glLinkProgram(secondRecShaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if (!status) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, error_message);
    std::cout << "Error (Shader program): " << error_message << std::endl;
  }

  glGetProgramiv(secondRecShaderProgram, GL_LINK_STATUS, &status);
  if (!status) {
    glGetProgramInfoLog(secondRecShaderProgram, 512, NULL, error_message);
    std::cout << "Error (Second rec shader program): " << error_message
              << std::endl;
  }

  glDetachShader(shaderProgram, vertexShader);
  glDetachShader(shaderProgram, fragmentShader);
  glDetachShader(secondRecShaderProgram, secondRecVertexShader);
  glDetachShader(secondRecShaderProgram, secondRecFragmentShader);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  glDeleteShader(secondRecVertexShader);
  glDeleteShader(secondRecFragmentShader);

  // vertex data
  GLfloat vertices[] = {
      -0.8f, 0.6f,  0.0f,
      0.2f,  0.44f,  0.66f, // triangle 1 vertex 1, triangle 2 vertex 1
      -0.8f, -0.6f, 0.0f,
      0.2f,  0.44f,  0.66f, // triangle 1 vertex 2
      0.8f,  -0.6f, 0.0f,
      0.2f,  0.44f,  0.66f, // triangle 1 vertex 3, triangle 2 vertex 2
      0.8f,  0.6f,  0.0f,
      0.2f,  0.44f,  0.66f // triangle 2 vertex 3
  };

  GLuint indices[] = {0, 1, 2, 0, 2, 3};

  GLfloat vertices2[] = {
    -0.9f, -0.1f, 0.0f, // top left
    -0.1f, -0.1f, 0.0f, // top right
    -0.1f, -0.7f, 0.0f, // bottom right
    -0.9f, -0.7f, 0.0f  // bottom left
  };

  GLuint indices2[] = {0, 1, 2, 0, 2, 3};

  GLuint VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (void *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  GLuint VAO2;
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);

  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

  GLuint EBO2;
  glGenBuffers(1, &EBO2);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(0);

  glViewport(0, 0, (GLuint)window_width, (GLuint)window_height);

  // pętla zdarzeń
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.18f, 0.2f, 0.22f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glUseProgram(secondRecShaderProgram);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteVertexArrays(1, &VAO2);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &VBO2);
  glDeleteBuffers(1, &EBO);
  glDeleteBuffers(1, &EBO2);
  glDeleteProgram(shaderProgram);
  glDeleteProgram(secondRecShaderProgram);
  

  glfwTerminate();
  return 0;
}