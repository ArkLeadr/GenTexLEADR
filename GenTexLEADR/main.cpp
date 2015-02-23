#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "IL/il.h"
#include "fichier.h"
#include "image.h"



int main(int argc, char *argv[])
{
    ilInit();
    if(argc < 2)
    {
        printf("Il n'y pas de fichier en entrée.\n");
        exit(-1);
    }
    const char* filename = argv[1];

    unsigned int m_width;
    unsigned int m_height;
    unsigned char* m_data;
    unsigned int m_bytesPerPixel;
    ILuint m_imageId;
    bool reversed = false;

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


    image imgGray(m_width,m_height);
    image imgGradX(m_width,m_height);
    image imgGradY(m_width,m_height);

    if (m_bytesPerPixel == 3)
        imgGray.fromRGB_toNormalizedGrayscale(m_data);
    else if (m_bytesPerPixel == 1)
        imgGray.fromGrayscale_toNormalizedGrayscale(m_data);

    imgGray.imgradient(&imgGradX,&imgGradY);

    //Ecriture Texture 1 x,y,xy,xx
    char* binaryFilename = (char*) malloc(strlen(filename)  + 1 + strlen("leadr") + 1);
    strcpy(binaryFilename, getFilenameWithoutExt(filename));
    strcat(binaryFilename, ".leadr");
    printf("\n%s\n", binaryFilename);

    FILE* fp = NULL;

    fp = fopen(binaryFilename, "wb");
    fwrite(&m_height, sizeof(int), 1, fp);
    fwrite(&m_width, sizeof(int), 1, fp);

    for(int i=0; i < m_height; i++)
    {
        for(int j=0;j < m_width; j++)
        {
            float tmp[4] = {imgGradX[i*m_width + j],
                            imgGradY[i*m_width + j],
                            imgGradX[i*m_width + j]*imgGradY[i*m_width + j],
                            imgGradX[i*m_width + j]*imgGradX[i*m_width + j]};

            fwrite(tmp, sizeof(float),4, fp);
        }
    }

//    fclose(fp);

    //Ecriture Texture 2 yy,disp,0,0
//    binaryFilename = (char*) malloc(strlen(filename) +1+ strlen("leadr2") + 1);
//    strcpy(binaryFilename, getFilenameWithoutExt(filename));
//    strcat(binaryFilename, ".leadr2");
//    printf("\n%s\n", binaryFilename);
//    fp = NULL;

//    fp = fopen(binaryFilename, "wb");
//    fwrite(&m_height, sizeof(int), 1, fp);
//    fwrite(&m_width, sizeof(int), 1, fp);

    for(int i=0; i < m_height; i++)
    {
        for(int j=0;j < m_width; j++)
        {
            float tmp[1] = {imgGradY[i*m_width + j]*imgGradY[i*m_width + j]};

            unsigned char disp = {(unsigned char)(imgGray[i*m_width + j] * 255.f)};

            fwrite(tmp, sizeof(float),1, fp);
            fwrite(&disp, sizeof(unsigned char),1, fp);
        }
    }

    fclose(fp);

    return 0;
}

