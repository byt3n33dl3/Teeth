#include <sys/time.h>
#include <stdio.h>
#include "hashdict.h"

int time1000() {
	struct timeval val;
	gettimeofday(&val, 0);
	val.tv_sec &= 0xffff;
	return val.tv_sec * 1000 + val.tv_usec / 1000;
}

int main() {
	int best_ins = 9999, best_find = 9999, t, iters = 10;
	printf("running %i iterations\n", iters); fflush(0);
	for (int z = 0; z < iters; z++) printf(" ");
	printf(" |\r|");fflush(0);
	for (int z = 0; z < iters; z++) {
		int T = time1000(), i, KEY_SIZE = 8;
		__int64_t STEPS = 100000, STEP = 500000000, key;
		struct dictionary* dic = dic_new(STEPS*1.3);
		key = 0;
		for (i = 0; i < STEPS; i++) {
			key += STEP;
			dic_add(dic, &key, KEY_SIZE);
			*dic->value = (key+55) & 0xff;
		}
		t = time1000() - T;
		if (t < best_ins) best_ins = t;
		T = time1000();
		int err = 0;
		key = 0;
		for (i = 0; i < STEPS; i++) {
			key += STEP;
			if (dic_find(dic, &key, KEY_SIZE)) {
				if (*dic->value != ((key+55) & 0xff)) err++;
			}
			else err++;
		}
		t = time1000() - T;
		if (t < best_find) best_find = t;
		if (err > 0) {
			printf("errors:%i\n", err);
			return 0;
		}
		dic_delete(dic);
		printf(" >\b"); fflush(0);
	}
	printf(" \r");
	printf("lowest insert time:%i\n", best_ins);
	printf("lowesr find time:%i\n", best_find);
	return 0;
}
