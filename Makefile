srcdir = .

SHELL = /bin/sh

top_builddir = .

include ./Makedefs


FLAGS_TO_PASS = \
        MAKE='$(MAKE)'

#SUBDIRS = ho cp1 cpn diffs testmat testrng
SUBDIRS = diffs 

all:
	@for subdir in $(SUBDIRS) ; do \
	  (cd $$subdir && $(MAKE) $(FLAGS_TO_PASS) $@ ) || exit 1; \
	done

clean:
	#rm -f config.cache blitz/config.h
	@for subdir in $(SUBDIRS) ; do \
	  (cd $$subdir && $(MAKE) $(FLAGS_TO_PASS) $@ ) || exit 1; \
	done

clobber:
	#rm -f config.cache blitz/config.h
	@for subdir in $(SUBDIRS) ; do \
	  (cd $$subdir && $(MAKE) $(FLAGS_TO_PASS) $@ ) || exit 1; \
	done
