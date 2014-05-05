#! /bin/bash

make clean
echo
make
echo "Running tests..."
echo

main="eavl.out"
test="test"
dir="tests/"
for i in `seq 1 10`;
do
    echo
    echo $test $i:
    ./$main $dir$test$i
    
done

echo
echo "Tests done "

echo
