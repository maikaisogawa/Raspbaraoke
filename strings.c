#include "strings.h"

void *memset(void *s, int c, size_t n)
{
    unsigned char * loc = (unsigned char *)s;
    unsigned char ch = (unsigned char)c;
    for (int i = 0; i < n; i++) {
	loc[i] = ch;
    }

    return s;
}

void *memcpy(void *dst, const void *src, size_t n)
{
    unsigned char * dest = (unsigned char *)dst;
    unsigned char * source = (unsigned char *)src;
    for (int i = 0; i < n; i++) {
	dest[i] = source[i];
    }

    return dst;
}

int strlen(const char *s)
{
    /* Implementation a gift to you from lab3 */
    int i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

int strcmp(const char *s1, const char *s2)
{
    int shortest_length = (strlen(s1) > strlen(s2) ? strlen(s2) : strlen(s1));
    for (int i = 0; i < shortest_length; i++) {
	if (s1[i] < s2[i]) {
	    return -1;
	} else if (s1[i] > s2[i]) {
	    return 1;
	}
    }
    if (strlen(s2) > strlen(s1))  {
	return -1;
    } else if (strlen(s2) < strlen(s1)) {
	return 1;
    } else {
	return 0;
    }
}

int strlcat(char *dst, const char *src, int maxsize)
{
   int counter = strlen(dst);
   for (int i = 0; i < strlen(src); i++) {
	if (counter < (maxsize - strlen(dst) - 1)) {
	    dst[counter + i] = src[i];
	} else {
	    break;
	}
   }
   dst[strlen(dst)] = '\0';	
   return counter + strlen(src);
}

int power(int base, int exponent) {
    if (exponent == 0) {
	return 1;
    } else {
        int pwr = 1;
        for (int i = 0; i < exponent; i++) {
	    pwr *= base;
	}
	return pwr;
    }
}

unsigned int convert_to_int(const char *str, int base, const char **endptr) 
{
    int loc = 0;
    char curr_val = str[0];
    unsigned int final_val = 0;
    for (int i = 0; i < strlen(str); i++) {
	if (base == 16 && str[i] > 96) { 
	    curr_val = str[i] - 'W';
	    if (curr_val > 15) {
		break;
	    }
	} else {
	    curr_val = str[i] - '0';
	    if (curr_val > 9) {
		break;
	    }	
	}
	final_val += ((int) curr_val * (power(base, (strlen(str) - i - 1))));
	loc++;
    }
    *endptr = &str[loc];
    return final_val;
}

unsigned int strtonum(const char *str, const char **endptr)
{
    unsigned int result = NULL;
    if (str[0] == '0' && str[1] == 'x') {
	result = convert_to_int(str + 2, 16, endptr);
    } else {
	result = convert_to_int(str, 10, endptr);
    }
    
    return result;
}
