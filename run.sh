#!/bin/bash

# enter path to the code:
export installdir="/local/home/admin-local/Documents/T2K/Micromegas/Calibration/Code"
# enter path to data
export file_path="/local/home/admin-local/Documents/T2K/Micromegas/Calibration/Electronics/data/211126_3"

echo "************ SET UP ************"
echo "The directory has been installed to: " $installdir
echo "ROOT files are stored here: " $file_path
echo "********************************"

cd $installdir
mkdir -p results/{histograms/{ampl/macros,peaks/macros,lines/macros,separation/macros},txt}
mkdir -p bin

cd src
make clean
make || { echo "compilation failed" ; exit 1; }
cd ../

for file in $file_path/*.root; 
do
	./bin/Calibration "$file"
done

./bin/Display