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
#include "Light.h"



namespace Importal
{
  glm::mat4 lastPos;
  glm::vec3 lcp;
  glm::vec3 lcr;
  float camAdd;
  glm::vec3 mechAdd;
  glm::vec3 moveAdd;
  float pAdd;

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
      if (key.IsJustPressed()) {
        stopped = !stopped;
        if (!stopped) {
          Camera::SetPos(lcp);
          Camera::Rotate(lcr);
        }
      }
    });

    InputManager::BindAction(GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, [this](float xAxis, float yAxis)
    {
      if (xAxis == 0 && yAxis == 0)
        move = false;
      else
        move = true;

      Camera::MoveRelationly(glm::vec3(xAxis, -yAxis, 0.0f), _time.GetDeltaTime());
    });


    glewExperimental = GL_TRUE;
    glewInit();

    auto shader = Shader("Shaders/VertexShader.glsl", "Shaders/FragmentShader.glsl");
    auto shaderDepth = Shader("Shaders/DepthVertex.glsl", "Shaders/DepthFragment.glsl");

    //shader.SetVec3("lightPos", 10.f, 3.5f, 4.6f);

    Object pigeon("Objects/pigeon/D0901B73.obj");
    Object cat("Objects/cat/cat.obj");
    Object mecha("Objects/Mecha/QuadrupedTank.obj");
    Object apple("Objects/apple/apple.obj");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    auto light = Light(Light::Directional);
    light.setPosition(glm::vec4(0, 20, 0, 1));
    light.setDiffuseColor(glm::vec4(1, 1, 1, 1));
    light.setAmbienceColor(glm::vec3(1, 0, 1));
    light.setDirection(glm::vec4(glm::quarter_pi<float>(), glm::quarter_pi<float>(), 0, 1));
    light.setCutoff(3.f / 180.f * glm::pi<float>());
    light.setPower(1);

    auto light1 = Light(Light::Spot);
    light1.setPosition(glm::vec4(0, 0, 0, 1));
    light1.setDiffuseColor(glm::vec4(1, 1, 0, 1));
    light1.setCutoff(12.f / 180.f * glm::pi<float>());

    Light* lights[2] = {};
    lights[0] = &light;
    lights[1] = &light1;

    auto projectionLight = glm::ortho(-40, 40, -40, 40, -40, 40);

    while (!glfwWindowShouldClose(hWnd))
    {
      glfwPollEvents();

      _time.Update();
      InputManager::ProcessActions();


      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      if (!stopped)
        Camera::SetPos(glm::vec3(Camera::GetPos().x, 0, Camera::GetPos().z));
      else
        Camera::SetPos(glm::vec3(Camera::GetPos().x, glm::max(0.01f, Camera::GetPos().y), Camera::GetPos().z));

      camAdd = glm::sin(_time.GetLastFramTime() * 3) * 0.005f;
      mechAdd = glm::vec3(glm::sin(_time.GetLastFramTime() * 15) * 0.02f,
        glm::cos(_time.GetLastFramTime() * 13) * 0.01f,
        glm::sin(_time.GetLastFramTime() * 11) * 0.008f);

      moveAdd = glm::vec3(glm::sin(_time.GetLastFramTime() * 6) * 0.2f,
        glm::cos(_time.GetLastFramTime() * 5) * 0.2f,
        glm::sin(_time.GetLastFramTime() * 8) * 0.2);

      pAdd = glm::max(0.0f, glm::cos(_time.GetLastFramTime() * 7)) * 1.0f;

      const auto camPos = Camera::GetPos();
      const auto camRot = Camera::GetRotation();

      if (!stopped) {
        lastPos = glm::rotate(glm::translate(glm::identity<glm::mat4>(), camPos), glm::radians(-90 - camRot.y), glm::vec3(0, 1, 0));


        if (!move) {
          lastPos = glm::rotate(lastPos, mechAdd.x, glm::vec3(1, 0, 0));
          lastPos = glm::rotate(lastPos, mechAdd.y, glm::vec3(0, 1, 0));
          lastPos = glm::rotate(lastPos, mechAdd.z, glm::vec3(0, 0, 1));
        }
        else {
          lastPos = glm::translate(lastPos, glm::vec3(0, pAdd, 0));
          lastPos = glm::rotate(lastPos, moveAdd.x, glm::vec3(1, 0, 0));
          lastPos = glm::rotate(lastPos, moveAdd.y, glm::vec3(0, 1, 0));
          lastPos = glm::rotate(lastPos, moveAdd.z, glm::vec3(0, 0, 1));
        }

        lcp = camPos;
        lcr = camRot;
      }

      glm::mat4 trans = lastPos;

      if (stopped)
        Camera::SetPos(glm::vec3(Camera::GetPos().x, Camera::GetPos().y + camAdd, Camera::GetPos().z));

      if (!stopped)
        Camera::SetPos(glm::vec3(
          Camera::GetPos().x + glm::cos(glm::radians(camRot.y)) * 10,
          10,
          Camera::GetPos().z + glm::sin(glm::radians(camRot.y)) * 10)
        );

      if (stopped)
        light1.setPower(100);
      else
        light1.setPower(0);

      light1.setPosition(glm::vec4(camPos, 1));
      light1.setDirection(glm::vec4(glm::radians(camRot.x), glm::radians(camRot.z), glm::radians(camRot.y), 1));
      
      glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)_window.GetW() / (float)_window.GetH(), 0.1f, 100.0f);
      glm::mat4 view = Camera::GetView();

      if (!stopped)
        Camera::SetPos(camPos);

      //shaderDepth.Use();
      //shaderDepth.SetMat4("projectionLight", projectionLight);
      //shaderDepth.SetMat4("shadowLight", light.getLightMatrix());
      //mecha.Draw(shaderDepth);

      shader.Use();

      shader.SetMat4("transform", trans);
      shader.SetMat4("view", view);
      shader.SetMat4("projection", proj);
      shader.SetMat4("lightProjection", projectionLight);
      shader.SetMat4("shadowLight", light.getLightMatrix());
      shader.SetFloat("lightPower", 1.0f);

      for (int i = 0; i < sizeof(lights) / sizeof(*lights); i++) {
        //if (!stopped && i == sizeof(lights) / sizeof(*lights) - 1) continue;
        shader.SetVec3(std::format("light[{}].ambienceColor", i), lights[i]->getAmbienceColor());
        shader.SetVec3(std::format("light[{}].diffuseColor", i), lights[i]->getDiffuseColor());
        shader.SetVec3(std::format("light[{}].specularColor", i), lights[i]->getSpecularColor());
        shader.SetVec4(std::format("light[{}].position", i), lights[i]->getPosition());
        shader.SetVec4(std::format("light[{}].direction", i), lights[i]->getDirection());
        shader.SetFloat(std::format("light[{}].cutoff", i), lights[i]->getCutoff());
        shader.SetInt(std::format("light[{}].type", i), lights[i]->getType());
        shader.SetFloat(std::format("light[{}].power", i), lights[i]->getPower());
      }

      shader.SetInt("countLights", sizeof(lights) / sizeof(*lights));
      shader.SetInt("indexLightForShadow", 0);

      mecha.Draw(shader);

      //auto t = (float)glfwGetTime();
      //for (int i = 0; i < index; ++i)
      //{
      //  trans = glm::translate(trans, glm::vec3(glm::cos(i) / 1.2f, glm::sin(i) / 1.2f, -0.2f));

      //  Shader::SetMat4(0, trans);
      //  cat.Draw(shader);
      //}

      trans = glm::translate(glm::identity<glm::mat4>(), glm::vec3(0, 0, 0));
      Shader::SetMat4("transform", trans);
      pigeon.Draw(shader);



      //trans = glm::scale(glm::mat4(1), glm::vec3(.01, .01, .01));

      //Shader::SetMat4(0, trans);
      //apple.Draw(shader);
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
