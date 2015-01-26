#include <qtimagelib.h>
#include "DanProcessor.h"
#include "DerekProcessor.h"
#include "ImageLibProcessor.h"

int main(int argc, char** argv)
{
  DanProcessor dan;
  DerekProcessor derek;
  ImageLibProcessor ilp;
  ImageApp app(argc, argv);

  app.AddActions(&dan);
  app.AddActions(&derek);
  app.AddActions(&ilp);
  return app.Start();
}
