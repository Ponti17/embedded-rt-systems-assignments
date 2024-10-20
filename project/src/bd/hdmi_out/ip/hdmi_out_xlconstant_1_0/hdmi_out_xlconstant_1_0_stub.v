// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.2 (win64) Build 1909853 Thu Jun 15 18:39:09 MDT 2017
// Date        : Sat Oct 19 11:46:44 2024
// Host        : andreas-xps15 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               C:/home/university/7-semester/embedded-rt-systems-assignments/project/src/bd/hdmi_out/ip/hdmi_out_xlconstant_1_0/hdmi_out_xlconstant_1_0_stub.v
// Design      : hdmi_out_xlconstant_1_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7z010clg400-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "xlconstant_v1_1_3_xlconstant,Vivado 2017.2" *)
module hdmi_out_xlconstant_1_0(dout)
/* synthesis syn_black_box black_box_pad_pin="dout[0:0]" */;
  output [0:0]dout;
endmodule
