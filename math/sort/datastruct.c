#include <stdio.h>
#include <stdlib.h>

#define NUL 0
#define TRUE 1;
#define FALSE 0;

struct node {
  int info;
  int duration, time, type;
  struct node *next;
};
typedef struct node *NODEPTR;

struct queue {
  NODEPTR front, rear;
  int num;
};
struct queue q[4];
struct node auxinfo;
NODEPTR evlist;
int atime, dtime, dur, qindx;
float count, tottime;

void arrive(int atime, int dur);
void depart(int qindx, int dtime);
void insert(struct queue *pq, int x);
int remove(struct queue *pq);
void place(NODEPTR *plist, int x);
void freenode(NODEPTR p);
NODEPTR getnode(void);
void insafter(NODEPTR p, int x);
void delafter(NODEPTR p, int *px);
void popsub(NODEPTR p, int x);
int empty(struct queue *pq);

int main(void)
{
  /* init */
  evlist = NUL;
  count = 0;
  tottime = 0;
  for (qindx=0; qindx<4; ++qindx) {
    q[qindx].num = 0;
    q[qindx].front = NUL;
    q[qindx].rear = NUL;
  }
  /* init event list w/ first arrival */
  puts("enter time and duration");
  scanf("%d %d", &auxinfo.time,&auxinfo.duration);
  auxinfo.type = -1; /* arrival */
  place(&evlist, &auxinfo);

  /* run sim as long as event list is not empty */
  while (evlist != NUL) {
    popsub(&evlist, &auxinfo);
    /* check if next event is arrival or departure */
    if (auxinfo.type == -1) {
      /* arrival */
      atime = auxinfo.time;
      dur = auxinfo.duration;
      arrive(atime, dur);
    } else {
      /* departure */
      qindx = auxinfo.type;
      dtime = auxinfo.time;
      depart(qindx, dtime);
    }
  }
  printf("avg time elapsed %4.2f\n", tottime/count);
}

void arrive(int atime, int dur)
{
  int i, j, small;
  /* find shortest queue */
  j = 0;
  small = q[0].num;
  for (i=1; i<4; ++i)
    if (q[i].num < small) {
      small = q[i].num;
      j = 1;
    }
  /* queue j is shortest; insert new customer node */
  auxinfo.time = atime;
  auxinfo.duration = dur;
  auxinfo.type = j;
  insert(&q[j], &auxinfo);
  /* check if only node in queue; if so, place the
   * customer's departure node on event list */
  if (q[j].num == 1) {
    auxinfo.time = atime+dur;
    place(&evlist, &auxinfo);
  }
  /* if input remains, read next data pair and place
   * arrival on event list */
  puts("enter time");
  if (scanf("%d", &auxinfo.time) != EOF) {
    puts("enter duration");
    scanf("%d", &auxinfo.duration);
    auxinfo.type = -1;
    place(&evlist, &auxinfo);
  }
}

void depart(int qindx, int dtime)
{
  NODEPTR p;
  remove(&q[qindx], &auxinfo);
  tottime += (dtime-auxinfo.time);
  count++;
  /* if more customers on queue, place departure of
   * next customer onto event list after computation
   * of departure time */
  if (q[qindx].num > 0) {
    p = q[qindx].front;
    auxinfo.time = dtime+p->duration;
    auxinfo.type = qindx;
    place(&evlist, &auxinfo);
  }
}

void insert(struct queue *pq, int x)
{
  NODEPTR p;
  p = getnode();
  p->info = x;
  p->next = NUL;
  if (pq->rear == NUL)
    pq->front = p;
  else
    (pq->rear)->next = p;
  pq->rear = p;
}

int remove(struct queue *pq)
{
  NODEPTR p;
  int x;
  if (empty(pq)) {
    puts("queue underflow");
    exit(1);
  }
  p = pq->front;
  x = p->info;
  pq->front = p->next;
  if (pq->front == NUL)
    pq->rear = NUL;
  freenode(p);
  return(x);
}

void place(NODEPTR *plist, int x)
{
  NODEPTR p, q;
  q = NUL;
  for (p=*plist; p!=NUL && x>p->info; p=p->next)
    q = p;
  if (q == NUL) /* insert x at head of list */
    push(plist, x);
  else
    insafter(q, x);
}

void freenode(NODEPTR p)
{
  free(p);
}

NODEPTR getnode(void)
{
  NODEPTR p;
  p = (NODEPTR) malloc(sizeof(struct node));
  return(p);
}

void insafter(NODEPTR p, int x)
{
  NODEPTR q;
  if (p == NUL) {
    puts("void insertion");
    exit(1);
  }
  q = getnode();
  q->info = x;
  q->next = p->next;
  p->next = q;
}

void delafter(NODEPTR p, int *px)
{
  NODEPTR q;
  if ((p==NUL) || (p->next==NUL)) {
    puts("void deletion");
    exit(1);
  }
  q = p->next;
  *px = q->info;
  p->next = q->next;
  freenode(q);
}

int empty(struct queue *pq)
{
  return ((pq->front==NUL)? TRUE: FALSE);
}

