#include "DerekProcessor.h"
#include <cmath>
#include <string>
#include <qfiledialog.h>
#include <stdlib.h>

bool DerekProcessor::Menu_DerekFunctions_ApplyGamma(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};

  double gamma = 0.0;
  getParams(gamma);

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 256; j++)
      memory[i][j] = (char)(pow((j/255.0), gamma)*255.0);

  if (image.IsNull()) return false;

  int rows = image.Height();
  int cols = image.Width();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      image[i][j].SetRed(memory[0][image[i][j].Red()]);
      image[i][j].SetGreen(memory[1][image[i][j].Green()]);
      image[i][j].SetBlue(memory[2][image[i][j].Blue()]);
    }
  }

  return true;
}

bool DerekProcessor::Menu_DerekFunctions_ApplyLogTransform(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};
  static bool lookup_table = false;

  // Build the lookup table
  if (!lookup_table)
  {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 256; j++)
        memory[i][j] = log(j+1.0)*(255.0/log(256.0));
    lookup_table = true;
  }

  if (image.IsNull()) return false;

  int rows = image.Height();
  int cols = image.Width();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      image[i][j].SetRed(memory[0][image[i][j].Red()]);
      image[i][j].SetGreen(memory[1][image[i][j].Green()]);
      image[i][j].SetBlue(memory[2][image[i][j].Blue()]);
    }
  }

  return true;
}

bool DerekProcessor::Menu_DerekFunctions_DisplayImageHistogram(Image& image)
{
  std::vector<uint>histogram = std::vector<uint>(256);

  int rows = image.Height();
  int cols = image.Width();

  //compute the histogram
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
        histogram[image[i][j].Intensity()]++;
    }
  }

  displayHistogram(histogram, "Image Histogram");
  return true;
}

bool DerekProcessor::Menu_DerekFunctions_Equalize(Image& image)
{
    return true;
}

bool DerekProcessor::Menu_DerekFunctions_ApplyContinuousPseudocolor(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};
  static bool lookup_table = false;

  // Build the lookup table
  if (!lookup_table)
  {
    for (int j = 0; j < 256; j++)
    {
      // applying the example pseudocolor from class
      memory[0][j] = j;
      memory[1][j] = 255-abs(255-j*2);
      memory[2][j] = 255-j;
    }
    lookup_table = true;
  }

  if (image.IsNull()) return false;

  int rows = image.Height();
  int cols = image.Width();

  grayscale(image);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
        image[i][j].SetRed(memory[0][image[i][j].Intensity()]);
        image[i][j].SetGreen(memory[1][image[i][j].Intensity()]);
        image[i][j].SetBlue(memory[2][image[i][j].Intensity()]);
    }
  }

  return true;
}

bool DerekProcessor::Menu_DerekFunctions_SubtractImage(Image& image)
{
  std::string subtractor_filepath = QFileDialog::getOpenFileName().toStdString();
  Image subtractor(subtractor_filepath);


  if (image.IsNull() || subtractor.IsNull()) return false;

  //find the smallest dimension, so we don't step outside of either image
  int rows = std::min(image.Height(), subtractor.Height());
  int cols = std::min(image.Width(), subtractor.Width());

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      image[i][j].SetRed(image[i][j].Red() - subtractor[i][j].Red());
      image[i][j].SetGreen(image[i][j].Green() - subtractor[i][j].Green());
      image[i][j].SetBlue(image[i][j].Blue() - subtractor[i][j].Blue());
    }
  }

  return true;
}
