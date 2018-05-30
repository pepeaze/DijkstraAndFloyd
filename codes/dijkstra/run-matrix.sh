#!/bin/bash
echo NY distance:
time ./a.out -d -NY -m
echo COL distance:
time ./a.out -d -COL -m
echo FLA distance:
time ./a.out -d -FLA -m
echo BAY distance:
time ./a.out -d -BAY -m
#echo NY timeTravel:
#time ./a.out -t -NY -m
#echo COL timeTravel:
#time ./a.out -t -COL -m
#echo FLA timeTravel:
#time ./a.out -t -FLA -m
#echo BAY timeTravel:
#time ./a.out -t -BAY -m
