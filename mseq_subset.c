#include "mCommon.h"
#include "mSequence.h"

#define subprogram "subset"

int mseq_subset_main(int argc, char* argv[]) {
	kseq_t *seq;
	FILE   *list_stream, *output;
	gzFile  input;
	char    line[LINE_MAX];
	int     status;
	int     i;
	int     window = FASTA_COLUMNS;
	int     exclude;
	int     pair;
	zoeHash keep;
	zoeTVec keys;
	char   *key;

	int              argcount = 0;
	int              nerrors;
	void           **argtable;

	struct arg_str  *in_file;
	struct arg_str  *out_file;
	struct arg_str  *list_file;
	struct arg_int  *arg_window;
	struct arg_lit  *arg_exclude;
	struct arg_lit  *arg_pair;
	struct arg_lit  *arg_uncompressed;
	struct arg_lit  *help;
	struct arg_end  *end;

	in_file             = arg_str1("i", "input",  "<file>",         "input fasta/fastq file");
	out_file            = arg_str1("o", "output", "<file>",         "output file (gzipped)");
	list_file           = arg_str1("l", "list",   "<file>",         "file containing list of fasta/fastq identifiers");
	arg_exclude         = arg_lit0("v", "exclude",                  "exclude sequences in this list (default: false)");
	arg_pair            = arg_lit0("p", "paired",                   "get both reads from a pair corresponding to the entry; needs pairs to be marked with /1 and /2 (default: false)");
	arg_window          = arg_int0("w", "window", "<int>",          "number of chars per line in fasta file (default: " FASTA_COLUMNS_STR ")");
	arg_uncompressed    = arg_lit0("u", "uncompressed",             "write uncompressed output (default: false)");
	help                = arg_lit0("h", "help",                     "print this help and exit");
	end                 = arg_end(20); /* this needs to be even, otherwise each element in end->parent[] crosses an 8-byte boundary */


	argtable          = (void**) mMalloc(9*sizeof(void*));
	argtable[argcount++] = in_file;
	argtable[argcount++] = out_file;
	argtable[argcount++] = list_file;
	argtable[argcount++] = arg_exclude;
	argtable[argcount++] = arg_uncompressed;
	argtable[argcount++] = arg_pair;
	argtable[argcount++] = arg_window;
	argtable[argcount++] = help;
	argtable[argcount++] = end;

	if (arg_nullcheck(argtable) != 0) {
		mDie("insufficient memory");
	}
	nerrors = arg_parse(argc, argv, argtable);

	if (help->count > 0) {
		fprintf(stdout, "Usage:\n------\n\n%s %s", PROGRAM, subprogram);
		arg_print_syntax(stdout, argtable, "\n");
		fprintf(stdout, "\nOptions:\n--------\n\n");
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		arg_freetable(argtable, argcount);
		mFree(argtable);
		return 0;
	}

	if (nerrors > 0) {
		arg_print_errors(stderr, end, "mseqtools subset");
		fprintf(stderr, "try using -h\n");
		arg_freetable(argtable, argcount);
		mFree(argtable);
		mQuit("");
	}

	exclude = (arg_exclude->count > 0);
	pair    = (arg_pair->count > 0);

	if (arg_window->count > 0) 
		window = arg_window->ival[0];

	/* Make a hash of sequence names from the list file */
	list_stream = mSafeOpenFile(list_file->sval[0], "r", 0);
	keep = zoeNewHash();
	key  = (char*) mMalloc(LINE_MAX*sizeof(char));
	while (fgets(line, LINE_MAX, list_stream) != NULL) {
		char  def[LINE_MAX];
		int  *code;
		if (sscanf(line, "%s", def) != 1) {
			mDie("LIST LINE ERROR");
		}

		code = (int*) mMalloc(sizeof(int));
		*code = 1;

		/* If pair, then check if there is template. Otherwise, just use def */
		if (pair && mGetIlluminaTemplate(def, key)) {
			zoeSetHash(keep, key, code);
		} else {
			zoeSetHash(keep, def, code);
		}
	}
	mSafeCloseFile(list_stream, 0);

	/* Process the input files one by one */
	output = mSafeOpenFile(out_file->sval[0], "w", arg_uncompressed->count == 0);
	for (i=0; i<in_file->count; i++) {
		if (strcmp(in_file->sval[i], "-") == 0) { /* If '-' was given as output, redirect to stdout */
			input = gzdopen(fileno(stdin), "r");
		} else {
			input = gzopen(in_file->sval[i], "r");
		}
		seq = kseq_init(input);
		while ((status = kseq_read(seq)) >= 0) {
			int  *ptr;
			if (pair && mGetIlluminaTemplate(seq->name.s, key)) {
				ptr = (int*)zoeGetHash(keep, key);
			} else {
				ptr = (int*)zoeGetHash(keep, seq->name.s);
			}
			if ((ptr != NULL) != exclude) { 
				mWriteSeqN(output, seq, window);
			}
		}
		kseq_destroy(seq);
		gzclose(input);
	}
	mSafeCloseFile(output, arg_uncompressed->count == 0);

	/* Free memory etc */
	keys = zoeKeysOfHash(keep);
	for (i=0; i<keys->size; i++) {
		mFree(zoeGetHash(keep, keys->elem[i]));
	}
	zoeDeleteTVec(keys);
	zoeDeleteHash(keep);
	mFree(key);

	arg_freetable(argtable, argcount);
	mFree(argtable);

	return 0;
}
