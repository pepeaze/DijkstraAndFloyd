#!/bin/bash
echo NY distance:
./dijkstra -d -NY -h
echo
echo NY time:
./dijkstra -t -NY -h
echo
echo
echo BAY distance:
./dijkstra -d -BAY -h
echo
echo BAY time:
./dijkstra -t -BAY -h
echo
echo
echo COL distance:
./dijkstra -d -COL -h
echo
echo COL time:
./dijkstra -t -COL -h
echo
echo
echo FLA distance:
./dijkstra -d -FLA -h
echo
echo FLA time:
./dijkstra -t -FLA -h
echo
echo
#echo BAY distance heap:
#time ./dijkstra -d -BAY -h
#echo BAY distance array:
#time ./dijkstra -d -BAY -v
#echo
#echo COL distance heap:
#time ./dijkstra -d -COL -h
#echo COL distance array:
#time ./dijkstra -d -COL -v
#echo
#echo FLA distance heap:
#time ./dijkstra -d -FLA -h
#echo FLA distance array:
#time ./dijkstra -d -FLA -v
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
