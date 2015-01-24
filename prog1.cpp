#include <qtimagelib.h>
#include "PointProcessor.h"

int main(int argc, char** argv)
{
  PointProcessor obj;
  ImageApp app(argc, argv);
  app.AddActions(&obj);
  return app.Start();
}

