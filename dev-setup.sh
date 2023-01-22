#!/bin/bash

# dependencies for Ubuntu 22.04


sudo apt-get install \
  ninja-build \
   srecord \
   yotta \
   cc-arm-none-eabi

# ensure there is a default python (rather than python2.7, python3)
sudo update-alternatives --install /usr/local/bin/python python /usr/bin/python

# one off repo setup
npm install pxt-microbit@5.1.2
pxt target microbit
pxt install
