#include "Application.h"

#include <iostream>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Input/InputManager.h"
#include "Camera.h"
#include "GlExt.h"
#include "Object.h"

namespace Importal
{
  Timer Application::_time;
  Window Application::_window;

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

    size_t index = 1;
    InputManager::BindAction(GLFW_KEY_SPACE, [&index](const Key& key)
    {
      if (key.IsDown())
        index++;
    });

    InputManager::BindAction(GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, [this](float xAxis, float yAxis)
    {
      Camera::MoveRelationly(glm::vec3(xAxis, -yAxis, 0.0f), _time.GetDeltaTime());
    });

    glewExperimental = GL_TRUE;
    glewInit();

    auto shader = Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
    shader.Use();

    Object pigeon("Objects/pigeon/D0901B73.obj");
    Object cat("Objects/cat/cat.obj");
    Object mecha("Objects/Mecha/QuadrupedTank.obj");


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    while (!glfwWindowShouldClose(hWnd))
    {
      glfwPollEvents();

      _time.Update();
      InputManager::ProcessActions();


      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      glm::mat4 trans = glm::scale(glm::mat4(1), glm::vec3(1, 1, 1));
      glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)_window.GetW() / (float)_window.GetH(), 0.1f, 100.0f);
      
      glm::mat4 view = Camera::GetView();
      
      Shader::SetMat4(0, trans);
      Shader::SetMat4(1, view);
      Shader::SetMat4(2, proj);
      

      for (int i = 0; i < index; ++i)
      {
        trans = glm::translate(trans, glm::vec3(glm::cos(i) / 1.2f, glm::sin(i) / 1.2f, -0.2f));
        Shader::SetMat4(0, trans);
        cat.Draw(shader);
      }

      trans = glm::translate(glm::scale(glm::mat4(1), glm::vec3(0.1, 0.1, 0.1)), glm::vec3(3, 0, 0));
      Shader::SetMat4(0, trans); 
      pigeon.Draw(shader);

      trans = glm::translate(glm::scale(glm::mat4(1), glm::vec3(0.1, 0.1, 0.1)), glm::vec3(-3, 0, 0));
      Shader::SetMat4(0, trans);
      mecha.Draw(shader);

      glfwSwapBuffers(hWnd);
    }

    std::cout << index << '\n';
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
    Camera::OnMouseMove(xpos, ypos);
  }

}
