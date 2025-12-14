#include <stdio.h>

// Ex. 1: Assume you know the row count
#define MAXCHAR_LINE 100
#define N_ROWS 10

int main(int argc, char *argv[])
{
	const char *filename = "A2_1_data.csv";
	FILE *fp = fopen(filename, "r");
	
	char data[MAXCHAR_LINE];
	int elements[N_ROWS][N_COLS];
	int row_counter = 0;
	int col_counter = 0;

	while (!feof(fp)) {
		fgets(data, MAXCHAR_LINE, fp);
		sscanf(data, "%d,%d\n", &elements[row_counter][0], &elements[row_counter][1]);
		row_counter++;	
	}

	// Testing to check if I did the CSV read correctly
	for (int r=0; r<N_ROWS; ++r) {
		printf("Row: %d, %d\n", elements[r][0], elements[r][1]);
	}
}
