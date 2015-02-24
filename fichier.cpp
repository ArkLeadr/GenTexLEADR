#include "fichier.h"

char* getFilenameWithoutExt(const char* filename) {
    const char *dot = strrchr(filename, '.');

    if(!dot || dot == filename) return "";

    size_t size = dot - filename;

    char* ret = (char*) malloc(size + 1);

    memcpy(ret, filename, size);
    ret[size] = 0;

    return ret;
}

char* getFilenameExt(const char* filename) {
    const char *dot = strrchr(filename, '.');

    if(!dot || dot == filename) return "";

    return strdup(dot + 1);
}
