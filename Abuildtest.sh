#!/bin/bash
set -e
reset
(cd ./build/ && cmake .)
(cd ./build/ && make -B) 
(cd ./build/ && make test)