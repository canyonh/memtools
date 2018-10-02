#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

int main(int argc, char*argv[])
{
	char ten[] = "1234567890";
	char *p = (char*) malloc(sizeof(ten) - 1);
	memcpy(p, ten, sizeof(ten));
	free(p);
	return 0;
}
