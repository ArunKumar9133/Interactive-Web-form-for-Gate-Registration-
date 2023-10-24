#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

char *HelpMessage = "create-random-matrix -r rows -c cols -o output_file\n";
#define CommandArgs "r:c:o:"

int num_rows;
int num_cols;
char *output_file_path;

int main(int argc, char **argv)
{
    int option;
    int i;
    int j;
    double random_val;
    struct timeval timestamp;
    unsigned long seed;

    FILE *output_file;

    while ((option = getopt(argc, argv, CommandArgs)) != EOF)
    {
        switch (option)
        {
            case 'r':
                num_rows = atoi(optarg);
                break;
            case 'c':
                num_cols = atoi(optarg);
                break;
            case 'o':
                output_file_path = optarg;
                break;
            default:
                fprintf(stderr, "unrecognized option %c\n", (char)option);
                fprintf(stderr, "usage: %s", HelpMessage);
                exit(1);
        }
    }

    if (num_rows <= 0)
    {
        fprintf(stderr, "please specify the number of rows\n");
        fprintf(stderr, "usage: %s", HelpMessage);
        exit(1);
    }

    if (num_cols <= 0)
    {
        fprintf(stderr, "please specify the number of columns\n");
        fprintf(stderr, "usage: %s", HelpMessage);
        exit(1);
    }

    if (output_file_path == NULL)
    {
        fprintf(stderr, "please specify an output file path\n");
        fprintf(stderr, "usage: %s", HelpMessage);
        exit(1);
    }

    gettimeofday(&timestamp, NULL);
    seed = timestamp.tv_sec + timestamp.tv_usec;
    srand48(seed);

    output_file = fopen(output_file_path, "w");
    if (output_file == NULL)
    {
        fprintf(stderr, "error opening output file\n");
        exit(1);
    }

    fprintf(output_file, "%d %d\n", num_rows, num_cols);
    for (i = 0; i < num_rows; i++)
    {
        fprintf(output_file, "# Row %d\n", i);
        for (j = 0; j < num_cols; j++)
        {
            random_val = drand48();
            fprintf(output_file, "%f\n", random_val);
        }
    }

    fclose(output_file);

    exit(0);
}

