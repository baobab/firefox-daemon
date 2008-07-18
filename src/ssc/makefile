
TNFILESCPP = \
		tnlib/tnnode.cpp					\
		tnlib/tnargs.cpp					\
		tnlib/tnbuffer.cpp					\
		tnlib/tnstring.cpp					\
		tnlib/tnlist.cpp					\
		tnlib/tnsocket.cpp					\
		tnlib/tnsocketip4.cpp				\
		tnlib/tnip.cpp						\
		tnlib/tndaemon.cpp					\
		tnlib/tndaemonip4.cpp				\
		tnlib/tncriticalsection.cpp 		\
		tnlib/tntokenbase.cpp				\
		tnlib/tntokenfile.cpp				\
		tnlib/tnstringto.cpp				\
		\
		tnos/linux/tnlcriticalsection.cpp 	\
		tnos/linux/tnthread.cpp 			\
		\

TNFILESC =	\
		tnos/tnos.c					\
		tnos/tnmem.c				\
		tnos/tnlog.c				\
		tnos/tnosstdio.c			\
		tnos/linux/linux.c			\
		\
		tnclib/tnclib.c				\
		tnclib/tncbuffer.c			\
		tnclib/tncstring.c			\
		tnclib/tnprintf.c			\
		tnclib/tncnode.c			\
		tnclib/tncmath.c
	
TNFILES = $(TNFILESC) $(TNFILESCPP)

TNOBJS = $(TNFILESC:.c=.o) $(TNFILESCPP:.cpp=.o)

CFLAGS = -Wall -g -I$(CURDIR)

TN = tn.a

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $(@D)/$(@F)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(@D)/$(@F)

all: tn.a test
	#$(MAKE) -C apps

tn.a: $(TNOBJS) 
	 $(AR) -r tn.a $(TNOBJS)

tilde:
	find ./ -name \*~ | xargs rm -f

clean: tilde
	find ./ -name core | xargs rm -f
	find ./ -name \*.o | xargs rm -f
	find ./ -name \*.a | xargs rm -f
	rm -f test

test: tn.a test.cpp
	$(CXX) $(CFLAGS) -o test test.cpp tn.a

