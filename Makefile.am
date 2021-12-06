# These are the installed programs
mseq_PROGRAMS = mseqtools

# We will also distribute a README.md markdown file
EXTRA_DIST = README.md LICENSE

# Where to install the programs
mseqdir = $(bindir)

# mseq library will be built and not distributed nor installed, 
# but its sources should be distributed

noinst_LIBRARIES = libmseq.a
dist_libmseq_a_SOURCES = mCommon.c \
                         mCommon.h \
                         mSequence.c \
                         mSequence.h \
                         mseq.h \
                         zoeTools.c \
                         zoeTools.h \
                         mseq_subset.c

nodist_libmseq_a_SOURCES = kseq.h

*.c: kseq.h

kseq.h:
	@echo -e "\033[1;31mDownloading kseq.h from Heng Li's seqtk github repository:\033[0m"
	$(WGET) @WGET_ARGS@ "https://raw.githubusercontent.com/lh3/seqtk/7c04ce7898ad5909bd309c6ba3cd9c3bd0651f0e/kseq.h" > $@

# Augment CFLAGS and LDFLAGS

AM_CFLAGS = $(MYCFLAGS) -DBUILD=\"@BUILD@\" -DPROGRAM=\"mseqtools\" 

# mseq added to every program
LDADD = $(builddir)/libmseq.a

clean-local:
	for file in libmseq.a; do \
		if [ -f "$$file" ]; then \
			rm $$file; \
		fi; \
	done

maintainer-clean-local:
	@echo 'This command is intended for maintainers to use; it'
	@echo 'deletes files that may need special tools to rebuild.'
	for file in Makefile.in; do \
		if [ -f "$$file" ]; then \
			rm $$file; \
		fi; \
	done
