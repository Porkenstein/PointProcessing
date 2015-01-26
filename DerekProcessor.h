#pragma once
#include <qtimagelib.h>

class DerekProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_DerekProcesses_NegateImage(Image& image);
};

