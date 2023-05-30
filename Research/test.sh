#!/bin/bash

repeat_count=90
output_file="output.txt"

touch $output_file

for ((i=1; i<=$repeat_count; i++))
do
    ./rbtree >> $output_file
done