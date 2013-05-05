all:
	cd assembler && $(MAKE)
	cd simulator && $(MAKE)
	cd  debugger && $(MAKE)

.PHONY: clean

clean:
	cd assembler && $(MAKE) $@
	cd simulator && $(MAKE) $@
	cd debugger && $(MAKE) $@
