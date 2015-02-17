#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "IL/il.h"


#include <iostream>


char* getFilenameWithoutExt(const char* filename) {
    const char *dot = strrchr(filename, '.');

    if(!dot || dot == filename) return "";

    size_t size = dot - filename;

    char* ret = (char*) malloc(size + 1);

    memcpy(ret, filename, size);
    ret[size] = 0;

    return ret;
}

char* getFilenameExt(const char* filename) {
    const char *dot = strrchr(filename, '.');

    if(!dot || dot == filename) return "";

    return strdup(dot + 1);
}


int main(void)
{
    ilInit();


    const char* filename = "wall002_hmap2_512x512.jpg";

    unsigned int m_width;
    unsigned int m_height;

    unsigned char* m_data;

    unsigned int m_bytesPerPixel;

    ILuint m_imageId;

    bool reversed = true;

     // The image name to return.
    ilGenImages(1, &m_imageId); // Grab a new image name.

    ilBindImage(m_imageId);

    ilEnable(IL_ORIGIN_SET);

    if (reversed)
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
    else
        ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    if (ilLoadImage(filename) != IL_TRUE) {
        std::cerr << "Error loading image from: " << filename << '\n';
        return false;
    }

    m_data = ilGetData();

    m_width = ilGetInteger(IL_IMAGE_WIDTH);
    m_height = ilGetInteger(IL_IMAGE_HEIGHT);

    m_bytesPerPixel = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);

    printf("%d  %d  %d\n", m_width, m_height, m_bytesPerPixel);

    printf("%d %d %d\n", m_data[0], m_data[1], m_data[2]);

    printf("Filename            : %s\n", filename);
    printf("Filename (no ext)   : %s\n", getFilenameWithoutExt(filename));
    printf("Extension           : %s\n", getFilenameExt(filename));

    char* binaryFilename = (char*) malloc(strlen(filename) + 1 + strlen("leadrshc") + 1);
    strcpy(binaryFilename, getFilenameWithoutExt(filename));
    strcat(binaryFilename, ".leadrshc");

    printf("\n%s\n", binaryFilename);

    FILE* fp = NULL;

    fp = fopen(binaryFilename, "wb");

//    fwrite(coeffs, sizeof(float), 9*3, fp);

    fclose(fp);


    return 0;
}

