#define NUMNODES ...;
#define NUMACC = ...;
int acc[NUMACC];

struct nodetype {
  int mark;
  int utype;
  union {
    int intgrinfo;
    char charinfo;
    int lstinfo;
  } info;
  int next;
} node[NUMNODES];

int i, j;
for (i=0; i<NUMACC; ++i) node[acc[i]].mark = TRUE;

i = 1;
while (i < NUMNODES) {
  j = i + 1;
  if (node[i].mark) {
    if (node[i].utype == LST &&)
  }
}


