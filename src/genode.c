/**
 * based on x-cli-lin platform work
 */
#include "xsAll.h"
#include "xsScript.h"
#include "mc.xs.h"

typedef struct sxJob txJob;
typedef void (*txJobCallback)(txJob*);

struct sxJob {
	txJob* next;
	txMachine* the;
	// TODO: setTimeout and friends
	// txNumber when;
	txJobCallback callback;
	txSlot function;
	txSlot argument;
	txNumber interval;
};

extern void applyConfig(xsMachine *the); // see FFImod.c

static void fxQueuePromiseJobsCallback(txJob* job);
static void fxRunLoop(txMachine* the);

int main(int argc, char* argv[])  // here
{
	int error = 0;

	xsMachine* machine = fxPrepareMachine(NULL, xsPreparation(), argv[0], NULL, NULL);

	xsBeginHost(machine);
	{
		xsVars(5);
		{
			xsTry {
				if (argc != -1) {
					xsRangeError("expected argc == -1 to signal novel use of argv");
				}
				xsVar(0) = xsNewObject();
				xsVar(4) = xsNewHostFunction(applyConfig, 1);
				xsVar(3) = xsNewHostObject(NULL);
				xsSetHostData(xsVar(3), argv[0]);
				xsDefine(xsVar(0), xsID("sandbox"), xsVar(3), xsDontSet);
				xsDefine(xsVar(3), xsID("applyConfig"), xsVar(4), xsDontSet);

				// printf("lin_xs_cli: loading top-level main.js\n");
				xsVar(1) = xsAwaitImport("main", XS_IMPORT_DEFAULT);
				// printf(" lin_xs_cli: loaded\n");

				// printf("lin_xs_cli: invoking main(argv)\n");
				xsVar(2) = xsCallFunction2(xsVar(1), xsUndefined, xsVar(0), xsVar(3));
				if (!xsIsInstanceOf(xsVar(2), xsPromisePrototype)) {
					// fprintf(stderr, "main() returned immediate value (not a promise). exiting\n");
					exit(xsToInteger(xsVar(2)));
				}
				// printf(" lin_xs_cli: main() returned a promise; entering event loop\n");
			}
			xsCatch {
				xsStringValue message = xsToString(xsException);
				fprintf(stderr, "### %s\n", message);
				error = 1;
			}
		}
	}
	xsEndHost(the);
	fxRunLoop(machine);
	xsDeleteMachine(machine);
	return error;
}


void fxAbort(xsMachine* the, int status)
{
  fprintf(stderr, "fxAbort(the=%p, status=%d).\n", the, status);
  exit(status);
}

char* fxCStackLimit()
{
  pthread_attr_t attrs;

  if (pthread_attr_init(&attrs) == 0) {
    void *stackAddr = C_NULL;
    size_t stacksize = 0;
    if (pthread_attr_getstacksize(&attrs, &stacksize) == 0) {
      return (char*)stackAddr + (4 * 1024);
    }
  }
  return C_NULL;
}


void fxCreateMachinePlatform(txMachine* the)
{
	the->host = NULL;
}

void fxDeleteMachinePlatform(txMachine* the)
{
}


void fxQueuePromiseJobs(txMachine* the)
{
	// c_timeval tv;
	txJob* job;
	txJob** address = (txJob**)&(the->context);
	while ((job = *address))
		address = &(job->next);
	job = *address = malloc(sizeof(txJob));
    c_memset(job, 0, sizeof(txJob));
    job->the = the;
    job->callback = fxQueuePromiseJobsCallback;
	// c_gettimeofday(&tv, NULL);
	// job->when = ((txNumber)(tv.tv_sec) * 1000.0) + ((txNumber)(tv.tv_usec) / 1000.0);
}

void fxQueuePromiseJobsCallback(txJob* job)
{
	txMachine* the = job->the;
	fxRunPromiseJobs(the);
}


void fxRunLoop(txMachine* the)
{
	// c_timeval tv;
	// txNumber when;
	txJob* job;
	txJob** address;

	for (;;) {
		// c_gettimeofday(&tv, NULL);
		// when = ((txNumber)(tv.tv_sec) * 1000.0) + ((txNumber)(tv.tv_usec) / 1000.0);
		address = (txJob**)&(the->context);
		if (!*address)
			break;
		while ((job = *address)) {
			if (1 /* job->when <= when */) {
				(*job->callback)(job);
				// if (job->interval) {
				// 	job->when += job->interval;
				// }
				// else {
					*address = job->next;
					c_free(job);
				// }
			}
			else
				address = &(job->next);
		}
	}
}

// Local Variables:
// tab-width: 4
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// vim: noet ts=4 sw=4
