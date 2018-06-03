#!/bin/bash
echo NY distance heap:
time ./dijkstra -d -NY -h
echo NY distance array:
time ./dijkstra -d -NY -v
echo
echo BAY distance heap:
time ./dijkstra -d -BAY -h
echo BAY distance array:
time ./dijkstra -d -BAY -v
echo
echo COL distance heap:
time ./dijkstra -d -COL -h
echo COL distance array:
time ./dijkstra -d -COL -v
echo
echo FLA distance heap:
time ./dijkstra -d -FLA -h
echo FLA distance array:
time ./dijkstra -d -FLA -v
#echo COL distance:
#time ./dijkstra -d -COL -l
#echo FLA distance:
#time ./dijkstra -d -FLA -l
#echo BAY distance:
#time ./dijkstra -d -BAY -l
#echo NY timeTravel:
#time ./dijkstra -t -NY -l
#echo COL timeTravel:
#time ./dijkstra -t -COL -l
#echo FLA timeTravel:
#time ./dijkstra -t -FLA -l
#echo BAY timeTravel:
#time ./dijkstra -t -BAY -l
