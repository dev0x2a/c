/* Copyright (C) 2000  The PARI group.

This file is part of the PARI/GP package.

PARI/GP is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation. It is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY WHATSOEVER.

Check the License for details. You should have received a copy of it, along
with the package; see the file 'COPYING'. If not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

/* For compatibility with older PARI versions */
/* Following obsoleted in 2.9.* (2016) */
#define cmpui abscmpui
#define equalui absequalui
#define equaliu absequaliu
#define cmpiu abscmpiu
#define absi_factor absZ_factor
#define absi_factor_limit absZ_factor_limit
#define absi_cmp abscmpii
#define absr_cmp abscmprr
#define absi_equal absequalii
#define anell ellan
#define anellsmall ellanQ_zv
#define leading_term leading_coeff
#define constant_term constant_coeff
#define concat gconcat
#define concat1 gconcat1
#define mathell ellheightmatrix
#define ghell ellheight

/* Following obsoleted in 2.7.* (2014) */
#define mpexp1 mpexpm1
#define ggamd ggammah
#define gach gacosh
#define gash gasinh
#define gath gatanh
#define gch gcosh
#define gsh gsinh
#define gth gtanh
#define recip serreverse
#define gcmpX gequalX
#define ZM_hnfremdiv ZM_hnfdivrem
#define rnfidealhermite rnfidealhnf
#define rnfelementabstorel rnfeltabstorel
#define rnfelementreltoabs rnfeltreltoabs
#define rnfelementdown rnfeltdown
#define rnfelementup rnfeltup
#define exp_Ir expIr
#define vecbezout gcdext0
#define vecbezoutres polresultantext
#define init_primepointer init_primepointer_geq
#define ellap0(e,p,flag) ellap(e,p)
#define apell2(e,p) ellap(e,p)
#define geulerphi eulerphi
#define numbdiv numdiv
#define gnumbdiv numdiv
#define gsumdivk sumdivk
#define gnextprime nextprime
#define gprecprime precprime
#define leftright_pow_fold gen_pow_fold
#define leftright_pow_u_fold gen_powu_fold
#define subell ellsub
#define addell elladd
#define powell ellmul
#define ggval gvaluation
#define stackmalloc stack_malloc
#define listcreate mklist

/* Following obsoleted in 2.5.* (2011) */
#define fprintferr err_printf
#define msgTIMER timer_printf
#define TIMER timer_delay
#define TIMERread timer_get
#define TIMERstart timer_start
#define rnfinitalg rnfinit
#define ordell ellordinate
#define gcmp0 gequal0
#define gcmp1 gequal1
#define gcmp_1 gequalm1
#define nfsmith nfsnf
#define certifybuchall bnfcertify
#define greffe(x,y,z) (RgX_to_ser(x,y))
#define newbloc newblock
#define killbloc killblock
#define taille2 gsizeword
#define taille gsizebyte
#define polymodrecip modreverse
#define primedec idealprimedec
#define initalg nfinit
#define initalgred nfinitred
#define initalgred2 nfinitred2
#define initell ellinit
#define smallinitell smallellinit
#define isunit bnfisunit
#define zideallog ideallog
#define ideallllred idealred0
#define ideal_two_elt idealtwoelt
#define ideal_two_elt2 idealtwoelt2
#define ideal_two_elt0 idealtwoelt0
#define gregula quadregulator
#define gfundunit quadunit
#define minideal(x,y,z,t) idealmin(x,y,z)
#define idealhermite idealhnf
#define srgcd(x) RgX_gcd(x)
#define nfdiscf0(x) nfdisc0(x)
#define discf(x) nfdisc(x)
#define discsr(x) poldisc0((x),-1)
#define factorpadic4 factorpadic
#define smith2 smithall
#define gsmith2 gsmithall
#define derivpol RgX_deriv
#define gpmalloc pari_malloc
#define gprealloc pari_realloc
#define gpfree pari_free
#define pariprintf pari_printf
#define pariputc pari_putc
#define pariputs pari_puts
#define pariflush pari_flush

