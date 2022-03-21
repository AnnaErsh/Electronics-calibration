#!/bin/bash

make

for file in root_files/*.root; 
do
	./test "$file"
done