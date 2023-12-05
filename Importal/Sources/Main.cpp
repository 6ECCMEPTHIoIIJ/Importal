#include "Application.h"

int main()
{
  auto app = new Importal::Application();
  app->Run();
  delete app;

  return 0;
}