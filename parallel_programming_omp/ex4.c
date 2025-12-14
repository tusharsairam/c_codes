#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define MAXCHAR_LINE 100
#define N_BOOT 10000000 // I run a fairly powerful machine so I chose 10 million

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

	// printf("No. of rows: %d\n", row_count);
	int (*elements)[2];
	elements = calloc(row_count, sizeof(*elements));

	for (int i=0; i<row_count; ++i) {
		fgets(data, MAXCHAR_LINE, fp);
		sscanf(data, "%d,%d\n", &elements[i][0], &elements[i][1]);
		// printf("Row: %d, %d\n", elements[i][0], elements[i][1]);
	}
	
	int t_large_count = 0;
	int x1_mean, x2_mean, x1_var, x2_var, t_value;
	srand(time(NULL));

	// Random sample with replacement
	for (int x=0; x<N_BOOT; ++x) {
		x1_mean = 0; 
		x2_mean = 0;
	
		for (int i=0; i<row_count; ++i) {
			int rand_idx = rand() % row_count;
			x1_mean += elements[rand_idx][0];
			x2_mean += elements[rand_idx][1];
		}
		x1_mean /= row_count;
		x2_mean /= row_count;

		// printf("Means: %f, %f\n", x1_mean, x2_mean);
	
		// Calculate the variances of column 1 and 2
		x1_var = 0.0;
		x2_var = 0.0;
		
		for (int i=0; i<row_count; ++i) {
			int rand_idx = rand() % row_count;
			x1_var += pow(elements[rand_idx][0] - x1_mean, 2);
			x2_var += pow(elements[rand_idx][1] - x2_mean, 2);
			// printf("%d, %f", elements[rand_idx][0], x1_mean);
		}	
		x1_var /= row_count;
		x2_var /= row_count;
		// printf("Vars: %f, %f\n", x1_var, x2_var);
	
		// t-statistic 
		t_value = 0.0;
		t_value = (x2_mean - x1_mean) / sqrt(x1_var + x2_var);

		// printf("t statistic: %f\n", t_value);
		// 00.759133 was the value of the t-stat obtained from ex. 3
		if (t_value >= 0.759133) 
			t_large_count++;
	}
	
	printf("No. times t >= 0.759133: %d\n", t_large_count);
}

