############################
# On-board LEDS            #
############################
set_property PACKAGE_PIN M14 [get_ports outLeds[0]]
set_property IOSTANDARD LVCMOS33 [get_ports outLeds[0]]
set_property PACKAGE_PIN M15 [get_ports outLeds[1]]
set_property IOSTANDARD LVCMOS33 [get_ports outLeds[1]]
set_property PACKAGE_PIN G14 [get_ports outLeds[2]]
set_property IOSTANDARD LVCMOS33 [get_ports outLeds[2]]
set_property PACKAGE_PIN D18 [get_ports outLeds[3]]
set_property IOSTANDARD LVCMOS33 [get_ports outLeds[3]]

############################
# On-board SWS             #
############################
set_property PACKAGE_PIN G15 [get_ports inSwitch[0]]
set_property IOSTANDARD LVCMOS33 [get_ports inSwitch[0]]
set_property PACKAGE_PIN P15 [get_ports inSwitch[1]]
set_property IOSTANDARD LVCMOS33 [get_ports inSwitch[1]]
set_property PACKAGE_PIN W13 [get_ports inSwitch[2]]
set_property IOSTANDARD LVCMOS33 [get_ports inSwitch[2]]
set_property PACKAGE_PIN T16 [get_ports inSwitch[3]]
set_property IOSTANDARD LVCMOS33 [get_ports inSwitch[3]]

############################
# On-board BTNS             #
############################
#set_property PACKAGE_PIN R18 [get_ports inBtns[0]]
#set_property IOSTANDARD LVCMOS33 [get_ports inBtns[0]]
#set_property PACKAGE_PIN P16 [get_ports inBtns[1]]
#set_property IOSTANDARD LVCMOS33 [get_ports inBtns[1]]
#set_property PACKAGE_PIN V16 [get_ports inBtns[2]]
#set_property IOSTANDARD LVCMOS33 [get_ports inBtns[2]]
#set_property PACKAGE_PIN Y16 [get_ports inBtns[3]]
#set_property IOSTANDARD LVCMOS33 [get_ports inBtns[3]]