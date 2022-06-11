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
);

int main(){
	ap_uint<1> start_out, reset_out;
	ap_uint<32> counter_in=0;
	ap_uint<1> countdone_in=0;
	ap_uint<32> count_result=0;
	ap_uint<3> rgb_led=0;
	ap_uint<1> measure_start=0;
	ap_uint<1> measure_finished=0;
	ap_uint<1> measure_reset=0;
	ap_uint<32> kekka=0;

	measure_reset = 1;
	measure_con(&counter_in, &countdone_in, &start_out, &reset_out, &count_result, &rgb_led, measure_start, &measure_finished, measure_reset);
	printf("reset: m_start=%u m_finished=%u m_reset=%u result=%u\n", (unsigned int)measure_start, (unsigned int)measure_finished, (unsigned int)measure_reset, (unsigned int)count_result);
	for(int i=0; i<5; i++){
		measure_start = 1;
		for(int k=0; k<10; k++){
			if(k==8){
				countdone_in = 1;
			} else {
				countdone_in = 0;
			}
			measure_con(&counter_in, &countdone_in, &start_out, &reset_out, &count_result, &rgb_led, measure_start, &measure_finished, measure_reset);
			if(measure_finished==1){
				kekka = count_result;
				printf("kekka=%u\n",(unsigned int)kekka);
				measure_reset = 1;
				printf("m_start=%u m_finished=%u m_reset=%u result=%u led=%u\n", (unsigned int)measure_start, (unsigned int)measure_finished, (unsigned int)measure_reset, (unsigned int)count_result, (unsigned int)rgb_led);
			} else {
				measure_reset = 0;
				counter_in++;
				printf("m_start=%u m_finished=%u m_reset=%u result=%u led=%u\n", (unsigned int)measure_start, (unsigned int)measure_finished, (unsigned int)measure_reset, (unsigned int)count_result, (unsigned int)rgb_led);
			}
		}
	}

	return 0;
}
