#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR_LINE 100

int main(int argc, char *argv[]) 
{
	const char *filename = "A2_1_data.csv";
	FILE *fp = fopen(filename, "r");

	char data[MAXCHAR_LINE];
	int row_count = 0;

	while (!feof(fp)) {
		fgets(data, MAXCHAR_LINE, fp);
		row_count++;
	}
	row_count -= 1; // x rows, x-1 indexing
	
	fseek(fp, 0, SEEK_SET);

	printf("No. of rows: %d\n", row_count);
	int (*elements)[2];
	elements = calloc(row_count, sizeof(*elements));

	for (int i=0; i<row_count; ++i) {
		fgets(data, MAXCHAR_LINE, fp);
		sscanf(data, "%d,%d\n", &elements[i][0], &elements[i][1]);
		printf("Row: %d, %d\n", elements[i][0], elements[i][1]);
	}
}
