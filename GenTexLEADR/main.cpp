#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "IL/il.h"
#include "fichier.h"
#include "image.h"




int main(void)
{
    ilInit();

    const char* filename = "wall002_hmap2_512x512.jpg";

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

    imgGray.toGray( m_data);
    imgGray.imgradient(&imgGradX,&imgGradY);

    //Ecriture Texture 1 x,y,xy,xx
    char* binaryFilename = (char*) malloc(strlen(filename)  + 1+strlen("leadr1") + 1);
    strcpy(binaryFilename, getFilenameWithoutExt(filename));
    strcat(binaryFilename, ".leadr1");
    printf("\n%s\n", binaryFilename);

    FILE* fp = NULL;

    fp = fopen(binaryFilename, "wb");
    fwrite(&m_height, sizeof(int), 1, fp);
    fwrite(&m_width, sizeof(int), 1, fp);

//    for(int i = m_height - 1; i >= 0; --i)
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

    fclose(fp);

    //Ecriture Texture 2 yy,disp,0,0
    binaryFilename = (char*) malloc(strlen(filename) +1+ strlen("leadr2") + 1);
    strcpy(binaryFilename, getFilenameWithoutExt(filename));
    strcat(binaryFilename, ".leadr2");
    printf("\n%s\n", binaryFilename);
    fp = NULL;

    fp = fopen(binaryFilename, "wb");
    fwrite(&m_height, sizeof(int), 1, fp);
    fwrite(&m_width, sizeof(int), 1, fp);
    printf("%d",sizeof(float));

//    for(int i = m_height - 1; i >= 0; --i)
    for(int i=0; i < m_height; i++)
    {
        for(int j=0;j < m_width; j++)
        {
            float tmp[4] = {imgGradY[i*m_width + j]*imgGradY[i*m_width + j],
                            imgGray[i*m_width + j],
                            0,
                            0};

            fwrite(tmp, sizeof(float),4, fp);
        }
    }

    fclose(fp);

    return 0;
}

