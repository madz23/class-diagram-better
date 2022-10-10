#include <iostream>
#include "CImg.h"

using namespace cimg_library;
int sudoMain() {

	unsigned int w = 300;
	unsigned int h = 400;

	CImg<unsigned char> bg(w,h,2,3,255);

	const unsigned char bluegreen[] = { 0,170,255 };
	const unsigned char grey[] = { 220,220,220 };
	const unsigned char black[] = { 0,0,0};
	const unsigned char white[] = { 255,255,255 };


	bg.draw_circle(w / 2, h / 2, 100,bluegreen);
	bg.draw_arrow(0, 0, w-50, h-50, black);
	bg.draw_rectangle(120, 160, 180, 240, grey, 1);
	bg.draw_text(120,160,"Yeet",black,grey,1,15);
	
	CImgDisplay dsp(w,h,"Hello",0);
	dsp.display(bg);
	bg.save("test.bmp");
	
	std::getchar();
	return 0;
}