#ifndef M_SEQ_H
#define M_SEQ_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <regex.h>
#include <zlib.h>
#include <argtable2.h>
#include "zoeTools.h"
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

/* Helper functions */

zoeHash mReadIntegerHash(const char *filename);
void    mEmptyZoeHash(zoeHash hash);

void mPrintHelp (const char *subprogram, void **argtable);
void mPrintCommandLine(FILE *output, int argc, char *argv[]);
void mPrintCommandLineGzip(gzFile output, int argc, char *argv[]);

/* Main functions for the subprograms */

int mseq_filter_main(int argc, char* argv[]);

#endif
