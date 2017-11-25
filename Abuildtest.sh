#!/bin/bash
set -e
reset
(cd ./build/ && cmake .)
(cd ./build/ && make) 
(cd ./build/ && make test)