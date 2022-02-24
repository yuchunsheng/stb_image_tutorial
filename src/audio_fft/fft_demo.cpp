// https://github.com/LinnesLab/KickFFT/blob/master/examples/EXAMPLE01_Basic/EXAMPLE01_Basic.ino
#include <cstdint>
#include <iostream>
#include <vector>
#include <complex>
#include <iterator>
#include <cmath>


#include "KickFFT.h"
#include "kiss_fftr.h"
#include "pocketfft_hdronly.h"

void kickfft_demo(){
    const uint16_t samples = 128;
    //data is sampled every 42 milliseconds
    //the input signal is a simulated photoplethysmogram used to measure
    //heart rate. Each major peak is a new heart beat. The smaller peak is a
    //dicrotic notch which is generated when the aortic valve closes.
    const int16_t input[] = {773, 702, 515, 389, 370, 447, 554, 601, 561, 492, 455, 458, 480, 497, 545, 724, 801, 651, 460, 370, 396, 494, 579, 570, 507, 450, 433, 449, 480, 499, 500, 591, 756, 736, 548, 396, 356, 416, 522, 577, 549, 479, 436, 430, 455, 485, 502, 504, 496, 570, 737, 731, 540, 391, 362, 436, 539, 580, 543, 471, 428, 427, 450, 473, 486, 492, 485, 471, 486, 635, 748, 639, 455, 354, 363, 461, 560, 577, 518, 463, 443, 458, 482, 503, 521, 515, 499, 585, 735, 710, 536, 402, 368, 422, 520, 584, 551, 487, 444, 433, 448, 478, 496, 502, 505, 595, 753, 695, 514, 383, 366, 433, 529, 584, 562, 498, 447, 437, 454, 479, 494, 500, 530, 681, 752, 622, 450, 366, 384, 468, 557, 584, 534, 469, 435, 438, 464, 495, 517, 526, 634, 777, 730, 544, 402, 366, 424, 528, 602, 574, 499, 450, 440, 457, 481, 500, 520, 658, 781, 678, 485, 374, 374, 447, 547, 599, 563, 491, 442, 439, 459, 480, 495, 567, 742, 768, 599, 421, 350, 377, 481, 574, 590, 528, 458, 430, 438, 464, 488, 510, 640, 776, 689, 502, 379, 363, 437, 546, 605, 581, 507, 452, 438, 455, 478, 504, 633, 790, 740, 541, 390, 356, 418, 520, 588, 573, 506, 450, 430, 444, 472, 581, 770, 764, 558, 383, 327, 377, 477, 564, 573, 514, 452, 425, 428, 449, 556, 752, 762, 575, 398, 337, 385, 496, 595, 590, 522, 460, 440, 451, 484, 650, 810, 723, 521, 389};
    const float Fs = 23.8; //Hz

    uint32_t mag[samples] = {0};
    uint16_t startIndex = 0;
    uint16_t endIndex = 0;
    KickFFT<int16_t>::fft(Fs, 0, Fs/2, samples, input, mag, startIndex, endIndex);


    //Print to Serial Monitor and copy and paste
    //into a .csv file to display in Excel
    std::cout << ("Freq(Hz),Magnitude") << std::endl; //Use SerialUSB for SparkFun SAMD21 boards
    for(uint16_t i = startIndex; i < endIndex; i++)
    {
        //Peak should be around 1.3 Hz or so
        
        std::cout <<(i*Fs/samples); //Use SerialUSB for SparkFun SAMD21 boards
        std::cout <<(","); //Use SerialUSB for SparkFun SAMD21 boards
        std::cout <<(mag[i]); //Use SerialUSB for SparkFun SAMD21 boards
        std::cout <<std::endl; //Use SerialUSB for SparkFun SAMD21 boards
    }

    //Print the Raw Signal
    std::cout <<("Time(ms),PPG")<< std::endl; //Use SerialUSB for SparkFun SAMD21 boards
    for(uint16_t i = 0; i < samples; i++)
    {
        std::cout <<(i*1/Fs); //Use SerialUSB for SparkFun SAMD21 boards
        std::cout <<(","); //Use SerialUSB for SparkFun SAMD21 boards
        std::cout <<(input[i]); //Use SerialUSB for SparkFun SAMD21 boards
        std::cout << std::endl; //Use SerialUSB for SparkFun SAMD21 boards
    }

    


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

inline double simple_drand()
  {
  constexpr double norm = 1./RAND_MAX;
  return rand()*norm;
  }

template<typename T> void crand(std::vector<std::complex<T>> &v)
  {
  for (auto & i:v)
    i = std::complex<T>(simple_drand()-0.5, simple_drand()-0.5);
  }

template<typename T1, typename T2> long double l2err
  (const std::vector<T1> &v1, const std::vector<T2> &v2)
  {
  long double sum1=0, sum2=0;
  for (size_t i=0; i<v1.size(); ++i)
    {
    long double dr = v1[i].real()-v2[i].real(),
                di = v1[i].imag()-v2[i].imag();
    long double t1 = sqrt(dr*dr+di*di), t2 = abs(v1[i]);
    sum1 += t1*t1;
    sum2 += t2*t2;
    }
  return sqrt(sum1/sum2);
  }


void pocketfft_demo(){
    for (size_t len=1; len<8192; ++len)
    {
        pocketfft::shape_t shape{len};
        pocketfft::stride_t stridef(shape.size()), strided(shape.size()), stridel(shape.size());
        size_t tmpf=sizeof(std::complex<float>),
            tmpd=sizeof(std::complex<double>),
            tmpl=sizeof(std::complex<long double>);
        for (int i=shape.size()-1; i>=0; --i)
        {
            stridef[i]=tmpf;
            tmpf*=shape[i];
            strided[i]=tmpd;
            tmpd*=shape[i];
            stridel[i]=tmpl;
            tmpl*=shape[i];
        }
        size_t ndata=1;
        for (size_t i=0; i<shape.size(); ++i)
            ndata*=shape[i];

        std::vector<std::complex<float>> dataf(ndata);
        std::vector<std::complex<double>> datad(ndata);
        std::vector<std::complex<long double>> datal(ndata);
        crand(dataf);
        for (size_t i=0; i<ndata; ++i)
        {
            datad[i] = dataf[i];
            datal[i] = dataf[i];
        }
        pocketfft::shape_t axes;
        for (size_t i=0; i<shape.size(); ++i)
        axes.push_back(i);
        auto resl = datal;
        auto resd = datad;
        auto resf = dataf;
        pocketfft::c2c(shape, stridel, stridel, axes, pocketfft::FORWARD,
            datal.data(), resl.data(), 1.L);
        pocketfft::c2c(shape, strided, strided, axes, pocketfft::FORWARD,
            datad.data(), resd.data(), 1.);
        pocketfft::c2c(shape, stridef, stridef, axes, pocketfft::FORWARD,
            dataf.data(), resf.data(), 1.f);
    //    c2c(shape, stridel, stridel, axes, POCKETFFT_BACKWARD,
    //        resl.data(), resl.data(), 1.L/ndata);
        std::cout << l2err(resl, resf) << std::endl;
    }
}