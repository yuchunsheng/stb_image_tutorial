#ifndef jpeg_decoder_h
#define jpeg_decoder_h

#include "tjpgdcnf.h"
#include "tjpgd.h"
uint16_t jd_input(JDEC* jdec, uint8_t* buf, uint16_t len);
uint16_t jd_output(JDEC* jdec, void* bitmap, JRECT* jrect);
void tjpg_test();

#endif