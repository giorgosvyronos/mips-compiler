#!/bin/bash
set -eo pipefail



echo " Cleaning the temporaries and outputs"
echo "========================================"

rm -f bin/*
rm -rf working

echo "========================================"

mkdir -p working

echo " Force building compiler"
echo "========================================"
make bin/c_compiler

FOLDER=$1



    echo "========================================="
    echo "-----------------------------------------"
    echo "Folder : ${FOLDER}"
    echo "-----------------------------------------"
    echo "========================================="


for i in compiler_tests/${FOLDER}/source_files/*; do
    echo "$i"
    b=$(basename ${i})
    b_short=$(basename ${i} .c)

    mkdir -p working/${FOLDER}/$b_short/

    ASSEMBLY_ID="working/${FOLDER}/$b_short/"
    echo "-----------------------------------------"
    echo "Testing functionality of $b_short"
    echo ""    
    echo "File Name under Test : $b"
    echo "Assembly file to be made : ${b_short}.s"
    echo ""

    echo "Running ${i} on THIS COMPILER ..."
    bin/c_compiler -S $i -o ${ASSEMBLY_ID}${b_short}.s
    echo "Produced ${ASSEMBLY_ID}${b_short}.s"
    
    echo "- - - - - - - - - - - - - - - - - - - - -"

    echo "Running on mips..."

    echo "Running mips-linux-gnu-gcc -mfp32 -o ${ASSEMBLY_ID}${b_short}.o -c ${ASSEMBLY_ID}${b_short}.s ..."
    mips-linux-gnu-gcc -mfp32 -o ${ASSEMBLY_ID}${b_short}.o -c ${ASSEMBLY_ID}${b_short}.s
    echo "Running mips-linux-gnu-gcc -mfp32 -static -o ${ASSEMBLY_ID}${b_short} ${ASSEMBLY_ID}${b_short}.o compiler_tests/${FOLDER}/${b}_driver.c ..."
    mips-linux-gnu-gcc -mfp32 -static -o ${ASSEMBLY_ID}${b_short} ${ASSEMBLY_ID}${b_short}.o compiler_tests/${FOLDER}/drivers/${b_short}_driver.c
    echo "Running qemu-mips ${ASSEMBLY_ID}${b_short} ..."
    qemu-mips ${ASSEMBLY_ID}${b_short}
    echo "Done!"
done