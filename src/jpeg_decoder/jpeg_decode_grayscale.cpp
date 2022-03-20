#include <iostream>
#include <fstream>
#include <string.h>

#include "jpeg_decode_grayscale.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"


/* Bytes per pixel of image input */
#define N_BPP 3               //color
/* Session identifier for input/output functions (name, members and usage are as user defined) */
typedef struct {
    std::ifstream *fp;               /* Input stream */
    unsigned int file_size;
    uint8_t *fbuf;          /* Output frame buffer */
    unsigned int wfbuf;     /* Width of the frame buffer [pix] */
    int crop_width;
    int crop_height;
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

uint16_t jd_output_new(
    JDEC* jd,       /* Decompression object */
    void* bitmap,   /* Bitmap data to be output */
    JRECT* rect     /* Rectangular region of output image */)
{
    // std::cout << "inside jd_output !!! " << std::endl;
    IODEV *dev = (IODEV*)jd->device;   /* Session identifier (5th argument of jd_prepare function) */
    uint8_t *src, *dst;
    uint16_t x, y, bws;
    unsigned int bwd;

    src = (uint8_t*)bitmap;
    dst = dev->fbuf ;  /* Left-top of destination rectangular */

    int height = rect->bottom- rect->top;
    int width = rect->right - rect->left;

    int x_origin = rect->left;
    int y_origin = rect->top;
    uint8_t r, g, b;


    for (int mcu_row = 0; mcu_row <=height; mcu_row++){
        for (int mcu_col = 0; mcu_col <= width; mcu_col++) {
            // std::cout << "mcu_row =" << mcu_row << " mcu_col =" << mcu_col << std::endl;
            int src_index = 3 * (mcu_row *16 + mcu_col);
            r = *(src + src_index );
            g = *(src + src_index + 1);
            b = *(src + src_index + 2);

            int des_index = 3 * ((rect->top + mcu_row )*320 + rect->left + mcu_col);
            *(dst + des_index) = r;
            *(dst + des_index + 1)  = g;
            *(dst + des_index + 2) = b;



        }
    }

    

    return 1;
}

uint16_t jd_output_grayscale(
    JDEC* jd,       /* Decompression object */
    void* bitmap,   /* Bitmap data to be output */
    JRECT* rect     /* Rectangular region of output image */)
{
    // std::cout << "inside jd_output !!! " << std::endl;
    IODEV *dev = (IODEV*)jd->device;   /* Session identifier (5th argument of jd_prepare function) */
    uint8_t *src, *dst;
    uint16_t x, y, bws;
    unsigned int bwd;
    
    int start_x = (jd->width -dev->crop_width)/2;
    int end_x = start_x + dev->crop_width;

    int start_y = (jd->height - dev->crop_height)/2 ;
    int end_y = start_y + dev->crop_height ;

    uint16_t current_row = 0;
    uint16_t current_col = 0;

   
    /* Copy the output image rectanglar to the frame buffer */
    src = (uint8_t*)bitmap;
    dst = dev->fbuf ;  /* Left-top of destination rectangular */
    
    uint8_t r, g, b;

    int current_width = rect->right - rect->left + 1;

    for (y = rect->top; y <= rect->bottom ; y++) {
        //if y in the center cropping area
        current_col = 0;
        for(x=rect->left; x <= rect->right ; x++){
            if((x>start_x) && (x <end_x) && (y > start_y) && (y<end_y)){

                int current_index = N_BPP * (current_row*current_width  + current_col);

                r = *(src + current_index);
                g = *(src + current_index + 1);
                b = *(src + current_index +2);

                int current_out_index = ((y-start_y)* dev->crop_width + (x-start_x));
                // Convert to grayscale by calculating luminance
                // See https://en.wikipedia.org/wiki/Grayscale for magic numbers
                float gray_value = (0.2126 * r) + (0.7152 * g) + (0.0722 * b);
                // Convert to signed 8-bit integer by subtracting 128.
                // *(dst + current_out_index) = (gray_value -= 128);
                // gray_value -= 128;
                *(dst + current_out_index) = static_cast<uint8_t>(gray_value); 

            }
            current_col ++;
        }
        current_row ++;      
    }
    current_row = 0;

    return 1;
}



uint16_t jd_output(
    JDEC* jd,       /* Decompression object */
    void* bitmap,   /* Bitmap data to be output */
    JRECT* rect     /* Rectangular region of output image */)
{
    // std::cout << "inside jd_output !!! " << std::endl;
    IODEV *dev = (IODEV*)jd->device;   /* Session identifier (5th argument of jd_prepare function) */
    uint8_t *src, *dst;
    uint16_t x, y, bws;
    unsigned int bwd;
    
    int start_x = (320 -224)/2;
    int end_x = start_x + 224;

    int start_y = (240-224)/2 ;
    int end_y = start_y + 224 ;

    // std::cout << "start_x " << start_x << " end_x " << end_x << std::endl;
    // std::cout << "start_y " << start_y << " end_y " << end_y << std::endl;

    uint16_t current_row = 0;
    uint16_t current_col = 0;
    // uint16_t max_row = rect->bottom - rect->top ;
    // uint16_t max_col = rect->right - rect->left ;

    /* Put progress indicator */
    // if (rect->left == 0) {
    //     std::cout<< ((rect->top << jd->scale) * 100UL / jd->height) << " percents" << std::endl;
    // }

    // std::cout << "x left = " << rect->left <<"x right = " << rect->right <<std::endl;
    // std::cout << "y top = "<< rect->top << "y bottom = " << rect->bottom << std::endl;

   
    /* Copy the output image rectanglar to the frame buffer */
    src = (uint8_t*)bitmap;
    dst = dev->fbuf ;  /* Left-top of destination rectangular */
    
    uint8_t r, g, b;

    int current_width = rect->right - rect->left + 1;

    for (y = rect->top; y <= rect->bottom ; y++) {
        //if y in the center cropping area
        current_col = 0;
        for(x=rect->left; x <= rect->right ; x++){
            if((x>start_x) && (x <end_x) && (y > start_y) && (y<end_y)){

                int current_index = 3*(current_row*current_width  + current_col);

                r = *(src + current_index);
                g = *(src + current_index + 1);
                b = *(src + current_index +2);

                int current_out_index = ((y-start_y)*224 + (x-start_x));
                
                *(dst + current_out_index) = r;
                *(dst + current_out_index + 1) = g;
                *(dst + current_out_index + 2) = b;

            }
            current_col ++;
        }
        current_row ++;      
    }
    current_row = 0;

    return 1;
}



void tjpg_test(){
    std::string inputPath = "/home/ycsheng/temp/ov2640.jpg";
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

    devid.crop_width = 224;
    devid.crop_height = 224;

    result = jd_prepare(&decoder, jd_input, workspace, TJPGD_WORKSPACE_SIZE, &devid);
    if (JDR_OK == result) {
        std::cout <<"Image size is " << decoder.width << ", " << decoder.height << std::endl;
        std::cout << (TJPGD_WORKSPACE_SIZE - decoder.sz_pool) << " bytes of work ares is used." << std::endl;
        std::cout << "MCUs X = " << (int)decoder.msx << " MCUs Y = " << (int)decoder.msy << std::endl;

        /* Initialize output device */
        // devid.fbuf = (uint8_t*)malloc(N_BPP * decoder.width * decoder.height);; /* Create frame buffer for output image */
        // devid.wfbuf = decoder.width;
        devid.fbuf = (uint8_t*)malloc( devid.crop_width * devid.crop_height * 1);; /* Create frame buffer for output image */
        // devid.fbuf = (uint8_t*)malloc( 224 * 224 * 3);; /* Create frame buffer for output image */
        // devid.fbuf = (uint8_t*)malloc( 320 * 240 * 3);; /* Create frame buffer for output image */
        devid.wfbuf = decoder.width;

        // result = jd_decomp(&decoder, jd_output_new, jpg_scale);
        // result = jd_decomp(&decoder, jd_output, jpg_scale);
        result = jd_decomp(&decoder, jd_output_grayscale, jpg_scale);
        
        if (result == JDR_OK) {
            /* Decompression succeeded. You have the decompressed image in the frame buffer here. */
            std::cout <<("Decompression succeeded.") << std::endl;
             
            // Write pictures
            std::string outputPath = "/home/ycsheng/temp/output.bmp";
            // int res = stbi_write_bmp(outputPath.c_str(), 320, 240, 3, devid.fbuf);
            int res = stbi_write_bmp(outputPath.c_str(), 224, 224, 1, devid.fbuf);
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