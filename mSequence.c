#include <string.h>
#include <ctype.h>
#include "mSequence.h"
#include "mCommon.h"

/******************************
 *  Seq writing  functions    *
 ******************************/

/* Write normally using fprintf */

void mWriteFixedLengthFasta(FILE *stream, size_t length, char *string, int columns) {
	size_t  i;
	size_t  full_lines = length - length%columns;
	for (i=0; i < full_lines; i+=columns) {
		fprintf(stream, "%.*s", columns, string+i);
		fprintf(stream, "\n");
	}
	for (i=full_lines; i < length; i++) {
		fprintf(stream, "%c", string[i]);
	}
	if (length%columns != 0) fprintf(stream, "\n");
}

void mWriteSeqN(FILE *stream, kseq_t *seq, int columns) {
	if (seq->qual.l) {
		fprintf(stream, "@%s", seq->name.s);
		if (seq->comment.l) {
			fprintf(stream, " %s", seq->comment.s);
		}
		fprintf(stream, "\n");
		fprintf(stream, "%s\n", seq->seq.s);
		fprintf(stream, "+\n");
		fprintf(stream, "%s\n", seq->qual.s);
	} else {
		fprintf(stream, ">%s\n", seq->name.s);
		mWriteFixedLengthFasta(stream, seq->seq.l, seq->seq.s, columns);
	}
}

void mWriteSeq(FILE *stream, kseq_t *seq) {
	mWriteSeqN(stream, seq, FASTA_COLUMNS);
}

/* Write using libz */

void mWriteFixedLengthFastaGzip(gzFile stream, size_t length, char *string, int columns) {
	size_t  i;
	size_t  full_lines = length - length%columns;
	for (i=0; i < full_lines; i+=columns) {
		gzprintf(stream, "%.*s", columns, string+i);
		gzprintf(stream, "\n");
	}
	for (i=full_lines; i < length; i++) {
		gzprintf(stream, "%c", string[i]);
	}
	if (length%columns != 0) gzprintf(stream, "\n");
}

void mWriteSeqNGzip(gzFile stream, kseq_t *seq, int columns) {
	if (seq->qual.l) {
		gzprintf(stream, "@%s", seq->name.s);
		if (seq->comment.l) {
			gzprintf(stream, " %s", seq->comment.s);
		}
		gzprintf(stream, "\n");
		gzprintf(stream, "%s\n", seq->seq.s);
		gzprintf(stream, "+\n");
		gzprintf(stream, "%s\n", seq->qual.s);
	} else {
		gzprintf(stream, ">%s\n", seq->name.s);
		mWriteFixedLengthFastaGzip(stream, seq->seq.l, seq->seq.s, columns);
	}
}

void mWriteSeqGzip(gzFile stream, kseq_t *seq) {
	mWriteSeqNGzip(stream, seq, FASTA_COLUMNS);
}
