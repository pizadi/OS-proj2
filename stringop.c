#include "stringop.h"

char * print_int(char * buffer, int i) {
	char * ptr = buffer;
	if (i | (1 << (8*sizeof(int)-1))) {
		*ptr = '-';
		ptr++;
		i = ~i + 1;
	}
	int t = 0;
	char digits[10];
	if (i){
		while (i){
			digits[t] = i%10;
			i = i/10;
			t++;
		}
		while (t){
			*ptr = '0' + digits[t];
			ptr++;
			t--;
		}
		ptr = '\0';
		return ptr;
	}
	else {
		*ptr = '0';
		*(ptr+1) = '\0';
		return ptr+1;
	}
}
