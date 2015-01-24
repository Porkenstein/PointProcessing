#pragma once
#include <qtimagelib.h>

class PointProcessor : public QObject
{
  Q_OBJECT;
  
  public slots:
    bool Menu_Test_Test(Image& image);
    bool Menu_Test_MyNegate(Image& image);
    bool Menu_Test_LUNegate(Image& image);
};

