//
// Created by yons on 2020/12/24.
//

#ifndef SIMPLE_PYVM_DUMPHEX_HPP
#define SIMPLE_PYVM_DUMPHEX_HPP
#define __is_print(ch) ((unsigned int)((ch) - ' ')+' ')

#include <stdio.h>

class dumpHex {

public:
/**
 * dump_hex
 *
 * @brief dump data in hex format
 *
 * @param buf: User buffer
 * @param size: Dump data size
 * @param number: The number of outputs per line
 *
 * @return void
*/
    static void dump_hex(const unsigned int *buf, unsigned int size, unsigned int number) {
        int i, j;
        for (i = 0; i < 16; i++) {
            printf("%08X: ", i);
            for (j = 0; j < 16; j++) {
                if (j % 8 == 0) {
                    printf(" ");
                }
                if (i + j)
                    printf("%02X ", buf[i + j]);
                else
                    printf("   ");
            }
            printf(" ");

            for (j = 0; j < 16; j++) {
                if (i + j) {
                    printf("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
                }
            }
            printf("\n");
        }
        return;
    }
};


#endif //SIMPLE_PYVM_DUMPHEX_HPP
