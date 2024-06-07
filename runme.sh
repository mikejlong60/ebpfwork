docker run -it -v /usr/src:/usr/src:ro \
	-v $(pwd):/workspace \
        -v /lib/modules/:/lib/modules:ro \
        -v debugfs:/sys/kernel/debug:rw \
        --net=host --pid=host --privileged \
 	 --ulimit memlock=1073741824 --cap-add=SYS_ADMIN --cap-add=NET_ADMIN  \
	libbpf-bootstrap-env                       

