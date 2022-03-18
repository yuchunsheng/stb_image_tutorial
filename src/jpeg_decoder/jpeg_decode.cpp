#include <iostream>
#include <fstream>
#include <string.h>

#include "jpeg_decode.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"


/* Bytes per pixel of image output */
#define N_BPP (3 - JD_FORMAT)
/* Session identifier for input/output functions (name, members and usage are as user defined) */
typedef struct {
    std::ifstream *fp;               /* Input stream */
    unsigned int file_size;
    uint8_t *fbuf;          /* Output frame buffer */
    unsigned int wfbuf;     /* Width of the frame buffer [pix] */
} IODEV;

uint16_t jd_input(    /* Returns number of bytes read (zero on error) */
    JDEC* jd,       /* Decompression object */
    uint8_t* buff,  /* Pointer to the read buffer (null to remove data) */
    uint16_t len    /* Number of bytes to read/remove */
)
{
    IODEV* devid = (IODEV*)jd->device;   /* Session identifier (5th argument of jd_prepare function) */
    int bytes_left = devid->file_size - devid->fp->tellg();
    if(bytes_left < len) len = bytes_left;

    if (buff) { /* Raad data from imput stream */
      // Read into buffer, pointer moved as well
      devid->fp->read(reinterpret_cast<char *>(buff), len);
    //   std::cout << "current position in jpeg =" << fin.tellg() << std::endl;
    }
    else {  /* Remove data from input stream */
        // std::cout << "buf is null" << std::endl;
        // Buffer is null, so skip data by moving pointer
        int offset = (len + static_cast<int>(devid->fp->tellg()));
        devid->fp->seekg(offset, std::ios_base::beg);
    } 
    // std::cout << "len = " << len << std::endl;
    return len;
}

uint16_t jd_output(
    JDEC* jd,       /* Decompression object */
    void* bitmap,   /* Bitmap data to be output */
    JRECT* rect     /* Rectangular region of output image */)
{
    // std::cout << "inside jd_output !!! " << std::endl;
    IODEV *dev = (IODEV*)jd->device;   /* Session identifier (5th argument of jd_prepare function) */
    uint8_t *src, *dst;
    uint16_t y, bws;
    unsigned int bwd;

    /* Put progress indicator */
    if (rect->left == 0) {
        std::cout<< ((rect->top << jd->scale) * 100UL / jd->height) << " percents" << std::endl;
    }

    // std::cout << "x left = " << rect->left <<"x right = " << rect->right <<std::endl;
    // std::cout << "y top = "<< rect->top << "y bottom = " << rect->bottom << std::endl;
    /* Copy the output image rectanglar to the frame buffer */
    src = (uint8_t*)bitmap;
    dst = dev->fbuf + N_BPP * (rect->top * dev->wfbuf + rect->left);  /* Left-top of destination rectangular */
    bws = N_BPP * (rect->right - rect->left + 1);     /* Width of output rectangular [byte] */
    bwd = N_BPP * dev->wfbuf;                         /* Width of frame buffer [byte] */
    for (y = rect->top; y <= rect->bottom; y++) {
        memcpy(dst, src, bws);   /* Copy a line */
        src += bws; dst += bwd;  /* Next line */
    }

    return 1;
}


void tjpg_test(){
    std::string inputPath = "/home/ycsheng/disk220G/play_ground/16329372_opencv.jpg";
    // Must align workspace to a 32 bit boundary
    uint8_t workspace[TJPGD_WORKSPACE_SIZE] __attribute__((aligned(4)));
    JDEC decoder;
    JRESULT result;

    int jpg_scale = 0;
    IODEV devid;      /* Session identifier */

    std::ifstream fin(inputPath, std::ios::in | std::ios::binary);
    devid.fp = &fin;
    // Check how many bytes are available
    fin.seekg(0, std::ios::end);
    devid.file_size = fin.tellg();
    fin.seekg(0, std::ios::beg);

    result = jd_prepare(&decoder, jd_input, workspace, TJPGD_WORKSPACE_SIZE, &devid);
    if (JDR_OK == result) {
        std::cout <<"Image size is " << decoder.width << ", " << decoder.height << std::endl;
        std::cout << (TJPGD_WORKSPACE_SIZE - decoder.sz_pool) << " bytes of work ares is used." << std::endl;

        /* Initialize output device */
        devid.fbuf = (uint8_t*)malloc(N_BPP * decoder.width * decoder.height);; /* Create frame buffer for output image */
        devid.wfbuf = decoder.width;

        result = jd_decomp(&decoder, jd_output, jpg_scale);
    
        if (result == JDR_OK) {
            /* Decompression succeeded. You have the decompressed image in the frame buffer here. */
            std::cout <<("Decompression succeeded.") << std::endl;
            std::string outputPath = "/home/ycsheng/temp/output.bmp";
            // Write pictures
            int res = stbi_write_bmp(outputPath.c_str(), decoder.width, decoder.height, 3, devid.fbuf);
            std::cout << "stb_image result = " << res << std::endl;

        } else {
            std::cout <<"jd_decomp() failed (rc="<< result <<")"<< std::endl;
        }
        free(devid.fbuf);    /* Discard frame buffer */

    }else{
        std::cout << "jd_prepare failed" << std::endl;
    };
    fin.close();
    // fclose(fp);
}