// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	int i=0;
	while(source[i]!='\0')
	{
		destination[i]=source[i];
		i++;
	}
	destination[i]='\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	unsigned int i=0;
	size_t lungimedest=strlen(destination);
	while(source[i]!='\0' && i<len)
	{
		destination[i]=source[i];
		i++;
	}
	if(lungimedest<len) destination[i]='\0';
	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	int i=0,j=0;
	while(destination[i]!='\0')
	{
		i++;
	}
	while(source[j]!='\0')
	{
		destination[i+j]=source[j];
		j++;
	}
	destination[i+j]='\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	size_t i=0,j=0;
	while(destination[i]!='\0')
	{
		i++;
	}
	while(source[j]!='\0' && j<len)
	{
		destination[i+j]=source[j];
		j++;
	}
	destination[i+j]='\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
	int i=0;
	while(str1[i]!='\0' && str2[i]!='\0') {
		if(str1[i]>str2[i]) return 1;
		if(str1[i]<str2[i]) return -1;
		i++;
	}
	if(str1[i]=='\0' && str2[i]=='\0') return 0;
	if(str1[i]=='\0') return -1;
	return 1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
	size_t i=0;
	while(str1[i]!='\0' && str2[i]!='\0' && i<len) {
		if(str1[i]>str2[i]) return 1;
		if(str1[i]<str2[i]) return -1;
		i++;
	}
	if(str1[i]=='\0' && str2[i]=='\0') return 0;
	if(i==len) return 0;
	if(str1[i]=='\0') return -1;
	return 1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	size_t i=0;
	while(str[i]!='\0')
	{
		if(str[i]==c) {
			return (char*)(str + i);
		}
		i++;
	}
	return '\0';
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	size_t i=0;
	int ultimpoz=-1;
	while(str[i]!='\0')
	{
		if(str[i]==c) ultimpoz=i;
		i++;
	}
	if(ultimpoz==-1) return NULL;
	return (char*)(str+ultimpoz);
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	size_t i=0,j=0,lungimeneed=strlen(needle);
	while(haystack[i]!='\0')
	{
		j=0;
		while(j<lungimeneed)
		{
			if(haystack[i+j]!=needle[j]) break;
			j++;
		}
		if(j==lungimeneed) return (char*)(haystack+i);
		i++;
	}
	return '\0';
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
	size_t i=0,j=0,lungimeneed=strlen(needle);
	int ultimpoz=-1;
	while(haystack[i]!='\0')
	{
		j=0;
		while(j<lungimeneed)
		{
			if(haystack[i+j]!=needle[j]) break;
			j++;
		}
		if(j==lungimeneed) ultimpoz=i;
		i++;
	}
	if(ultimpoz==-1) return NULL;
	return (char*)(haystack+ultimpoz);
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	size_t i=0;
	size_t lungimedest=strlen(destination);
	while(((char *)source)[i]!='\0' && i<num)
	{
		((char *)destination)[i]=((char *)source)[i];
		i++;
	}
	if(lungimedest<num) ((char *)destination)[i]='\0';
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	size_t i=0;
	size_t lungimedest=strlen(destination);
	while(((char *)source)[i]!='\0' && i<num)
	{
		((char *)destination)[i]=((char *)source)[i];
		i++;
	}
	if(lungimedest<num) ((char *)destination)[i]='\0';
	return destination;
}



int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	size_t i=0;
	while(((char *)ptr1)[i]!='\0' && ((char *)ptr2)[i]!='\0' && i<num) {
		if(((char *)ptr1)[i]>((char *)ptr2)[i]) return 1;
		if(((char *)ptr1)[i]<((char *)ptr2)[i]) return -1;
		i++;
	}
	if(((char *)ptr1)[i]=='\0' && ((char *)ptr2)[i]=='\0') return 0;
	if(i==num) return 0;
	if(((char *)ptr1)[i]=='\0') return -1;
	return 1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
    for (size_t i = 0; i < num; i++) {
        ((char *)source)[i] = (unsigned char)value;
    }
	return source;
}