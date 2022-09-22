#!/bin/bash
echo "Compiling to MIPS..."
cat $2 | ./src/bin/compiler 2> /dev/null 1> $4
