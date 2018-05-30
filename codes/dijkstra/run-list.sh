#!/bin/bash
echo NY distance:
time ./a.out -d -NY -l
echo COL distance:
time ./a.out -d -COL -l
echo FLA distance:
time ./a.out -d -FLA -l
echo BAY distance:
time ./a.out -d -BAY -l
echo NY timeTravel:
time ./a.out -t -NY -l
echo COL timeTravel:
time ./a.out -t -COL -l
echo FLA timeTravel:
time ./a.out -t -FLA -l
echo BAY timeTravel:
time ./a.out -t -BAY -l
