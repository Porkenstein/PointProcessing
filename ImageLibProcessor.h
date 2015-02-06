#pragma once
#include <qtimagelib.h>

class ImageLibProcessor : public QObject
{
  Q_OBJECT;

  public slots:
    bool Menu_ImageLibFunctions_ConvertToGreyscale(Image& image);
    bool Menu_ImageLibFunctions_NegateImage(Image& image);
    bool Menu_ImageLibFunctions_ApplyBinaryThreshold(Image& image);
    bool Menu_ImageLibFunctions_PosterizeImage(Image& image);
    bool Menu_ImageLibFunctions_ApplyGamma(Image& image);
    bool Menu_ImageLibFunctions_ApplyLogTransform(Image& image);
    bool Menu_ImageLibFunctions_Apply8LevelPseudocolor(Image& image);
    bool Menu_ImageLibFunctions_ApplyContinuousPseudocolor(Image& image);
    bool Menu_ImageLibFunctions_AutoContrastStretch(Image& image);
    bool Menu_ImageLibFunctions_ModifiedContrastStretch(Image& image);
    bool Menu_ImageLibFunctions_Equalize(Image& image);
    bool Menu_ImageLibFunctions_EqualizeWithClipping(Image& image);
    bool Menu_ImageLibFunctions_ViewImageHistogram(Image& image);
};

