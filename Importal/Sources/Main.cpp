#include "Application.h"

int main()
{
  auto win = new Importal::Application();
  win->Run();
  delete win;

  return 0;
}