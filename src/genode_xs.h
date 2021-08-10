/*
 * cribbed from wasm_xs.h
 */

#ifndef __GENODE_XS__
#define __GENODE_XS__

// pretty close to WASM
#undef mxWasm
#define mxWasm 1

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#define mxUseGCCAtomics 1
#define mxUsePOSIXThreads 1

#define mxUseDefaultBuildKeys 1
#define mxUseDefaultChunkAllocation 1
#define mxUseDefaultSlotAllocation 1
#define mxUseDefaultFindModule 1
#define mxUseDefaultLoadModule 1
#define mxUseDefaultParseScript 1
#define mxUseDefaultSharedChunks 1

#define mxMachinePlatform \
	void* host; \
	void* waiterCondition; \
	void* waiterData; \
	void* waiterLink;

#endif /* __GENODE_XS__ */
