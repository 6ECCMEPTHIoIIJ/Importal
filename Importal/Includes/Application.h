#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <unordered_map>
#include "Window.h"

namespace Importal
{
  class Application
  {
  public:
    Application()
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

    Application(const Application&) = delete;
    Application(Application&&) = delete;

    void Run()
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
      _window->GetInput()->BindActionOnPress(GLFW_KEY_ESCAPE, [window = _window]() { glfwSetWindowShouldClose(window->GetHandler(), GL_TRUE); });

      glewExperimental = GL_TRUE;
      glewInit();

      glEnable(GL_DEPTH_TEST);


      while (!glfwWindowShouldClose(_window->GetHandler()))
      {
        glfwPollEvents();
        glfwSwapBuffers(_window->GetHandler());
      }

      DeleteWindow();
    }

    ~Application()
    {
      glfwTerminate();
    }


  private:
    void CreateWindow()
    {
      const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
      _window = new Window();
      _window->Create(mode->width, mode->height, "Importal");
    }

    void DeleteWindow()
    {
      _windows.erase(_window->GetHandler());
      delete _window;
    }

    GLboolean CheckWindowCreationStatus()
    {
      return _window->GetHandler() != nullptr;
    }

    void LogWindowCreationError()
    {
      std::cerr << "ERROR::WINDOW::NOT_SUCCESSFULLY_CREATED" << std::endl;
    }

    void RegisterWindow()
    {
      _windows[_window->GetHandler()] = _window;
    }

    void Update()
    {

    }

    static void HandleWindowResize(GLFWwindow* handler, GLint width, GLint height)
    {
      _windows[handler]->OnResize(width, height);
    }

    static void HandleKeyInput(GLFWwindow* handler, int key, int scancode, int action, int mods)
    {
      _windows[handler]->GetInput()->OnKeyInState(key, action);
    }

    Window* _window = nullptr;
    static std::unordered_map<const GLFWwindow*, Window*> _windows;
  };
}