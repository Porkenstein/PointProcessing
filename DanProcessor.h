#pragma once
#include <qtimagelib.h>

class DanProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_DanProcesses_NegateImage(Image& image);
};
