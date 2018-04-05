include ./Make.defines

TOPTARGETS := all clean

SUBDIRS := $(wildcard */.)
SUBDIRS := $(filter-out include/., $(SUBDIRS))
SUBDIRS := $(filter-out tests/., $(SUBDIRS))

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)

library: 
	$(MAKE) -C libs/.
 
clean:
	rm $(LIBPUNP)
