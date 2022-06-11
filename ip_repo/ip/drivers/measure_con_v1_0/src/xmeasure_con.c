// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xmeasure_con.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XMeasure_con_CfgInitialize(XMeasure_con *InstancePtr, XMeasure_con_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Axilites_BaseAddress = ConfigPtr->Axilites_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XMeasure_con_Start(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL) & 0x80;
    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL, Data | 0x01);
}

u32 XMeasure_con_IsDone(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XMeasure_con_IsIdle(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XMeasure_con_IsReady(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XMeasure_con_EnableAutoRestart(XMeasure_con *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL, 0x80);
}

void XMeasure_con_DisableAutoRestart(XMeasure_con *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_AP_CTRL, 0);
}

u32 XMeasure_con_Get_result_count_V(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_RESULT_COUNT_V_DATA);
    return Data;
}

u32 XMeasure_con_Get_result_count_V_vld(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_RESULT_COUNT_V_CTRL);
    return Data & 0x1;
}

void XMeasure_con_Set_measure_start_V(XMeasure_con *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_MEASURE_START_V_DATA, Data);
}

u32 XMeasure_con_Get_measure_start_V(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_MEASURE_START_V_DATA);
    return Data;
}

u32 XMeasure_con_Get_result_finished_V(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_RESULT_FINISHED_V_DATA);
    return Data;
}

u32 XMeasure_con_Get_result_finished_V_vld(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_RESULT_FINISHED_V_CTRL);
    return Data & 0x1;
}

void XMeasure_con_Set_measure_reset_V(XMeasure_con *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_MEASURE_RESET_V_DATA, Data);
}

u32 XMeasure_con_Get_measure_reset_V(XMeasure_con *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_MEASURE_RESET_V_DATA);
    return Data;
}

void XMeasure_con_InterruptGlobalEnable(XMeasure_con *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_GIE, 1);
}

void XMeasure_con_InterruptGlobalDisable(XMeasure_con *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_GIE, 0);
}

void XMeasure_con_InterruptEnable(XMeasure_con *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_IER);
    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_IER, Register | Mask);
}

void XMeasure_con_InterruptDisable(XMeasure_con *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_IER);
    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_IER, Register & (~Mask));
}

void XMeasure_con_InterruptClear(XMeasure_con *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XMeasure_con_WriteReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_ISR, Mask);
}

u32 XMeasure_con_InterruptGetEnabled(XMeasure_con *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_IER);
}

u32 XMeasure_con_InterruptGetStatus(XMeasure_con *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XMeasure_con_ReadReg(InstancePtr->Axilites_BaseAddress, XMEASURE_CON_AXILITES_ADDR_ISR);
}

