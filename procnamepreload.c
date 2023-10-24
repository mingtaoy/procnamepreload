#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

#ifndef PROCNAME_PRELOAD_ENV_VAR
#define PROCNAME_PRELOAD_ENV_VAR "PROCNAME_OVERRIDE"
#endif

__attribute__((constructor)) static void init() {
  const char* procname = getenv(PROCNAME_PRELOAD_ENV_VAR);
  if (!procname) {
    return;
  }

  char buf[16];
  strncpy(buf, procname, sizeof(buf));
  buf[sizeof(buf)-1] = 0;
  if (strcmp(buf, procname) != 0) {
    fprintf(stderr, "[procnamepreload] Requested process name \"%s\" truncated to \"%s\"\n", procname, buf);
  }

  if (prctl(PR_SET_NAME, buf, NULL, NULL, NULL) < 0) {
    fprintf(stderr, "[procnamepreload] failed to set process name: %s\n", strerror(errno));
    return;
  }
}
