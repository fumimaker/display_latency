// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// AXILiteS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - Channel 0 (ap_done)
//        bit 1  - Channel 1 (ap_ready)
//        others - reserved
// 0x10 : Data signal of result_count_V
//        bit 31~0 - result_count_V[31:0] (Read)
// 0x14 : Control signal of result_count_V
//        bit 0  - result_count_V_ap_vld (Read/COR)
//        others - reserved
// 0x18 : Data signal of measure_start_V
//        bit 0  - measure_start_V[0] (Read/Write)
//        others - reserved
// 0x1c : reserved
// 0x20 : Data signal of result_finished_V
//        bit 0  - result_finished_V[0] (Read)
//        others - reserved
// 0x24 : Control signal of result_finished_V
//        bit 0  - result_finished_V_ap_vld (Read/COR)
//        others - reserved
// 0x28 : Data signal of measure_reset_V
//        bit 0  - measure_reset_V[0] (Read/Write)
//        others - reserved
// 0x2c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XMEASURE_CON_AXILITES_ADDR_AP_CTRL                0x00
#define XMEASURE_CON_AXILITES_ADDR_GIE                    0x04
#define XMEASURE_CON_AXILITES_ADDR_IER                    0x08
#define XMEASURE_CON_AXILITES_ADDR_ISR                    0x0c
#define XMEASURE_CON_AXILITES_ADDR_RESULT_COUNT_V_DATA    0x10
#define XMEASURE_CON_AXILITES_BITS_RESULT_COUNT_V_DATA    32
#define XMEASURE_CON_AXILITES_ADDR_RESULT_COUNT_V_CTRL    0x14
#define XMEASURE_CON_AXILITES_ADDR_MEASURE_START_V_DATA   0x18
#define XMEASURE_CON_AXILITES_BITS_MEASURE_START_V_DATA   1
#define XMEASURE_CON_AXILITES_ADDR_RESULT_FINISHED_V_DATA 0x20
#define XMEASURE_CON_AXILITES_BITS_RESULT_FINISHED_V_DATA 1
#define XMEASURE_CON_AXILITES_ADDR_RESULT_FINISHED_V_CTRL 0x24
#define XMEASURE_CON_AXILITES_ADDR_MEASURE_RESET_V_DATA   0x28
#define XMEASURE_CON_AXILITES_BITS_MEASURE_RESET_V_DATA   1

