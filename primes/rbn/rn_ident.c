#include "rbn_priv.h"
#define RN_VER_S "v0.0.1"
#define STANDALONE

const char *rn_ident(void)
{
  static char buf[1024];

  memset(buf, 0, sizeof(buf));
  snprintf(buf, sizeof(buf)-1, "\nRBN " RN_VER_S "\n"

#if defined(RN_IDENT_BUILD_DATE)
      "Built on " __DATE__ " at " __TIME__ "\n"
#endif
      "\n  digit\tsizeof(rnd) = %lu\n"
      "  word \tsizeof(rnw) = %lu\n\n"
      "  MAX_SIZ = %u\n\n"
      "Using \n"
#ifdef __i386__
      "  __i386__ "
#endif
#ifdef __x86_64__
      "  __x86_64__ "
#endif
      "\n\n",
    (unsigned long)sizeof(rnd),
    (unsigned long)sizeof(rnw),
    MAX_SIZ);

  if (sizeof(rnd) == sizeof(rnw)) {
    strncat(buf, "WARNING:\n  sizeof(rnd) == sizeof(rnw), this build is "
                 "likely to not work properly\n", sizeof(buf)-strlen(buf)-1);
  }
  return buf;
}

#ifdef STANDALONE
int main(void)
{
  printf("%s\n", rn_ident());
  return 0;
}
#endif

