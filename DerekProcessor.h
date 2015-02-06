#pragma once
#include <qtimagelib.h>

class DerekProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_DerekFunctions_ApplyGamma(Image& image);
    bool Menu_DerekFunctions_ApplyLogTransform(Image& image);
    bool Menu_DerekFunctions_DisplayImageHistogram(Image& image);
    bool Menu_DerekFunctions_ApplyContinuousPseudocolor(Image& image);
    bool Menu_DerekFunctions_SubtractImage(Image& image);
    bool Menu_DerekFunctions_Equalize(Image& image);
};

