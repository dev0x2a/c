#======================================================================#
#                                                                      #
# c makefile                                                           #
# ------------                                                         #
#   $ make           		compile & link                                 #
#   $ make NODEP=yes 		compile & link w/o generating dependencies     #
#   $ make objs      		compile only (no linking)                      #
#   $ make ctags     		create ctags for vi                            #
#   $ make clean     		clean objects & executable                     #
#   $ make distclean 		clean objects, executable & dependencies       #
#   $ make help      		print usage                                    #
#                                                                      #
#======================================================================#

## custom
##=====================================================================

MY_CFLAGS =
MY_LIBS   =
LDFLAGS   =
SRCDIRS   =
PROGRAM   = main

## implicit
##=====================================================================

SRCEXTS    = .c
HDREXTS    = .h
CC         = cc
CTAGS 		 = ctags
CTAGSFLAGS =
#CFLAGS     = -g -O2
#RM         = rm -f

## stable
##=====================================================================

SHELL = /bin/sh
EMPTY =
SPACE = $(EMPTY) $(EMPTY)
ifeq ($(PROGRAM),)
  CUR_PATH_NAMES = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))
  PROGRAM = $(word $(words $(CUR_PATH_NAMES)),$(CUR_PATH_NAMES))
  ifeq ($(PROGRAM),)
    PROGRAM = a.out
  endif
endif
ifeq ($(SRCDIRS),)
  SRCDIRS = .
endif
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
OBJS    = $(addsuffix .o, $(basename $(SOURCES)))
DEPS    = $(OBJS:.o=.d)
DEP_OPT = $(shell if `$(CC) --version | grep "GCC" >/dev/null`; then \
                  echo "-MM -MP"; else echo "-M"; fi )
DEPEND    = $(CC)  $(DEP_OPT)  $(MY_CFLAGS) $(CFLAGS)
DEPEND.d  = $(subst -g ,,$(DEPEND))
COMPILE.c = $(CC) $(MY_CFLAGS) $(CFLAGS) -c
LINK.c    = $(CC) $(MY_CFLAGS) $(CFLAGS) $(LDFLAGS)
.PHONY: all objs ctags clean distclean help show
.SUFFIXES:
all: $(PROGRAM)
%.d:%.c
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@
objs:$(OBJS)
%.o:%.c
	$(COMPILE.c) $< -o $@
ctags: $(HEADERS) $(SOURCES)
	$(CTAGS) $(CTAGSFLAGS) $(HEADERS) $(SOURCES)
ifndef NODEP
ifneq ($(DEPS),)
  sinclude $(DEPS)
endif
endif
clean:
	$(RM) $(OBJS) $(PROGRAM)
distclean: clean
	$(RM) $(DEPS) TAGS
help:
	@echo 'c makefile'
	@echo
	@echo 'usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all         (=make) compile & link'
	@echo '  NODEP=yes   make w/o dependencies'
	@echo '  objs        compile only (no linking)'
	@echo '  ctags       create ctags for vi'
	@echo '  clean       clean objects & the executable'
	@echo '  distclean   clean objects, executable & dependencies'
	@echo '  show        show variables'
	@echo '  help        print this message'
	@echo
show:
	@echo 'PROGRAM       :' $(PROGRAM)
	@echo 'SRCDIRS       :' $(SRCDIRS)
	@echo 'HEADERS       :' $(HEADERS)
	@echo 'SOURCES       :' $(SOURCES)
	@echo 'OBJS          :' $(OBJS)
	@echo 'DEPS          :' $(DEPS)
	@echo 'DEPEND        :' $(DEPEND)
	@echo 'COMPILE.c     :' $(COMPILE.c)
	@echo 'link.c        :' $(LINK.c)

