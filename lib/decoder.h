#ifndef _DECODER_H_
#define _DECODER_H_

void decoder_input(const char* input);
__attribute__((weak)) void decoder_callback(const char* cmd, const char* arg1, const char* arg2);

#endif /*_DECODER_H_*/
