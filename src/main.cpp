
// #include "std_image_tutorial.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "std_image_tutorial.hpp"
#include "audio_read.hpp"
#include "fft_demo.h"
#include "jpeg_decode.h"

using namespace std;
void check_endian(){
    uint32_t x = 0x12345678;
    const uint8_t* p = reinterpret_cast<const uint8_t*>(&x);
    std::cout <<std::hex << x << std::endl;

    std::cout<<std::hex << (int)p[0] << std::endl;
}


int main() {
    // std_image_test();
    std::cout << "Hello From Main with switch" << std::endl;
    tjpg_test();
    // 
    // std::vector<char> result = read_bytes_from_file("/home/ycsheng/disk3T/temp/audio_raw");
    // std::cout << result.size() << std::endl;

    // convert_bytes_2_int16(result);
    // save_wav("/home/ycsheng/disk3T/temp/audio_raw", "/home/ycsheng/disk3T/temp/wavefile");
    // write_file();
    // generate_wave_sound();
    // generate_sin_wave();
    // check_endian();
    // kissfft_demo();
    // kickfft_demo();
    // pocketfft_demo();
    return 0;
}

