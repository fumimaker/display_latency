// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.2 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xmeasure_con.h"

extern XMeasure_con_Config XMeasure_con_ConfigTable[];

XMeasure_con_Config *XMeasure_con_LookupConfig(u16 DeviceId) {
	XMeasure_con_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XMEASURE_CON_NUM_INSTANCES; Index++) {
		if (XMeasure_con_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XMeasure_con_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XMeasure_con_Initialize(XMeasure_con *InstancePtr, u16 DeviceId) {
	XMeasure_con_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XMeasure_con_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XMeasure_con_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

