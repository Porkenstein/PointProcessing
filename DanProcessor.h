#pragma once
#include <qtimagelib.h>
#include <iostream>

class DanProcessor : public QObject
{
  Q_OBJECT;
  
  public slots:
    bool Menu_DanFunctions_Negate(Image& image);
    bool Menu_DanFunctions_Grayscale(Image& image);
    bool Menu_DanFunctions_BinaryThreshold(Image& image);
    bool Menu_DanFunctions_Posterize(Image& image);
    bool Menu_DanFunctions_Brighten(Image& image);
    bool Menu_DanFunctions_LinearContrast(Image& image);
    bool Menu_DanFunctions_8LayerPseudocolor(Image& image);
};

