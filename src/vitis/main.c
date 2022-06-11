/******************************************************************************
 *
 * Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * Use of the Software is limited solely to applications:
 * (a) running on a Xilinx device, or
 * (b) that interact with a Xilinx device through a bus or interconnect.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the name of the Xilinx shall not be used
 * in advertising or otherwise to promote the sale, use or other dealings in
 * this Software without prior written authorization from Xilinx.
 *
 ******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>

#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xmeasure_con.h"
XMeasure_con mcon_inst;

#define CLKPERMSEC (1/(148.5*1000.0))

int main() {
    int Status;
    init_platform();

    print("Hello World\n\rinput something to start.\n\r");
    char test;
    scanf("%s",&test);

    Status = XMeasure_con_Initialize(&mcon_inst, XPAR_MEASURE_CON_0_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        xil_printf("mcon Initialization Failed\r\n");
        return XST_FAILURE;
    }
    print("init\n\r");
    XMeasure_con_EnableAutoRestart(&mcon_inst);
    XMeasure_con_Start(&mcon_inst);
    XMeasure_con_Set_measure_reset_V(&mcon_inst,1);
    usleep(1000*100);
    XMeasure_con_Set_measure_reset_V(&mcon_inst,0);

    while(1){
    	//print("started!\n\r");
    	XMeasure_con_Set_measure_start_V(&mcon_inst, 1);
		while ( ( XMeasure_con_Get_result_finished_V_vld(&mcon_inst) && XMeasure_con_Get_result_finished_V(&mcon_inst)) != 1 ); //XMeasure_con_Get_measure_finished_V_vld(&mcon_inst)
		XMeasure_con_Set_measure_start_V(&mcon_inst, 0);
		//print("finished\n\r");
		while(XMeasure_con_Get_result_count_V_vld(&mcon_inst)==0);
		unsigned int result = XMeasure_con_Get_result_count_V(&mcon_inst);

		printf("%.3f\n",(float)CLKPERMSEC*result);

		XMeasure_con_Set_measure_reset_V(&mcon_inst,1);
		usleep(1000*100);
		XMeasure_con_Set_measure_reset_V(&mcon_inst,0);
    }



    cleanup_platform();
    return 0;
}
