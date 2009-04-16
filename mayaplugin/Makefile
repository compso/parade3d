#!csh

#
# Makefile for parade3d plugin for Maya2009
#
#

include buildconfig

TAR           = tar -cf
COMPRESS      = gzip -9f
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
MOVE          = mv -f
SYMLINK       = ln -sf
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
CHK_FILE_EXISTS= test -f

.SUFFIXES: .cpp .cc .o .so .c

.cc.o:
	$(C++) -c $(INCLUDES) $(C++FLAGS) -o $@ $<
	mv -f $@ ../build

.cpp.o:
	$(C++) -c $(INCLUDES) $(C++FLAGS) -o $@ $<
	mv -f $@ ../build

.cc.i:
	$(C++) -E $(INCLUDES) $(C++FLAGS) $*.cc > $*.i

.cc.so:
	-rm -f $@
	$(LD) -o $@ $(INCLUDES) $< $(LIBS)

.cpp.so:
	-rm -f $@
	$(LD) -o $@ $(INCLUDES) $< $(LIBS)

.o.so:
	-rm -f $@
	$(LD) -o $@ $< $(LIBS)




####### Output directory

OBJECTS_DIR   = build/
	
SOURCES = src/ParadeFileTranslator.cpp src/pluginMain.cpp
OBJECTS = build/ParadeFileTranslator.o  build/pluginMain.o

DESTDIR       = bin/
TARGET        = bin/parade3d-$(MAYA_VERSION).so

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CHK_DIR_EXISTS) bin || $(MKDIR) bin
	-rm -f $@
	$(LD) -o $@ $(OBJECTS) $(LIBS)

build/ParadeFileTranslator.o: src/ParadeFileTranslator.cpp
	@$(CHK_DIR_EXISTS) build || $(MKDIR) build
	$(C++) -c $(INCLUDES) $(C++FLAGS) -o $@ $<

build/pluginMain.o: src/pluginMain.cpp
	@$(CHK_DIR_EXISTS) build || $(MKDIR) build
	$(C++) -c $(INCLUDES) $(C++FLAGS) -o $@ $<

install: 
	$(COPY) bin/*.so $(PLUG_LOCATION)

dist:
	@$(CHK_DIR_EXISTS) build/parade3d-$(MAYA_VERSION) || $(MKDIR) build/parade3d-$(MAYA_VERSION)
	$(COPY_FILE) --parents $(TARGET) scripts/*.mel build/parade3d-$(MAYA_VERSION)/ && (cd `dirname build/parade3d-$(MAYA_VERSION)` && $(TAR) parade3d-$(MAYA_VERSION).tar parade3d-$(MAYA_VERSION) && $(COMPRESS) parade3d-$(MAYA_VERSION).tar) && $(MOVE) `dirname build/parade3d-$(MAYA_VERSION)`/parade3d-$(MAYA_VERSION).tar.gz . && $(DEL_FILE) -r build/parade3d-$(MAYA_VERSION)

clean:
	-rm -f build/*.o scripts/*~ src/*~ *~

Clean:
	-rm -f build/*.o bin/*.so *.bak scripts/*~ src/*~ *~
