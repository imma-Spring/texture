#include "texture.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void testInitTexture_d() {
  double textureData[] = {0.0, 1.0, 0.5, 0.25};
  Texture texture;
  initTexture_d(&texture, 2, 2, textureData);

  // Check if the texture dimensions are correct
  assert(texture.w == 2);
  assert(texture.h == 2);

  // Check if the data is properly initialized
  assert(texture.data[0] == 0);
  assert(texture.data[1] == UINT32_MAX);
  assert(texture.data[2] == (UINT32_MAX / 2));
  assert(texture.data[3] == (UINT32_MAX / 4));

  freeTexture(&texture);
}

void testInitTexture_i() {
  uint32_t textureData[] = {0, UINT32_MAX, 2147483647, 1073741823};
  Texture texture;
  initTexture_i(&texture, 2, 2, textureData);

  // Check if the texture dimensions are correct
  assert(texture.w == 2);
  assert(texture.h == 2);

  // Check if the data is properly initialized
  assert(texture.data[0] == 0);
  assert(texture.data[1] == UINT32_MAX);
  assert(texture.data[2] == 2147483647);
  assert(texture.data[3] == 1073741823);

  freeTexture(&texture);
}

void testWriteReadTexture() {
  double textureData[] = {0.0, 1.0, 0.5, 0.25};
  Texture texture;
  initTexture_d(&texture, 2, 2, textureData);

  // Write the texture to a CSV file
  writeTexture(&texture, "test_texture.csv");

  // Read the texture back from the CSV file
  Texture loadedTexture;
  readTexture(&loadedTexture, "test_texture.csv");

  // Check if the loaded texture has the correct dimensions
  assert(loadedTexture.w == 2);
  assert(loadedTexture.h == 2);

  // Check if the loaded data matches the original data
  assert(loadedTexture.data[0] == 0);
  assert(loadedTexture.data[1] == UINT32_MAX);
  assert(loadedTexture.data[2] == (UINT32_MAX / 2));
  assert(loadedTexture.data[3] == (UINT32_MAX / 4));

  // Clean up
  freeTexture(&texture);
  freeTexture(&loadedTexture);

  // Clean up the test CSV file
  remove("test_texture.csv");
}

void testFreeTexture() {
  double textureData[] = {0.0, 1.0};
  Texture texture;
  initTexture_d(&texture, 1, 2, textureData);

  // Ensure memory is properly allocated
  assert(texture.data != NULL);

  // Free the texture and check if memory is released
  freeTexture(&texture);
  assert(texture.data == NULL);
}

int main() {
  // Run the tests
  testInitTexture_d();
  testInitTexture_i();
  testWriteReadTexture();
  testFreeTexture();

  printf("All tests passed!\n");
  return 0;
}
