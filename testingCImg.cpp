#include <iostream>
#include "CImg.h"

using namespace cimg_library;
int sudoMain() {

	unsigned int w = 300;
	unsigned int h = 400;

	CImg<unsigned char> bg(w,h,1,3,255);

	const unsigned char bluegreen[] = { 0,170,255 };

	bg.draw_circle(w / 2, h / 2, 100,bluegreen);
	bg.display();

	

	return 0;
}