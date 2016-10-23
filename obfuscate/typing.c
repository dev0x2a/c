#include <stdio.h>
#define A(a) G a();
#define B(a) G (*a)();
#define C(a,b) G a() { printf(b); return X; }
typedef struct F G;A(a)A(b)A(c)A(d)A(e)A(f)A(g)A(h)A(i)A(j)A(k)A(l)A(m)A(n)A(
o)A(p)A(q)A(r)A(s)A(t)A(u)A(v)A(w)A(x)A(y)A(z)A(S)A(N)void Q();struct F{B(a)B
(b)B(c)B(d)B(e)B(f)B(g)B(h)B(i)B(j)B(k)B(l)B(m)B(n)B(o)B(p)B(q)B(r)B(s)B(t)B(
u)B(v)B(w)B(x)B(y)B(z)B(S)B(N)void(*Q)();}X={a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,
q,r,s,t,u,v,w,x,y,z,S,N,Q};C(a,"z")C(b,"y")C(c,"x")C(d,"w")C(e,"v")C(f,"u")C(
g,"t")C(h,"s")C(i,"r")C(j,"q")C(k,"p")C(l,"o")C(m,"n")C(n,"m")C(o,"l")C(p,"k"
)C(q,"j")C(r,"i")C(s,"h")C(t,"g")C(u,"f")C(v,"e")C(w,"d")C(x,"c")C(y,"b")C(z,
"a")C(S," ")C(N,"\n") void Q(){}main(){X=g().s().v().S().j().f().r().x().p().
S().y().i().l().d().m().S().u().l().c().S().q().f().n().k().v().w().S().l().e
().v().i().S().g().s().v().S().o().z().a().b().S().w().l().t().N();}
/*
------------------------------------------------------------
Most Unusual Data Structure <pjr@pyra.co.uk> Peter J Ruczynski

  Peter J Ruczynski.
  Pyramid Technology Ltd.
  Pyramid House,
  Solatron Road
  Farnborough.
  Hants GU14 7PL
  England, U.K.

Judges' comments:
    This program prints out a string.  Can you figure out how
    it is done?
    By use of pointers to functions returning a struct of pointers 
    to functions!
    Note that some compilers will be unable to compile the
    expression 'X=g()...' in main due to lack of temporary
    value space.  One might want to try replacing main with:

      main(){X=s().v().o().o().l().S().d().l().i().o().w().N();}
    
    if this is a problem.

Spoiler: (rot13 to read)
    Guvf cebtenz cevagf bhg gur fgevat:

    gur dhvpx oebja sbk whzcrq bire gur ynml qbt

    ol hfr bs cbvagref gb shapgvbaf ergheavat n fgehpg bs cbvagref 
    gb shapgvbaf!

Selected notes from the author: (rot13 to read)
    Vg vf fvzcyr gb znxr gur cebtenz cevag bgure fgevatf.  Rnpu
    nycunorgvpny punenpgre sebz n gb m vf cevagrq bhg nf vgf
    bccbfvgr:

      n->m o->l p->k rgp

    Gb rapbqr n arj fgevat vachg gur fgevat nf vg vf zrnag gb pbzr bhg:

      K=f().i().b().b().y().F().q().y().v().b().j().A();

    Abgr: F() ercerfragf n fcnpr naq A() n arjyvar.  Guvf jvyy abj
    cebqhpr...

      uryyb jbeyq

    By the way, there is actually a piece of code which is not used
    in the original program! I leave it as an intellectual exercise
    to the reader to find out what it is.

Copyright (c) 1990, Landon Curt Noll & Larry Bassel.
All Rights Reserved.  Permission for personal, educational or non-profit use is
granted provided this this copyright and notice are included in its entirety
and remains unaltered.  All other uses must receive prior permission in writing
from both Landon Curt Noll and Larry Bassel.
*/

