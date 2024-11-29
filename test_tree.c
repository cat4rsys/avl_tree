#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

extern int counterOfNodes;

void* str_clone(const void* a) {
	return strdup((const char*)a);
}

int str_cmp(const void* a, const void* b) {

	return strcmp((const char*)a, (const char*) b);
}


int tree_print(Tree* t, int level, void* v) {
	//for(int i = 0; i < level; i++ ) printf("\t");
	//printf("%s\n", (char*)v);
	fputs((char*)v, stdout);
	return 0;
}

#define SEC_TO_US(sec) ((sec)*1000000)
#define NS_TO_US(ns)   ((ns)/1000)

uint64_t micros()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    uint64_t us = SEC_TO_US((uint64_t)ts.tv_sec) + NS_TO_US((uint64_t)ts.tv_nsec);
    return us;
}

int main() {
	char buf[1024];
	char id[1024];
	uint64_t treeInitTime = micros();
	Tree *tree = tree_create(str_clone, str_cmp, free);
	while(fgets(buf, sizeof(buf), stdin)) {
		/*
		if (sscanf(buf, "A %s", id) == 1) {
			tree_insert(tree, id);
		} else if ( sscanf(buf, "D %s", id) == 1 ) {
			tree_delete(tree, id);
		} else if ( sscanf(buf, "S %s", id) == 1 ) {
			char* result;
			if ( tree_search(tree, id, (void**)&result)  ) {
				printf("%s Found\n", result);
			} else {
				printf("Not found\n");
			}
		} else {
			printf("unknown command\n");
		}
		printf("After insert\n");
		tree_traverse(tree, NULL, tree_print);
		*/
		tree_insert(tree, buf);
	}
	//printf("%d %lu\n", counterOfNodes, micros() - treeInitTime);
	
	uint64_t treeSearchTime = micros();
	tree_search(tree, "abc", (void **)&buf);             // max time of search - when there is no such element in tree
	printf("%d %lu\n", counterOfNodes, micros() - treeSearchTime);

	uint64_t treeDeleteTime = micros();
	tree_delete(tree, "1");
	//printf("%d %lu\n", counterOfNodes, micros() - treeDeleteTime);

	//tree_traverse(tree, NULL, (tree_cb)tree_print);
	tree_destroy(tree);

}
