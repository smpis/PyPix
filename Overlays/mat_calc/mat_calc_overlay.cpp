void mat_calc(int x, int y, int z, int mat_0_0, int mat_0_1, int mat_0_2, int mat_1_0, int mat_1_1, int mat_1_2, int mat_2_0, int mat_2_1, int mat_2_2, int *out_x, int *out_y, int *out_z) {
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE s_axilite port=x
#pragma HLS INTERFACE s_axilite port=y
#pragma HLS INTERFACE s_axilite port=z
#pragma HLS INTERFACE s_axilite port=mat_0_0
#pragma HLS INTERFACE s_axilite port=mat_0_1
#pragma HLS INTERFACE s_axilite port=mat_0_2
#pragma HLS INTERFACE s_axilite port=mat_1_0
#pragma HLS INTERFACE s_axilite port=mat_1_1
#pragma HLS INTERFACE s_axilite port=mat_1_2
#pragma HLS INTERFACE s_axilite port=mat_2_0
#pragma HLS INTERFACE s_axilite port=mat_2_1
#pragma HLS INTERFACE s_axilite port=mat_2_2
#pragma HLS INTERFACE s_axilite port=out_x
#pragma HLS INTERFACE s_axilite port=out_y
#pragma HLS INTERFACE s_axilite port=out_z

#pragma HLS dataflow
#pragma HLS latency min=0 max=2
*out_x=x * mat_0_0 + y * mat_0_1 + z * mat_0_2;
#pragma HLS latency min=0 max=2
#pragma accel task
*out_y=x * mat_1_0 + y * mat_1_1 + z * mat_1_2;
#pragma HLS latency min=0 max=2
#pragma accel task
*out_z=x * mat_2_0 + y * mat_2_1 + z * mat_2_2;
}
