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

    CreateWindow();
    if (!CheckWindowCreationStatus())
    {
      LogWindowCreationError();
      return;
    }

    RegisterWindow();

    glfwMakeContextCurrent(_window->GetHandler());
    glfwSetFramebufferSizeCallback(_window->GetHandler(), HandleWindowResize);
    glfwSetKeyCallback(_window->GetHandler(), HandleKeyInput);
    _window->GetInput()->BindActionOnPress(GLFW_KEY_ESCAPE, [window = _window]()
    {
      glfwSetWindowShouldClose(window->GetHandler(), GL_TRUE);
    });

    glewExperimental = GL_TRUE;
    glewInit();

    auto shader = Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");

    GLfloat vertices[] = {
      0.5f, -0.5f, 0.5f,
      -0.5f, -0.5f, 0.5f,
      -0.5f,  0.5f, 0.5f,
      0.5f,  0.5f, 0.5f,
      0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
    };

    GLfloat colours[] = {
      1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 1.0f,
      0.0f, 0.0f, 1.0f,
      0.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f,
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
    IndexBuffer ib(indices, sizeof(indices) / sizeof(*indices), GL_STATIC_DRAW);
    VertexBuffer vb(vertices, sizeof(vertices), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    VertexBuffer cb(colours, sizeof(colours), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    VertexBuffer::Unbind();
    ArrayBuffer::Unbind();


    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(_window->GetHandler()))
    {
      glfwPollEvents();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      glm::mat4 trans = glm::mat4(1.0f);
      glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)_window->GetWidth() / (float)_window->GetHeight(), 0.1f, 100.0f);
      trans = glm::translate(trans, glm::vec3(glm::cos((float)glfwGetTime() * 2.0f), glm::sin((float)glfwGetTime() * 2.0f), 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
      trans = glm::rotate(trans, (float)glfwGetTime() * -1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
      glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));


      Shader::SetMat4(0, trans);
      Shader::SetMat4(1, view);
      Shader::SetMat4(2, proj);

      shader.Use();

      ab.Bind();
      glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
      ArrayBuffer::Unbind();



      glfwSwapBuffers(_window->GetHandler());
    }

    DeleteWindow();
  }

  Application::~Application()
  {
    glfwTerminate();
  }

  void Application::CreateWindow()
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    _window = new Window();
    _window->Create(mode->width, mode->height, "Importal");
  }

  void Application::DeleteWindow()
  {
    _windows.erase(_window->GetHandler());
    delete _window;
  }

  GLboolean Application::CheckWindowCreationStatus()
  {
    return _window->GetHandler() != nullptr;
  }

  void Application::LogWindowCreationError()
  {
    std::cerr << "ERROR::WINDOW::NOT_SUCCESSFULLY_CREATED" << std::endl;
  }

  void Application::RegisterWindow()
  {
    _windows[_window->GetHandler()] = _window;
  }

  void Application::HandleWindowResize(GLFWwindow* handler, GLint width, GLint height)
  {
    _windows[handler]->OnResize(width, height);
  }

  void Application::HandleKeyInput(GLFWwindow* handler, int key, int scancode, int action, int mods)
  {
    _windows[handler]->GetInput()->OnKeyInState(key, action);
  }

}
