#include <stdio.h>
#include <string.h>

int main (int argc, char * argv []) {
	struct {
		char buf [8];
		unsigned ver;
	} s;
	s.ver = 100;
	strcpy (s.buf, argv [0]);
	printf ("version: %u\n", s.ver);
	return 0;
}
