TARGETS = hello hello-func redirect

all: $(TARGETS)
.PHONY: all

$(TARGETS): %: %.bpf.o 

%.bpf.o: %.bpf.c
	clang \
	    -target bpf \
	    -I/usr/include -I/workspace/libbpf/src \
		-g \
	    -O2 -o $@ -c $<

clean: 
	- rm *.bpf.o
	- rm -f /sys/fs/bpf/hello 
	- rm -f /sys/fs/bpf/hello-func
	- rm -f /sys/fs/bpf/redirect
	- rm -f /sys/fs/bpf/redirect-free
	

