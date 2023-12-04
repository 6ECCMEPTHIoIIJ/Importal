#include "Application.h"

#include <iostream>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Input.h"


namespace Importal
{
  Application::Application()
  {
        
  }

  void OnResize(GLFWwindow* window, int width, int height);

  void Application::Run()
  {
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(300, 300, "Importal", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LESS);

    // Set the required callback functions
    glfwSetFramebufferSizeCallback(window, OnResize);
    glfwSetKeyCallback(window, KeyCallback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);


    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,   // Нижний правый угол
        -0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 0.0f,   // Нижний левый угол
        -0.5f,  0.5f, 0.5f,  0.0f, 1.0f, 0.0f,    // Верхний угол
        0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 1.0f    // Верхний угол
    };

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,  // First Triangle
        1, 3, 2
    };

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    Shader ourShader("Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   // Атрибут с координатами
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Атрибут с цветом
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
      glfwPollEvents();

      // Render
      // Clear the colorbuffer
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Draw our first triangle
      glm::mat4 trans = glm::mat4(1.0f);
      glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
      glfwGetWindowSize(window, &width, &height);
      //glfwGetVideoMode(glfwGetCu);
      trans = glm::scale(trans, glm::vec3((float)height / width, 1.0f, 1.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * 5.0f, glm::vec3(0.0f, 1.0f, 0.0f));
      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));

      ourShader.Use();
      ourShader.setMat4("projection", proj);
      ourShader.setMat4("transform", trans);
      ourShader.setMat4("view", view);
      //GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
      //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

      //GLfloat timeValue = glfwGetTime();
      //GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
      //glUniform1f(glGetUniformLocation(ourShader.GetProgram(), "someUniform"), 1.0f);
      ////GLint vertexColorLocation = glGetUniformLocation(ourShader.GetProgram(), "ourColor");
      ////glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

      // Swap the screen buffers
      glfwSwapBuffers(window);
    }
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
  }

  void Application::KeyCallback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods)
  {
    Input::SetKeyAction(key, action);
  }

  void OnResize(GLFWwindow* window, int width, int height)
  {
      // make sure the viewport matches the new window dimensions; note that width and 
      // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
  }
}
