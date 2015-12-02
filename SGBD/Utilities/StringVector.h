typedef struct
{
	char **tab;
	int length;
} StringVector;

StringVector *createStringVector();

int addStringToVector(StringVector *vec, char *mot);
int removeStringVector(StringVector *vec, char *mot);

void deleteStringVector(StringVector *vec);
