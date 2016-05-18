.PHONY : all check doc clean

all : doc check

check :
	@(cd src/ && $(MAKE))
doc :
	@(cd doc/ && $(MAKE) $@)
clean :
	@(cd src/ && $(MAKE) $@)
mrproper :
	@(cd src/ && $(MAKE) $@)
	@(cd doc/ && $(MAKE) $@)

