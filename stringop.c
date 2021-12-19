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

char * put_type(char * buffer, int * dest){
	char * ptr = buffer;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\r' || *ptr == '\n') ptr++;
	if (*ptr == 'r') *dest = -1;
	else if (*ptr == 'e') *dest = 1;
	else if (*ptr == 'v') *dest = 2;
	else if (*ptr == 'b') *dest = 3;
	else *dest = 0;
	return ptr+1;
}

char * put_int_s(char * buffer, int * dest){
	char * ptr = buffer;
	int out = 0;
	while (*ptr == ' ' || *ptr == '\t' || *ptr == '\r' || *ptr == '\n') ptr++;
	if (*ptr == '-'){
		*dest = 0;
		return ptr+1;
	}
	else if (*ptr >= '0' && *ptr <= '9') {
		while (*ptr >= '0' && *ptr <= '9'){
			out *= 10;
			out += *ptr - '0';
			ptr++;
		}
		*dest = out;
		return ptr;
	}
	else {
		*dest = -1;
		return ptr;
	}
}
