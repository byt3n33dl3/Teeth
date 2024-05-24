#include <stdio.h>
#include <string.h>

/**
 * Larger the number, larger will the table
 * If the table size is too large, elements distirubtion will be too widespread
 * and makes the table to be not utilized efficiently
 * 
 * Hence choose the table size judiciously
 * 
 * Better choice would be the next prime number after the maximum number of unique elements
 * eg. If total number of unique elements are 10,000: TABLE_SIZE could be 10007
 */
#define MAX_TABLE_SIZE 10007 //Prime Number

#define MAX_WORDS 4
#define MAX_LENGTH 10

char words[MAX_WORDS][MAX_LENGTH] = {"abcd", "defg", "fghcv", "zscdf"};

typedef struct _hashList
{
    char word[MAX_LENGTH];
    int len;
    unsigned long hash;
}HashList;

HashList hashData[MAX_TABLE_SIZE];


/**
 * Sample Hash Function for integers
 * This mostly works until the numbers has any special properties
 */
int getHashForIntegers(int num)
{
    int hash = 0;
    
    hash = (num%MAX_TABLE_SIZE);
    
    return hash;
}

/**
 * Sample Hash Function for strings
 * For integers, above option would be better choice
 * For strings, multiple methods can be followed
 * 
 * Below method takes the sum of ASCII values of
 * all the characters in given string
 */
int getHashForStrings_ASCIISum(char *word)
{
    unsigned long hash = 0;
    
    while(*word != '\0')
    {
        hash += *word++;
    }
    
    return (hash%MAX_TABLE_SIZE);
}

/**
 * Above method has more chances for collisions
 * And also values wont be able to distrube equally
 * 
 * Below method assumes, minimum two characters available
 * in input and calculates the hash
 * 
 * 27 - 26 Alphabets + blank
 */
int getHashForStrings_MinTwoChar(char *word)
{
    unsigned long hash = 0;
    
    hash = (word[0] + word[1]*27 + word[2]*27*27);
    
    return (hash%MAX_TABLE_SIZE);
}

/**
 * Even above method has more chances for collisions
 * And also values wont be able to distrube equally
 * 
 * Below method inlcudes all the characters of string
 * and has the possibility of better distribution compared
 * to previous methods
 */
unsigned long getHashForStrings_AllChar(char *word)
{
    unsigned long hash = 0;
    
    while(*word != '\0')
    {
        hash = ((hash<<5) + *word++);
    }
    
    return (hash%MAX_TABLE_SIZE);
}

int main()
{
    
    char testStr[] = "abcdef";
    int i;
    unsigned long curHash;
    
    printf("Lets do Hashing!\n\n");
    
    /**
     * If the strings are too lengthy, overflow may happen while calculating hash
     * Especially in getHashForStrings_AllChar() Function
     * Change the return value from int to unsigned int/long based on necessity
     */
    printf("HashValue for the string[%s] using ASCII Sum: [%d]\n", testStr, getHashForStrings_ASCIISum(&testStr[0]));
    printf("HashValue for the string[%s] using first two characters: [%d]\n", testStr, getHashForStrings_MinTwoChar(&testStr[0]));
    printf("HashValue for the string[%s] using leftshift: [%ld]\n", testStr, getHashForStrings_AllChar(&testStr[0]));


    /**
     * Sample code to show, how each value is stored in hashing table
     * and how each value can be retrieved
     * 
     * Using arrays for hash table representation
     * 
     * Insert -> Calculate hash function and insert the data
     * Find -> Given a word, get its hash and display its length
     */
     
     // Filling hash structure with values
     for(i = 0; i < MAX_WORDS; i++)
     {
         curHash = getHashForStrings_AllChar(&words[i][0]);
         hashData[curHash].hash = curHash;
         hashData[curHash].len  = strlen(words[i]);
         strcpy(hashData[curHash].word, &words[i]);
         
         printf("Inserting into hash table: Hash = [%ld], Word = [%s], Len = [%d]\n", curHash,
                               hashData[curHash].word, hashData[curHash].len);
     }
     
     
     //Extracting details for a word based on hash
     curHash = getHashForStrings_AllChar(&words[2][0]);
     printf("Word details: Hash = [%ld], Word = [%s], Len = [%d]\n", curHash,
                               hashData[curHash].word, hashData[curHash].len);
     
    return 0;
}
