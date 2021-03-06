#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef UNIX
#include <unistd.h>
#endif

#include "Utilities/StringVector.h"
#include "View/ConsoleView.h"

#define INPUT_OPTION "-i"
#define OUTPUT_OPTION "-o"

#define ERROR_OUTPUT "ERR_OUTPUT_FILE"

int main(int argc, char **argv)
{
	char** input_streams = NULL;
	char *output = NULL;
	int nbFile = 0;
	if (argc > 1)
	{
		int i;
		for (i = 1; i < argc; i++)
		{
			if ( !strcmp(*(argv + i),INPUT_OPTION) )
			{
				i++;

					#ifdef WINDOWS
						struct _stat s;
						_stat(*(argv + i), &s);

					#elif defined(UNIX)
						struct stat s;
						stat(*(argv + i), &s);
					#endif

				if (errno == ENOENT)
					fprintf(stderr, "Cannot open the file %s : %s\n", *(argv + i), strerror(errno));
				else
				{
					char** tmp = (char**)realloc(input_streams, (nbFile + 1) * sizeof(FILE*));

					if (tmp == NULL)
						fprintf(stderr, "Cannot read %s : Not enough RAM\n", *(argv + i));
					else
					{
						input_streams = tmp;

						input_streams[nbFile] = *(argv + i);
						nbFile++;
					}
				}
			}

			else if ( !strcmp(*(argv + i),OUTPUT_OPTION) )
			{
				i++;
				if (i < argc || output != NULL)
				{
					#ifdef WINDOWS
						struct _stat s;
						_stat(*(argv + i), &s);

					#elif defined(UNIX)
						struct stat s;
						stat(*(argv + i), &s);
					#endif

					if (errno == ENOENT)
						output= *(argv + i);
					else
						fprintf(stderr, "%s\n", ERROR_OUTPUT);
				}
				else
					fprintf(stderr, "%s\n", ERROR_OUTPUT);

			}
			else
				fprintf(stderr, "Usage : %s [-i input_files][-o output_file]\n", *argv);
		}
	}

	if (output != NULL)
	{
		freopen(output, "w", stdout);
		freopen(output, "w", stderr);
	}

	run(input_streams, nbFile);
}
