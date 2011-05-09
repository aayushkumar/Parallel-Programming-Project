CC	= gcc 
CFLAGS	= -O `pkg-config --libs --cflags gtk+-2.0`
LDFLAGS	= -lm
LINT	= lint
PRINT	= ato2ps -Ple

INCS 	=\
	dc.h\
	edge.h\
	draw.h\

SRC 	=\
	dc.c\
	edge.c\
	drawlines.c


OBJS 	=\
	dc.o\
	edge.o\
	drawlines.o

TEXT	= Makefile README $(INCS) $(SRC) 

dct	: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(LDFLAGS)

lint	: $(SRC) $(INCS)
	$(LINT) $(SRC)

print	:
	$(PRINT) $(TEXT)

tar	:
	tar cvf dct.tar $(TEXT)

DINCS	=\

$(OBJS) 	: $(DINCS)

edge.o	: edge.h 
dc.o	: dc.h edge.h