/* Following deprecated for a long time now, obsoleted in 2.3.* (2007) */
#ifdef PARI_OLD_NAMES
#define apell ellap
#define gscalsmat scalarmat_s
#define sqred qfgaussred
#define signat qfsign
#define infile pari_infile
#define errfile pari_errfile
#define logfile pari_logfile
#define voir dbgGEN
#define pointch ellchangepoint
#define coordch ellchangecurve
#define Flx_rand random_Flx
#define FpX_rand random_FpX
#define galois polgalois
#define sindexlexsort indexlexsort
#define sindexsort indexsort
#define sindexrank indexrank
#define decomp Z_factor
#define gmodulcp gmodulo
#define forcecopy gcopy
#define lseriesell elllseries
#define uissquarerem uissquareall
#define Z_issquarerem Z_issquareall
#define gissquarerem gissquareall
#define gcarrecomplet gissquareall
#define gcarreparfait gissquare
#define rnfhermitebasis rnfhnfbasis
#define wf weberf
#define wf1 weberf1
#define wf2 weberf2
#define coefs_to_col mkcoln
#define coefs_to_int mkintn
#define coefs_to_pol mkpoln
#define coefs_to_vec mkvecn
#define localreduction elllocalred
#define idmat matid
#define globalreduction ellglobalred
#define taniyama(e) elltaniyama((e),precdl)
#define chinois chinese
#define binome binomial
#define egalii equalii
#define gegal gequal
#define gegalgs gequalgs
#define gegalsg gequalsg
#define gzero gen_0
#define gun   gen_1
#define gdeux gen_2
#define realzero real_0
#define realzero_bit real_0_bit
#define realun real_1
#define realmun real_m1
#define gen2str GENtostr
#define gpui gpow
#define gpuigs gpowgs
#define classno3 hclassno
#define strtoGEN gp_read_str
#define flisexpr gp_read_str
#define flisseq gp_read_str
#define lisseq readseq
#define lisGEN gp_read_stream
#define lisexpr readseq
#define permute numtoperm
#define permuteInv permtonum
#define evallgef(x) 0
#define lgef lg
#define setlgef setlg
#define leadingcoeff(x) (pollead((x),-1))
#define poldivres poldivrem
#define nfdivres nfdivrem
#define gred gcopy
#define pvaluation Z_pvalrem
#define svaluation u_lvalrem
#define isprincipalrayall bnrisprincipal
#define rayclassno bnrclassno
#define rayclassnolist bnrclassnolist
#define idealhermite2 idealhnf0
#define gener_Fp pgener_Fp
#define gener_Fl pgener_Fl
#define cyclo polcyclo
#define tchebi polchebyshev1
#define legendre pollegendre
#define subcyclo polsubcyclo
#define leftright_pow gen_pow
#define leftright_pow_u gen_powu

#define apprgen padicappr
#define apprgen9 padicappr
#define factmod9 factorff
#define ggrandocp ggrando
#define glogagm glog
#define logagm  mplog
#define mpsqrtz  gopgz(absr,(x),(y))
#define adduumod Fl_add
#define subuumod Fl_sub
#define muluumod Fl_mul
#define divuumod Fl_div
#define powuumod Fl_powu
#define invumod Fl_inv
#define invsmod Fl_inv_signed
#define mpinvmod Fp_inv
#define powmodulo Fp_pow
#define mpsqrtmod Fp_sqrt
#define mpsqrtnmod Fp_sqrtn
#define mpsqrt  sqrtr
#define mpsqrtn  sqrtnr
#define resii  remii
#define resis  remis
#define ressi  remsi
#define resss  remss
#define resiiz  remiiz
#define resisz  remisz
#define ressiz  remsiz
#define resssz  remssz
#define gres    grem
#define lres    lrem
#define gdivise gdvd
#define divise dvdii
#define mpdivis dvdiiz
#define mpdivisis dvdisz
#define mpent mpfloor
#define mpentz mpfloorz
#define mpnegz(x,y) \
  STMT_START {pari_sp _av=avma;mpaff(mpneg(x),y);avma=_av;} STMT_END
