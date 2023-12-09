#include "Application.h"

#include <iostream>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Input/InputManager.h"

#include "GlExt.h"

namespace Importal
{
  Timer Application::_time;
  Window Application::_window;
  double Application::_lastX = 1920 / 2;
  double Application::_lastY = 1080 / 2;
  float Application::_offsetX;
  float Application::_offsetY;
  float Application::_yaw = 0.0f;
  float Application::_pitch = 0.0f;


  Application::Application()
  {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  }

  void Application::Run()
  {
    glfwMakeContextCurrent(nullptr);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    GLFWwindow* hWnd = _window.Create(mode->width, mode->height, "Importal");
    if (hWnd == nullptr)
    {
      std::cerr << "ERROR::WINDOW::NOT_SUCCESSFULLY_CREATED" << std::endl;
      return;
    }

    glfwMakeContextCurrent(hWnd);
    glfwSetFramebufferSizeCallback(hWnd, HandleWindowResize);
    glfwSetKeyCallback(hWnd, HandleKeyInput);
    glfwSetCursorPosCallback(hWnd, HandleMouseInput);
    glfwSetInputMode(hWnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    InputManager::BindAction(GLFW_KEY_ESCAPE, [](const Key& key)
    {
      if (key.IsDown())
        glfwSetWindowShouldClose(_window.GetHWnd(), GL_TRUE);
    });

    InputManager::BindAction(GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, [this](float xAxis, float yAxis)
    {
      _direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
      _direction.y = sin(glm::radians(_pitch));
      _direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
      _camFront = glm::normalize(_direction);
      auto rawInput = -yAxis * _camFront + xAxis * glm::normalize(glm::cross(_camFront, _camUp));
      if (rawInput != glm::vec3(0.0f, 0.0f, 0.0f))
        rawInput = glm::normalize(rawInput);

      _camPos += rawInput * _time.GetDeltaTime();
    });

    glewExperimental = GL_TRUE;
    glewInit();

    auto shader = Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
    shader.Use();


    GLfloat vertices[] = {
      0.5f,  -0.5f,  0.5f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f,
      -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
      0.5f,   0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
      0.5f,   0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    };

    GLuint indices[] = {
      0, 1, 2,
      0, 2, 3,
      2, 1, 5,
      2, 5, 6,
      3, 2, 6,
      3, 6, 7,
      0, 3, 7,
      0, 7, 4,
      1, 0, 4,
      1, 4, 5,
      6, 5, 4,
      6, 4, 7,
    };

    ArrayBuffer ab;
    ab.Bind();
    
    VertexBuffer vb(vertices, 3 * 2 * 8 * sizeof(GLfloat), GL_STATIC_DRAW);
    VertexBufferLayout vb_layout;
    vb_layout.Push(GL_FLOAT, 3);
    vb_layout.Push(GL_FLOAT, 3);
    ab.AddBuffer(vb, vb_layout);

   // GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0));
   // GL_CALL(glEnableVertexAttribArray(0));

   // VertexBuffer cb(colours, sizeof(colours) / 2, GL_STATIC_DRAW);
   // GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0));
   // GL_CALL(glEnableVertexAttribArray(1));

    IndexBuffer ib(indices, sizeof(indices) / sizeof(*indices), GL_STATIC_DRAW);

    VertexBuffer::Unbind();
    ArrayBuffer::Unbind();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    while (!glfwWindowShouldClose(hWnd))
    {
      glfwPollEvents();

      _time.Update();
      InputManager::ProcessActions();


      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      glm::mat4 trans = glm::mat4(1.0f);
      glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)_window.GetW() / (float)_window.GetH(), 0.1f, 100.0f);
      trans = glm::translate(trans, glm::vec3(glm::cos((float)glfwGetTime() * 2.5231f), glm::sin((float)glfwGetTime() * 3.213f), glm::sin((float)glfwGetTime() * 5.463f)));
      trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * -1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
      glm::mat4 view = glm::lookAt(_camPos,
        glm::vec3(_camPos - _camFront),
        glm::vec3(0.0f, 1.0f, 0.0f));

      Shader::SetMat4(0, trans);
      Shader::SetMat4(1, view);
      Shader::SetMat4(2, proj);


      ab.Bind();
      glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
      ArrayBuffer::Unbind();

      trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.5f));
      trans = glm::translate(trans, glm::vec3(glm::cos((float)glfwGetTime() * -2.5231f), glm::sin((float)glfwGetTime() * -3.213f), glm::sin((float)glfwGetTime() * 5.463f)));
      trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * -1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
      
      Shader::SetMat4(0, trans);
      Shader::SetMat4(1, view);
      Shader::SetMat4(2, proj);


      ab.Bind();
      glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
      ArrayBuffer::Unbind();

      glfwSwapBuffers(hWnd);
    }
  }

  Application::~Application()
  {
    glfwTerminate();
  }

  void Application::HandleWindowResize(GLFWwindow* handler, GLint width, GLint height)
  {
    _window.OnResize(width, height);
  }

  void Application::HandleKeyInput(GLFWwindow* handler, int key, int scancode, int action, int mods)
  {
    if (action == GLFW_PRESS)
      KeyManager::PressKey(key);
    else if (action == GLFW_RELEASE)
      KeyManager::ReleaseKey(key);
  }

  void Application::HandleMouseInput(GLFWwindow* window, double xpos, double ypos)
  {
    _offsetX = xpos - _lastX;
    _offsetY = _lastY - ypos;
    _lastX = xpos;
    _lastY = ypos;

    const float sensitivity = 0.05f;
    _offsetX *= sensitivity;
    _offsetY *= sensitivity;

    _yaw += _offsetX;
    _pitch -= _offsetY;

    if (_pitch > 89.9f)
      _pitch = 89.9f;
    if (_pitch < -89.9f)
      _pitch = -89.9f;
  }

}
