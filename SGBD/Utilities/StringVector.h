typedef struct
{
	char **tab;
	int length;
} StringVector;

StringVector *createStringVector();

int addStringToVector(StringVector *vec, char *mot);
int removeStringToVector(StringVector *vec, char *mot);

void deleteStringVector(StringVector *vec);
