#
##
#

APPNAME = baobab.firefox

TOP = ../../ssc
TNET = tn.a

FILESCPP = \
		   main.cpp \
		   baobabthread.cpp

FILESC =

CFLAGS = -Wall -g -I$(TOP) -lpthread

OBJS = $(FILESC:.c=.o) $(FILESCPP:.cpp=.o)

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $(@D)/$(@F)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(@D)/$(@F)

all: $(TOP)/$(TNET) $(APPNAME)

dummy:
	 

$(TOP)/$(TNET): dummy
	make -C $(TOP)

$(APPNAME): $(OBJS) $(TOP)/$(TNET)
	$(CXX) $(CFLAGS) -o $(APPNAME) $(OBJS) $(TOP)/$(TNET)

tilde:
	find ./ -name \*~ | xargs rm -f

clean: tilde
	find ./ -name core | xargs rm -f
	find ./ -name \*.o | xargs rm -f
	find ./ -name \*.a | xargs rm -f
	rm -f test

