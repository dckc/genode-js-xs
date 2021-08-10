/**
 * based on x-cli-lin platform work
 */
#include "xsAll.h"
#include "xsScript.h"
#include "mc.xs.h"

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


int main(int argc, char* argv[])  // here
{
	int error = 0;

	xsMachine* machine = fxPrepareMachine(NULL, xsPreparation(), "tool", NULL, NULL);

	xsBeginHost(machine);
	{
		xsVars(3);
		{
			xsTry {
				int argi;
				xsVar(0) = xsNewArray(0);
				for (argi = 1; argi < argc; argi++) {
					xsSetAt(xsVar(0), xsInteger(argi - 1), xsString(argv[argi]));
				}

				printf("lin_xs_cli: loading top-level main.js\n");
				xsVar(1) = xsAwaitImport("main", XS_IMPORT_DEFAULT);
				printf(" lin_xs_cli: loaded\n");

				printf("lin_xs_cli: invoking main(argv)\n");
				xsVar(2) = xsCallFunction1(xsVar(1), xsUndefined, xsVar(0));
				if (!xsIsInstanceOf(xsVar(2), xsPromisePrototype)) {
					fprintf(stderr, "main() returned immediate value (not a promise). exiting\n");
					exit(xsToInteger(xsVar(2)));
				}
				printf(" lin_xs_cli: main() returned a promise; entering event loop\n");

#if MAIN_LOOP_TODO
				GMainContext *mainctx = g_main_context_default();
				while (the->promiseJobsFlag || fxPromiseIsPending(the, &xsVar(2))) {
					while (the->promiseJobsFlag) {
						the->promiseJobsFlag = 0;
						fxRunPromiseJobs(the);
					}
					g_main_context_iteration(mainctx, TRUE);
				}
				if (fxPromiseIsRejected(the, &xsVar(2))) {
					error = 1;
				}
				// ISSUE: g_main_context_unref(mainctx); causes xsDeleteMachine() below
				//        to hang in g_main_context_find_source_by_id() aquiring a lock.
#endif
			}
			xsCatch {
				xsStringValue message = xsToString(xsException);
				fprintf(stderr, "### %s\n", message);
				error = 1;
			}
		}
	}
	xsEndHost(the);
	xsDeleteMachine(machine);
	return error;
}
