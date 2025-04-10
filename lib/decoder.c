#include "decoder.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void decoder_input(const char* input)
{
    char buf[64];
    strncpy(buf, input, sizeof(buf));
    buf[sizeof(buf)-1] = '\0';

    char* cmd = strtok(buf, " ,\r\n");
    char* arg1 = strtok(NULL, " ,\r\n");
    char* arg2 = strtok(NULL, " ,\r\n");

    if (cmd) {
        decoder_callback(cmd, arg1, arg2);
    }
}
