#include "hls_stream.h"
#include "ap_int.h"
#include <ap_axi_sdata.h>

void measure_con(
		ap_uint<32> *counter_in,
		ap_uint<1> *countdone_in,
		ap_uint<1> *start_out,
		ap_uint<1> *reset_out,
		ap_uint<32> *result_count, // ps<--pl
		ap_uint<3> *rgb_led,
		ap_uint<1> measure_start, // ps-->pl
		ap_uint<1> *result_finished,// ps<--pl
		ap_uint<1> measure_reset // ps-->pl
) {
#pragma HLS INTERFACE s_axilite port=result_finished
#pragma HLS INTERFACE s_axilite port=result_count

#pragma HLS INTERFACE ap_none port=countdone_in
#pragma HLS INTERFACE ap_none port=counter_in
#pragma HLS INTERFACE s_axilite port=measure_reset
#pragma HLS INTERFACE s_axilite port=measure_start
#pragma HLS INTERFACE ap_none port=rgb_led
#pragma HLS INTERFACE ap_none port=reset_out
#pragma HLS INTERFACE ap_none port=start_out
#pragma HLS INTERFACE s_axilite port=return
	*result_count = *counter_in;
	if(measure_reset==1){
		*start_out = 0;
		*reset_out = 1;
		*result_finished = 0;
		*rgb_led = 0;
	} else {
		if(measure_start==1){
			*reset_out = 0;
			*start_out = 1;
			*rgb_led = 1;
			if(*countdone_in==1){
				*result_finished = 1; //hold until reset from ps
				*rgb_led = 7;
			} else {
				*rgb_led = 2;
				*result_finished = 0;
			}
		} else {
			*reset_out = 0;
			*start_out = 0;
			*rgb_led = 0;
			*result_finished = 0;
		}
	}
}
