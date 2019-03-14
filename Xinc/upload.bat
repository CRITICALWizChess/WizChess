@echo off 
cd C:\Users\thecr\OneDrive\Documents\sxc-c-example\build 
rem "replace this directory with your directory and save in the minGW folder"
cmake -G "MinGW Makefiles" ..
make
sxc-xdt -t -d \\.\COM3 -i minimal.hex
rem "change the com port to your com port"