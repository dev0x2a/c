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
    if (node[i].utype == LST && node[node[i].lstinfo].mark != TRUE) {
      node[node[i].lstinfo] = TRUE;
      if (node[i].lstinfo < j) j = node[i].lstinfo;
    }
    if (node[node[i].next].mark != TRUE) {
      node[node[i].next].mark = TRUE;
      if (node[i].next < j) j = node[i].next;
    }
  }
  i = j;
}
