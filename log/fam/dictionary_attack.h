void find_files();
void* look_in_fil_runner(void* arg);
void open_file(int num_thread);

typedef struct data
{
    int start, end;    

} data_to_reader;