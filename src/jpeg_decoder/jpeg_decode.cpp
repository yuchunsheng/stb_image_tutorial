#include <iostream>
#include <fstream>

#include "jpeg_decode.h"

std::string inputPath = "/home/ycsheng/disk220G/play_ground/16329372_opencv.jpg";
std::ifstream fin(inputPath, std::ios::in | std::ios::binary);
uint32_t bytes_left = 0;

uint16_t jd_input(JDEC* jdec, uint8_t* buf, uint16_t len)
{
    
    std::cout << "insied jd_input !!!"<< "len = "<<len << std::endl;
    // uint32_t bytesLeft = 0;

    if (bytes_left < len) len = bytes_left;

    if (buf) {
      // Read into buffer, pointer moved as well
      fin.read(reinterpret_cast<char *>(buf), len);
      std::cout << "current position in jpeg =" << fin.tellg() << std::endl;
    }
    else {
        std::cout << "buf is null" << std::endl;
        // Buffer is null, so skip data by moving pointer
        int offset = (len + static_cast<int>(fin.tellg()));
        fin.seekg(offset, std::ios_base::beg);
    } 
    std::cout << "len = " << len << std::endl;
    return len;
}

int jd_output(JDEC* jdec, void* bitmap, JRECT* jrect)
{
    return 0;
}


void tjpg_test(){
    // Check how many bytes are available
    fin.seekg(0, std::ios::end);
    bytes_left= fin.tellg();
    std::cout << "bytes_left = " << bytes_left << std::endl;
    fin.seekg(0, std::ios_base::beg);

    // Must align workspace to a 32 bit boundary
    uint8_t workspace[TJPGD_WORKSPACE_SIZE] __attribute__((aligned(4)));
    // FILE *fp;
    JDEC decoder;
    JRESULT result;

    // sdcard_init();

    // fp = fopen("/sdcard/image.jpg", "rb");

    result = jd_prepare(&decoder, jd_input, workspace, TJPGD_WORKSPACE_SIZE, 0);
    if (JDR_OK == result) {
        // jd_decomp(&decoder, tjpgd_data_writer, 0);
        std::cout << "OK" << std::endl;
    };
    fin.close();
    // fclose(fp);
}