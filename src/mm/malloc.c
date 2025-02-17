
// SPDX-License-Identifier: BSD-3-Clause
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <block_meta.h>
#include <string.h>


#define MMAP_THRESHOLD (128 * 1024)
#define BLOCK_ALIGN 8
#define INITIAL_HEAP_SIZE (128 * 1024)
static size_t align_size(size_t size)
{
	return (size + sizeof(struct block_meta) + 7) & ~7;
}

void *heap;
struct block_meta *varf = NULL, *curent = NULL;

size_t spatiuramas;

static struct block_meta *find_best_fit(size_t size)
{
	struct block_meta *aux = varf;
	struct block_meta *best_fit = NULL;

	while (aux != NULL) {
		if (aux->status == STATUS_FREE && aux->size >= size && (best_fit == NULL || aux->size < best_fit->size))
			best_fit = aux;
		aux = aux->next;
	}
	if (best_fit == NULL) {
		if (curent != NULL) {
			if (curent->status == 0) {
				sbrk(size - curent->size);
				curent->size = size;
				curent->status = 1;
				return curent;
			}
		}
	}
	return best_fit;
}

static void split_block(struct block_meta **block, size_t size)
{
	if ((*block)->size >= size + sizeof(struct block_meta) + 8) {
		struct block_meta *new_block = (struct block_meta *)((char *)(*block) + size);

		new_block->size = (*block)->size - size;
		new_block->status = STATUS_FREE;
		new_block->prev = (*block);
		new_block->next = (*block)->next;
		if ((*block)->next != NULL)
			(*block)->next->prev = new_block;
		else
			curent = new_block;
		(*block)->size = size;
		(*block)->next = new_block;
		(*block)->status = 1;
	} else {
		(*block)->status = 1;
	}
}

static void coalesce_blocks(struct block_meta *block)
{
	struct block_meta *copie = block;

	while (block->next != NULL && block->next->status == STATUS_FREE) {
		block->size += block->next->size;
		block->next = block->next->next;

		if (block->next != NULL)
			block->next->prev = block;
	}
	block = copie;
	while (block != NULL && block->prev != NULL && block->prev->status == STATUS_FREE) {
		block->prev->size += block->size;
		block->prev->next = block->next;
		if (block->next != NULL)
			block->next->prev = block->prev;
		block = block->prev;
	}
}

