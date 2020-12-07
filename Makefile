include Makefile.inc

SRC = $(wildcard *cpp)
OBJS = $(SRC:.cpp=.o)
#OBJS := $(addprefix obj/, $(OBJS))

all: bin

bin:
	$(MAKE) $(EXENAME)

$(EXENAME): $(OBJS)
	$(LINKMAIN) $(LNFLAGS) -o $(EXENAME) $(OBJS) $(LIBS)

%.o: %.cpp variables.h Makefile.inc
	$(CC) $(CFLAGS) -I$(INC) $(INCBOOST) $(INCNETCDF) $(INCCONF) -o $@ -c $<

clean:
	$(RM) $(RMFLAGS) *.o $(EXENAME)
	
.PHONY: clean all
