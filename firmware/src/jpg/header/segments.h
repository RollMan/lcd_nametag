#ifndef __SEGMENTS_H__
#define __SEGMENTS_H__
#include "../decode.h"
int decode_application_default_header(uint8_t const **buf,
                                      struct jpgdec_state_t *const state);
#endif
