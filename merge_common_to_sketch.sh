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

# 2. Comment out "perror", "fprintf", "printf" and "puts".
cp elg_client_demo/common/src/protocol/sky_protocol.c elg_client_demo/sky_protocol.c
sed -i -e "s|perror|//perror|g" elg_client_demo/sky_protocol.c
sed -i -e "s|fprintf|//fprintf|g" elg_client_demo/sky_protocol.c
sed -i -e "s| printf| //printf|g" elg_client_demo/sky_protocol.c
sed -i -e "s|puts|//puts|g" elg_client_demo/sky_protocol.c

# 3. Copy crypto files and comment out "perror".
cp elg_client_demo/common/external/HMAC/hmac256.? elg_client_demo/
cp elg_client_demo/common/external/tiny-AES128-C/aes.? elg_client_demo/
cp elg_client_demo/common/inc/mauth.h elg_client_demo/
cp elg_client_demo/common/inc/sky_crypt.h elg_client_demo/
cp elg_client_demo/common/src/security/mauth.c elg_client_demo/
cp elg_client_demo/common/src/security/sky_crypt.c elg_client_demo/
sed -i -e "s|perror|//perror|g" elg_client_demo/sky_crypt.c

