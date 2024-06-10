FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    clang \
    llvm \
    gcc \
    make \
    git \
    iproute2 \
    libelf-dev \
    file \
    build-essential \
    cmake \
    pkg-config \
    vim \	
    libpcap-dev

#RUN unminimize
#RUN apt-get install man-db
WORKDIR /workspace

# Set the default command
CMD ["/bin/bash"]

