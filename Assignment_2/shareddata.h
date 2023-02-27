//
// Created by Turner Trowbridge on 2/26/23.
//

#ifndef ASSIGNMENT_2_SHAREDATA_H
#define ASSIGNMENT_2_SHAREDATA_H

/**
* Shared constants and data structures among threads
**/
#define NUMOFFILES 2
#define DICTSRCFILEINDEX 0
#define VOCAB_FILE_INDEX 1
#define TEST_FILE_INDEX 2

#define SHARED_VOCAB_INDEX 0
#define SHARED_TEST_INDEX 1

#define OPT_ARG_START_IDX 3

/* default number of progress marks for representing 100% progress */
#define DEFAULT_NUMOF_MARKS 50
/* minimum number of progress marks for representing 100% progress */
#define MIN_NUMOF_MARKS 10

/* place hash marks in the progress bar every N marks */
#define DEFAULT_HASHMARKINTERVAL 10
/* minimum number of hash marks */
#define MIN_HASHMARKINTERVAL 0
/* maximum number of hash marks */
#define MAX_HASHMARKINTERVAL 10

/* default minimum number of dictionary words starting from a prefix for printing or writing to
the output */
#define DEFAULT_MINNUM_OFWORDS_WITHAPREFIX 1

typedef struct {

    /**
    * root node of the dictionary tree
    */
    dictNode *dictRootNode;
    /**
    * parameters for printing progress bar
    */
    int numOfProgressMarks;
    int hashmarkInterval;
    /**
    * print the prefix and its count to the output file only if the
    * number of dictionary words starting from the prefix is equal to or
    * greater than this number
    */
    int minNumOfWordsWithAPrefixForPrinting;

    /**
    * filePath[0] - file path for the dictionary vocabulary file
    * providing words to populate the dictionary tree
    * filePath[1] - file path for the test source file providing prefixes
    */
    const char *filePath[NUMOFFILES];

    const char *delimiters = "\n\r !\"#$%&()*+,./0123456789:;<=>?@[\\]^`{|}~";  // separates words

    /** store total number of characters in files
    totalNumOfCharsInFile[DICTSRCFILEINDEX]
    * - number of total chars in the dictionary vocabulary file.
    * use stat, lstat, or fstat system call
    * totalNumOfCharsInFile[TEST_FILE_INDEX]
    * - number of total chars in the test file, you may NOT need this count
    * for this assignment
    *
    * Hints: see man stat, lstat, or fstat to get the total number of bytes of the file
    * stat or lstat uses a filename, whereas fstat requires a file descriptor from a
    * low-level I/O call: e.g. open. If you are using high-level I/O, either use stat
    * (or lstat), or open the file first with the low-level I/O, then call fstat,
    * then close it.)
    *
    * Important: assume all text files are in Unix text file format, meaning, the end
    * of each line only has a line feed character. The stat, lstat, fstat would include the
    * count of the line feed character from each line.
    */
    long totalNumOfCharsInFile[NUMOFFILES];
    /**
    * Use numOfCharsProcessedFromFile to track ongoing progress of
    * number of characters read in from files and the subsequent thread logic.
    *
    * This progress indicator is updated by worker threads, and used by the main
    * thread to display the progress for tracking the execution of the populatetree thread
    *
    * Important: this number can be incremented by the number of characters in
    * the line that is being read and processed, plus one to include the
    * line feed character at the end of each line of a Unix text file.
    * Do NOT convert the text files to a Windows DOS format.
    *
    * File is read in line by line, for each line read in:
    * 1) tokenize the line by delimiters to a word array, with each separated word:
    * insert the word to the dictionary tree or search, count, and print the word
    * in the dictionary tree, and then increment the word count of the file:
    * wordCountInFile (see below)
    *
    * 2) update the numOfCharsReadFromFile by incrementing it by the
    * number of characters in the line, plus one to include the line feed
    * character at the end of each line of a Unix text file.
    *
    * numOfCharsReadFromFile[DICTSRCFILEINDEX]
    * - number of chars read in and processed from
    * the dictionary vocabulary file
    * numOfCharsReadFromFile[TEST_FILE_INDEX]
    * - number of chars read in and processed from
    * the test file, you may NOT this number for this assignment
    */
    long numOfCharsReadFromFile[NUMOFFILES];
    /**
    * wordCountInFile[DICTSRCFILEINDEX]
    * - number of total words in the dictionary vocabulary file.
    * wordCountInFile[TEST_FILE_INDEX]
    * - number of total words in the test file
    */
    long wordCountInFile[NUMOFFILES];
    /**
    * number of prefixes that have been read from the prefix queue,
    * searched and printed
    * this is used for tracking the progress of the countprefix thread
    */
    long numOfProcessedPrefixes;
    /**
    * buffer prefixes read from test file
    */
    queue <string>prefixQueue;
    /**
    * pthread mutex for accessing the prefixQueue
    */
    pthread_mutex_t queue_mutex;
    /**
    * completed flags indicate the completion of the thread logic, one
    * for the populatetree thread, one for countprefix thread
    * Important: the completed flag of populatetree thread may be
    * used to force the precedence constraint that the
    * readprefix and countprefix threads have to wait for populatetree
    * thread logic to complete before executing their thread logic
    *
    * taskCompleted[DICTSRCFILEINDEX]
    * - boolean flag to indicate whether the tree population
    * thread has completed the task: read words from the
    * dictionary source file and populate the tree
    *
    * important: you may want to set the completed flag for the
    * populatetree thread to true only after the main thread fully displays
    * the progress bar upon the completion of the thread logic
    *
    * taskCompleted[TEST_FILE_INDEX]
    * - boolean flag to indicate whether the readprefix
    * thread has completed the task: read prefixes from the
    * a test file, and insert each prefix to a queue
    * - main thread progress display would use this flag to
    * start to show the countprefix progress bar
    */
    bool taskCompleted[NUMOFFILES];
} SHARED_DATA;

#endif //ASSIGNMENT_2_SHAREDATA_H
