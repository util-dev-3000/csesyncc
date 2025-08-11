#!/bin/bash
./clean.sh && ./build.sh
clear
./build/csesyncc "$@"