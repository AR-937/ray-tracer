#!/bin/bash

set -e

OUTPUT_FILE="ray_tracer.ppm"

mkdir -p build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

rm -f "$OUTPUT_FILE"

cmake --build build

time ./build/ray_tracer >"$OUTPUT_FILE"

feh "$OUTPUT_FILE"
