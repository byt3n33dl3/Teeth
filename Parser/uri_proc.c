#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "uri_proc.h"
#define UP_NUMBER_COUNTRY_CODE	256 // 255 country code
#define UP_NUMBER_TOP_LEVEL 8 // 7 top level domain
#define UP_NUMBER_GENERIC_DOMAIN 255 // maximum 215 domain
#define UP_MAX_BUFFER_SIZE 255 // Maximum length of domain - 18
#define UP_MAX_DOMAIN_LENGTH 20 // Maximum length of domain - 18
#define UP_DOMAIN_TOP_LEVEL "top_level.txt" // Path to the file contains top level domains
#define UP_DOMAIN_CONTRY_CODE "country_code.txt" // Path to the file contains list country code domain
#define UP_DOMAIN_GENERIC_LOCATION "generic-" // Path to the location where all the files contains list generic domain.
//- - - - - - - - - - - - - - - - - - -
//
//	P R I V A T E
//
//- - - - - - - - - - - - - - - - - - -

static char * _up_country_code[UP_NUMBER_COUNTRY_CODE];
static char * _up_top_level[UP_NUMBER_TOP_LEVEL];
static char * _up_generic[UP_MAX_DOMAIN_LENGTH][UP_NUMBER_GENERIC_DOMAIN];
static int _up_inited = 0; // To mark if we already init 

/**
 * Check if a character is a good character in a URI
 * @param  c character to check
 * @return   0 if it is valid
 *             > 0 if it does not valid
 */
int _is_uri_character(char c) {
	return 0;
}

/**
 * Create new uri_proc_t structure
 * @return a pointer points to a new uri_proc_t structure
 *           NULL if cannot allocate memory
 */
uri_proc_t * _up_new() {
	uri_proc_t * up = (uri_proc_t *)malloc(sizeof(uri_proc_t));

	if (up == NULL) {
		fprintf(stderr, "[error] Cannot allocate memory to create a new uri_proc_t structure!\n");
		return NULL;
	}

	// Initilize value
	up->length = 0;
	up->based_uri =0x0; // https://luongnv89.github.io.fr
	up->host =0x0; // host: luongnv89.github.io.fr
	up->port_number = 0; // Port number
	up->based_domain =0x0; // based domain: github
	up->sub_domain =0x0; // sub domain: luongnv89
	up->top_domain =0x0; // root domain: .io.fr
	up->protocol =0x0; // protocol: https
	up->path =0x0; // URI path: radio
	up->user_args =0x0; // User argument
	return up;
}
/**
 * Compare 2 string
 * @param  str1   first string
 * @param  str2   second string
 * @param  length length to compare
 * @return        1 - equal
 *                  0 - not equal
 */
int _up_str_eq(char * str1, char * str2, int length) {
	int i = 0;
	for ( i = 0 ; i < length; i ++) {
		if (str1[i] != str2[i] ) {
			return 0;
		}
	}
	return 1;
}

/**
 * Check if a given domain is an element of list_domains
 * @param  domain       given domain
 * @param  length       length of given domain
 * @param  list_domains list domains
 * @return              1 - yes
 *                        0 - no
 */
int _up_check_top_domain(char * domain, int length, char ** list_domains) {
	int i = 0;

	while (list_domains[i] != NULL) {
		if (_up_str_eq(domain, list_domains[i], length) == 1) {
			return 1;
		}
		i++;
	}
	return 0;
}

/**
 * Initialize the value of _up_generic
 * @return 1 - if initialize successful
 *         -1 - if there is some problem in loading any value
 *
 */
int _up_load_domain_all_generic(char * domain_location) {
	int i = 0;
	for ( i = 0; i < UP_MAX_DOMAIN_LENGTH; i++) {
		char * fileName;
		fileName = (char *) malloc( sizeof(char) * 256);
		sprintf(fileName, "%s/%s%d", domain_location,UP_DOMAIN_GENERIC_LOCATION, i);
		if (access(fileName, R_OK) != -1) {
			if (create_string_array_from_file(_up_generic[i], fileName,NULL) != 0) {
				free(fileName);
				return -1;
			}
		}
		free(fileName);
	}
	return 1;
}

/**
 * Check if a given domain is a root domain
 * @param  domain given domain name
 * @param  length length of given domain name
 * @param	root_level: the current level of top_domain
 * @return        1 - if yes and stop go further
 *                2 - yes and go further (in case of the first top_domain is a country domain)
 *                0 - if no
 *                -1 - error in reading data from domain files
 *
 * Start:
 *  - Based on the length of the domain name to check the set of top_domain: from 2 - xxx
 */
