FROM ubuntu:latest

# ----------------------------------
# Update Ubuntu and install Gcc
RUN apt-get -y update
RUN apt-get -y install gcc-9 g++-9
RUN apt-get -y install build-essential