#define mpabsz(x,y) \
  STMT_START {pari_sp _av=avma;mpaff(mpabs(x),y);avma=_av;} STMT_END
#define absrz(x,z)  mpabsz((x),(z))
#define negrz(x,z)  mpnegz((x),(z))

#define err pari_err
#define init pari_init

#define zero  (long)gen_0
#define un    (long)gen_1
#define deux  (long)gen_2
#define lhalf (long)ghalf

/* removed GEN subtypes */
#define t_FRACN  t_FRAC
#define t_RFRACN t_RFRAC
#define is_frac_t(t) ( (t) == t_FRAC )
#define is_rfrac_t(t) ( (t) == t_RFRAC )

/*casts*/
#define labsi   (long)absi
#define labsr   (long)absr
#define lach    (long)gacosh
#define lacos   (long)gacos
#define ladd    (long)gadd
#define laddgs  (long)gaddgs
#define laddii  (long)addii
#define laddir  (long)addir
#define laddis  (long)addis
#define laddrr  (long)addrr
#define laddsg  (long)gaddsg
#define laddsi  (long)addsi
#define laddrs  (long)addrs
#define laddsr  (long)addsr
#define ladj    (long)adj
#define larg    (long)garg
#define lash    (long)gasinh
#define lasin   (long)gasin
#define lassmat (long)matcompanion
#define latan   (long)gatan
#define lath    (long)gatanh
#define lbezout (long)bezout
#define lbinome (long)binomial
#define lcaract (long)caract
#define lcaradj (long)caradj
#define lceil   (long)gceil
#define lch     (long)gcosh
#define lchangevar (long)changevar
#define lclone  (long)gclone
#define lconcat (long)gconcat
#define lconj   (long)gconj
#define lcontent (long)content
#define lcopy   (long)gcopy
#define lcos    (long)gcos
#define lcvtoi  (long)gcvtoi
#define lderiv  (long)deriv
#define ldet2   (long)det2
#define ldet    (long)det
#define ldeuc   (long)gdeuc
#define ldiscsr (long)discsr
#define ldiventgs (long)gdiventgs
#define ldiventsg (long)gdiventsg
#define ldivgs  (long)gdivgs
#define ldivii  (long)divii
#define ldivir  (long)divir
#define ldivis  (long)divis
#define ldivmod (long)gdivmod
#define ldivri  (long)divri
#define ldivrr  (long)divrr
#define ldivrs  (long)divrs
#define ldivsg    (long)gdivsg
#define ldivsi  (long)divsi
#define ldivsr  (long)divsr
#define ldvmdii (long)dvmdii
#define ldvmdis (long)dvmdis
#define ldvmdsi (long)dvmdsi
#define lexp    (long)gexp
#define lfibo   (long)fibo
#define lfloor  (long)gfloor
#define lfrac   (long)gfrac
#define lgamd   (long)ggammah
#define lgamma  (long)ggamma
#define lgauss  (long)gauss
#define lgcd    (long)ggcd
#define lgetg   (long)cgetg
#define lgeti   (long)cgeti
#define lgetp   (long)cgetp
#define lgetr   (long)cgetr
#define licopy  (long)icopy
#define limag   (long)gimag
#define linteg  (long)integ
#define linv    (long)ginv
#define linvmat (long)RgM_inv
#define linvmod (long)ginvmod
#define llegendre (long)legendre
#define llift   (long)lift
#define llngamma  (long)glngamma
#define llog    (long)glog
#define lmaxgs    (long)gmaxgs
#define lmax    (long)gmax
#define lmaxsg    (long)gmaxsg
#define lmings    (long)gmings
#define lmin    (long)gmin
#define lminsg    (long)gminsg
#define lmodgs    (long)gmodgs
#define lmodii  (long)modii
#define lmod    (long)gmod
#define lmodsg    (long)gmodsg
#define lmodsi  (long)modsi
#define lmodulcp  (long)gmodulo
#define lmodulo   (long)gmodulo
#define lmpabs  (long)mpabs
#define lmpadd  (long)mpadd
#define lmpcos  (long)mpcos
#define lmpdiv  (long)mpdiv
#define lmpent  (long)mpent
#define lmpeuler (long)mpeuler
#define lmpexp1 (long)mpexpm1
#define lmpexp  (long)mpexp
#define lmpfact (long)mpfact
#define lmplog  (long)mplog
#define lmpmul  (long)mpmul
#define lmpneg  (long)mpneg
#define lmppgcd (long)mppgcd
#define lmppi   (long)mppi
#define lmpshift (long)mpshift
#define lmpsin  (long)mpsin
#define lmpsqrt (long)mpsqrt
#define lmpsub  (long)mpsub
#define lmptrunc (long)mptrunc
#define lmul2n  (long)gmul2n
#define lmulgs  (long)gmulgs
#define lmulii  (long)mulii
#define lmulir  (long)mulir
#define lmulis  (long)mulis
#define lmul    (long)gmul
#define lmulri  (long)mulri
#define lmulrr  (long)mulrr
#define lmulrs  (long)mulrs
#define lmulsg  (long)gmulsg
#define lmulsi  (long)mulsi
#define lmulsr  (long)mulsr
#define lmulss  (long)mulss
#define lnegi   (long)negi
#define lneg    (long)gneg
#define lnegr   (long)negr
#define lnorml2 (long)gnorml2
#define lnorm   (long)gnorm
#define lpile   (long)gerepile
#define lpilecopy (long)gerepilecopy
#define lpileupto (long)gerepileupto
#define lpileuptoint (long)gerepileuptoint
#define lpileuptoleaf (long)gerepileuptoleaf
#define lpoleval (long)poleval
#define lpowgs  (long)gpowgs
#define lprec   (long)gprec
#define lpsi    (long)gpsi
#define lpuigs  (long)gpuigs
#define lpui    (long)gpui
#define lquadgen (long)quadgen
#define lquadpoly (long)quadpoly
#define lracine (long)sqrtint
#define lrcopy  (long)rcopy
#define lreal   (long)greal
#define lrecip  (long)recip
#define lred    (long)gred
#define lremii  (long)remii
#define lrem    (long)grem
#define lrndtoi (long)grndtoi
#define lroots  (long)roots
#define lscalmat (long)scalarmat
#define lscalsmat (long)scalarmat_s
#define lsh     (long)gsinh
#define lshifti (long)shifti
#define lshift  (long)gshift
#define lshiftr (long)shiftr
#define lsin    (long)gsin
#define lsqri   (long)sqri
#define lsqr    (long)gsqr
#define lsqrt   (long)gsqrt
#define lstoi   (long)stoi
#define lsub    (long)gsub
#define lsubgs  (long)gsubgs
#define lsubii  (long)subii
#define lsubir  (long)subir
#define lsubis  (long)subis
#define lsubres (long)resultant
#define lsubri  (long)subri
#define lsubrr  (long)subrr
#define lsubrs  (long)subrs
#define lsubst  (long)gsubst
#define lsubsg  (long)gsubsg
#define lsubsi  (long)subsi
#define lsubsr  (long)subsr
#define ltan    (long)gtan
#define ltchebi (long)polchebyshev
#define lth     (long)gtanh
#define ltrace  (long)gtrace
#define ltrans  (long)gtrans
#define ltrunc  (long)gtrunc
#define lutoi   (long)utoi
#define lround  (long)ground
#define ldiv    (long)gdiv
#endif
