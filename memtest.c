#include <stdio.h>

extern void* __libc_malloc(size_t);
extern void* __libc_free(void*);
/*
#include <dlfcn.h>

extern void* __libc_calloc(size_t, size_t);
extern void* __libc_malloc(size_t);
extern void* __libc_realloc(void*, size_t);
extern void* __libc_free(void*);
//extern void* __libc_memalign(size_t, size_t);

static void* (*callocp)(size_t, size_t) = NULL;
static void* (*mallocp)(size_t) = NULL;
static void* (*reallocp)(void*, size_t) = NULL;
static void* (*freep) (void*) = NULL;
//static void* (*memalignp) (size_t, size_t) = NULL;

static void __attribute((constructor)) init(void)
{
	callocp = __libc_calloc;
	mallocp = __libc_malloc;
	reallocp = __libc_realloc;
	freep = __libc_free;
	//memalignp = __libc_memalign;
}
*/

static __thread int no_hook = 0;

void* malloc(size_t len)
{
	if (no_hook)
		return (*__libc_malloc)(len);

	no_hook = 1;
	void* p = (*__libc_malloc)(len);
	printf("+%p:%d\n", p, (int)len);
	no_hook = 0;
	return p;
}

void free(void*p)
{
	printf("-%p\n", p);
	__libc_free(p);
}



