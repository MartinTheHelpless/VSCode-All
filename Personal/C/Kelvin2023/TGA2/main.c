#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

const int IMG_HEIGHT = 34;

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

    FILE *letters[26];

    if (argc == 4)
    {
        printf("Wrong parameters");
        return 1;
    }

    FILE *img = fopen("img1.tga", "rb");
    assert(img);

    if (img == NULL)
    {
        printf("Could not load image");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {

        char fnt[100];
        strcpy(fnt, "font/");
        char cr[2] = {(char)(65 + i), '\0'};
        strcat(fnt, cr);
        strcat(fnt, ".tga");

        letters[i] = fopen(fnt, "rb");

        if (letters[i] == NULL)
        {
            printf("Could not load font file %s\n", fnt);
            return 1;
        }
    }

    char tmp[100];

    fgets(tmp, 100, stdin);

    int top = atoi(strtok(tmp, " "));

    int bottom = atoi(strtok(NULL, "\0"));

    int total = top + bottom;

    printf("top: %d\nbottom:%d\ntop + bottom: %d\n", top, bottom, total);

    char **str = (char **)malloc(total * sizeof(char *));

    for (size_t i = 0; i < top + bottom; i++)
    {
        fgets(tmp, 100, stdin);
        str[i] = strdup(tmp);
    }

    FILE *output = fopen("output.tga", "wb");
    assert(output);

    TGAHeader header = {};
    assert(fread(&header, sizeof(TGAHeader), 1, img) == 1);

    int width = 0;
    int height = 0;

    memcpy(&width, header.width, 2);
    memcpy(&height, header.height, 2);

    fwrite(&header, sizeof(TGAHeader), 1, output);

    Image outImg;

    outImg.header = header;
    outImg.height = height;
    outImg.width = width;
    outImg.pixels = load_pixels(header, img);

    fwrite(outImg.pixels, sizeof(RGBPixel), outImg.width * outImg.height, output);

    // Free allocated memory
    fclose(output);
    fclose(img);

    for (size_t i = 0; i < top + bottom; i++)
        free(str[i]);
    free(str);

    for (int i = 0; i < 26; i++)
        fclose(letters[i]);

    return 0;
}
