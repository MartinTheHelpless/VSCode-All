#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

// Height of each character.
const int FONT_ROW_HEIGHT = 34;

typedef unsigned char byte;

typedef struct
{
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct
{
    byte blue;
    byte green;
    byte red;
} RGBPixel;

typedef struct
{
    TGAHeader header;
    RGBPixel *pixels;
    int width;
    int height;
} Image;

// Loads an image from the given `path`.
// If loading fails, return false.
bool image_load(Image *image, const char *path)
{
    FILE *file = fopen(path, "rb");

    memset(image, 0, sizeof(Image));
    fread(&image->header, sizeof(image->header), 1, file);

    // We only support RGB images.
    assert(image->header.depth == 24);
    assert(image->header.image_type == 2);

    memcpy(&image->width, image->header.width, sizeof(image->header.width));
    memcpy(&image->height, image->header.height, sizeof(image->header.height));

    image->pixels = (RGBPixel *)malloc(sizeof(RGBPixel) * image->width * image->height);
    fread(image->pixels, sizeof(RGBPixel) * image->width * image->height, 1, file);

    fclose(file);

    return true;
}

// Free the memory of the given image.
void image_free(Image *image)
{
    free(image->pixels);
}

RGBPixel *load_pixels(TGAHeader header, FILE *file)
{
    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    RGBPixel *pixels = (RGBPixel *)malloc(sizeof(RGBPixel) * width * height);
    assert(fread(pixels, sizeof(RGBPixel) * width * height, 1, file) == 1);
    return pixels;
}

int main(int argc, char const *argv[])
{

    RGBPixel *array[26];
    int w = 0;
    int h = 0;

    for (int i = 0; i < 26; i++)
    {

        char fnt[6] = "font/";
        char end[5] = ".tga";

        char cr[1] = {(char)(65 + i)};

        strcat(fnt, cr);

        FILE *file = fopen(fnt, "rb");
        assert(file);

        TGAHeader header = {};
        assert(fread(&header, sizeof(TGAHeader), 1, file) == 1);

        int width = 0;
        int height = 0;

        memcpy(&width, header.width, 2);
        memcpy(&height, header.height, 2);

        w += width;
        h += height;

        fclose(fnt);
    }

    for (int i = 0; i < 26; i++) // Load all letters
    {

        char fnt[6] = "font/";
        char end[5] = ".tga";

        char cr[1] = {(char)(65 + i)};

        strcat(fnt, cr);

        FILE *file = fopen(fnt, "rb");
        assert(file);

        TGAHeader header = {};
        assert(fread(&header, sizeof(TGAHeader), 1, file) == 1);

        int width = 0;
        int height = 0;

        memcpy(&width, header.width, 2);
        memcpy(&height, header.height, 2);

        array[i] = load_pixels(header, file);

        fclose(fnt);
    }

    FILE *file = fopen("img2.tga" /* argv[1] */, "rb");
    assert(file);

    TGAHeader header = {};
    assert(fread(&header, sizeof(TGAHeader), 1, file) == 1);

    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    RGBPixel *pixels = load_pixels(header, file);

    FILE *output = fopen("output.tga", "wb");

    printf("%d", pixels[40].blue);

    for (int i = 0; i < 26; i++)
        free(array[i]);

    free(pixels);

    return 0;
}
