/**
 * URI processing - provide some simple APIs to work with URI
 */

#ifndef URI_PROC_H
#define URI_PROC_H

/**
 * Present a structure of a URI: https://luongnv89.github.io.fr:8080/radio
 */
typedef struct uri_proc_struct{ 
	unsigned int length; // Length of URI
	char * based_uri; // https://luongnv89.github.io.fr
	char * host; // host: luongnv89.github.io.fr
	char * based_domain; // based domain: github
	char * sub_domain; // sub domain: luongnv89
	char * top_domain; // root domain: .io.fr
	char * protocol; // protocol: https
	char * path; // URI path: radio
	unsigned port_number; // Port number: 8080
	void * user_args; // User argument
}uri_proc_t;

/**
 * Initialize the static variables for uri_proccessing
 * - Initialize the list of country_domain
 * - Initialize the list of top domain
 * - Initialize the list of generic domain
 * @return 0 - if everything OK
 *           1 - if failed to init list of country domain
 *           2 - if failed to init list of top domain
 *           3 - if failed to init list of generic domain
 */
int up_init(char * domain_location);
/**
 * Clean memmory of static variables: list of country domain, top_domain and generic domain
 *  This is a public function because we need to call it explicitly when we finish working with up
 */
void up_close();

/**
 * Create a uri_proc_struct
 * @param  uri       given URI
 * @param  uri_len   length of given URI
 * @param  user_args user arguments
 * @return           a pointer points to a new uri_proc_struct
 *                     NULL if :
 *                     	- Cannot allocate memory for new uri_proc_struct
 *                     	- given URI is invalid
 */
uri_proc_t * up_create(char * uri, int uri_len, void * user_args);

/**
 * Create a uri_proc_struct from a hostname
 * @param  hostname  hostname
 * @param  host_len  length of hostname
 * @param  user_args user argument
 * @return           a pointer points to a new uri_proc_struct
 *                     NULL if:
 *                     - cannot allocate memory for a new uri_proc_struct
 *                     - given hostname is invalid
 */
uri_proc_t * up_create_from_host(char * hostname, int host_len, void * user_args);

/**
 * Free a uri_proc_struct
 * @param  up given up
 */
void up_free(uri_proc_t *up);

/**
 * Check the validation of a given URI
 * Make this public because we may use this many times
 * @param  uri     given URI
 * @param  uri_len length of given URI
 * @return         1 - if the given URI is valid
 *                 0 - if the given URI is invalid:
 *                 	- uri is NULL
 *                 	- ...
 */	
int up_valid_uri(char * uri, int uri_len);

/**
 * Get based URI
 * @param  up [description]
 * @return    [description]
 */
char * up_get_based_uri(uri_proc_t * up);

/**
 * Get host name
 * @param  up [description]
 * @return    [description]
 */
char * up_get_host(uri_proc_t * up);

/**
 * Get based domain
 * @param  up [description]
 * @return    [description]
 */
char * up_get_based_domain(uri_proc_t * up);

/**
 * Get sub domain
 * @param  up [description]
 * @return    [description]
 */
char * up_get_sub_domain(uri_proc_t * up);

/**
 * Get top domain
 * @param  up [description]
 * @return    [description]
 */
char * up_get_top_domain(uri_proc_t * up);

/**
 * Get protocol
 * @param  up [description]
 * @return    [description]
 */
char * up_get_protocol(uri_proc_t * up);

/**
 * Get path
 * @param  up [description]
 * @return    [description]
 */
char * up_get_path(uri_proc_t * up);

/**
 * Extract port number
 * @param  up [description]
 * @return    [description]
 */
unsigned int up_get_port_number(uri_proc_t * up);

/**
 * Show up structure
 * @param up [description]
 */
void up_show(uri_proc_t * up);

// Utility functions
/**
 * Update a string array by reading from a file.
 * Each element of string array will contain the content from one line of the file
 * @param list_strings array string
 * @param fileName     file name
 * @param counter      counter - count number of elements -> can be NULL
 * @return	0 - failed
 *           1 - Success
 */
int create_string_array_from_file(char ** list_strings, char * fileName, int * counter);

#endif
// End of URI_PROC_H
