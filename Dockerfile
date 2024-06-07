FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    clang \
    llvm \
    gcc \
    make \
    git \
    libelf-dev \
#    gcc-multilib \
    build-essential \
    cmake \
    pkg-config \
    vim \	
    libpcap-dev

WORKDIR /workspace



# Use the latest CentOS image as the base
#FROM rockylinux:9


#run yum -y update

#run dnf -y install clang libbpf elfutils-libelf elfutils-libelf-devel zlib-devel git vim
# Install basic packages
#RUN yum -y update && \
#    yum -y install epel-release && \
#    yum -y install \
#    vim \
#    wget \
#    curl \
#    git \
#    net-tools && \
#    yum clean all

# Set the working directory
#WORKDIR /root

# Set the default command
CMD ["/bin/bash"]

