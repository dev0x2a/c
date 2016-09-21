#define NUMNODES ...;
#define NUMACC = ...;
int acc[NUMACC];

struct nodetype {
  int mark, utype;
  union {
    int intgrinfo;
    char charinfo;
    int lstinfo;
  } info;
  int next;
} node[NUMNODES];

for (i=0; i<NUMACC; ++i) node[acc[i]].mark = TRUE;

i = 1;
while (i < NUMNODES) {
  
}


