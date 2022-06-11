// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XMEASURE_CON_H
#define XMEASURE_CON_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xmeasure_con_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
#else
typedef struct {
    u16 DeviceId;
    u32 Axilites_BaseAddress;
} XMeasure_con_Config;
#endif

typedef struct {
    u32 Axilites_BaseAddress;
    u32 IsReady;
} XMeasure_con;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XMeasure_con_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XMeasure_con_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XMeasure_con_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XMeasure_con_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XMeasure_con_Initialize(XMeasure_con *InstancePtr, u16 DeviceId);
XMeasure_con_Config* XMeasure_con_LookupConfig(u16 DeviceId);
int XMeasure_con_CfgInitialize(XMeasure_con *InstancePtr, XMeasure_con_Config *ConfigPtr);
#else
int XMeasure_con_Initialize(XMeasure_con *InstancePtr, const char* InstanceName);
int XMeasure_con_Release(XMeasure_con *InstancePtr);
#endif

void XMeasure_con_Start(XMeasure_con *InstancePtr);
u32 XMeasure_con_IsDone(XMeasure_con *InstancePtr);
u32 XMeasure_con_IsIdle(XMeasure_con *InstancePtr);
u32 XMeasure_con_IsReady(XMeasure_con *InstancePtr);
void XMeasure_con_EnableAutoRestart(XMeasure_con *InstancePtr);
void XMeasure_con_DisableAutoRestart(XMeasure_con *InstancePtr);

u32 XMeasure_con_Get_result_count_V(XMeasure_con *InstancePtr);
u32 XMeasure_con_Get_result_count_V_vld(XMeasure_con *InstancePtr);
void XMeasure_con_Set_measure_start_V(XMeasure_con *InstancePtr, u32 Data);
u32 XMeasure_con_Get_measure_start_V(XMeasure_con *InstancePtr);
u32 XMeasure_con_Get_result_finished_V(XMeasure_con *InstancePtr);
u32 XMeasure_con_Get_result_finished_V_vld(XMeasure_con *InstancePtr);
void XMeasure_con_Set_measure_reset_V(XMeasure_con *InstancePtr, u32 Data);
u32 XMeasure_con_Get_measure_reset_V(XMeasure_con *InstancePtr);

void XMeasure_con_InterruptGlobalEnable(XMeasure_con *InstancePtr);
void XMeasure_con_InterruptGlobalDisable(XMeasure_con *InstancePtr);
void XMeasure_con_InterruptEnable(XMeasure_con *InstancePtr, u32 Mask);
void XMeasure_con_InterruptDisable(XMeasure_con *InstancePtr, u32 Mask);
void XMeasure_con_InterruptClear(XMeasure_con *InstancePtr, u32 Mask);
u32 XMeasure_con_InterruptGetEnabled(XMeasure_con *InstancePtr);
u32 XMeasure_con_InterruptGetStatus(XMeasure_con *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