int _up_is_top_domain(char * domain, int length, int root_level) {

	if (root_level > 2) return 0;

	if (root_level == 1) {

		if(length == 2){
			// There is an exception for .co.jp ...
			if(strcmp(domain,"co") == 0){
				return 1;
			}
		}
		
		if (length != 3) return 0;

		if (_up_check_top_domain(domain, length, _up_top_level) == 1) {
			return 1;
		}
	}

	if (length == 2) {
		if (_up_inited && _up_check_top_domain(domain, length, _up_country_code) == 1) {
			return 2;
		}
	}

	if (length == 3) {
		if (_up_check_top_domain(domain, length, _up_top_level) == 1) {
			return 1;
		}
	}

	return _up_check_top_domain(domain, length, _up_generic[length]);
}


/**
 * Get the index of the . which separate the hostname into top_domain and based domain
 * @param  hostname hostname
 * @param  last_index the last index to check the position of .
 * @param	root_level: the current level of top_domain
 * @return          index of the .
 *                  last index if there is no . in hostname or the last part (from last_index to start of the hostname) is not a top_domain
 *                  -2 if cannot allocate memory
 */
int _up_get_top_level_index(char * hostname, int last_index, int root_level) {

	// Get the top_domain name first  - from end to begin of the hostname: .io.fr
	// Get the last . in hostname
	int last_dot_index = last_index;
	int found = 0;
	for ( last_dot_index = last_index; last_dot_index >= 0; last_dot_index--) {
		if (hostname[last_dot_index] == '.') {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		// Cannot find any .
		if (root_level >= 1) return last_index + 1; // If the level >1 -> need to add 1 character for the dot
		return last_index;
	}

	char * last_dot_part = NULL;
	int last_dot_part_length = 0;
	if (root_level == 0) {
		last_dot_part_length = last_index - last_dot_index - 1; // -1 for the dot
	} else {
		last_dot_part_length = last_index - last_dot_index; // for the second level, the last_index is not the length of the hostname
	}
	last_dot_part = (char *) malloc(sizeof(char) * (last_dot_part_length + 1));
	if (last_dot_part == NULL) {
		fprintf(stderr, "[error] _up_get_top_level_index: Cannot allocate memory\n");
		return -2;
	}
	memcpy(last_dot_part, hostname + last_dot_index + 1, last_dot_part_length);
	last_dot_part[last_dot_part_length] = '\0';

	int ret_top_domain = _up_is_top_domain(last_dot_part, last_dot_part_length, root_level);
	free(last_dot_part);
	if ( ret_top_domain == 2) {
		// This is the country domain, can go further
		int next_level = root_level + 1;
		return _up_get_top_level_index(hostname, last_dot_index - 1, next_level); // Start from the character before the dot
	} else if (ret_top_domain == 1) {
		// This is top level domain, cannot go further
		return last_dot_index;
	} else {
		// This is not top domain, return the last_index;
		if (root_level >= 1) return last_index + 1; // If the level >1 -> need to add 1 character for the dot
		return last_index;
	}
}

/**
 * Get based domain index in hostname
 * @param  hostname                   hostname
 * @param  last_index_of_based_domain the last index of based domain where separate based domain and top level domain
 * @return                            0 if there is no sub domain
 *                                      the position of . which separate subdomain and based domain
 */
int _up_get_based_domain_index(char * hostname, int last_index_of_based_domain) {
	int last_dot_index = last_index_of_based_domain;
	int found = 0;
	for ( last_dot_index = last_index_of_based_domain; last_dot_index >= 1; last_dot_index--) {
		if (hostname[last_dot_index] == '.') {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		// Cannot find any . -> based domain will be count from begining of the hostname
		return 0;
	}
	return last_dot_index + 1; // + 1 to ignore the dot before based domain
};

/**
 *  Parse host name to extract based_domain, sub_domain and top_domain: www.luongnv89.github.io.fr
 * @param  up       uri_proc_t struct
 * @param  host_len length of host name
 * @return          0 - if successful
 *                    !=0 - if failed
 *                    1 - cannot allocate memory for cloning hostname
 *                    2 - Cannot allocate memory for top_domain
 */
int _up_parse_host(uri_proc_t * up, int host_len) {
	// Clone hostname
	char * temp_host = NULL;
	temp_host = (char *) malloc(sizeof(char) * (host_len + 1));
	if (temp_host == NULL) {
		return 1;
	}
	memcpy(temp_host, up->host, host_len);
	temp_host[host_len] = '\0';

	// extract port number
	int port_nb_index = host_len;
	for (port_nb_index = host_len; port_nb_index >= 0; port_nb_index--) {
		if (temp_host[port_nb_index] == ':') {
			break;
		}
	}

	if (port_nb_index > 0) {
		// may found port number
		char * temp_port = NULL;
		int temp_port_length = host_len - port_nb_index;
		temp_port = (char*)malloc(sizeof(char) * (temp_port_length + 1));
		memcpy(temp_port, temp_host + port_nb_index + 1, temp_port_length);
		temp_port[temp_port_length] = '\0';
		unsigned int port_nb = atoi(temp_port);
		if (port_nb > 0 ) {
			up->port_number = port_nb;
			host_len = port_nb_index;
		}
		free(temp_port);
	} else {
		// Guessing the port number based on protocol - this is not always TRUE
		if (up->protocol != NULL) {
			if (strcmp(up->protocol, "http") == 0) {
				up->port_number = 80;
			} else if (strcmp(up->protocol, "https") == 0) {
				up->port_number = 443;
			} else if (strcmp(up->protocol, "ftp") == 0) {
				up->port_number = 21;
			}
		}
	}

	// Find the last index of the based domain which separate top_domain with the sub/based domain.
	int last_index_of_based_domain = _up_get_top_level_index(temp_host, host_len, 0);
	if (last_index_of_based_domain != host_len) {
		char * temp_root_dm = NULL;
		int temp_root_dm_length = host_len - last_index_of_based_domain - 1;
		temp_root_dm = (char *) malloc(sizeof(char) * (temp_root_dm_length + 1));
		if (temp_root_dm == NULL) {
			fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory for top_domain\n");
			free(temp_host);
			return 2;
		} else {
			memcpy(temp_root_dm, temp_host + last_index_of_based_domain + 1, temp_root_dm_length);
			temp_root_dm[temp_root_dm_length] = '\0';
			up->top_domain = temp_root_dm;
		}
	}

	// Extract based domain name
	int based_domain_index = _up_get_based_domain_index(temp_host, last_index_of_based_domain - 1); // -1 for the dot
	char * temp_based_domain = NULL;
	int temp_based_domain_length = 0;
	temp_based_domain_length = last_index_of_based_domain - based_domain_index ;

	temp_based_domain = (char *)malloc(sizeof(char) * (temp_based_domain_length + 1));
	if (temp_based_domain == NULL) {
		fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory for based_domain\n");
		free(temp_host);
		return 3;
	}

	memcpy(temp_based_domain, temp_host + based_domain_index, temp_based_domain_length);
	temp_based_domain[temp_based_domain_length] = '\0';
	up->based_domain = temp_based_domain;

	// Extract sub domain
	if (based_domain_index > 0 ) {
		char * temp_sub_domain = NULL;
		int temp_sub_domain_length = based_domain_index - 1;
		temp_sub_domain = (char * )malloc(sizeof(char) * (temp_sub_domain_length + 1));
		if (temp_sub_domain == NULL) {
			fprintf(stderr, "[error] _up_parse_host: Cannot allocate memory for sub_domain\n");
			free(temp_host);
			return 4;
		}
		memcpy(temp_sub_domain, temp_host, temp_sub_domain_length);
		temp_sub_domain[temp_sub_domain_length] = '\0';
		up->sub_domain = temp_sub_domain;
	}

	free(temp_host);
	return 0;
}

/**
 * Parse a given URI to the path of uri_proc_struct
 * @param  up      given uri_proc_struct
 * @param  uri     given URI : https://www.luongnv89.github.io.fr/radio/france=abc&test
 * @param  uri_len the length of given URI
 * @return         0 - if successfully
 *                 !=0 - if failed
 *                 	1 - invalid input
 *                 	2 - cannot get protocol
 *                 	3 - cannot allocate memory for new protocol
 *                 	4 - cannot allocate memory for a new hostname
 *                 	5 - cannot allocate memory for a new based_uri
 *                 	6 - cannot allocate memory for a new path
 *                 	7 - Cannot allocate memory to clone uri
 *
 */
int _up_parse(uri_proc_t * up, char * uri, int uri_len) {

	if (up == NULL || uri == NULL || uri_len < 9) {
		fprintf(stderr, "[error] _up_parse : Invalid input!\n");
		return 1;
	}

	// Start parsing URI
	// Clone the given URI to process
	char * temp_uri; // https://www.luongnv89.github.io.fr/radio/france=abc&test
	temp_uri = (char*)malloc(sizeof(char) * (uri_len + 1));
	if (temp_uri == NULL) {
		fprintf(stderr, "[error] _up_parse : Cannot allocate memory to clone uri!\n");
		return 7;
	}
	memcpy(temp_uri, uri, uri_len);
	temp_uri[uri_len] = '\0';

	// Get the protocol first - by splitting the URI with `://`
	char * temp_proto = NULL;
	char * proto = NULL;
	int temp_proto_len = 0;
	temp_proto = strstr(temp_uri, "://");
	if (temp_proto == NULL) {
		fprintf(stderr, "[error] _up_parse : Cannot get protocol from given URI: %s!\n", uri);
		free(temp_uri);
		return 2;
	};
	temp_proto_len = temp_proto - temp_uri;
	proto = (char *) malloc(sizeof(char) * (temp_proto_len + 1));
	if (proto != NULL) {
		memcpy(proto, temp_uri, temp_proto_len);
		proto[temp_proto_len] = '\0';
		up->protocol = proto;
	} else {
		fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new protocol\n");
		free(temp_uri);
		return 3;
	}
	// Remove protocol://
	char * temp_uri2 = temp_proto + 3; // www.luongnv89.github.io.fr/radio/france=abc&test

	// Extract hostname - by splitting the remain uri with `/`
	char * temp_host = NULL;
	char * host = NULL; // www.luongnv89.github.io.fr
	int temp_host_length = 0;
	temp_host = strstr(temp_uri2, "/");
	if (temp_host == NULL) {
		// Does not contain path -> only hostname left
		temp_host_length = uri_len - 3 - temp_proto_len;
	} else {
		temp_host_length = temp_host - temp_uri2;
	}
	host = (char *) malloc(sizeof(char) * (temp_host_length + 1));
	if (host != NULL) {
		memcpy(host, temp_uri2, temp_host_length);
		host[temp_host_length] = '\0';
		up->host = host;
	} else {
		fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new host\n");
		free(temp_uri);
		return 4;
	}

	// Get based URI
	char * based_uri = NULL;
	if ( proto != NULL && host != NULL) {
		int based_uri_length = temp_proto_len + 3 + temp_host_length;
		based_uri = (char*)malloc(sizeof(char) * (based_uri_length + 1));
		if (based_uri != NULL) {
			sprintf(based_uri, "%s://%s", proto, host);
			up->based_uri = based_uri;
		} else {
			fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new based_uri\n");
			free(temp_uri);
			return 5;
		}

	}

	// Get path - the rest of temp_uri2 without hostname: /radio/france=abc&test
	char * path = NULL;
	if (temp_host != NULL) {
		int path_length = uri_len - 3 - temp_proto_len - temp_host_length;
		path = (char *)malloc(sizeof(char) * (path_length + 1));
		if (path != NULL) {
			memcpy(path, temp_host, path_length);
			path[path_length] = '\0';
			up->path = path;
		} else {
			fprintf(stderr, "[error] _up_parse: Cannot allocate memory for a new path\n");
			free(temp_uri);
			return 6;
		}
	}

	free(temp_uri);
	return _up_parse_host(up, temp_host_length);
}

/**
 * Check the validation of a hostname
 * @param  hostname given hostname
 * @param  host_len hostname length
 * @return          0 - OK
 *                    1 - hostname is NULL
 *                    2 - hostname contains '/' character
 */
int _up_valid_hostname(char * hostname, int host_len) {
	if (hostname == 0x0) return 1;
	int i = 0;
	for (i = 0 ; i < host_len; i++) {
		if (hostname[i] == '/') {
			return 2;
		}
	}
	return 0;
}

//- - - - - - - - - - - - - - - - - - -
//
//	P U B L I C   F U N C T I O N S
//
//- - - - - - - - - - - - - - - - - - -

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
int up_init(char * domain_location) {
	
	// Init list of country domain
	char country_domain_file[255];
	sprintf(country_domain_file,"%s/%s",domain_location,UP_DOMAIN_CONTRY_CODE);
	country_domain_file[strlen(country_domain_file)] = '\0';
	if (create_string_array_from_file(_up_country_code, country_domain_file,NULL) == 0) {
		fprintf(stderr, "[error] up_init: cannot init list of country domain\n");
		return 1;
	}
	// Init list of top level domain
	char top_domain_file[255];
	sprintf(top_domain_file,"%s/%s",domain_location,UP_DOMAIN_TOP_LEVEL);
	top_domain_file[strlen(top_domain_file)] = '\0';
	if (create_string_array_from_file(_up_top_level, top_domain_file,NULL) == 0) {
		fprintf(stderr, "[error] up_init: cannot init list of top domain\n");
		return 2;
	}
	// Init list of generic domain
	if (_up_load_domain_all_generic(domain_location) == 0){
		fprintf(stderr, "[error] up_init: cannot init list of top domain\n");
		return 3;
	}
	_up_inited = 1;
	return 0;
};

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
uri_proc_t * up_create(char * uri, int uri_len, void * user_args) {
	// Always check for initialisation of static variables
	if(_up_inited == 0){
		fprintf(stderr, "[error] You need to call up_init(domain_location) before using up_\n");
		return NULL;
	}

	int ret_valid = up_valid_uri(uri, uri_len);
	if (ret_valid  != 0 ) {
		fprintf(stderr, "[error] up_create: Invalid URI: %s (error: %d)\n", uri, ret_valid);
		return NULL;
	}

	uri_proc_t * up = _up_new();

	if (up == NULL) {
		return NULL;
	}

	// Update value of uri_proc
	up->length = uri_len;
	up->user_args = user_args; // User argument
	int ret_parse = _up_parse(up, uri, uri_len);
	if ( ret_parse != 0) {
		fprintf(stderr, "[error] up_create: Cannot analyse given URI: %s (error: %d)\n", uri, ret_parse);
		up_free(up);
		return NULL;
	}

	return up;
}

uri_proc_t * up_create_from_host(char * hostname, int host_len, void * user_args) {
	// Always check for initialisation of static variables
	if(_up_inited == 0){
		fprintf(stderr, "[error] You need to call up_init(domain_location) before using up_\n");
		return NULL;
	}

	int ret_valid = _up_valid_hostname(hostname, host_len);

	if (ret_valid != 0) {
		fprintf(stderr, "[error] up_create_from_host: Invalid hostname: %s (error: %d)\n", hostname, ret_valid);
		return NULL;
	}

	uri_proc_t * up = _up_new();

	if (up == NULL) {
		return NULL;
	}

	up->length = host_len;
	up->user_args = user_args;

	char * temp_host = NULL;
	temp_host = (char *) malloc(sizeof(char) * (host_len + 1));
	if (temp_host == NULL) {
		fprintf(stderr, "[error] up_create_from_host: Cannot allocate memory for a new temp_host: %s\n", hostname);
		up_free(up);
		return NULL;
	}
	memcpy(temp_host, hostname, host_len);
	up->host = temp_host;
	int ret_parse = _up_parse_host(up, host_len);
	if ( ret_parse != 0) {
		fprintf(stderr, "[error] up_create_from_host: Cannot analyse given hostname: %s (error: %d)\n", hostname, ret_parse);
		up_free(up);
		return NULL;
	}
	return up;
}

/**
 * Free a uri_proc_struct
 * @param  up given up
 */
void up_free(uri_proc_t *up) {
	if (up == NULL) return;

	if (up->based_uri != NULL) {
		free(up->based_uri);
		up->based_uri = NULL;
	}

	if (up->host != NULL) {
		free(up->host);
		up->host = NULL;
	}

	if (up->based_domain != NULL) {
		free(up->based_domain);
		up->based_domain = NULL;
	}

	if (up->sub_domain != NULL) {
		free(up->sub_domain);
		up->sub_domain = NULL;
	}


	if (up->top_domain != NULL) {
		free(up->top_domain);
		up->top_domain = NULL;
	}


	if (up->protocol != NULL) {
		free(up->protocol);
		up->protocol = NULL;
	}


	if (up->path != NULL) {
		free(up->path);
		up->path = NULL;
	}

	free(up);
};

/**
 * Check the validation of a given URI
 * Make this public because we may use this many times
 * @param  uri     given URI
 * @param  uri_len length of given URI
 * @return         0 - if the given URI is valid
 *                 > 0 - if the given URI is invalid:
 *                 	1 - uri is NULL
 *                 	2 - given length < minimum uri: lenth("ws://t.co") = 9
 *                 	3 - does not contain protocol path: "://"
 *                 	4 - does not contain protocol name: start with "://"
 *                 	5 - end with "://"
 *                 	6 - contains invalid URI
 */
int up_valid_uri(char * uri, int uri_len) {

	if (uri == NULL) return 1;

	// Check the length of URI
	if (uri_len < 9) return 2;

	// Check for protocol path: a URI must contains protocol
	char * proto_path = strstr(uri, "://");
	// Does not contain "://"
	if (proto_path == NULL) return 3;
	// Start with "://"
	if (proto_path == uri) return 4;
	// End with "://"
	if (uri_len - (proto_path - uri) == 3) return 5;

	// Check for special character
	int i = 0;
	for (i = 0; i < uri_len; i ++) {
		if ( _is_uri_character(uri[i]) != 0) {
			return 6;
		}
	}

	return 0;
}

/**
 * Get based URI
 * @param  up [description]
 * @return    [description]
 */
char * up_get_based_uri(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->based_uri;
};


char * up_get_host(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->host;
};


char * up_get_based_domain(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->based_domain;
};


char * up_get_sub_domain(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->sub_domain;
};

char * up_get_top_domain(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->top_domain;
};

char * up_get_protocol(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->protocol;
};

char * up_get_path(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->path;
};

void * up_get_user_arguement(uri_proc_t * up) {
	if (up == NULL) return NULL;
	return up->user_args;
};

unsigned int up_get_port_number(uri_proc_t * up){
	if(up == NULL) return 0;
	return up->port_number;
};

void up_show(uri_proc_t * up) {
	if (up == NULL) {
		printf("\nuri_proc is NULL!\n");
	} else {
		printf("\nUP: \n");
		printf("Length: %d\n", up->length );
		printf("based_uri: %s\n", up->based_uri );
		printf("host: %s\n", up->host );
		printf("port_number: %d\n", up->port_number );
		printf("sub_domain: %s\n", up->sub_domain );
		printf("based_domain: %s\n", up->based_domain );
		printf("top_domain: %s\n", up->top_domain );
		printf("protocol: %s\n", up->protocol );
		printf("path: %s\n", up->path );
	}
};

void up_close() {
	
	int i =0 ;
	//free list of country code
	for(i = 0; i < UP_NUMBER_COUNTRY_CODE; i ++){
		if(_up_country_code[i]!=NULL) free(_up_country_code[i]);
	}

	// Free list of top level
	for(i = 0; i < UP_NUMBER_TOP_LEVEL; i ++){
		if(_up_top_level[i]!=NULL) free(_up_top_level[i]);
	}	

	// Free list of generic domain
	int j = 0; 
	for(j = 0; j < UP_MAX_DOMAIN_LENGTH; j++){
		for(i = 0; i < UP_NUMBER_GENERIC_DOMAIN; i ++){
			if(_up_generic[j][i]!=NULL) free(_up_generic[i]);
		}	
	}

	_up_inited = 0;
#ifdef DEBUG
	printf("Cleaned uri_proc!\n");
#endif	
	
}

int create_string_array_from_file(char ** list_strings, char * fileName, int * counter) {
    if (access(fileName, R_OK) == -1) {
        fprintf(stderr, "[error] create_string_array_from_file: file does not exists: %s\n", fileName);
        return 0;
    }
    
    FILE *fd = NULL;
    
    fd = fopen(fileName, "r");
    
    if (fd == NULL) {
        fprintf(stderr, "[error] create_string_array_from_file: Cannot read file: %s\n", fileName);
        return 0;
    } else {
        int index = 0;
        char * buffer;
        buffer = (char*)malloc(sizeof(char) * UP_MAX_BUFFER_SIZE);
        while (fgets(buffer, UP_MAX_BUFFER_SIZE, (FILE*)fd) != NULL) {
            int length = strlen(buffer);
            char * new_string = NULL;
            new_string = (char *) malloc(sizeof(char) * (length+1));
            memcpy(new_string, buffer, length);
            new_string[length] = '\0';
            list_strings[index] = new_string;
            index++;
        }
        if(counter!=NULL) *counter = index;
        list_strings[index] = 0x0;
        free(buffer);
    }
    fclose(fd);
    return 1;
}