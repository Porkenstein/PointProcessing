#include "DerekProcessor.h"

bool DerekProcessor::Menu_DerekProcesses_NegateImage(Image& image)
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
