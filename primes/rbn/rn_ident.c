#include "rbn_priv.h"
#define STANDALONE

const char *rn_ident(void)
{
  static char buf[1024];

  memset(buf, 0, sizeof(buf));
  snprintf(buf, sizeof(buf)-1,
      "\n-------------------------------------"
      "\nRBN " RN_VER_S "\n"

#if defined(RN_IDENT_BUILD_DATE)
      "Built on " __DATE__ " at " __TIME__ "\n"
#endif
      "\n  int_st  sizeof(rni) = %lu\n"
      "  digit   sizeof(rnd) = %lu\n"
      "  word    sizeof(rnw) = %lu\n\n"
      "  __SIZEOF_LONG__     = %u\n"
      "  DGT_BIT             = %u\n"
      "  MAX_SIZ             = %u\n"
      "  RN_SIZ              = %u\n"
      "  PR_SIZ              = %u\n\n"
      "  Using\n"
#ifdef __i386__
      "                         __i386__ "
#endif
#ifdef __x86_64__
      "                         __x86_64__ "
#endif
      "\n------------------------------------\n",
    (unsigned long)sizeof(rni),
    (unsigned long)sizeof(rnd),
    (unsigned long)sizeof(rnw),
    __SIZEOF_LONG__,
    DGT_BIT,
    MAX_SIZ,
    RN_SIZ,
    PR_SIZ);

  if (sizeof(rnd) == sizeof(rnw)) {
    strncat(buf, "WARNING:\n  sizeof(rnd) == sizeof(rnw), this build is "
                 "likely to not work properly\n\n",
                 sizeof(buf)-strlen(buf)-1);
  } else {
    strncat(buf, "No warning flags\n", sizeof(buf)-1);
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

