
// #include "std_image_tutorial.h"

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "std_image_tutorial.hpp"
#include "audio_read.hpp"

using namespace std;

int main() {
    // std_image_test();
    std::cout << "Hello From Main with switch" << std::endl;
    
    // std::vector<char> result = read_bytes_from_file("/home/ycsheng/disk3T/temp/audio_raw");
    // std::cout << result.size() << std::endl;

    // convert_bytes_2_int16(result);
    save_wav("/home/ycsheng/disk3T/temp/audio_raw", "/home/ycsheng/disk3T/temp/wavefile");
    // write_file();
    // generate_wave_sound();
    // generate_sin_wave();
    
    return 0;
}