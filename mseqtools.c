#include "mseq.h"

/* This main entry file was rewritten after being inspired by the samtools codebase. */

static int usage(FILE *out)
{
	fprintf(out, "\n");
	fprintf(out, "Program: %s (Sequence manipulation toolkit)\n", PROGRAM);
    fprintf(out, "Version: %s\n", PACKAGE_VERSION);
	fprintf(out, "\n");
	fprintf(out, "Usage:   %s <command> [options]\n\n", PROGRAM);
	fprintf(out, "Commands:\n");
	fprintf(out, " -- Subsetting\n");
	fprintf(out, "     subset         subset sequences based on a given list\n");
	fprintf(out, "\n");
	return 1;
}

int main(int argc, char* argv[]) {

	if (argc < 2) return usage(stderr);

	     if (strcmp(argv[1], "subset"    ) == 0) return mseq_subset_main  (argc-1, argv+1);
	else if (strcmp(argv[1], "help"      ) == 0) return usage(stdout);
	else {
		fprintf(stderr, "[mseqtools] unrecognized command '%s'\n", argv[1]);
		usage(stderr);
		return 1;
	}

	return 0;
}
