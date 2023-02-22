#ifndef SALTWATER_H
#define SALTWATER_H

#include <3ds.h>

// Saltwater version

#define STR(X) #X
#define STRC(X) STR(X)

#define HEX2(Y) 0x##Y
#define HEX(Y) HEX2(Y)

#ifdef RELEASE

#define VERSION_MAJOR 0
#define VERSION_MINOR 2
#define VERSION_PATCH 0

#define VERSION "v" STRC(VERSION_MAJOR) "." STRC(VERSION_MINOR) "." STRC(VERSION_PATCH)

#else

#define VERSION "rev " STRC(COMMIT)
#define COMMIT_NUM HEX(COMMIT)

#endif

// Params struct
extern "C" {
    struct SaltwaterParams {
        u16 barista;
        bool rhmpatch;
        bool plgldr;
        u32 null[31];
    };
}

#endif