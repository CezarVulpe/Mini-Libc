// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>


void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
	void *mem=mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	mem_list_add(mem,size);
	return mem;
}


void *calloc(size_t nmemb, size_t size)
{
	void *mem=malloc(nmemb*size);
	mem=memset(mem,0, nmemb* size);
    return mem;
}


void free(void *ptr)
{
	/* TODO: Implement free(). */
	struct mem_list* structura;
	structura=mem_list_find(ptr);
	munmap(ptr,structura->len);
	mem_list_del(ptr);

}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	void *mem=malloc(size);
	memcpy(mem,ptr,size);
	free(ptr);
	return mem;

}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */

	size_t max_sizet=(size_t) -1;
	if(nmemb>max_sizet/size) return NULL;

	void *mem=malloc(size*nmemb);
	memcpy(mem,ptr,size*nmemb);
	free(ptr);
	return mem;
}
