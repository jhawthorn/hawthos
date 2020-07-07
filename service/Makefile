SERVICES=boot ping

all:
	for dir in $(SERVICES); do make -C "$$dir"; done

clean:
	for dir in $(SERVICES); do make -C "$$dir" clean; done
