// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// CTRL_BUS
// 0x000 : Control signals
//         bit 0  - ap_start (Read/Write/COH)
//         bit 1  - ap_done (Read/COR)
//         bit 2  - ap_idle (Read)
//         bit 3  - ap_ready (Read)
//         bit 7  - auto_restart (Read/Write)
//         others - reserved
// 0x004 : Global Interrupt Enable Register
//         bit 0  - Global Interrupt Enable (Read/Write)
//         others - reserved
// 0x008 : IP Interrupt Enable Register (Read/Write)
//         bit 0  - Channel 0 (ap_done)
//         bit 1  - Channel 1 (ap_ready)
//         others - reserved
// 0x00c : IP Interrupt Status Register (Read/TOW)
//         bit 0  - Channel 0 (ap_done)
//         bit 1  - Channel 1 (ap_ready)
//         others - reserved
// 0x010 : Data signal of Input_r
//         bit 31~0 - Input_r[31:0] (Read/Write)
// 0x014 : reserved
// 0x018 : Data signal of Input1
//         bit 31~0 - Input1[31:0] (Read/Write)
// 0x01c : reserved
// 0x020 : Data signal of Input2
//         bit 31~0 - Input2[31:0] (Read/Write)
// 0x024 : reserved
// 0x028 : Data signal of Input3
//         bit 31~0 - Input3[31:0] (Read/Write)
// 0x02c : reserved
// 0x030 : Data signal of Output_r
//         bit 31~0 - Output_r[31:0] (Read/Write)
// 0x034 : reserved
// 0x038 : Data signal of Output1
//         bit 31~0 - Output1[31:0] (Read/Write)
// 0x03c : reserved
// 0x040 : Data signal of Weight
//         bit 31~0 - Weight[31:0] (Read/Write)
// 0x044 : reserved
// 0x048 : Data signal of Beta
//         bit 31~0 - Beta[31:0] (Read/Write)
// 0x04c : reserved
// 0x050 : Data signal of InFM_num
//         bit 31~0 - InFM_num[31:0] (Read/Write)
// 0x054 : reserved
// 0x058 : Data signal of OutFM_num
//         bit 31~0 - OutFM_num[31:0] (Read/Write)
// 0x05c : reserved
// 0x060 : Data signal of Kernel_size
//         bit 31~0 - Kernel_size[31:0] (Read/Write)
// 0x064 : reserved
// 0x068 : Data signal of Kernel_stride
//         bit 31~0 - Kernel_stride[31:0] (Read/Write)
// 0x06c : reserved
// 0x070 : Data signal of Input_w
//         bit 31~0 - Input_w[31:0] (Read/Write)
// 0x074 : reserved
// 0x078 : Data signal of Input_h
//         bit 31~0 - Input_h[31:0] (Read/Write)
// 0x07c : reserved
// 0x080 : Data signal of output_w
//         bit 31~0 - output_w[31:0] (Read/Write)
// 0x084 : reserved
// 0x088 : Data signal of output_h
//         bit 31~0 - output_h[31:0] (Read/Write)
// 0x08c : reserved
// 0x090 : Data signal of Padding
//         bit 31~0 - Padding[31:0] (Read/Write)
// 0x094 : reserved
// 0x098 : Data signal of IsNL
//         bit 0  - IsNL[0] (Read/Write)
//         others - reserved
// 0x09c : reserved
// 0x0a0 : Data signal of IsBN
//         bit 0  - IsBN[0] (Read/Write)
//         others - reserved
// 0x0a4 : reserved
// 0x0a8 : Data signal of TM
//         bit 31~0 - TM[31:0] (Read/Write)
// 0x0ac : reserved
// 0x0b0 : Data signal of TN
//         bit 31~0 - TN[31:0] (Read/Write)
// 0x0b4 : reserved
// 0x0b8 : Data signal of TR
//         bit 31~0 - TR[31:0] (Read/Write)
// 0x0bc : reserved
// 0x0c0 : Data signal of TC
//         bit 31~0 - TC[31:0] (Read/Write)
// 0x0c4 : reserved
// 0x0c8 : Data signal of mLoops
//         bit 31~0 - mLoops[31:0] (Read/Write)
// 0x0cc : reserved
// 0x0d0 : Data signal of nLoops
//         bit 31~0 - nLoops[31:0] (Read/Write)
// 0x0d4 : reserved
// 0x0d8 : Data signal of rLoops
//         bit 31~0 - rLoops[31:0] (Read/Write)
// 0x0dc : reserved
// 0x0e0 : Data signal of cLoops
//         bit 31~0 - cLoops[31:0] (Read/Write)
// 0x0e4 : reserved
// 0x0e8 : Data signal of LayerType
//         bit 31~0 - LayerType[31:0] (Read/Write)
// 0x0ec : reserved
// 0x0f0 : Data signal of InputQ
//         bit 31~0 - InputQ[31:0] (Read/Write)
// 0x0f4 : reserved
// 0x0f8 : Data signal of OutputQ
//         bit 31~0 - OutputQ[31:0] (Read/Write)
// 0x0fc : reserved
// 0x100 : Data signal of WeightQ
//         bit 31~0 - WeightQ[31:0] (Read/Write)
// 0x104 : reserved
// 0x108 : Data signal of BetaQ
//         bit 31~0 - BetaQ[31:0] (Read/Write)
// 0x10c : reserved
// 0x110 : Data signal of trow_loops
//         bit 31~0 - trow_loops[31:0] (Read/Write)
// 0x114 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XYOLO2_FPGA_CTRL_BUS_ADDR_AP_CTRL            0x000
#define XYOLO2_FPGA_CTRL_BUS_ADDR_GIE                0x004
#define XYOLO2_FPGA_CTRL_BUS_ADDR_IER                0x008
#define XYOLO2_FPGA_CTRL_BUS_ADDR_ISR                0x00c
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUT_R_DATA       0x010
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUT_R_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUT1_DATA        0x018
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUT1_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUT2_DATA        0x020
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUT2_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUT3_DATA        0x028
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUT3_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_OUTPUT_R_DATA      0x030
#define XYOLO2_FPGA_CTRL_BUS_BITS_OUTPUT_R_DATA      32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_OUTPUT1_DATA       0x038
#define XYOLO2_FPGA_CTRL_BUS_BITS_OUTPUT1_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_WEIGHT_DATA        0x040
#define XYOLO2_FPGA_CTRL_BUS_BITS_WEIGHT_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_BETA_DATA          0x048
#define XYOLO2_FPGA_CTRL_BUS_BITS_BETA_DATA          32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INFM_NUM_DATA      0x050
#define XYOLO2_FPGA_CTRL_BUS_BITS_INFM_NUM_DATA      32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_OUTFM_NUM_DATA     0x058
#define XYOLO2_FPGA_CTRL_BUS_BITS_OUTFM_NUM_DATA     32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_KERNEL_SIZE_DATA   0x060
#define XYOLO2_FPGA_CTRL_BUS_BITS_KERNEL_SIZE_DATA   32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_KERNEL_STRIDE_DATA 0x068
#define XYOLO2_FPGA_CTRL_BUS_BITS_KERNEL_STRIDE_DATA 32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUT_W_DATA       0x070
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUT_W_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUT_H_DATA       0x078
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUT_H_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_OUTPUT_W_DATA      0x080
#define XYOLO2_FPGA_CTRL_BUS_BITS_OUTPUT_W_DATA      32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_OUTPUT_H_DATA      0x088
#define XYOLO2_FPGA_CTRL_BUS_BITS_OUTPUT_H_DATA      32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_PADDING_DATA       0x090
#define XYOLO2_FPGA_CTRL_BUS_BITS_PADDING_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_ISNL_DATA          0x098
#define XYOLO2_FPGA_CTRL_BUS_BITS_ISNL_DATA          1
#define XYOLO2_FPGA_CTRL_BUS_ADDR_ISBN_DATA          0x0a0
#define XYOLO2_FPGA_CTRL_BUS_BITS_ISBN_DATA          1
#define XYOLO2_FPGA_CTRL_BUS_ADDR_TM_DATA            0x0a8
#define XYOLO2_FPGA_CTRL_BUS_BITS_TM_DATA            32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_TN_DATA            0x0b0
#define XYOLO2_FPGA_CTRL_BUS_BITS_TN_DATA            32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_TR_DATA            0x0b8
#define XYOLO2_FPGA_CTRL_BUS_BITS_TR_DATA            32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_TC_DATA            0x0c0
#define XYOLO2_FPGA_CTRL_BUS_BITS_TC_DATA            32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_MLOOPS_DATA        0x0c8
#define XYOLO2_FPGA_CTRL_BUS_BITS_MLOOPS_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_NLOOPS_DATA        0x0d0
#define XYOLO2_FPGA_CTRL_BUS_BITS_NLOOPS_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_RLOOPS_DATA        0x0d8
#define XYOLO2_FPGA_CTRL_BUS_BITS_RLOOPS_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_CLOOPS_DATA        0x0e0
#define XYOLO2_FPGA_CTRL_BUS_BITS_CLOOPS_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_LAYERTYPE_DATA     0x0e8
#define XYOLO2_FPGA_CTRL_BUS_BITS_LAYERTYPE_DATA     32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_INPUTQ_DATA        0x0f0
#define XYOLO2_FPGA_CTRL_BUS_BITS_INPUTQ_DATA        32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_OUTPUTQ_DATA       0x0f8
#define XYOLO2_FPGA_CTRL_BUS_BITS_OUTPUTQ_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_WEIGHTQ_DATA       0x100
#define XYOLO2_FPGA_CTRL_BUS_BITS_WEIGHTQ_DATA       32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_BETAQ_DATA         0x108
#define XYOLO2_FPGA_CTRL_BUS_BITS_BETAQ_DATA         32
#define XYOLO2_FPGA_CTRL_BUS_ADDR_TROW_LOOPS_DATA    0x110
#define XYOLO2_FPGA_CTRL_BUS_BITS_TROW_LOOPS_DATA    32

