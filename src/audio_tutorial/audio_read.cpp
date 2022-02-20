
#include <math.h> 

#include "audio_read.hpp"
/**
 * @brief 
 * reference: https://gist.github.com/csukuangfj/c1d1d769606260d436f8674c30662450
 */

//! Byte swap short
int16_t swap_int16( int16_t val ) 
{
    return (val << 8) | ((val >> 8) & 0xFF);
}

void save_wav(std::string in_file, std::string out_wave){
    static_assert(sizeof(wav_hdr) == 44, "");
    std::string in_name = in_file; // raw pcm data without wave header
    std::ifstream in(in_name, std::ifstream::binary);

    uint32_t fsize = in.tellg();
    in.seekg(0, std::ios::end);
    fsize = (uint32_t)in.tellg() - fsize;
    in.seekg(0, std::ios::beg);

    std::cout <<"file size: " <<fsize <<std::endl;

    wav_hdr wav;
    wav.ChunkSize = fsize + sizeof(wav_hdr) - 8;
    wav.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;

    std::ofstream out(out_wave, std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char *>(&wav), sizeof(wav));
    if(out.good()){
        std::cout << "out file is good" << std::endl;
    }

    int16_t d;
    int16_t swapped;

    for (int i = 0; i < (fsize/sizeof(int16_t)); ++i) {
        // TODO: read/write in blocks
        in.read(reinterpret_cast<char *>(&d), sizeof(int16_t));
        // swapped = swap_int16(d);
        // std::cout << d << std::endl;
        // std::cout << swapped << std::endl;
        out.write(reinterpret_cast<char *>(&d), sizeof(int16_t));

    }
    out.close();
    std::cout << "save to the file" <<std::endl;

}

std::vector<char> read_bytes_from_file(char const* filename)
{
    
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    
    if(!(ifs.is_open())){
        
        std::cout << "Unable to open file"; 
        return std::vector<char>{};
    }

    std::ifstream::pos_type pos = ifs.tellg();

    if (pos == 0) {
        return std::vector<char>{};
    }

    std::vector<char>  result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);
    return result;    
}

void convert_bytes_2_int16(std::vector<char> in_bytes){
    int length = in_bytes.size();
    std::cout << "input length: " << length << std::endl;

    std::cout << "samples: " << length/sizeof(int16_t) << std::endl;

    
    for(int i=0 ; i <= length/sizeof(int16_t); i ++){
        int16_t value = ((int16_t)(in_bytes[i*2 ]) << 8) + ((int16_t)in_bytes[i*2 + 1]); //big endian
        // int16_t value = ((int16_t)(in_bytes[i*2 + 1 ]) << 8) + ((int16_t)in_bytes[i*2]); //small endian
        std::cout << value << std::endl;

    }
}

void read_bytes(char const* filename){
    std::ifstream ifs(filename, std::ios::binary);
    char b;
    if (ifs.is_open())
    {
        while (ifs.good())
        {
          ifs.read(&b, 1);
          std::cout << b << std::endl;
        }
        ifs.close();
    }
    else 
    {  
        std::cout << "Unable to open file"; 
    }
}

void write_file(){
    std::string out = "/home/ycsheng/disk3T/temp/test.dat";
    std::ofstream outfile(out, std::ios::out | std::ios::binary);

    char buffer[4]{0x00, 0x01, 0x02, 0x03};
    outfile.write( buffer, sizeof( buffer ) );
    if(outfile.good()){
        std::cout << "out file is good" << std::endl;
    }
}

template <typename Word>
std::ostream& write_word( std::ostream& outs, Word value, unsigned size = sizeof( Word ) )
{
    for (; size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
    return outs;
}

void generate_wave_sound(){
    std::ofstream f( "/home/ycsheng/disk3T/temp/sinexample", std::ios::out | std::ios::binary );

    // Write the file headers
    f << "RIFF----WAVEfmt ";     // (chunk size to be filled in later)
    write_word( f,     16, 4 );  // no extension data
    write_word( f,      1, 2 );  // PCM - integer samples
    // write_word( f,      2, 2 );  // two channels (stereo file)
    write_word( f,      1, 2 );  // one channels (stereo file)
    // write_word( f,  44100, 4 );  // samples per second (Hz)
    write_word( f,  16000, 4 );  // samples per second (Hz)
    // write_word( f, 176400, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    write_word( f, 32000, 4 );  // (Sample Rate * BitsPerSample * Channels) / 8
    // write_word( f,      4, 2 );  // data block size (size of two integer samples, one for each channel, in bytes)
    write_word( f,      2, 2 );  // data block size (size of one integer samples, mono)
    write_word( f,     16, 2 );  // number of bits per sample (use a multiple of 8)

    // Write the data chunk header
    size_t data_chunk_pos = f.tellp();
    f << "data----";  // (chunk size to be filled in later)
    
    // Write the audio samples
    // (We'll generate a single C4 note with a sine wave, fading from left to right)
    constexpr double two_pi = 6.283185307179586476925286766559;
    constexpr double max_amplitude = 32760;  // "volume"

    // double hz        = 44100;    // samples per second
    double hz        = 16000;    // samples per second
    double frequency = 261.626;  // middle C
    double seconds   = 2.5;      // time

    int N = hz * seconds;  // total number of samples
    for (int n = 0; n < N; n++)
    {
        double amplitude = (double)n / N * max_amplitude;
        double value     = sin( (two_pi * n * frequency) / hz );
        write_word( f, (int)(                 amplitude  * value), 2 );
        // write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
    }
    
    // (We'll need the final file size to fix the chunk sizes above)
    size_t file_length = f.tellp();

    // Fix the data chunk header to contain the data size
    f.seekp( data_chunk_pos + 4 );
    write_word( f, file_length - data_chunk_pos + 8 );

    // Fix the file header to contain the proper RIFF chunk size, which is (file size - 8) bytes
    f.seekp( 0 + 4 );
    write_word( f, file_length - 8, 4 ); 

}

void generate_sin_wave(){

    
    double hz        = 16000;    // samples per second
    double frequency = 261.626;  // middle C
    double seconds   = 2.5;      // time

    int N = hz * seconds;  // total number of samples

    uint32_t fsize = N*2;

    wav_hdr wav;
    wav.ChunkSize = fsize + sizeof(wav_hdr) - 8;
    wav.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;

    std::ofstream out("/home/ycsheng/disk3T/temp/sin2", std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char *>(&wav), sizeof(wav));

    constexpr double two_pi = 6.283185307179586476925286766559;
    constexpr double max_amplitude = 32760;  // "volume"

    
    for (int n = 0; n < N; n++)
    {
        double amplitude = (double)n / N * max_amplitude;
        double value     = sin( (two_pi * n * frequency) / hz );
        write_word( out, (int)(                 amplitude  * value), 2 );
        std::cout << (int)(amplitude  * value) << std::endl;
        // write_word( f, (int)((max_amplitude - amplitude) * value), 2 );
    }

    if(out.good()){
        std::cout << "out file is good" << std::endl;
    }
    out.close();

    std::cout << "output end" << std::endl;

}
