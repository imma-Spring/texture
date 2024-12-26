# Physical Texture Library

This is a header-only C library designed for representing and managing *physical* textures. Unlike traditional graphical textures, this library focuses on handling physical properties (such as roughness or height) on a 2D grid, where each value represents a specific physical attribute and is normalized between 0.0 and 1.0.

The library allows you to initialize textures, read and write them in CSV format, and manage memory allocation, making it a lightweight solution for handling physical texture data in C projects.

---

## Features

- **Header-only**: No need for separate compilation or linking; just include the header file directly into your project.
- **Normalized float values**: Each texture value is a floating-point number normalized between [0.0, 1.0].
- **CSV Serialization**: Simple functions for saving and loading textures using CSV files.
- **Memory Management**: Provides functions to initialize and free textures dynamically.
  
---

## License

This library is released under the **GNU GPLv3 License**. See [GNU GPLv3](https://www.gnu.org/licenses/) for more details.

---

## Usage

### 1. Include the Header File

To use the library, simply include the `texture.h` file in your C project.

```c
#include "texture.h"
```

### 2. Initialize a Texture

You can initialize a texture using either `double` (normalized) or `uint32_t` data.

- **For normalized `double` data** (values between 0.0 and 1.0):

```c
double textureData[] = { 0.0, 1.0, 0.5, ... };
Texture texture;
initTexture_d(&texture, 4, 4, textureData); // 4x4 texture
```

- **For `uint32_t` data**:

```c
uint32_t textureData[] = { 0, 255, 128, ... };
Texture texture;
initTexture_i(&texture, 4, 4, textureData); // 4x4 texture
```

### 3. Serialize and Deserialize

- **Write a texture to a CSV file**:

```c
writeTexture(&texture, "texture.csv");
```

- **Read a texture from a CSV file**:

```c
Texture texture;
readTexture(&texture, "texture.csv");
```

### 4. Free Memory

Don't forget to free the memory allocated for the texture data when you're done:

```c
freeTexture(&texture);
```

---

## Example

Here’s a quick example of how you can use the library in a project:

```c
#include "texture.h"
#include <stdio.h>

int main() {
    // Initialize a texture with some normalized float data
    double textureData[] = { 0.0, 1.0, 0.5, 0.25 };
    Texture texture;
    initTexture_d(&texture, 2, 2, textureData);

    // Write the texture to a CSV file
    writeTexture(&texture, "myTexture.csv");

    // Read the texture back from the CSV file
    Texture loadedTexture;
    readTexture(&loadedTexture, "myTexture.csv");

    // Free the memory
    freeTexture(&texture);
    freeTexture(&loadedTexture);

    return 0;
}
```

---

## Functions

### `void initTexture_f(Texture *texture, uint16_t w, uint16_t h, const double *data)`
Initializes a texture using double data, scaling each value to the range of `uint32_t`.

### `void initTexture_i(Texture *texture, uint16_t w, uint16_t h, const uint32_t *data)`
Initializes a texture using `uint32_t` data directly.

### `void writeTexture(const Texture *texture, const char *path)`
Writes the texture to a CSV file, including its width, height, and data.

### `void readTexture(Texture *texture, const char *path)`
Reads the texture from a CSV file and initializes it with the data.

### `void freeTexture(Texture *texture)`
Frees the dynamically allocated memory for the texture's data.

---

## Notes

- The library assumes that the data is stored in a specific format in the CSV file, where the first two values represent the width and height of the texture, followed by the texture data itself.
- The texture data is normalized to fit within the range of `uint32_t` (0 to 4294967295), representing physical properties like roughness or height.
  
---

## Disclaimer

This library is provided *as-is*, without warranty of any kind, either expressed or implied, including but not limited to the implied warranties of merchantability or fitness for a particular purpose.

