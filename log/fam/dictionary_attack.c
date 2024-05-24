#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "controller.h"
#include "controller.h"
#include "dictionary_attack.h"

static char *data_map, resources[100][100];
static DIR *dp;
static struct dirent *ep;
static int number_of_files = 0;

void find_files()
{
    dp = opendir ("./resources");
    
    if (dp != NULL)
        {
            int i = 0;
            while ( (ep = readdir (dp)) )
                if (ep->d_name[0] != 46)
                    strncpy(resources[i++],  ep->d_name, 50);
                
            (void) closedir (dp);

            number_of_files = i;
        }
    else
        perror ("Couldn't open the directory");

    free(ep);
}

void* look_in_fil_runner(void *arg)
{
    struct data *arg_struct = (struct data*) arg;
    char password[50] = { '\0' };
    int j = 0;
    int i = arg_struct->start;

    while (j < 50)
    {
        if(found_password()) 
            break;

        if (data_map[i] == '\n')
            {
                check(password);
                j = 0;

                if(i > arg_struct->end)
                    break;

                memset(password, 0, strlen (password) );
            }
        else
            password[j++] = data_map[i];

        i++;
    }
    return NULL;
}

void open_file(int num_thread)
{   

    find_files();
    printf("Activate Dictionary Attack!\n");

    for(int i = 0; i < number_of_files; i++)
    {
        struct stat st;

        if(found_password())
            break;

        char fil_path[100] = "./resources/";
        char* file_name = resources[i];
        strcat(fil_path, file_name);

        int fd = open(fil_path, O_RDONLY, 0);

        if(fstat( fd , &st ) == -1)
            perror("COULD NOT GET FILE SIZE");
        
        printf("File %d out of %d: %s\n", i+1, number_of_files, file_name);

        data_map = mmap( NULL, st.st_size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);

        pthread_t tids[num_thread];
        struct data arg[num_thread];
        int chunk = st.st_size / num_thread;
        
        for (int i = 0; i <  num_thread; i++)
        {
            arg[i].start = chunk * i;
            arg[i].end = ((i + 1) * chunk) + (i == num_thread - 1 ? st.st_size % num_thread : 0);
            pthread_create(&tids[i], NULL, look_in_fil_runner, &arg[i]);
        }

        for (int i = 0; i < num_thread; i++)
            pthread_join(tids[i], NULL);
            

        munmap(data_map, st.st_size);
        close(fd);
    }
    
}
