dev=tap0
# $LOGNAME turned into root
user=connolly

ip tuntap add dev $dev mode tap user $user
ip address flush dev $dev
ip address add 10.0.2.1/24 brd 10.0.2.255 dev $dev
ip link set dev $dev addr 02:00:00:ca:fe:01
ip link set dev $dev up