void *malloc(size_t size)
{
	if (size == 0)
		return NULL;
	size_t totalsize = align_size(size);
	struct block_meta *best_fit = find_best_fit(totalsize);

	if (best_fit == NULL) {
		if (totalsize < MMAP_THRESHOLD) {
			if (heap == NULL) {
				heap = sbrk(INITIAL_HEAP_SIZE);
				spatiuramas = INITIAL_HEAP_SIZE;
				if (heap == (void *)-1)
					DIE(1, "sbrk");
			}
			void *p = NULL;

			if (totalsize < spatiuramas) {
				spatiuramas -= totalsize;
				p = heap;
				heap = heap + totalsize;
			} else {
				p = sbrk(totalsize);
				spatiuramas = 0;
			}
			struct block_meta *p1 = (struct block_meta *)p;

			p1->size = totalsize;
			p1->status = 1;
			if (varf == NULL) {
				varf = p1;
				p1->prev = NULL;
				p1->next = NULL;
				curent = p1;
			} else {
				curent->next = p1;
				p1->prev = curent;
				p1->next = NULL;
				curent = p1;
			}
			return (void *)(p1 + 1);
		}
		size_t totalsize = align_size(size);
		void *p = mmap(NULL, totalsize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (p == (void *)-1)
			DIE(1, "mmap");
		struct block_meta *p1 = (struct block_meta *)p;

		p1->size = totalsize;
		p1->status = 2;
		return (void *)(p1 + 1);
	}
	best_fit->status = 1;
	split_block(&best_fit, totalsize);

	return (void *)(best_fit + 1);
}

void *malloccaloc(size_t size)
{
	if (size == 0)
		return NULL;

	size_t totalsize = align_size(size);
	struct block_meta *best_fit = find_best_fit(totalsize);

	if (best_fit == NULL) {
		if (totalsize < 4096) {
			if (heap == NULL) {
				heap = sbrk(INITIAL_HEAP_SIZE);
				spatiuramas = INITIAL_HEAP_SIZE;
				if (heap == (void *)-1)
					DIE(1, "sbrk");
			}
			void *p = NULL;

			if (totalsize < spatiuramas) {
				spatiuramas -= totalsize;
				p = heap;
				heap = heap + totalsize;
			} else {
				p = sbrk(totalsize);
			}
			struct block_meta *p1 = (struct block_meta *)p;

			p1->size = totalsize;
			p1->status = 1;
			if (varf == NULL) {
				varf = p1;
				p1->prev = NULL;
				p1->next = NULL;
				curent = p1;
			} else {
				curent->next = p1;
				p1->prev = curent;
				p1->next = NULL;
				curent = p1;
			}
			return (void *)(p1 + 1);
		}
		size_t totalsize = align_size(size);
		void *p = mmap(NULL, totalsize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (p == (void *)-1)
			DIE(1, "mmap");
		struct block_meta *p1 = (struct block_meta *)p;

		p1->size = totalsize;
		p1->status = 2;
		return (void *)(p1 + 1);
	}
	best_fit->status = 1;
	split_block(&best_fit, totalsize);

	return (void *)(best_fit + 1);
}

void *calloc(size_t nmemb, size_t size)
{
	size_t total_size = nmemb * size;
	void *ptr = malloccaloc(total_size);

	if (ptr != NULL)
		memset(ptr, 0, total_size);

	return ptr;
}

void *realloc(void *ptr, size_t size)
{
	size_t noulsizetotal = align_size(size);

	if (ptr == NULL)
		return malloc(size);
	if (size == 0) {
		free(ptr);
		return NULL;
	}
	struct block_meta *block = (struct block_meta *)ptr - 1;

	if (block->status == 0)
		return NULL;
	if (block->size == noulsizetotal)
		return ptr;
	if (block->size > MMAP_THRESHOLD) {
		if (noulsizetotal > MMAP_THRESHOLD) {
			void *p = mmap(NULL, noulsizetotal, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

			if (p == (void *)-1)
				DIE(1, "mmap");
			struct block_meta *p1 = (struct block_meta *)p - 1;

			p1->size = noulsizetotal;
			p1->status = 2;
			if (block->size > p1->size)
				memcpy(p1 + 1, block + 1, p1->size - sizeof(struct block_meta));
			else
				memcpy(p1 + 1, block + 1, block->size - sizeof(struct block_meta));
			free(ptr);
			return (void *)(p1 + 1);
		}
		void *p = malloc(size);

		if (p == (void *)-1)
			DIE(1, "mmap");
		struct block_meta *p1 = (struct block_meta *)p - 1;

		p1->size = noulsizetotal;
		p1->status = 1;
		if (block->size > p1->size)
			memcpy(p1 + 1, block + 1, p1->size - sizeof(struct block_meta));
		else
			memcpy(p1 + 1, block + 1, block->size - sizeof(struct block_meta));
		free(ptr);
		return (void *)(p1 + 1);
	}
	if (noulsizetotal >= MMAP_THRESHOLD) {
		void *p = mmap(NULL, noulsizetotal, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (p == (void *)-1)
			DIE(1, "mmap");
		struct block_meta *p1 = (struct block_meta *)p - 1;

		p1->size = noulsizetotal;
		p1->status = 2;
		if (block->size > p1->size)
			memcpy(p1 + 1, block + 1, p1->size - sizeof(struct block_meta));
		else
			memcpy(p1 + 1, block + 1, block->size - sizeof(struct block_meta));
		free(ptr);
		return (void *)(p1 + 1);
	}
	if (noulsizetotal <= block->size) {
		split_block(&block, noulsizetotal);
		if (block->next != NULL) {
			if (block->next->status == 0)
				coalesce_blocks(block->next);
		}
		return (void *)(block + 1);
	}
	if (block->next == NULL) {
		sbrk(noulsizetotal - block->size);
		block->size = noulsizetotal;
		return ptr;
	}
	if (block->next->status == 0) {
		coalesce_blocks(block->next);
		if (block->size + block->next->size > noulsizetotal) {
			block->size = block->size + block->next->size;
			block->next = block->next->next;
			split_block(&block, noulsizetotal);
			return (void *)(block + 1);
		}
	}
	void *p = malloc(size);

	if (p == (void *)-1)
		DIE(1, "mmap");
	struct block_meta *p1 = (struct block_meta *)p - 1;

	p1->size = noulsizetotal;
	p1->status = 1;
	p1->next = NULL;
	if (block->size > p1->size)
		memcpy(p1 + 1, block + 1, p1->size - sizeof(struct block_meta));
	else
		memcpy(p1 + 1, block + 1, block->size - sizeof(struct block_meta));
	free(ptr);
	return (void *)(p1 + 1);

	return NULL;
}

void free(void *ptr)
{
	if (ptr == NULL)
		return;
	struct block_meta *block = (struct block_meta *)ptr - 1;

	if (block->status == 1) {
		block->status = STATUS_FREE;
		coalesce_blocks(block);
	}
	if (block->status == 2)
		munmap(block, block->size);
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
