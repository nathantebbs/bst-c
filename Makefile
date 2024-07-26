COMPILER = clang
SOURCE_LIBS = -Ilib/
OSX_OUT = -o "bin/build_osx"
CFILES = src/*.c

build_osx:
	$(COMPILER) $(CFILES) $(OSX_OUT) $(OSX_OPT)
