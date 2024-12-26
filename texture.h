//!
//! Physical Texture Library
//! ~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! This is a header-only C library for representing and managing *physical*
//! textures. Unlike graphical textures, this library focuses on physical
//! texture data, where each value represents a physical property (e.g.,
//! roughness, height) on a 2D grid. Values in float format are normalized
//! between 0.0 and 1.0.
//!
//! The library provides functions to initialize textures, read and write them
//! in CSV format, and manage memory allocation. Designed for ease of
//! integration into projects requiring lightweight physical texture data
//! handling.
//!
//! :copyright: (c) 2024 by Jairus Davis
//! :license: GNU GPLv3, see <https://www.gnu.org/licenses/> for details.
//!
//! Usage:
//! - Include this header file directly in your C project.
//! - Initialize textures using either float (normalized) or uint32_t data.
//! - Serialize and deserialize textures via CSV files for easy persistence.
//!
//! Features:
//! - Header-only for seamless integration.
//! - Focus on physical texture data, with float values normalized to
//! [0.0, 1.0].
//! - CSV file support for simple serialization and deserialization.
//!
//! Note: This library is provided "as-is" without warranty of any kind,
//! either expressed or implied, including but not limited to the implied
//! warranties of merchantability or fitness for a particular purpose.
//!

#ifndef H_TEXTURE
#define H_TEXTURE

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Texture structure representing a 2D grid of data.
 * - `w`: The width of the texture (number of columns).
 * - `h`: The height of the texture (number of rows).
 * - `data`: Pointer to a dynamically allocated array of uint32_t values
 * representing the texture's data.
 */
typedef struct {
  uint16_t w, h;
  uint32_t *data;
} Texture;

/**
 * Initializes a Texture object using float data.
 * Each float value is scaled to the range of uint32_t.
 *
 * @param texture Pointer to the Texture to initialize.
 * @param w Width of the texture.
 * @param h Height of the texture.
 * @param data Pointer to an array of float values, each in the range
 * [0.0, 1.0].
 */
inline void initTexture_f(Texture *texture, uint16_t w, uint16_t h,
                          const float *data) {
  texture->w = w;
  texture->h = h;
  texture->data = (uint32_t *)calloc(w * h, sizeof(uint32_t));
  assert(texture->data && "Memory allocation failed for texture data.");
  for (size_t i = 0; i < w * h; ++i) {
    texture->data[i] = (uint32_t)(UINT32_MAX * data[i]);
  }
}

/**
 * Initializes a Texture object using uint32_t data.
 *
 * @param texture Pointer to the Texture to initialize.
 * @param w Width of the texture.
 * @param h Height of the texture.
 * @param data Pointer to an array of uint32_t values to initialize the
 * texture's data.
 */
inline void initTexture_i(Texture *texture, uint16_t w, uint16_t h,
                          const uint32_t *data) {
  texture->w = w;
  texture->h = h;
  texture->data = (uint32_t *)calloc(w * h, sizeof(uint32_t));
  assert(texture->data && "Memory allocation failed for texture data.");
  for (size_t i = 0; i < w * h; ++i) {
    texture->data[i] = data[i];
  }
}

/**
 * Writes a Texture object to a CSV file.
 * The format is: `width,height,data1,data2,...`
 *
 * @param texture Pointer to the Texture to write.
 * @param path Path to the file where the texture will be written.
 */
inline void writeTexture(const Texture *texture, const char *path) {
  FILE *fp = fopen(path, "w");
  assert(fp && "File unable to be opened.");
  fprintf(fp, "%hu,%hu,", texture->w, texture->h);
  for (size_t i = 0; i < texture->w * texture->h; ++i) {
    fprintf(fp, "%u,", texture->data[i]);
  }
  fclose(fp);
}

/**
 * Reads a Texture object from a CSV file.
 * Assumes the format: `width,height,data1,data2,...`
 *
 * @param texture Pointer to the Texture to initialize from the file.
 * @param path Path to the file containing the texture data.
 */
inline void readTexture(Texture *texture, const char *path) {
  FILE *fp = fopen(path, "r");
  assert(fp && "File unable to be opened.");

  // Read width and height
  fscanf(fp, "%hu,%hu,", &texture->w, &texture->h);

  // Allocate memory for data
  size_t size = texture->w * texture->h;
  texture->data = (uint32_t *)malloc(size * sizeof(uint32_t));
  assert(texture->data && "Memory allocation failed for texture data.");

  // Read data
  for (size_t i = 0; i < size; ++i) {
    fscanf(fp, "%u,", &texture->data[i]);
  }

  fclose(fp);
}

/**
 * Frees the memory associated with a Texture object.
 *
 * @param texture Pointer to the Texture whose memory should be freed.
 */
inline void freeTexture(Texture *texture) {
  free(texture->data);
  texture->data = NULL;
}

#endif
