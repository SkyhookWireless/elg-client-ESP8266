#!/bin/sh

# Remove the unsupported header files.
cp elg_client_demo/common/inc/sky_protocol.h elg_client_demo/sky_protocol.h
sed -i -e "s|^#include <endian.h>.*||" elg_client_demo/sky_protocol.h
sed -i -e "s|^#include <byteswap.h>.*||" elg_client_demo/sky_protocol.h

# Comment out "perror" and "fprintf".
cp elg_client_demo/common/src/protocol/sky_protocol.c elg_client_demo/sky_protocol.c
sed -i -e "s|perror|//perror|g" elg_client_demo/sky_protocol.c
sed -i -e "s|fprintf|//fprintf|g" elg_client_demo/sky_protocol.c

