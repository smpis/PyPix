  #ifndef _CORE_H_
  #define _CORE_H_
  #include "hls_video.h"
  
  #define WIDTH 1280
  #define HEIGHT 720
  #define IMAGE_IN "IN.jpg"
  #define IMAGE_OUT "OUT.jpg"
  
  typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM;
  typedef hls::Scalar<3,unsigned char> RGB_PIXEL;
  void rtog(AXI_STREAM& vidIN, AXI_STREAM& vidOUT);
  
  #endif
