#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
    std::cout << "Hello, STB_Image" << std::endl;

    string inputPath = "/home/ycsheng/disk220G/play_ground/16329372_opencv.jpg";
    int iw, ih, n;
    
    // Loading Pictures to Get Wide, High and Color Channel Information
    unsigned char *idata = stbi_load(inputPath.c_str(), &iw, &ih, &n, 0);

    int ow = iw / 2;
    int oh = ih / 2;
    // auto *odata = (unsigned char *) malloc(ow * oh * n);
    auto* odata = new unsigned char[ow*oh*n];
    
    // Change picture size
    stbir_resize(idata, iw, ih, 0, odata, ow, oh, 0, STBIR_TYPE_UINT8, n, STBIR_ALPHA_CHANNEL_NONE, 0,
                 STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
                 STBIR_FILTER_BOX, STBIR_FILTER_BOX,
                 STBIR_COLORSPACE_SRGB, nullptr
    );

    string outputPath = "/home/ycsheng/temp/output.jpg";
    // Write pictures
    stbi_write_jpg(outputPath.c_str(), ow, oh, n, odata, 0);

    stbi_image_free(idata);
    stbi_image_free(odata);
    return 0;
}