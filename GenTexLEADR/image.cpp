#include "image.h"

image::image(int h,int w):m_width(w),m_height(h)
{
    m_img = (float*)malloc(m_width*m_height*sizeof(float));
}

void  image::toGray(unsigned char *data)
{
    int cpt = 0;
    for(int i = 0; i < m_width*m_height*3;i+=3)
    {
        m_img[cpt] = 0.2125*data[i] + 0.7154*data[i+1] +0.0721*data[i+2];
        m_img[cpt]/=255.0f;
        cpt++;
    }
}

float image::operationConv(const float *filtre, int i, int j, int k, int l, int widthFiltre)
{
    clamp(&j,0,m_width-1);
    clamp(&i,0,m_height-1);
    return m_img[i*m_width+j]*filtre[k *widthFiltre +l];
}

void clamp(int *i, int min, int max)
{
    if(*i<min)
        *i=min;
    if(*i>max)
        *i=max;
}

void image::imgradient(image*imgGradX,image*imgGradY){
    float filtreSY[9] = {-1.0f,-2.0f,-1.0f,
                         0.0f,0.0f,0.0f,
                         1.0f,2.0f,1.0f,};

    float filtreSX[9] = {    -1.0f,0.0f,1.0f,
                             -2.0f,0.0f,2.0f,
                             -1.0f,0.0f,1.0f,};
    float sumX = 0;
    float sumY = 0;
    //miroir
    for(int i = 0; i < m_height;i++)
    {
        for(int j = 0; j < m_width;j++)
        {
            float valX =
                    operationConv(filtreSX,i-1,j-1,0,0,3)
                    + operationConv(filtreSX,i-1,j+1,0,2,3)

                    + operationConv(filtreSX,i,j-1,1,0,3)
                    + operationConv(filtreSX,i,j+1,1,2,3)

                    + operationConv(filtreSX,i+1,j-1,2,0,3)
                    + operationConv(filtreSX,i+1,j+1,2,2,3);

            float valY =
                    operationConv(filtreSY,i-1,j-1,0,0,3)
                    + operationConv(filtreSY,i-1,j,  0,1,3)
                    + operationConv(filtreSY,i-1,j+1,0,2,3)

                    + operationConv(filtreSY,i+1,j-1,2,0,3)
                    + operationConv(filtreSY,i+1,j,  2,1,3)
                    + operationConv(filtreSY,i+1,j+1,2,2,3);

            imgGradX->setValue(valX,i,j);
            imgGradY->setValue(valY,i,j);
            sumX +=valX;
            sumY +=valY;

        }

    }
    printf("%f %f  \n",sumX,sumY);
}
