#include "DerekProcessor.h"
#include <cmath>
#include <string>
#include <qfiledialog.h>

bool DerekProcessor::Menu_DerekFunctions_ApplyGamma(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};
  static bool lookup_table = false;

  // Build the lookup table
  if (!lookup_table)
  {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 256; j++)
        memory[i][j] = 255 - (unsigned char) j;
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

bool DerekProcessor::Menu_DerekFunctions_ApplyLogTransform(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};
  static bool lookup_table = false;

  // Build the lookup table
  if (!lookup_table)
  {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 256; j++)
        memory[i][j] = 255 - (unsigned char) j;
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

bool DerekProcessor::Menu_DerekFunctions_Apply8LevelPseudocolor(Image& image)
{
  static unsigned char memory[3][256] = {{0},{0},{0}};
  static bool lookup_table = false;

  // Build the lookup table
  if (!lookup_table)
  {
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 256; j++)
        memory[i][j] = 255 - (unsigned char) j;
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

bool DerekProcessor::Menu_DerekFunctions_ApplyContinuousPseudocolor(Image& image)
{
  if (image.IsNull()) return false;

  int rows = image.Height();
  int cols = image.Width();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      image[i][j].SetRed();
      image[i][j].SetGreen();
      image[i][j].SetBlue();
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
