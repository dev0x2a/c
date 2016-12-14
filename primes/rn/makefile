VERSION=rbn-00.1
CFLAGS += -Wall -W -Wshadow -Isrc/headers

# Compiler and Linker Names
ifndef PREFIX
  PREFIX=
endif

ifeq ($(CC),cc)
  CC = $(PREFIX)gcc
endif
LD=$(PREFIX)ld
AR=$(PREFIX)ar
RANLIB=$(PREFIX)ranlib

ifndef MAKE
   MAKE=make
endif

ifeq ($V,1)
silent=
else
silent=@
endif

%.o: %.c
ifneq ($V,1)
	@echo "   * ${CC} $@"
endif
	${silent} ${CC} ${CFLAGS} -c $< -o $@

ifdef COMPILE_DEBUG
#debug
CFLAGS += -g3
else
ifndef IGNORE_SPEED
CFLAGS += -O3 -funroll-loops
#profiling
#PROF=-pg -g
#CFLAGS += $(PROF)

#speed
CFLAGS += -fomit-frame-pointer
endif
endif

#START_INS
OBJECTS=
HEADERS=rbn.h rn_mul.h
#END_INS

ifndef LIBPATH
   LIBPATH=/usr/lib
endif

ifndef INCPATH
   INCPATH=/usr/include
endif

ifndef INSTALL_GROUP
   GROUP=wheel
else
   GROUP=$(INSTALL_GROUP)
endif

ifndef INSTALL_USER
   USER=root
else
   USER=$(INSTALL_USER)
endif

ifndef LIBNAME
	LIBNAME=libtfm.a
endif

.PHONY: pre_gen
default: $(LIBNAME)

$(OBJECTS): $(HEADERS)

$(LIBNAME): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
	$(RANLIB) $@

install: $(LIBNAME)
	install -d -g $(GROUP) -o $(USER) $(DESTDIR)$(LIBPATH)
	install -d -g $(GROUP) -o $(USER) $(DESTDIR)$(INCPATH)
	install -g $(GROUP) -o $(USER) $(LIBNAME) $(DESTDIR)$(LIBPATH)
	install -g $(GROUP) -o $(USER) $(HEADERS_PUB) $(DESTDIR)$(INCPATH)

HEADER_FILES=$(notdir $(HEADERS_PUB))
uninstall:
	rm $(DESTDIR)$(LIBPATH)/$(LIBNAME)
	rm $(HEADER_FILES:%=$(DESTDIR)$(INCPATH)/%)

profiled:
	CC="$(CC)" PREFIX="${PREFIX} CFLAGS="${CFLAGS} -fprofile-generate" MAKE=${MAKE} ${MAKE} timing
	./test
	rm -f `find . -type f -name "*.o" | xargs`
	rm -f `find . -type f -name "*.a" | xargs`
	rm -f test
	CC=$(CC) PREFIX="${PREFIX} CFLAGS="${CFLAGS} -fprofile-use" MAKE=${MAKE} ${MAKE} timing
	
rsatest: $(LIBNAME) demo/rsa.o
	$(CC) $(CFLAGS) demo/rsa.o $(LIBNAME) -o rsatest

clean:
	rm -f a.out
	rm -f `find . -type f -name "*.o" | xargs`
	rm -f `find . -type f -name "*.lo"  | xargs`
	rm -f `find . -type f -name "*.a" | xargs`
	rm -f `find . -type f -name "*.la"  | xargs`
	rm -f `find . -type f -name "*.obj" | xargs`
	rm -f `find . -type f -name "*.lib" | xargs`
	rm -f `find . -type f -name "*.gcov" | xargs`
	rm -f `find . -type f -name "*.gcda" | xargs`
	rm -f `find . -type f -name "*.gcno" | xargs`
	rm -f `find . -type f -name "*.il" | xargs`
	rm -f `find . -type f -name "*.dyn" | xargs`
	rm -f `find . -type f -name "*.dpi" | xargs`
	rm -rf `find . -type d -name "*.libs" | xargs`

pre_gen:
	perl gen.pl
	sed -e 's/[[:blank:]]*$$//' mpi.c > pre_gen/mpi.c
	rm mpi.c

zipup:
	rm -rf ../tomsfastmath-$(VERSION) && rm -f ../rbn-$(VERSION).zip ../rbn-$(VERSION).tar.bz2 && \
	expsrc.sh -i . -o ../tomsfastmath-$(VERSION) --svntags --no-fetch -p '*.c' -p '*.h' && \
	MAKE=${MAKE} ${MAKE} -C ../tomsfastmath-$(VERSION) docs && \
	tar -c ../tomsfastmath-$(VERSION)/* | xz -cz > ../rbn-$(VERSION).tar.xz && \
	find ../tomsfastmath-$(VERSION)/ -type f -exec unix2dos -q {} \; && \
	zip -9 -r ../rbn-$(VERSION).zip ../tomsfastmath-$(VERSION)/* && \
	gpg -b -a ../rbn-$(VERSION).tar.xz && gpg -b -a ../rbn-$(VERSION).zip

