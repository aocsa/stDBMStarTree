# Borland C++ Compiler 5 Makefile

CC=bcc32
AR=tlib32
LIBNAME=..\arboretum.lib
SRCDIR=..\..\src
INCLUDEDIR=..\..\include
OBJ= ..\..\src\stUtil.obj ..\..\src\stCompress.obj \
    ..\..\src\stDiskPageManager.obj ..\..\src\stListPriorityQueue.obj \
    ..\..\src\stMemoryPageManager.obj ..\..\src\stPage.obj \
    ..\..\src\stPlainDiskPageManager.obj ..\..\src\stResult.obj \
    ..\..\src\stSlimNode.obj ..\..\src\stTreeInformation.obj \
    ..\..\src\CStorage.obj ..\..\src\stDBMNode.obj ..\..\src\stMNode.obj \
    ..\..\src\stDummyNode.obj ..\..\src\stMMNode.obj
SRC=  $(SRCDIR)/CStorage.cpp \
   $(SRCDIR)/stTreeInformation.cpp \
   $(SRCDIR)/stDummyNode.cpp \
   $(SRCDIR)/stMemoryPageManager.cpp \
   $(SRCDIR)/stSlimNode.cpp \
   $(SRCDIR)/stPartitionNode.cpp \
   $(SRCDIR)/stUtil.cpp \
   $(SRCDIR)/stPage.cpp \
   $(SRCDIR)/stListPriorityQueue.cpp \
   $(SRCDIR)/stDBMNode.cpp \
   $(SRCDIR)/stDiskPageManager.cpp \
   $(SRCDIR)/stPlainDiskPageManager.cpp
INCLUDEPATH = ..\include;..\..\include

# Rules
#.cpp.obj:
#   bcc32 -c $<

#$(LIBNAME): $(SRC)


# Implicit Rules
.cpp.obj:
   $(CC) -O2 -w -Vx -Ve -X- -a8 -b- -k- -vi -c -tW -tWM -I$(INCLUDEPATH) -n$(@D) {$< }

# Rules
$(LIBNAME): $(OBJ)
   $(AR) -r $(LIBNAME) $(OBJ)

default: $(LIBNAME)
