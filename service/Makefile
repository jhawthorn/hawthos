SERVICES=boot ping keyboard shell

all: services.list
	for dir in $(SERVICES); do make -C "$$dir"; done

services.list: Makefile
	for dir in $(SERVICES); do echo "$$dir"; done > services.list

clean:
	for dir in $(SERVICES); do make -C "$$dir" clean; done
