#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free e atoi */
#include <string.h> /* strcpy */

#include "case_two_gen.h"

int main(int argc, char **argv)
{
	int l;
	if (argc == 1 || argc >= 3)
		l = 4;
	else
		l = atoi(argv[1]);

	char **masks = create_masks(l);
	masks = fill_masks(l,masks);
	masks = shuffle_lengths(l,masks);

	print_masks(masks);
	return 0;
}

char **create_masks(int l)
{
	char **result = malloc(sizeof(char *));
	result[0] = NULL;

	char *temp = malloc(sizeof(char)*(l+1));
	temp[l] = 0;

	result = permutotion(l,result,temp,0,0,0);

	return result;
}

char **permutotion(int l, char **result, char *temp, int i, int blanks,
		int erasers)
{
	if (i == l) {
		int j = 0;
		while (result[j] != NULL)
			j++;

		result = realloc(result,sizeof(char *)*(j+2));
		result[j] = strdup(temp);
		result[j+1] = NULL;
	} else {
		if (blanks < l/2) {
			temp[i] = BLANK;
			result = permutotion(l,result,temp,i+1,
					blanks+1,erasers);
		}
		if (erasers < l - (l/2)) {
			temp[i] = ERASER;
			result = permutotion(l,result,temp,i+1,
					blanks,erasers+1);
		}
	}

	return result;
}

char **fill_masks(int l, char **masks)
{
	for (int i=0; masks[i]!=NULL; i++) {
		for (int j=0; j<l; j++) {
			if (masks[i][j] == BLANK)
				masks[i][j] = ALPHA[j];
		}
	}

	return masks;
}

char **shuffle_lengths(int l, char **masks)
{
	int k = 0;
	for (int i=0; masks[i]!=NULL; i++, k=(k+1)%MAX_CONCAT) {

		masks[i] = realloc(masks[i],sizeof(char)*(l+1+k));
		for (int j=0; j<k; j++)
			masks[i][l+j] = FILLER;
		masks[i][l+k] = 0;
	}

	return masks;
}


void print_masks(char **masks)
{
	for (int i=0; masks[i]!=NULL; i++)
		printf("%s\n",masks[i]);
}
