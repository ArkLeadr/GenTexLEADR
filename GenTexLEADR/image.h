#ifndef IMAGE_H
#define IMAGE_H
#include<iostream>
class image
{
public:
    image(int h, int w);
    float getValue(int h,int w){return m_img[h*m_width +w];}
    void setValue(float val, int h, int w){ m_img[h*m_width +w] = val;}
    void toGray( unsigned char* data);
    float operationConv(const float *filtre,int i, int j, int k, int l, int widthFiltre);
    float operator[](std::size_t idx) const { return m_img[idx]; }
    void imgradient(image*imgGradX, image*imgGradY);

int m_width;
int m_height;
float *m_img;
};

void clamp(int *i, int min, int max);
#endif // IMAGE_H
