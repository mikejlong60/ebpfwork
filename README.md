Building the docker comntainer for running eBPF experiments. MAC OSX does not support eBPF

  - docker build -t libbpf-bootstrap-env . 

Running the docker container:
sh ./runme.sh

This link helped me fifure out how to run the bootstrap toolset after I figured out how to build it: https://hemslo.io/run-ebpf-programs-in-docker-using-docker-bpf/

Follow the instructions here to build the bootstrap project: https://github.com/libbpf/libbpf-bootstrap


To install man pages run "unminimize".
To install man database run "apt-get install man-db".



Follow the instuctions here to build bpftool and the examples from the Liz Rice book: git@github.com:lizrice/learning-ebpf.git
