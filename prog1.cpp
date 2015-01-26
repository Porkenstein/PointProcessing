#include <qtimagelib.h>
#include "DanProcessor.h"
#include "DerekProcessor.h"

int main(int argc, char** argv)
{
  DanProcessor obj1;
  DerekProcessor obj2;
  ImageApp app(argc, argv);
  app.addActions(&obj1);
  app.AddActions(&obj2);
  return app.Start();
}

