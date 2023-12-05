#include "Application.h"

#include <iostream>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Input.h"


namespace Importal
{

  std::unordered_map<const GLFWwindow*, Window*> Application::_windows;

  //void Application::Run()
  //{
  //  // Set all the required options for GLFW


  //  // Create a GLFWwindow object that we can use for GLFW's functions
  //  GLFWwindow* window = glfwCreateWindow(300, 300, "Importal", nullptr, nullptr);
  //  glfwMakeContextCurrent(window);
  //  glEnable(GL_DEPTH_TEST);


  //  // Set the required callback functions
  //  glfwSetFramebufferSizeCallback(window, OnResize);
  //  glfwSetKeyCallback(window, OnKeyInput);

  //  // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
  //  glewExperimental = GL_TRUE;
  //  // Initialize GLEW to setup the OpenGL Function pointers
  //  glewInit();

  //  // Define the viewport dimensions
  //  int width, height;
  //  glfwGetFramebufferSize(window, &width, &height);
  //  glViewport(0, 0, width, height);


  //  // Set up vertex data (and buffer(s)) and attribute pointers
  //  GLfloat vertices[] = {
  //      0.5f, -0.5f, 0.5f,   // Нижний правый угол
  //      -0.5f, -0.5f, 0.5f,   // Нижний левый угол
  //      -0.5f,  0.5f, 0.5f,    // Верхний угол
  //      0.5f,  0.5f, 0.5f,    // Верхний угол
  //      0.5f, -0.5f, -0.5f,   // Нижний правый угол
  //      -0.5f, -0.5f, -0.5f,   // Нижний левый угол
  //      -0.5f,  0.5f, -0.5f,    // Верхний угол
  //      0.5f,  0.5f, -0.5f,   // Верхний угол
  //  };

  //  GLfloat clours[] = {
  //  1.0f, 0.0f, 1.0f,   // Нижний правый угол
  //   1.0f, 1.0f, 1.0f,   // Нижний левый угол
  //   0.0f, 1.0f, 1.0f,    // Верхний угол
  //  0.0f, 0.0f, 1.0f,    // Верхний угол
  //   0.0f, 1.0f, 1.0f,    // Верхний угол
  //    0.0f, 1.0f, 0.0f,    // Верхний угол
  //   1.0f, 0.0f, 0.0f,   // Нижний правый угол
  //    1.0f, 1.0f, 0.0f,   // Нижний левый угол
  //  };

  //  GLuint indices[] = {  // Note that we start from 0!
  //    0, 1, 2,
  //    0, 2, 3,
  //    2, 1, 5,
  //    2, 5, 6,
  //    3, 2, 6,
  //    3, 6, 7,
  //    0, 3, 7,
  //    0, 7, 4,
  //    1, 0, 4,
  //    1, 4, 5,
  //    6, 5, 4,
  //    6, 4, 7,
  //  };

  //  Shader ourShader("Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");

  //  GLuint VBO, CBO, VAO, EBO;
  //  glGenVertexArrays(1, &VAO);
  //  glGenBuffers(1, &VBO);
  //  glGenBuffers(1, &CBO);
  //  glGenBuffers(1, &EBO);

  //  // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
  //  glBindVertexArray(VAO);

  //  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  // // Атрибут с координатами
  //  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  //  glEnableVertexAttribArray(0);
  //  glBindBuffer(GL_ARRAY_BUFFER, CBO);
  //  glBufferData(GL_ARRAY_BUFFER, sizeof(clours), clours, GL_STATIC_DRAW);
  //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //   //Атрибут с цветом
  //  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
  //  glEnableVertexAttribArray(1);

  //  glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

  //  glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
  //  // Game loop
  //  while (!glfwWindowShouldClose(window))
  //  {
  //      // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
  //    glfwPollEvents();

  //    // Render
  //    // Clear the colorbuffer
  //    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  //    // Draw our first triangle

  //    //GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
  //    //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

  //    //GLfloat timeValue = glfwGetTime();
  //    //GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
  //    //glUniform1f(glGetUniformLocation(ourShader.GetProgram(), "someUniform"), 1.0f);
  //    ////GLint vertexColorLocation = glGetUniformLocation(ourShader.GetProgram(), "ourColor");
  //    ////glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

  //    glBindVertexArray(VAO);
  //    glm::mat4 trans = glm::mat4(1.0f);
  //    glfwGetFramebufferSize(window, &width, &height);
  //    glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 100.0f);
  //    trans = glm::translate(trans, glm::vec3(glm::cos((float)glfwGetTime() * 2.0f), glm::sin((float)glfwGetTime() * 2.0f), 0.0f));
  //    trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
  //    trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
  //    trans = glm::rotate(trans, (float)glfwGetTime() * -1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
  //    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

  //    ourShader.SetMat4("projection", proj);
  //    ourShader.SetMat4("transform", trans);
  //    ourShader.SetMat4("view", view);
  //    ourShader.Use();

  //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  //    glBindVertexArray(0);

  //    // Swap the screen buffers
  //    glfwSwapBuffers(window);
  //  }
  //  // Properly de-allocate all resources once they've outlived their purpose
  //  glDeleteVertexArrays(1, &VAO);
  //  glDeleteBuffers(1, &VBO);
  //  glDeleteBuffers(1, &EBO);
  //  // Terminate GLFW, clearing any resources allocated by GLFW.
  //  glfwTerminate();
  //}
}
