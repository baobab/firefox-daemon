#
## SSC Makefile
#

TNET=ssc


all: $(TNET)/tn.a
	$(MAKE) -C apps


clean:
	$(MAKE) -C $(TNET) clean
	$(MAKE) -C apps clean

tilde:
	find ./ -name \*~ | xargs rm -f

$(TNET)/tn.a:
	$(MAKE) -C $(TNET)

commit: tilde
	git commit -a
