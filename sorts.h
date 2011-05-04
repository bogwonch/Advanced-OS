#ifndef SORTS_H_
#define SORTS_H_

static void insert_sort(char *strings[], int n);
static void shell_sort(char *strings[], int n);
static void randomise(char *strings[], int n);
static void check_order(char *sort_type, char *strings[], int n);
int qs_string_compare(const void *a, const void *b);
int sort_main(void);






#endif /*SORTS_H_*/
