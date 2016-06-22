#!/usr/bin/python
from mininet.net import Mininet
from mininet.node import Controller, RemoteController
from mininet.cli import CLI
from mininet.log import setLogLevel, info

def myNet():


    #OpenDayLight controller 1
    ODL_CONTROLLER1_IP='192.168.1.10'

    #OpenDaylight controller 2
    ODL_CONTROLLER2_IP='192.168.1.11'
	
	 #OpenDaylight controller 3
    ODL_CONTROLLER3_IP='192.168.1.12'

    net = Mininet(topo=None, build=False)

    # Create nodes
    h1 = net.addHost( 'h1',ip='10.0.0.1')
    h2 = net.addHost( 'h2',ip='10.0.0.2')
    h3 = net.addHost( 'h3',ip='10.0.0.3')
    h4 = net.addHost( 'h4',ip='10.0.0.4')
    h5 = net.addHost( 'h5',ip='10.0.0.5')
    h6 = net.addHost( 'h6',ip='10.0.0.6')
    h7 = net.addHost( 'h7',ip='10.0.0.7')
    h8 = net.addHost( 'h8',ip='10.0.0.8')
    h01 = net.addHost( 'h01',ip='10.0.0.11')
    h02 = net.addHost( 'h02',ip='10.0.0.12')
    h03 = net.addHost( 'h03',ip='10.0.0.13')
    h04 = net.addHost( 'h04',ip='10.0.0.14')
    h05 = net.addHost( 'h05',ip='10.0.0.15')

    # Create switches
    s6 = net.addSwitch( 's6')
    s7 = net.addSwitch( 's7')
    s8 = net.addSwitch( 's8')
    s9 = net.addSwitch( 's9')
    s10 = net.addSwitch( 's10')
    s11 = net.addSwitch( 's11')
    s12 = net.addSwitch( 's12')
    s13 = net.addSwitch( 's13')
    s14 = net.addSwitch( 's14')
    s15 = net.addSwitch( 's15')
    s16 = net.addSwitch( 's16')
    s17 = net.addSwitch( 's17')
    s18 = net.addSwitch( 's18')
    s19 = net.addSwitch( 's19')
    s20 = net.addSwitch( 's20')
    s21 = net.addSwitch( 's21')
    s22 = net.addSwitch( 's22')
    s23 = net.addSwitch( 's23')
    s24 = net.addSwitch( 's24')
    s25 = net.addSwitch( 's25')
    


    print "*** Creating links"
    #external
    net.addLink(s1,h01,)
    net.addLink(s2,h02,)
    net.addLink(s3,h03,)
    net.addLink(s4,h04,)
    net.addLink(s5,h05,)

    net.addLink(s3,s10,)
    net.addLink(s3,s4,)
    net.addLink(s3,s1,)
    
    net.addLink(s1,s2,)
    net.addLink(s2,s5,)
    net.addLink(s4,s5,)

    net.addLink(s5,s17,)
    #internal
    net.addLink(s18,h1,)
    net.addLink(s19,h2,)
    net.addLink(s20,h3,)
    net.addLink(s21,h4,)
    net.addLink(s22,h5,)
    net.addLink(s23,h6,)
    net.addLink(s24,h7,)
    net.addLink(s25,h8,)

    net.addLink(s10, s18,)
    net.addLink(s10, s19,)

    net.addLink(s11, s18,)
    net.addLink(s11, s19,)

    net.addLink(s12, s20,)
    net.addLink(s12, s21,)

    net.addLink(s13, s20,)
    net.addLink(s13, s21,)

    net.addLink(s14, s22,)
    net.addLink(s14, s23,)

    net.addLink(s15, s22,)
    net.addLink(s15, s23,)

    net.addLink(s16, s24,)
    net.addLink(s16, s25,)

    net.addLink(s17, s24,)
    net.addLink(s17, s25,)

    net.addLink(s6, s10,)
    net.addLink(s6, s12,)
    net.addLink(s6, s14,)
    net.addLink(s6, s16,)

    net.addLink(s7, s10,)
    net.addLink(s7, s12,)
    net.addLink(s7, s14,)
    net.addLink(s7, s16,)

    net.addLink(s8, s11,)
    net.addLink(s8, s13,)
    net.addLink(s8, s15,)
    net.addLink(s8, s17,)

    net.addLink(s9, s11,)
    net.addLink(s9, s13,)
    net.addLink(s9, s15,)
    net.addLink(s9, s17,)

    # Add Controllers
    odl_ctrl1 = net.addController( 'c0', controller=RemoteController, ip=ODL_CONTROLLER1_IP, port=6633)

	
    net.build()
    #odl_ctrl.start()
    #fl_ctrl.start()

    # Connect each switch to a different controller
    s6.start([odl_ctrl1])
    s7.start([odl_ctrl1])
    s8.start([odl_ctrl1])
    s9.start([odl_ctrl1])
    s10.start([odl_ctrl1])
    s11.start([odl_ctrl1])
    s12.start([odl_ctrl1])
    s13.start([odl_ctrl1])
    s14.start([odl_ctrl1])
    s15.start([odl_ctrl1])
    s16.start([odl_ctrl1])
    s17.start([odl_ctrl1])
    s18.start([odl_ctrl1])
    s19.start([odl_ctrl1])
    s20.start([odl_ctrl1])
    s21.start([odl_ctrl1])
    s22.start([odl_ctrl1])
    s23.start([odl_ctrl1])
    s24.start([odl_ctrl1])
    s25.start([odl_ctrl1])


    #s6.cmdPrint('ovs-vsctl show')

    CLI( net )
    net.stop()

if __name__ == '__main__':
    setLogLevel( 'info' )
    myNet()
