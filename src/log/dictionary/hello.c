#include <sys/time.h>
#include <stdio.h>
#include "hashdict.h"

int main() {
	struct dictionary* dic = dic_new(0);
	
	dic_add(dic, "ABC", 3);
	*dic->value = 100;
	
	dic_add(dic, "DE", 2);
	*dic->value = 200;
	
	dic_add(dic, "HJKL", 4);
	*dic->value = 300;
	
	if (dic_find(dic, "ABC", 3))
		printf("ABC found: %i\n", *dic->value);
	else printf("error\n");
	
	if (dic_find(dic, "DE", 2))
		printf("DE found: %i\n", *dic->value);
	else printf("error\n");
	
	if (dic_find(dic, "HJKL", 4))
		printf("HJKL found: %i\n", *dic->value);
	else printf("error\n");
	
	dic_delete(dic);
	return 0;
}
