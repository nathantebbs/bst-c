COMPILER = clang
SOURCE_LIBS = -Ilib/
OSX_OUT = -o "bin/osx/bstc"
CFILES = src/*.c

TARGET = bstc

$(TARGET):
	$(COMPILER) $(CFILES) $(OSX_OUT) $(OSX_OPT)

install: $(TARGET)
	install -m 0755 ./bin/osx/$(TARGET) /usr/local/bin

uninstall: $(TARGET)
	rm -f /usr/local/bin/$(TARGET)
