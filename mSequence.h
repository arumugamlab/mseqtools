#ifndef _M_SEQUENCE_H_
#define _M_SEQUENCE_H_

#include "mseq.h"

#define FASTA_COLUMNS 80
#define FASTA_COLUMNS_STR "80"

void mWriteSeq(FILE *stream, kseq_t *seq);
void mWriteSeqN(FILE *stream, kseq_t *seq, int columns);
void mWriteFixedLengthFasta(FILE *stream, size_t length, char *string, int columns);

void mWriteSeqGzip(gzFile stream, kseq_t *seq);
void mWriteSeqNGzip(gzFile stream, kseq_t *seq, int columns);
void mWriteFixedLengthFastaGzip(gzFile stream, size_t length, char *string, int columns);

#endif
