#include <stdio.h>
#include <string.h>

#define MAX_ELEMENTS 10000
#define MAX_TABLE_SIZE 10007 //Prime Number
#define MAX_WORDS 5
#define MAX_WORD_LEN 10

char words[MAX_WORDS][MAX_WORD_LEN] = {"abcd", "hgtk", "bghytjk", "mnzqwdo", "qaoisjkcs"};

typedef struct _hashList
{
    char word[MAX_WORD_LEN];
    struct _hashList *next;
}HashList;

typedef struct _hashTbl
{
    int tableSize;
    HashList **listElements;
}HashTbl;

HashTbl *hashTbl = NULL;

unsigned long getHash(char *word)
{
    unsigned long hash = 0;
    
    while(*word != '\0')
    {
        hash += ( (hash << 5) + *word++);
    }
    
    return (hash%MAX_TABLE_SIZE);
}

HashList* matchWord(char *word, HashList *hashNode)
{
    if(word == NULL || hashNode == NULL)
    {
        //Invaid Data/Hash table
        return NULL;
    }
    
    while(hashNode != NULL && strcmp(hashNode->word, word))
    {
        hashNode = hashNode->next;
    }
    
    return hashNode;
}


HashList* FindHashEntry(char *word, HashTbl *hashNode)
{
    HashList *temp1 = NULL;
    unsigned hashValue = 0;
    //HashList temp1;
    
    if(word == NULL || hashNode == NULL)
    {
        //Invaid Data/Hash table
        return;
    }
    
    hashValue = getHash(word);
    temp1 = &hashNode->listElements[hashValue];

    
    return temp1;
}


void initHashTable(int curTableSize)
{
    int i;
    if(curTableSize > MAX_TABLE_SIZE)
    {
        //Cannot create hash table
        return;
    }
    
    
    if(hashTbl != NULL)
    {
        //Already hash table is initialized
        return;
    }
    
    hashTbl = (HashTbl*) malloc(sizeof(HashTbl));
    //Can also generate next best prime number of curTableSize
    hashTbl->tableSize = MAX_TABLE_SIZE; 
    
    if(hashTbl == NULL)
    {
        //Failure in memory allocation
        return;
    }
    
    hashTbl->listElements = (HashList*) malloc(sizeof(HashList) * hashTbl->tableSize);
    if(hashTbl->listElements == NULL)
    {
        //Failure in memory allocation
        free(hashTbl);
        return;
    }
    printf("Initialized HashTable\n");
}

HashList* insertHashTable(char *word, HashTbl *hashNode)
{
    HashList *curList = NULL, *newNode = NULL, *tempList = NULL;
    
    if(word == NULL || hashNode == NULL)
    {
        //Invaid Data/Hash table
        return NULL;
    }
    
    curList = FindHashEntry(word, hashNode);
    
    if(curList == NULL)
    {
        //Failure in finding the entry for the given word!
        // Ideally this shouldn't fail -- Some thing is happening there!
        return NULL;
    }
    
    tempList = matchWord(word, curList);
    
    if(tempList == NULL)
    {
        //current key doesnt exist - insert into hash value
        newNode = (HashList*)malloc(sizeof(HashList));
        if(newNode == NULL)
        {
            //Failure in memory allocation
            return NULL;
        }

        strcpy(newNode->word, word);
        //Inserting the data at the front
        newNode->next = curList->next;
        curList->next = newNode;
    }
    return curList;
}


int main()
{
    int i;
    printf("Lets check out Separate Chaining\n");
    
    initHashTable(10); //10 - current table size
    for(i = 0; i < MAX_WORDS; i++)
    {
        HashList *temp = NULL;
        temp = insertHashTable(&words[i][0], hashTbl);
        printf("Inserting word[%s] at pointer location: [%x]\n", words[i], temp);
    }
    printf("\n");
    for(i = 0; i < MAX_WORDS; i++)
    {
        HashList *temp = NULL;
        temp = FindHashEntry(&words[i][0], hashTbl);
        printf("Word[%s] is at pointer location[%x] in hash table\n", words[i], temp);
    }

    return 0;
}
