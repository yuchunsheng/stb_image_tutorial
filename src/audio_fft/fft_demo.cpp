// https://github.com/LinnesLab/KickFFT/blob/master/examples/EXAMPLE01_Basic/EXAMPLE01_Basic.ino
#include <cstdint>
#include <iostream>
#include <vector>
#include <complex>
#include <iterator>

#include "KickFFT.h"
#include "kiss_fftr.h"

void kickfft_demo(){
    const uint16_t samples = 128;
    //data is sampled every 42 milliseconds
    //the input signal is a simulated photoplethysmogram used to measure
    //heart rate. Each major peak is a new heart beat. The smaller peak is a
    //dicrotic notch which is generated when the aortic valve closes.
    const int16_t input[] = {773, 702, 515, 389, 370, 447, 554, 601, 561, 492, 455, 458, 480, 497, 545, 724, 801, 651, 460, 370, 396, 494, 579, 570, 507, 450, 433, 449, 480, 499, 500, 591, 756, 736, 548, 396, 356, 416, 522, 577, 549, 479, 436, 430, 455, 485, 502, 504, 496, 570, 737, 731, 540, 391, 362, 436, 539, 580, 543, 471, 428, 427, 450, 473, 486, 492, 485, 471, 486, 635, 748, 639, 455, 354, 363, 461, 560, 577, 518, 463, 443, 458, 482, 503, 521, 515, 499, 585, 735, 710, 536, 402, 368, 422, 520, 584, 551, 487, 444, 433, 448, 478, 496, 502, 505, 595, 753, 695, 514, 383, 366, 433, 529, 584, 562, 498, 447, 437, 454, 479, 494, 500, 530, 681, 752, 622, 450, 366, 384, 468, 557, 584, 534, 469, 435, 438, 464, 495, 517, 526, 634, 777, 730, 544, 402, 366, 424, 528, 602, 574, 499, 450, 440, 457, 481, 500, 520, 658, 781, 678, 485, 374, 374, 447, 547, 599, 563, 491, 442, 439, 459, 480, 495, 567, 742, 768, 599, 421, 350, 377, 481, 574, 590, 528, 458, 430, 438, 464, 488, 510, 640, 776, 689, 502, 379, 363, 437, 546, 605, 581, 507, 452, 438, 455, 478, 504, 633, 790, 740, 541, 390, 356, 418, 520, 588, 573, 506, 450, 430, 444, 472, 581, 770, 764, 558, 383, 327, 377, 477, 564, 573, 514, 452, 425, 428, 449, 556, 752, 762, 575, 398, 337, 385, 496, 595, 590, 522, 460, 440, 451, 484, 650, 810, 723, 521, 389};
    const float Fs = 23.8; //Hz

    auto input_size = sizeof(input)/sizeof(input[0]);
    std::cout<< sizeof(input) <<" bytes  " <<input_size <<" array length" << std::endl;

    std::vector<float> inputf(input_size);
    for(int i = 0 ; i < input_size; i ++){
        inputf.push_back(static_cast<float>(input[i]));
    }

    //  for (int i = 0; i < inputf.size(); i++)
    //     std::cout << inputf[i] << std::endl;

    std::vector<std::complex<float>> vout(inputf.size());
    


}

void kissfft_demo(){
    std::cout << "kissfft" << std::endl;
    const int16_t input[] = {773, 702, 515, 389, 370, 447, 554, 601, 561, 492, 455, 458, 480, 497, 545, 724, 801, 651, 460, 370, 396, 494, 579, 570, 507, 450, 433, 449, 480, 499, 500, 591, 756, 736, 548, 396, 356, 416, 522, 577, 549, 479, 436, 430, 455, 485, 502, 504, 496, 570, 737, 731, 540, 391, 362, 436, 539, 580, 543, 471, 428, 427, 450, 473, 486, 492, 485, 471, 486, 635, 748, 639, 455, 354, 363, 461, 560, 577, 518, 463, 443, 458, 482, 503, 521, 515, 499, 585, 735, 710, 536, 402, 368, 422, 520, 584, 551, 487, 444, 433, 448, 478, 496, 502, 505, 595, 753, 695, 514, 383, 366, 433, 529, 584, 562, 498, 447, 437, 454, 479, 494, 500, 530, 681, 752, 622, 450, 366, 384, 468, 557, 584, 534, 469, 435, 438, 464, 495, 517, 526, 634, 777, 730, 544, 402, 366, 424, 528, 602, 574, 499, 450, 440, 457, 481, 500, 520, 658, 781, 678, 485, 374, 374, 447, 547, 599, 563, 491, 442, 439, 459, 480, 495, 567, 742, 768, 599, 421, 350, 377, 481, 574, 590, 528, 458, 430, 438, 464, 488, 510, 640, 776, 689, 502, 379, 363, 437, 546, 605, 581, 507, 452, 438, 455, 478, 504, 633, 790, 740, 541, 390, 356, 418, 520, 588, 573, 506, 450, 430, 444, 472, 581, 770, 764, 558, 383, 327, 377, 477, 564, 573, 514, 452, 425, 428, 449, 556, 752, 762, 575, 398, 337, 385, 496, 595, 590, 522, 460, 440, 451, 484, 650, 810, 723, 521, 389};
    
    auto input_size = sizeof(input)/sizeof(input[0]);
    std::vector<float> inputf(input_size);

    for(int i = 0 ; i < input_size; i ++){
        inputf.push_back(static_cast<float>(input[i]));
    }

    std::vector<std::complex<float>> vout(inputf.size());
    kiss_fft_cpx* out = reinterpret_cast<kiss_fft_cpx*>(&vout[0]);

    const float real1 = out[0].r;
    const float imag1 = out[0].i;
    std::cout << (real1 * real1) + (imag1 * imag1) << std::endl;

    kiss_fftr_cfg cfg = kiss_fftr_alloc(inputf.size(), /*inverse*/false, 0, 0);
    
    kiss_fftr(cfg, inputf.data(), out);
    const float real = out[0].r;
    const float imag = out[0].i;
    std::cout << (real * real) + (imag * imag) << std::endl;
    kiss_fftr_free(cfg);
}