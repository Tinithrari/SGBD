#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../Utilities/StringVector.h"

#define STR1 "t1"
#define STR2 "t2"
#define STR3 "t3"
#define STR4 "t4"
#define STR5 "t5"

#define SUCCESS_STR "DONE !"

int main()
{
	StringVector *vec;

	vec = createStringVector();

	assert(vec != NULL);

	assert(addStringToVector(vec, STR1));
	assert(addStringToVector(vec, STR2));
	assert(addStringToVector(vec, STR3));
	assert(addStringToVector(vec, STR4));

	assert(! removeStringToVector(vec, STR5) );

	assert( removeStringToVector(vec, STR1) );
	assert( removeStringToVector(vec, STR3) );

	deleteStringVector(vec);
}
