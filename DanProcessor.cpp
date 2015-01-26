#include "DanProcessor.h"

bool DanProcessor::Menu_DanFunctions_Negate(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  unsigned char lutable[255] = {0};
  
  // Build lookup table
  for (int i = 0; i < 255; i++)
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

bool Menu_DanFunctions_BinaryThreshold(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int threshold;
  unsigned char lutable[255] = {0};
  
  // Propt user for threshold value
  if (!Dialog("Binary Threshold").Add(threshold, "Threshold", 0, 255).Show())
    return false;
  
  // Convert image to grayscale
  if (!Menu_DanFunctions_Grayscale(image))
    return false;
  
  // Build lookup table
  for (int i = 0; i < 255; i++)
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

bool Menu_DanFunctions_Posterize(Image& image)
{
  if (image.IsNull())
    return false;
  
  int rows = image.Height();
  int cols = image.Width();
  
  int levels;
  unsigned char lutable[255] = {0};
  
  // Propt user for threshold value
  if (!Dialog("Posterize Levels").Add(levels, "Levels", 0, 255).Show())
    return false;
  
  // Build lookup table
  for (int i = 0; i < 255; i++)
    lutable[i] = (unsigned char) (i / (256.0 / levels));
  
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Posterize each color, truncating down
      image[i][j].SetRGB((lutable[image[i][j].Red()]),
                         (lutable[image[i][j].Green()]),
                         (lutable[image[i][j].Blue()]));
    }
  }
  
  return true;
}

bool Menu_DanFunctions_Brighten(Image& image)
{
  return false;
}

bool Menu_DanFunctions_LinearContrast(Image& image)
{
  return false;
}

