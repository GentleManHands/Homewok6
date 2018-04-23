#
# UTD CS3377 CDK Example
# Dr. Perkins
# stephen.perkins@utdallas.edu
#

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = cdkexample

OBJS = cdkexample.o

PROJECTNAME = prog6

.PHONY: backup

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

backup:
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURIDNAME := $(shell basename 'pwd'))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date + '%Y.%m.%d-%H:%M:%s').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
