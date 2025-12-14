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

	// Calculate the mean of column 1 and column 2
	float x1_mean = 0, x2_mean = 0;
	for (int i=0; i<row_count; ++i) {
		x1_mean += elements[i][0];
	       	x2_mean += elements[i][1];
	}
	x1_mean /= row_count;
	x2_mean /= row_count;
	printf("Means: %f, %f\n", x1_mean, x2_mean);

	// Calculate the variances of column 1 and 2
	float x1_var = 0.0, x2_var = 0.0;
	for (int i=0; i<row_count; ++i) {
		x1_var += pow(elements[i][0] - x1_mean, 2);
		x2_var += pow(elements[i][1] - x2_mean, 2);
	}	
	x1_var /= row_count;
	x2_var /= row_count;
	printf("Vars: %f, %f\n", x1_var, x2_var);

	// t-statistic 
	float t_value = 0.0;
	t_value = (x2_mean - x1_mean) / sqrt(x1_var + x2_var);

	printf("t statistic: %f\n", t_value);
}
