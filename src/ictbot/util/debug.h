#ifndef DEBUG_H
#define DEBUG_H

#define PRINT_ARR(arr, str)                     \
    printf("[%s] recv [", str);                 \
    for (uint8_t i = 0; i < LENGTH(arr); i++) { \
        printf("0x%x", arr[i]);                 \
        if (i < LENGTH(arr) - 1) {              \
            printf(", ");                       \
        }                                       \
        else {                                  \
            printf("]");                        \
        }                                       \
    }                                           \
    printf("\n");                               \

#endif
