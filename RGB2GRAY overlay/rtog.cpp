#include "def.h"

void rtog() {
  #pragma HLS INTERFACE axis port=vidIN bundle=INPUT_STREAM
  #pragma HLS INTERFACE axis port=vidOUT bundle=OUTPUT_STREAM
  #pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
  
  RGB_IMAGE im1(HEIGHT, WIDTH);
  RGB_IMAGE im2(HEIGHT, WIDTH);
  
  #pragma HLS dataflow
  hls::AXIvideo2Mat(vidIN im1);
  hls::CvtColor<HLS_RGB2GRAY>(im1 im2);
  hls::Mat2AXIvideo(im2, vidOUT);
}
