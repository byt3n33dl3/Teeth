/**
 * This is an example to show you how to use `uri_proc`
 *
 * To compile:
 *
 * $ cd uri_proc/
 * $ gcc -o example uri_proc.c example.c
 *
 * To run the test parsing a uri:
 * $ ./example -u [your_uri]
 *
 * To run the test parsing a hostname:
 * $ ./example -h [your_hostname]
 *
 * For example: ./example https://google.com/q=hello
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "string.h"
#include "signal.h"
#include "uri_proc.h"
#define MAX_INPUT_STRING 255
#define HOSTNAME_MODE 1
#define URI_MODE 2
/**
 * Show help message
 * @param prg_name program name
 */
void usage(const char * prg_name) {
	printf("%s [<option>]\n", prg_name);
	printf("Option:\n");
	printf("\t-u <uri>  : Gives the uri to process.\n");
	printf("\t-h <hostname>   : Gives the hostname to process.\n");
	exit(1);
}

/**
 * parser input parameter
 * @param argc     number of parameter
 * @param argv     parameter string
 * @param input 	input string
 * @param mode     hostname or uri
 */
void parseOptions(int argc, char ** argv, char * input, int * mode) {
	int opt, optcount = 0;
	while ((opt = getopt(argc, argv, "u:h:")) != EOF) {
		switch (opt) {
		case 'u':
			optcount++;
			if (optcount != 1 ) {
				usage(argv[0]);
			}
			strncpy((char *) input, optarg, MAX_INPUT_STRING);
			*mode = URI_MODE;
			break;
		case 'h':
			optcount++;
			if (optcount != 1 ) {
				usage(argv[0]);
			}
			strncpy((char *) input, optarg, MAX_INPUT_STRING);
			*mode = HOSTNAME_MODE;
			break;
		default:
			usage(argv[0]);
		}
	}

	if (input == NULL || strcmp(input, "") == 0) {

		if (*mode == HOSTNAME_MODE) {
			fprintf(stderr, "[error] Missing hostname\n");
		}

		if (*mode == URI_MODE) {
			fprintf(stderr, "[error] Missing uri\n");
		}
		usage(argv[0]);
	}
}

/**
 * Main program start from here
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char ** argv) {

	printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("|\t\t URI_PROC example\n");
	printf("|\t %s: built %s %s\n", argv[0], __DATE__, __TIME__);
	printf("|\t https://github.com/luongnv89/uri_proc\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - -\n");

	char input[MAX_INPUT_STRING + 1]; // interface name or path to pcap file

	int mode; // Online or offline mode

	// Parse option
	parseOptions(argc, argv, input , &mode);
	up_init("domains");
	uri_proc_t *up = NULL;

	if (mode == HOSTNAME_MODE) {
		up = up_create_from_host(input, strlen(input), NULL);
	} else {
		up = up_create(input, strlen(input), NULL);
	}

	up_show(up);

	up_close();

	return EXIT_SUCCESS;
}