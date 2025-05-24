CC=gcc
LINT=splint
CFLAGS=-Wall -Wpedantic -O3
EXENAME=a.out
RNAME=lint.txt

ODIR=obj
LDIR=../lib
RDIR=rep
SDIR=../src

LIBS=

#################################
#Include Paths                  #
#################################
IDIR = -I../inc
IDIR += -I../OS/inc
IDIR += -I../Platform/inc

#################################
#OS Objects                     #
#################################
_OS_OBJ = LinkedList.o 
_OS_OBJ += LinkedListElement.o 
_OS_OBJ += Memory.o 
_OS_OBJ += Result.o 
_OS_OBJ += ErrorStorage.o 
_OS_OBJ += Time.o 
_OS_OBJ += Queue.o  
_OS_OBJ += StackAllocator.o 
_OS_OBJ += Scheduler.o
_OS_OBJ += DeviceManager.o
_OS_OBJ += NamedQueue.o

OS_OBJ = $(patsubst %,$(ODIR)/%,$(_OS_OBJ))

#################################
#HAL Objects                    #
#################################
_HAL_OBJ = Main.o
_HAL_OBJ += Platform.o 
_HAL_OBJ += PlatformConfig_imp.o 

HAL_OBJ = $(patsubst %,$(ODIR)/%,$(_HAL_OBJ))

#################################
#Config Objects                 #
#################################
_CFG_OBJ = VectorQueue_cfg.o

CFG_OBJ = $(patsubst %,$(ODIR)/%,$(_CFG_OBJ))

#################################

OBJ = $(HAL_OBJ) 
OBJ += $(OS_OBJ)
OBJ += $(CFG_OBJ)


#################################
#Build OS Objects               #
#################################
$(ODIR)/%.o: ../OS/src/%.c
	$(CC) -c -o $@ $<  $(IDIR) $(CFLAGS)

#################################
#Build Project Objects          #
#################################
$(ODIR)/%.o: ../Platform/src/%.c
	$(CC) -c -o $@ $<  $(IDIR) $(CFLAGS)

#################################
#Build Config Objects           #
#################################
$(ODIR)/%.o: ../Platform/cfg/%.c
	$(CC) -c -o $@ $<  $(IDIR) $(CFLAGS)

#################################
#Link Project Objects           #
#################################
$(EXENAME): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

#########################################################################################

#################################
#Other Targets                  #
#################################

.PHONY: clean
.PHONY: lint
.PHONY: doc

lint:
	$(LINT) $(SDIR)/*.c -I$(IDIR) > $(RDIR)/$(RNAME)

clean:
	rm -f $(ODIR)/*.o
	rm -f $(EXENAME)
	rm -f $(RDIR)/$(RNAME)

doc:
	doxygen doc/Doxyfile
