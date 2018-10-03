#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <execinfo.h>
#include <cxxabi.h>

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

void print_trace(void)
{
	void *array[10];
	size_t size = backtrace(array, 10);
	char** strings = backtrace_symbols(array, size);

	size_t i;
	Dl_info dlinfo;
	printf("-------------------------\n");	
	for (i = 0; i < size; ++i)
	{
		const char* function_name = NULL;
		if (dladdr(array[i], &dlinfo) != 0)
		{
			function_name = dlinfo.dli_sname;
			if (function_name != NULL)
			{
				const char* demangled_name = NULL;
				demangled_name = abi:__cxa_demangle(function_name, 0, 0, &status);
				if (status == 0)
					function_name = de_mangled_name;
			}
		}

		printf("%d %s %s\n", (int)i, strings[i], function_name);
	}
	printf("-------------------------\n");	
}

void* malloc(size_t len)
{
	if (no_hook)
		return (*__libc_malloc)(len);

	no_hook = 1;
	void* p = (*__libc_malloc)(len);
	printf("+%p:%d\n", p, (int)len);
	print_trace();	
	no_hook = 0;
	return p;
}

void free(void*p)
{
	no_hook = 1;
	printf("-%p\n", p);
	print_trace();	
	no_hook = 0;
	__libc_free(p);
}



