#!/bin/bash
set -e
reset
(cd ./build/ && cmake .)
(cd ./build/ && make)
# (cd bin && ./Vidya)
(cd ./build/ && make test)