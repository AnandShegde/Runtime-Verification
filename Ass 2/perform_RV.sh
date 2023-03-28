if [ ! -d bin/ ]; then mkdir bin/; fi
./construct_monitor.sh $1
g++ src/monitor.cpp src/mtree.cpp src/consts.cpp -o bin/monitor.out
./bin/monitor.out $2 $3