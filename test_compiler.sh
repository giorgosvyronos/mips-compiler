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


for i in basic_tests/${FOLDER}/*; do
    b=$(basename ${i})
    b_short=$(basename ${i} .c)

    mkdir -p basic_tests/assembly/$b_short/

    ASSEMBLY_ID="basic_tests/assembly/$b_short/"
    echo "-----------------------------------------"
    echo "Testing functionality of $b_short"
    echo ""    
    echo "File Name under Test : $b"
    echo "Assembly file to be made : ${b_short}.s"
    echo ""

    echo "Running ${i} on THIS COMPILER"
    bin/c_compiler -S $i -o ${ASSEMBLY_ID}${b_short}.s
    echo "Produced ${ASSEMBLY_ID}${b_short}.s"


#   FILE=$i/$b.txt
#   if [ -f "$FILE" ]
#     then
#       REF_RESULT=$(head -n 1 $FILE);
#     else
#       mips-linux-gnu-gcc -static $i/$b.c -o $i/exe
#       mips-linux-gnu-gcc -static -c -S $i/$b.c $i/$b.s
#       mv $b.s $i/$b.s
#       qemu-mips $i/exe
#       REF_RESULT=$?;
#       echo "${REF_RESULT}" > $i/$b.txt
#   fi


#   echo "Running $b on a MY COMPILER"
#   cat $i/$b.c | ./bin/c_compiler $i/$b.c > working/$b/$b.s

#   echo "Running $b Assembly into executable"
#   mips-linux-gnu-gcc -static working/$b/$b.s -o working/$b/$b

#   echo "Running $b MY EXECUTABLE"
#   qemu-mips working/$b/$b

#   MY_RESULT=$?;

#   echo "${MY_RESULT}" > working/$b/$b.txt

#   OK=0;

#   if [[ "${MY_RESULT}" -ne "${REF_RESULT}" ]]; then
#       echo "  got result : ${MY_RESULT}"
#       echo "  ref result : ${REF_RESULT}"
#       echo "  FAIL!";
#       printf "| %20s | %5s | %5s | \n" ${b} ${MY_RESULT} ${REF_RESULT}  >> working/log.txt
#       OK=1;
#   fi


#   if [[ "$OK" -eq "0" ]]; then
#       PASSED=$(( ${PASSED}+1 ));
#   fi

#   CHECKED=$(( ${CHECKED}+1 ));

#   NO=$(( ${NO}+1 ));
#   echo "========================================="
#   echo ""

done