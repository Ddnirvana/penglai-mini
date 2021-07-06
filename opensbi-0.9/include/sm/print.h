#ifndef SM_PRINT_H
#define SM_PRINT_H

#include <sbi/sbi_console.h>

#ifdef PENGLAI_DEBUG
#define printm(...) sbi_printf(__VA_ARGS__)
#else
#define printm(...)
#endif

#endif
