#include "DanProcessor.h"

bool DanProcessor::Menu_DanFunctions_Negate(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  unsigned char lutable[256] = {0};
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
    lutable[i] = 255-i;
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Negate each pixel
      image[i][j].SetRGB((lutable[image[i][j].Red()]),
                         (lutable[image[i][j].Green()]),
                         (lutable[image[i][j].Blue()]));
    }
  }
  
  return true;
}

bool DanProcessor::Menu_DanFunctions_Grayscale(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int gray;
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Calculate weighted averages
      gray = image[i][j].Red() * 30;
      gray += image[i][j].Green() * 59;
      gray += image[i][j].Blue() * 11;
      gray /= 100;
      
      // Set gray value
      image[i][j].SetGray(gray);
    }
  }
  
  return true;
}

bool DanProcessor::Menu_DanFunctions_BinaryThreshold(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int threshold;
  unsigned char lutable[256] = {0};
  
  // Propt user for threshold value
  threshold = 128;
  if (!Dialog("Binary Threshold").Add(threshold, "Threshold", 0, 255).Show())
    return false;
  
  // Convert image to grayscale
  if (!this -> Menu_DanFunctions_Grayscale(image))
    return false;
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
    lutable[i] = (i < threshold ? 0 : 255);
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Perform binary thresholding
      image[i][j].SetGray(lutable[image[i][j].Red()]);
    }
  }
  
  return true;
}

bool DanProcessor::Menu_DanFunctions_Posterize(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int level;
  int levels;
  double temp;
  double lsize;
  unsigned char lutable[256] = {0};
  
  // Propt user for threshold value
  levels = 4;
  if (!Dialog("Posterize Levels").Add(levels, "Levels", 1, 256).Show())
    return false;
  
  // Couple calculations
  lsize = 256.0 / levels;
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
  {
    // Determine current level
    level = (int) (i / lsize);
    
    // Scale to range and truncate
    temp = (int) (level * lsize);
    
    // Avoid overall darkening by distributing poserize levels
    // We aren't using floor, ceil, or median; posterize level is determined by
    //   the level itself.
    temp += lsize * ((double) level / ((double) levels - 1));
    
    // Avoid overflow in either direction just to be safe
    if (temp > 255) temp = 255;
    if (temp < 0)   temp = 0;
    
    // Save to lookup table (and truncate)
    lutable[i] = (unsigned char) temp;
  }

  // Perform posterization on each color of each pixel  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      image[i][j].SetRGB((lutable[image[i][j].Red()]),
                         (lutable[image[i][j].Green()]),
                         (lutable[image[i][j].Blue()]));
    }
  }
  
  return true;
}

bool DanProcessor::Menu_DanFunctions_Brighten(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int brightness;
  int maxpixel;
  int minpixel;
  unsigned char lutable[256] = {0};
  
  // Propt user for threshold value
  brightness = 0;
  if (!Dialog("Brightness").Add(brightness, "Brightness", -255, 255).Show())
    return false;
  
  maxpixel = 255 - brightness;
  minpixel = 0 - brightness;
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
    lutable[i] = (unsigned char) (i <= minpixel ? 0 :
                                  i >= maxpixel ? 255 :
                                  i + brightness);
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Brighten each color
      image[i][j].SetRGB((lutable[image[i][j].Red()]),
                         (lutable[image[i][j].Green()]),
                         (lutable[image[i][j].Blue()]));
    }
  }
  
  return true;
}

bool DanProcessor::Menu_DanFunctions_LinearContrast(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int lowbound;
  int upbound;
  double scale;
  unsigned char lutable[256] = {0};
  
  // Propt user for threshold value
  lowbound = 15;
  upbound = 240;
  if (!Dialog("Linear Contrast").Add(lowbound, "Minimum Intensity", 0, 255)
        .Add(upbound, "Maximum Intensity", 0, 255).Show())
    return false;
  
  // If reversed, flip 'em
  if (lowbound > upbound)
  {
    lowbound ^= upbound;
    upbound ^= lowbound;
    lowbound ^= upbound;
  }
  
  // Calculate scale
  if (lowbound != upbound)
    scale = 255 / (upbound - lowbound);
  else
    scale = 255;
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
    lutable[i] = (unsigned char) (i <= lowbound ? 0 :
                                  i >= upbound ? 255 :
                                  ((i - lowbound) * scale) + 0.5);
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Add contrast to each color
      image[i][j].SetRGB((lutable[image[i][j].Red()]),
                         (lutable[image[i][j].Green()]),
                         (lutable[image[i][j].Blue()]));
    }
  }
  
  return true;
}

bool DanProcessor::Menu_DanFunctions_8LayerPseudocolor(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  unsigned char lutable[256][3];
  unsigned char colortable[8][3] = {
    {0, 0, 0},
    {255, 0, 0},
    {255, 255, 0},
    {0, 255, 0},
    {0, 255, 255},
    {0, 0, 255},
    {255, 0, 255},
    {255, 255, 255}
  };
  
  // Build lookup table
  for (int i = 0; i < 256; i++)
  {
    lutable[i][0] = colortable[i / 8][0];
    lutable[i][1] = colortable[i / 8][1];
    lutable[i][2] = colortable[i / 8][2];
  }
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Pseudocolor each pixel based on intensity
      image[i][j].SetRGB(lutable[image[i][j]][0],
                         lutable[image[i][j]][1],
                         lutable[image[i][j]][2]);
    }
  }
  
  return true;
}



