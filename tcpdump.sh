#!/bin/bash
tcpdump -i eth1 "port $1" > ./gb/gb$1.txt 2> ./result/$1.txt &
echo $1
declare -i pid1=$!
tcpdump -i eth1 "port $2" > ./gb/gb$2.txt 2> ./result/$2.txt &
declare -i pid2=$!
tcpdump -i eth1 "port $3" > ./gb/gb$3.txt 2> ./result/$3.txt &
declare -i pid3=$!
tcpdump -i eth1 "port $4" > ./gb/gb$4.txt 2> ./result/$4.txt &
declare -i pid4=$!
tcpdump -i eth1 "port $5" > ./gb/gb$5.txt 2> ./result/$5.txt &
declare -i pid5=$!
tcpdump -i eth1 "port $6" > ./gb/gb$6.txt 2> ./result/$6.txt &
declare -i pid6=$!
tcpdump -i eth1 "port $7" > ./gb/gb$7.txt 2> ./result/$7.txt &
declare -i pid7=$!
tcpdump -i eth1 "port $8" > ./gb/gb$8.txt 2> ./result/$8.txt &
declare -i pid8=$!
tcpdump -i eth1 "port $9" > ./gb/gb$9.txt 2> ./result/$9.txt &
declare -i pid9=$!
tcpdump -i eth1 "port ${10}" > ./gb/gb${10}.txt 2> ./result/${10}.txt &
declare -i pid10=$!
tcpdump -i eth1 "port ${11}" > ./gb/gb${11}.txt 2> ./result/${11}.txt &
declare -i pid11=$!
tcpdump -i eth1 "port ${12}" > ./gb/gb${12}.txt 2> ./result/${12}.txt &
declare -i pid12=$!
tcpdump -i eth1 "port ${13}" > ./gb/gb${13}.txt 2> ./result/${13}.txt &
declare -i pid13=$!
tcpdump -i eth1 "port ${14}" > ./gb/gb${14}.txt 2> ./result/${14}.txt &
declare -i pid14=$!
tcpdump -i eth1 "port ${15}" > ./gb/gb${15}.txt 2> ./result/${15}.txt &
declare -i pid15=$!
tcpdump -i eth1 "port ${16}" > ./gb/gb${16}.txt 2> ./result/${16}.txt &
declare -i pid16=$!
tcpdump -i eth1 "port ${17}" > ./gb/gb${17}.txt 2> ./result/${17}.txt &
declare -i pid17=$!
tcpdump -i eth1 "port ${18}" > ./gb/gb${18}.txt 2> ./result/${18}.txt &
declare -i pid18=$!
tcpdump -i eth1 "port ${19}" > ./gb/gb${19}.txt 2> ./result/${19}.txt &
declare -i pid19=$!
tcpdump -i eth1 "port ${20}" > ./gb/gb${20}.txt 2> ./result/${20}.txt &
declare -i pid20=$!

sleep 1

kill $pid1
kill $pid2
kill $pid3
kill $pid4
kill $pid5
kill $pid6
kill $pid7
kill $pid8
kill $pid9
kill $pid10
kill $pid11
kill $pid12
kill $pid13
kill $pid14
kill $pid15
kill $pid16
kill $pid17
kill $pid18
kill $pid19
kill $pid20
