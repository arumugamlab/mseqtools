# mseqtools: fastq/fasta file manipulation toolkit

**mseqtools** provides useful functions that are commonly used in microbiome
data analysis, especially when analyzing shotgun metagenomics data. 

My first recommendation for any one trying to process fastq/fasta files will be to
look at [Heng Li](https://github.com/lh3)'s **seqtk** package: <https://github.com/lh3/seqtk>.
Having implemented many sequence manipulation functions, I find that **seqtk**
covers most functionalities I need, so the current **mseqtools** package is
a watered down version of what I used to have in a larger package.
**mseqtools** implements some functionalities that cannot be found in **seqtk**.

In fact, even though I had originally implemented sequence I/O routines, I
completely rewrote **mseqtools** to use Heng Li's **kseq.h** implementation
for both code reuse as well as efficiency reasons. I don't believe I can 
implement something that runs faster than his implementation :)

# Table of Contents
 1. [Installation](#installation)   
  1.1. [System requirements](#sys-requirements)   
  1.2. [Installing using conda](#install-conda)   
  1.3. [Using a docker container](#use-docker)   
  1.4. [Installing from source](#install-source)   
   1.4.1. [Required tools](#required-tools)   
   1.4.2. [Required libraries](#required-libraries)   
   1.4.3. [For normal users](#normal-users)   
   1.4.4. [For advanced users](#advanced-users)   
    1.4.4.1. [Getting the source code](#source-code)   
     1.4.4.1.1. [Cloning the git repository](#git-clone)   
     1.4.4.1.2. [Downloading the ZIP file from github](#git-zip)   
    1.4.4.2. [Running autoconf and automake](#automake)   
    1.4.4.3. [Building the program](#build)   
 2. [mseqtools](#mseqtools)   
 3. [mseqtools subset](#mseqtools-subset)   
## 1. Installation <a name="installation"></a>

### 1.1. System requirements <a name="sys-requirements"></a>

You should be able to use **mseqtools** on any flavor of linux and UNIX. 
Although I have not tested it myself, it should also work on macOS. A
macOS version is available from bioconda.

>NOTE: Even though **mseqtools** uses *zlib* to read compressed files, 
it spawns a child process that writes the compressed output files
by piping to `gzip`. This means `gzip` is a fixed dependency for
**mseqtools** to work. Conda and docker releases will ensure that `gzip` is 
available in your environment. Building from source will check at 
building time for the existense of `gzip` in your system. If you successfully build
in a system and migrate to another system that lacks `gzip`, this 
could be disastrous. Please ensure that `gzip` is available in your
path if you build **mseqtools** yourself.

### 1.2. Installing using conda <a name="install-conda"></a>

The easiest way to install **mseqtools** and the required dependencies is
via conda from the bioconda channel.

~~~
conda install -c bioconda mseqtools
~~~

Inside your conda environment, you can just invoke **mseqtools** directly. E.g.:
~~~
mseqtools help
~~~

### 1.3. Using a docker container <a name="use-docker"></a>

**mseqtools** is automatically available as a docker container from the BioConda build.
E.g., if you add this line in your snakemake rule
~~~
singularity: 'docker://quay.io/biocontainers/mseqtools:0.9.1--h5bf99c6_0'
~~~
you can use this dockerized version of **mseqtools** by invoking **snakemake**
as:
~~~
snakemake --use-singularity
~~~


### 1.4. Installing from source <a name="install-source"></a>

You can also download the source code and build it yourself.

#### 1.4.1. Required tools <a name="required-tools"></a>

While building **mseqtools**, you will need some standard tools that are 
most likely installed in your system by default. I will still list them here
anyway to be sure:

 1. gcc
 2. gzip
 3. tar
 4. wget

If any of these is missing in your system, or cannot be found in your 
application path, please fix that first.

#### 1.4.2. Required libraries <a name="required-libraries"></a>

The following libraries are required to build **mseqtools** from source:

 1. **zlib** development version (e.g., zlib1g-dev in ubuntu)
 2. **argtable2** development version (e.g., libargtable2-dev in ubuntu)

Please make sure that these are installed in your system before trying to 
build.

#### 1.4.3. For normal users <a name="normal-users"></a>

If you are a normal user, then the easiest way is to obtain the package file
and build the program right away. The following commands were written when
version 0.9.1 was the latest, so please update the version number in the
commands below.

~~~
wget https://github.com/arumugamlab/mseqtools/releases/download/0.9.1/mseqtools-0.9.1.tar.gz
tar xfz mseqtools-0.9.1.tar.gz
cd mseqtools-0.9.1
./configure
make
~~~

This should create `mseqtools` executable.

#### 1.4.4. For advanced users <a name="advanced-users"></a>

If you are an advanced user who would like to contribute to the code base
or if you just like to do things the hard way, you can check out the source
code and build the program in a series of steps involving `autoconf` and
`automake`. If these names confuse you or scare you, then please follow the
instructions for [normal users](#normal-users).

##### 1.4.4.1. Getting the source code <a name="source-code"></a>

You can get **mseqtools** code from github at 
<https://github.com/arumugamlab/mseqtools>. 
You can either `git clone` it or download the ZIP file and extract the 
package.

###### 1.4.4.1.1. Cloning the git repository <a name="git-clone"></a>

You can get a clone of the repository if you wish to keep it up-to-date 
independent of our releases.

~~~
$ git clone https://github.com/arumugamlab/mseqtools
Cloning into 'mseqtools'...
remote: Enumerating objects: 285, done.
remote: Counting objects: 100% (285/285), done.
remote: Compressing objects: 100% (181/181), done.
remote: Total 285 (delta 167), reused 215 (delta 101), pack-reused 0
Receiving objects: 100% (285/285), 130.93 KiB | 0 bytes/s, done.
Resolving deltas: 100% (167/167), done.
$ cd mseqtools
~~~

You can check the contents of the repository in *mseqtools* directory.

###### 1.4.4.1.2. Downloading the ZIP file from github <a name="git-zip"></a>

You can download the repository's snapshot as on the day of download by:
~~~
$ wget https://github.com/arumugamlab/mseqtools/archive/master.zip
--2021-11-17 12:24:24--  https://github.com/arumugamlab/mseqtools/archive/master.zip
Resolving github.com (github.com)... 140.82.121.4
Connecting to github.com (github.com)|140.82.121.4|:443... connected.
HTTP request sent, awaiting response... 302 Found
Location: https://codeload.github.com/arumugamlab/mseqtools/zip/master [following]
--2021-11-17 12:24:25--  https://codeload.github.com/arumugamlab/mseqtools/zip/master
Resolving codeload.github.com (codeload.github.com)... 140.82.121.10
Connecting to codeload.github.com (codeload.github.com)|140.82.121.10|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: unspecified [application/zip]
Saving to: ‘master.zip’

     0K .......... .......... .......... .......... .......... 1.68M
    50K .......... ........                                    67.2M=0.03s

2021-11-17 12:24:25 (2.28 MB/s) - ‘master.zip’ saved [70091]

$ unzip master.zip
$ cd mseqtools-master
~~~

##### 1.4.4.2. Running autoconf and automake <a name="automake"></a>

You can check the contents of the repository in the package directory.
~~~
$ ls
aclocal.m4  configure.ac  Makefile.in  mseq.h         mSequence.c  zoeTools.c
build-aux   LICENSE       mCommon.c    mseq_subset.c  mSequence.h  zoeTools.h
configure   Makefile.am   mCommon.h    mseqtools.c    README.md
~~~

You will note that the `configure` script does not exist in the package.
This is because you need to generate the `configure` script using 
`aclocal`, `autoconf` and `automake`.
~~~
aclocal
autoconf
mkdir build-aux
automake --add-missing
~~~

##### 1.4.4.3. Building the program <a name="build"></a>

You can then build mseqtools as follows:
~~~
./configure
make
~~~

## 2. mseqtools <a name="mseqtools"></a>

This is the master program that you call with the subprogram options. There 
are currently 4 subprograms that you can call as shown below.
~~~

Program: mseqtools (Sequence manipulation toolkit)
Version: 0.9.0

Usage:   mseqtools <command> [options]

Commands:
 -- Subsetting
     subset         subset sequences based on a given list
~~~

These represent the different manipulations of fastq/fasta files you can perform using
**mseqtools**. Input files can be optionally gzipped. Output files are **ALWAYS** gzipped.

## 3. mseqtools subset <a name="mseqtools-subset"></a>

**subset** program provides sequence subsetting based on a given list of
sequence identifiers. Sequence identifiers are the first word in the 
fasta or fastq header **before** whitespace. 

Here is an example command one would use to get a subset of sequences from
a gzipped fastq file into a new gzipped fastq file.
~~~
mseqtools subset --input sample1.1.fq.gz --list keep.list > sample1.keep.1.fq.gz
~~~

The reason for the existence of
**subset** mode is that **seqtk**'s `subseq` subprogram does not let you
subsetting by **skipping** the entries in the list - this is quite useful
in metagenomic data processing where we need to remove reads and their pairs
that map to the host (e.g. human) genome.

E.g., if you need to remove reads that mapped to the human genome, you can do that 
as follows:

~~~
mseqtools subset --input sample1.1.fq.gz --exclude --list human_reads.list > sample1.hostfree.1.fq.gz
mseqtools subset --input sample1.2.fq.gz --exclude --list human_reads.list > sample1.hostfree.2.fq.gz
~~~

Often we want to throw away both paired-end reads even when one of them mapped to the
human genome. In this situation, it is better to err on the safer side. When sequences
are mapped in single-end mode with `/1` or `/2` suffix at the end of the sequence
identifiers, it makes it tricky to match them directly by identifier alone. **mseqtools**
provides a paired mode via `--paired` where the `/1` or `/2` suffix is ignored from
the list and from the fastq header so that both ends of the pair are removed.

~~~
mseqtools subset --input sample1.1.fq.gz --exclude --paired --list human_reads.list > sample1.hostfree.1.fq.gz
mseqtools subset --input sample1.2.fq.gz --exclude --paired --list human_reads.list > sample1.hostfree.2.fq.gz
~~~

Combining **mseqtools** and **seqtk**, you can achieve quite a few things.
E.g., if you need to remove reads that mapped to the human genome and then filter
the remaining reads by length, you can do that using a snakemake rules such as:

~~~
rule fastq_qc_host_length:
    input: 
        fastq="{sample}.1.fq.gz", 
        list="{sample}.hg38.list"
    output: "{sample}.qc.1.fq.gz"
    params: seq_depth = lambda wildcards: seq_depth[wildcards.sample]
    shell:
        """
        seqtk seq -L 125 {input.fastq} \
            | mseqtools subset --input - --exclude --list {input.list} --output - \
            > {output}
        """
~~~

For piping between multiple sequence processing steps, please use `--uncompressed` so that 
sequences are not compressed and decompressed between steps.

A full description is given below:
~~~
Usage:
------

mseqtools subset [-vuph] -i <file> -o <file> -l <file> [-w <int>]

Options:
--------

  -i, --input=<file>        input fasta/fastq file
  -o, --output=<file>       output file (gzipped)
  -l, --list=<file>         file containing list of fasta/fastq identifiers
  -v, --exclude             exclude sequences in this list (default: false)
  -u, --uncompressed        write uncompressed output (default: false)
  -p, --paired              get both reads from a pair corresponding to the entry; needs pairs to be marked with /1 and /2 (default: false)
  -w, --window=<int>        number of chars per line in fasta file (default: 80)
  -h, --help                print this help and exit
~~~

