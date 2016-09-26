#!/bin/sh


# Background:
# As Arduino environment does not have printf family built-in, we need to manual change
# the code. Likewise, there are several header files are not supported by Arduino, so that
# we need to remove the unsupported header files and use skyhook home-grown utilities instead.
# So, this script is created to do manual changes.
# Reference - http://playground.arduino.cc/Main/Printf

# Usage:
# Before compilation, run this script as below:
# % merge_common_to_sketch.sh
# Then, you can do compilation correctly.

# Tasks:

# 1. Remove the unsupported header files.
cp elg_client_demo/common/inc/sky_protocol.h elg_client_demo/sky_protocol.h
sed -i -e "s|^#include <endian.h>.*||" elg_client_demo/sky_protocol.h
sed -i -e "s|^#include <byteswap.h>.*||" elg_client_demo/sky_protocol.h

# 2. Comment out "perror" and "fprintf".
cp elg_client_demo/common/src/protocol/sky_protocol.c elg_client_demo/sky_protocol.c
sed -i -e "s|perror|//perror|g" elg_client_demo/sky_protocol.c
sed -i -e "s|fprintf|//fprintf|g" elg_client_demo/sky_protocol.c

