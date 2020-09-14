#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)

{
	if(getenv("TEST"))
	{
		printf("test is valid\n");
	}
	else

	{
		printf("test is invalid!\n");
	}
	return 0;
}
