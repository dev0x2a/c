#ifndef _STDIO_H
#if!defined __need_FILE&&!defined __need___FILE
#define _STDIO_H 1
#include<features.h>
__BEGIN_DECLS
#define __need_size_t
#define __need_NULL
#include<stddef.h>
#include<bits/types.h>
#define __need_FILE
#define __need___FILE
#endif
#if!defined __FILE_defined&&defined __need_FILE
struct _IO_FILE;
__BEGIN_NAMESPACE_STD
typedef struct _IO_FILE FILE;
__END_NAMESPACE_STD
#if defined __USE_LARGEFILE64||defined __USE_POSIX||defined __USE_ISOC99||defined __USE_XOPEN||defined __USE_POSIX2
__USING_NAMESPACE_STD(FILE)
#endif
#define __FILE_defined 1
#endif
#undef __need_FILE
#if!defined ____FILE_defined&&defined __need___FILE
typedef struct _IO_FILE __FILE;
# define ____FILE_defined	1
#endif
#undef __need___FILE
#ifdef _STDIO_H
#define _STDIO_USES_IOSTREAM
#include<libio.h>
#if defined __USE_XOPEN||defined __USE_XOPEN2K8
#ifdef __GNUC__
#ifndef _VA_LIST_DEFINED
typedef _G_va_list va_list;
#define _VA_LIST_DEFINED
#endif
#else
#include<stdarg.h>
#endif
#endif
#if defined __USE_UNIX98||defined __USE_XOPEN2K
#ifndef __off_t_defined
#ifndef __USE_FILE_OFFSET64
typedef __off_t off_t;
#else
typedef __off64_t off_t;
#endif
#define __off_t_defined
#endif
#if defined __USE_LARGEFILE64&&!defined __off64_t_defined
typedef __off64_t off64_t;
#define __off64_t_defined
#endif
#endif
#ifdef __USE_XOPEN2K8
#ifndef __ssize_t_defined
typedef __ssize_t ssize_t;
#define __ssize_t_defined
#endif
#endif
__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
typedef _G_fpos_t fpos_t;
#else
typedef _G_fpos64_t fpos_t;
#endif
__END_NAMESPACE_STD
#ifdef __USE_LARGEFILE64
typedef _G_fpos64_t fpos64_t;
#endif
#define _IOFBF 0
#define _IOLBF 1
#define _IONBF 2
#ifndef BUFSIZ
#define BUFSIZ _IO_BUFSIZ
#endif
#ifndef EOF
#define EOF (-1)
#endif
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#ifdef __USE_GNU
#define SEEK_DATA 3
#define SEEK_HOLE 4
#endif
#if defined __USE_MISC||defined __USE_XOPEN
#define P_tmpdir "/tmp"
#endif
#include<bits/stdio_lim.h>
extern struct _IO_FILE*stdin;extern struct _IO_FILE*stdout;extern struct _IO_FILE*stderr;
#define stdin stdin
#define stdout stdout
#define stderr stderr
__BEGIN_NAMESPACE_STD
extern int remove(const char*__filename)__THROW;extern int rename(const char*__old,const char*__new)__THROW;
__END_NAMESPACE_STD
#ifdef __USE_ATFILE
extern int renameat(int __oldfd,const char*__old,int __newfd,const char*__new)__THROW;
#endif
__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
extern FILE*tmpfile(void)__wur;
#else
#ifdef __REDIRECT
extern FILE*__REDIRECT(tmpfile,(void),tmpfile64)__wur;
#else
#define tmpfile tmpfile64
#endif
#endif
#ifdef __USE_LARGEFILE64
extern FILE*tmpfile64(void)__wur;
#endif
extern char*tmpnam(char*__s)__THROW __wur;
__END_NAMESPACE_STD
#ifdef __USE_MISC
extern char*tmpnam_r(char*__s)__THROW __wur;
#endif
#if defined __USE_MISC||defined __USE_XOPEN
extern char*tempnam(const char*__dir,const char*__pfx)__THROW __attribute_malloc__ __wur;
#endif
__BEGIN_NAMESPACE_STD
extern int fclose(FILE*__stream);extern int fflush(FILE*__stream);
__END_NAMESPACE_STD
#ifdef __USE_MISC
extern int fflush_unlocked(FILE*__stream);
#endif
#ifdef __USE_GNU
extern int fcloseall(void);
#endif
__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
extern FILE*fopen(const char*__restrict __filename,const char*__restrict __modes)__wur;
extern FILE*freopen(const char*__restrict __filename,const char*__restrict __modes,FILE*__restrict __stream)__wur;
#else
#ifdef __REDIRECT
extern FILE*__REDIRECT(fopen,(const char*__restrict __filename,const char*__restrict __modes),fopen64)__wur;
extern FILE*__REDIRECT(freopen,(const char*__restrict __filename,const char*__restrict __modes,FILE*__restrict __stream),freopen64)__wur;
# else
#define fopen fopen64
#define freopen freopen64
#endif
#endif
__END_NAMESPACE_STD
#ifdef __USE_LARGEFILE64
extern FILE*fopen64(const char*__restrict __filename,const char*__restrict __modes)__wur;
extern FILE*freopen64(const char*__restrict __filename,const char*__restrict __modes,FILE*__restrict __stream)__wur;
#endif
#ifdef __USE_POSIX
extern FILE*fdopen(int __fd,const char*__modes)__THROW __wur;
#endif
#ifdef __USE_GNU
extern FILE*fopencookie(void*__restrict __magic_cookie,const char*__restrict __modes,_IO_cookie_io_functions_t __io_funcs)__THROW __wur;
#endif
#ifdef __USE_XOPEN2K8
extern FILE*fmemopen(void*__s,size_t __len,const char*__modes)__THROW __wur;extern FILE*open_memstream(char**__bufloc,size_t*__sizeloc)__THROW __wur;
#endif
__BEGIN_NAMESPACE_STD
extern void setbuf(FILE*__restrict __stream,char*__restrict __buf)__THROW;extern int setvbuf(FILE*__restrict __stream, char *__restrict __buf,int __modes,size_t __n)__THROW;
__END_NAMESPACE_STD
#ifdef __USE_MISC
extern void setbuffer(FILE*__restrict __stream,char*__restrict __buf,size_t __size)__THROW;extern void setlinebuf(FILE*__stream)__THROW;
#endif
__BEGIN_NAMESPACE_STD
extern int fprintf(FILE*__restrict __stream,const char*__restrict __format,...);extern int printf(const char*__restrict __format,...);
extern int sprintf(char*__restrict __s,const char*__restrict __format,...)__THROWNL;extern int vfprintf(FILE*__restrict __s,const char*__restrict __format,_G_va_list __arg);
extern int vprintf(const char*__restrict __format,_G_va_list __arg);extern int vsprintf(char*__restrict __s,const char*__restrict __format,_G_va_list __arg)__THROWNL;
__END_NAMESPACE_STD
#if defined __USE_ISOC99||defined __USE_UNIX98
__BEGIN_NAMESPACE_C99
extern int snprintf(char*__restrict __s,size_t __maxlen,const char*__restrict __format,...)__THROWNL __attribute__((__format__(__printf__,3,4)));
extern int vsnprintf(char*__restrict __s,size_t __maxlen,const char*__restrict __format,_G_va_list __arg)__THROWNL __attribute__((__format__(__printf__,3,0)));
__END_NAMESPACE_C99
#endif
#ifdef __USE_GNU
extern int vasprintf(char**__restrict __ptr,const char*__restrict __f,_G_va_list __arg)__THROWNL __attribute__((__format__(__printf__,2,0)))__wur;
extern int __asprintf(char**__restrict __ptr,const char*__restrict __fmt,...)__THROWNL __attribute__((__format__(__printf__,2,3)))__wur;
extern int asprintf(char**__restrict __ptr,const char*__restrict __fmt,...)__THROWNL __attribute__((__format__(__printf__,2,3)))__wur;
#endif
#ifdef __USE_XOPEN2K8
extern int vdprintf(int __fd,const char*__restrict __fmt,_G_va_list __arg)__attribute__((__format__(__printf__,2,0)));
extern int dprintf(int __fd,const char*__restrict __fmt,...)__attribute__((__format__(__printf__,2,3)));
#endif
__BEGIN_NAMESPACE_STD
extern int fscanf(FILE*__restrict __stream,const char*__restrict __format,...)__wur;extern int scanf(const char*__restrict __format,...)__wur;
extern int sscanf(const char*__restrict __s,const char*__restrict __format,...)__THROW;
#if defined __USE_ISOC99&&!defined __USE_GNU&&(!defined __LDBL_COMPAT||!defined __REDIRECT)&&(defined __STRICT_ANSI__||defined __USE_XOPEN2K)
#ifdef __REDIRECT
extern int __REDIRECT(fscanf,(FILE*__restrict __stream,const char*__restrict __format,...),__isoc99_fscanf)__wur;
extern int __REDIRECT(scanf,(const char*__restrict __format,...),__isoc99_scanf)__wur;extern int __REDIRECT_NTH(sscanf,(const char*__restrict __s,const char*__restrict __format,...),__isoc99_sscanf);
# else
extern int __isoc99_fscanf(FILE*__restrict __stream,const char*__restrict __format,...)__wur;extern int __isoc99_scanf(const char*__restrict __format,...)__wur;
extern int __isoc99_sscanf(const char*__restrict __s,const char*__restrict __format,...)__THROW;
#define fscanf __isoc99_fscanf
#define scanf __isoc99_scanf
#define sscanf __isoc99_sscanf
#endif
#endif
__END_NAMESPACE_STD
#ifdef __USE_ISOC99
__BEGIN_NAMESPACE_C99
extern int vfscanf(FILE*__restrict __s,const char*__restrict __format,_G_va_list __arg)__attribute__((__format__(__scanf__,2,0)))__wur;
extern int vscanf(const char*__restrict __format,_G_va_list __arg)__attribute__((__format__(__scanf__,1,0)))__wur;
extern int vsscanf(const char*__restrict __s,const char*__restrict __format,_G_va_list __arg)__THROW __attribute__((__format__(__scanf__,2,0)));
#if!defined __USE_GNU&&(!defined __LDBL_COMPAT||!defined __REDIRECT)&&(defined __STRICT_ANSI__||defined __USE_XOPEN2K)
#ifdef __REDIRECT
extern int __REDIRECT(vfscanf,(FILE*__restrict __s,const char*__restrict __format,_G_va_list __arg),__isoc99_vfscanf)__attribute__((__format__(__scanf__,2,0)))__wur;
extern int __REDIRECT(vscanf,(const char*__restrict __format,_G_va_list __arg),__isoc99_vscanf)__attribute__((__format__(__scanf__,1,0)))__wur;
extern int __REDIRECT_NTH(vsscanf,(const char*__restrict __s,const char*__restrict __format,_G_va_list __arg),__isoc99_vsscanf)__attribute__((__format__(__scanf__,2,0)));
#else
extern int __isoc99_vfscanf(FILE*__restrict __s,const char*__restrict __format,_G_va_list __arg)__wur;extern int __isoc99_vscanf(const char*__restrict __format,_G_va_list __arg)__wur;
extern int __isoc99_vsscanf(const char*__restrict __s,const char*__restrict __format,_G_va_list __arg)__THROW;
#define vfscanf __isoc99_vfscanf
#define vscanf __isoc99_vscanf
#define vsscanf __isoc99_vsscanf
#endif
#endif
__END_NAMESPACE_C99
#endif
__BEGIN_NAMESPACE_STD
extern int fgetc(FILE*__stream);extern int getc(FILE*__stream);extern int getchar(void);
__END_NAMESPACE_STD
#define getc(_fp) _IO_getc (_fp)
#ifdef __USE_POSIX199506
extern int getc_unlocked(FILE*__stream);extern int getchar_unlocked(void);
#endif
#ifdef __USE_MISC
extern int fgetc_unlocked(FILE*__stream);
#endif
__BEGIN_NAMESPACE_STD
extern int fputc(int __c,FILE*__stream);extern int putc(int __c,FILE*__stream);extern int putchar(int __c);
__END_NAMESPACE_STD
#define putc(_ch, _fp) _IO_putc (_ch, _fp)
#ifdef __USE_MISC
extern int fputc_unlocked(int __c,FILE*__stream);
#endif
#ifdef __USE_POSIX199506
extern int putc_unlocked(int __c,FILE*__stream);extern int putchar_unlocked(int __c);
#endif
#if defined __USE_MISC||(defined __USE_XOPEN&&!defined __USE_XOPEN2K)
extern int getw(FILE*__stream);extern int putw(int __w,FILE*__stream);
#endif
__BEGIN_NAMESPACE_STD
extern char*fgets(char*__restrict __s,int __n,FILE*__restrict __stream)__wur;
#if!defined __USE_ISOC11||(defined __cplusplus&&__cplusplus<=201103L)
extern char*gets(char*__s)__wur __attribute_deprecated__;
#endif
__END_NAMESPACE_STD
#ifdef __USE_GNU
extern char*fgets_unlocked(char*__restrict __s,int __n,FILE*__restrict __stream)__wur;
#endif
#ifdef __USE_XOPEN2K8
extern _IO_ssize_t __getdelim(char**__restrict __lineptr,size_t*__restrict __n,int __delimiter,FILE*__restrict __stream)__wur;
extern _IO_ssize_t getdelim(char**__restrict __lineptr,size_t*__restrict __n,int __delimiter,FILE*__restrict __stream)__wur;
extern _IO_ssize_t getline(char**__restrict __lineptr,size_t*__restrict __n,FILE*__restrict __stream)__wur;
#endif
__BEGIN_NAMESPACE_STD
extern int fputs(const char*__restrict __s,FILE*__restrict __stream);extern int puts(const char*__s);extern int ungetc(int __c,FILE*__stream);
extern size_t fread(void*__restrict __ptr,size_t __size,size_t __n,FILE*__restrict __stream)__wur;
extern size_t fwrite(const void *__restrict __ptr,size_t __size,size_t __n,FILE*__restrict __s);
__END_NAMESPACE_STD
#ifdef __USE_GNU
extern int fputs_unlocked(const char*__restrict __s,FILE*__restrict __stream);
#endif
#ifdef __USE_MISC
extern size_t fread_unlocked(void*__restrict __ptr,size_t __size,size_t __n,FILE*__restrict __stream)__wur;
extern size_t fwrite_unlocked(const void*__restrict __ptr,size_t __size,size_t __n,FILE*__restrict __stream);
#endif
__BEGIN_NAMESPACE_STD
extern int fseek(FILE*__stream,long int __off,int __whence);extern long int ftell(FILE*__stream)__wur;extern void rewind(FILE*__stream);
__END_NAMESPACE_STD
#if defined __USE_LARGEFILE||defined __USE_XOPEN2K
#ifndef __USE_FILE_OFFSET64
extern int fseeko(FILE*__stream,__off_t __off,int __whence);extern __off_t ftello(FILE*__stream)__wur;
#else
#ifdef __REDIRECT
extern int __REDIRECT(fseeko,(FILE*__stream,__off64_t __off,int __whence),fseeko64);extern __off64_t __REDIRECT(ftello,(FILE*__stream),ftello64);
#else
#define fseeko fseeko64
#define ftello ftello64
#endif
#endif
#endif
__BEGIN_NAMESPACE_STD
#ifndef __USE_FILE_OFFSET64
extern int fgetpos(FILE*__restrict __stream,fpos_t*__restrict __pos);extern int fsetpos(FILE*__stream,const fpos_t*__pos);
#else
#ifdef __REDIRECT
extern int __REDIRECT(fgetpos,(FILE*__restrict __stream,fpos_t*__restrict __pos),fgetpos64);extern int __REDIRECT(fsetpos,(FILE*__stream,const fpos_t*__pos),fsetpos64);
#else
#define fgetpos fgetpos64
#define fsetpos fsetpos64
#endif
#endif
__END_NAMESPACE_STD
#ifdef __USE_LARGEFILE64
extern int fseeko64(FILE*__stream,__off64_t __off,int __whence);extern __off64_t ftello64(FILE*__stream)__wur;
extern int fgetpos64(FILE*__restrict __stream,fpos64_t*__restrict __pos);extern int fsetpos64(FILE*__stream,const fpos64_t*__pos);
#endif
__BEGIN_NAMESPACE_STD
extern void clearerr(FILE*__stream)__THROW;extern int feof(FILE*__stream)__THROW __wur;extern int ferror(FILE*__stream)__THROW __wur;
__END_NAMESPACE_STD
#ifdef __USE_MISC
extern void clearerr_unlocked(FILE*__stream)__THROW;extern int feof_unlocked(FILE*__stream)__THROW __wur;extern int ferror_unlocked(FILE*__stream)__THROW __wur;
#endif
__BEGIN_NAMESPACE_STD
extern void perror(const char*__s);
__END_NAMESPACE_STD
#include<bits/sys_errlist.h>
#ifdef __USE_POSIX
extern int fileno(FILE*__stream)__THROW __wur;
#endif
#ifdef __USE_MISC
extern int fileno_unlocked(FILE*__stream)__THROW __wur;
#endif
#ifdef __USE_POSIX2
extern FILE*popen(const char*__command,const char*__modes)__wur;extern int pclose(FILE*__stream);
#endif
#ifdef __USE_POSIX
extern char *ctermid(char*__s)__THROW;
#endif
#if(defined __USE_XOPEN&&!defined __USE_XOPEN2K)||defined __USE_GNU
extern char *cuserid(char*__s);
#endif
#ifdef __USE_GNU
struct obstack;extern int obstack_printf(struct obstack*__restrict __obstack,const char*__restrict __format,...)__THROWNL __attribute__((__format__(__printf__,2,3)));
extern int obstack_vprintf(struct obstack*__restrict __obstack,const char*__restrict __format,_G_va_list __args)__THROWNL __attribute__((__format__(__printf__,2,0)));
#endif
#ifdef __USE_POSIX199506
extern void flockfile(FILE*__stream)__THROW;extern int ftrylockfile(FILE*__stream)__THROW __wur;extern void funlockfile(FILE*__stream)__THROW;
#endif
#if defined __USE_XOPEN&&!defined __USE_XOPEN2K&&!defined __USE_GNU
#define __need_getopt
#include<getopt.h>
#endif
#ifdef __USE_EXTERN_INLINES
#include<bits/stdio.h>
#endif
#if __USE_FORTIFY_LEVEL>0&&defined __fortify_function
#include<bits/stdio2.h>
#endif
#ifdef __LDBL_COMPAT
#include<bits/stdio-ldbl.h>
#endif
__END_DECLS
#endif 
#endif
