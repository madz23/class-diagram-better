#pragma once
#include <iostream>
#include "CImg.h"
#include "Graph.hh"
#include "Node.hh"
#include "Edge.hh"
#include "ClassInfo.hh"
using namespace cimg_library;
class PrintOnPaper
{
	const int PIX_PER_NODE_HEIGHT = 300;
	const int PIX_PER_NODE_WIDTH = 200;
	const int SPACING = 50;
	

	int nodeHeight;
	int nodeWidth;
	int pixHeight;
	int pixWidth;
	//CImg<unsigned char> bg;

public:
	PrintOnPaper(int height, int width) {
		const unsigned char bluegreen[] = { 0,170,255 };
		const unsigned char grey[] = { 220,220,220 };
		const unsigned char black[] = { 0,0,0 };
		const unsigned char white[] = { 255,255,255 };
		const unsigned char red[] = { 255,0,0 };
		const unsigned char green[] = { 0,255,0 };
		const unsigned char blue[] = { 0,0,255 };
		//std::vector<const unsigned char*> arr = {bluegreen,grey,black,white,red,green,blue};
		nodeHeight = height;
		nodeWidth = width;
		pixHeight = nodeHeight * PIX_PER_NODE_HEIGHT;
		pixWidth = nodeWidth * PIX_PER_NODE_WIDTH;
		CImg<unsigned char> bg(pixWidth, pixHeight,2,3,255);
		
		for (int x = 0; x < nodeWidth; x++) {
			for (int y = 0; y < nodeHeight; y++) {
				drawRectByNode(x, y, &bg);

			}
		}
		bg.draw_text(SPACING, SPACING, "testing",black, grey,1,16);
		bg.draw_text(SPACING, SPACING+16, "testing", black, grey, 1, 16);
		drawArrowFrom(0,0,1,1, &bg);
		drawArrowFrom(1,1,0,0, &bg);
		drawArrowFrom(1,0,0,1, &bg);
		drawArrowFrom(0,1, 1,0, &bg);
		drawArrowFrom(2, 0, 2,1, &bg);
		drawArrowFrom(2, 1, 2, 0, &bg);
		drawArrowFrom(3, 0, 2, 0, &bg);
		drawArrowFrom(2, 0, 3, 0, &bg);
		

		CImgDisplay dsp(pixWidth, pixHeight, "uwu",0);
		dsp.display(bg);
		std::getchar();

		bg.save_bmp("secondaryTest.bmp");
	}


	static int nodeBs(Graph<ClassInfo> g) {
		std::cout << g.getEdges()[0].getStartNode();
		std::cout<<g.getEdges()[0].getEndNode()<<std::endl;
		std::cout << g.getNodes()[0].getData().getBases()[0]<<std::endl;
		std::cout << g.getNodes()[0].getData().getFields()[0].getName()<<std::endl;
		std::cout << g.getNodes()[0].getData().getMethods()[0].getName()<<std::endl;
		std::cout << g.getNodes()[0].getData().getName();
		return 0;
	}
	
	// returns coords of top left corner of square x. 
	std::pair<int,int> getCornerOfPosition(int x) {
		int trueX = (x % nodeWidth) * PIX_PER_NODE_WIDTH;
		int trueY = (x / nodeWidth) * PIX_PER_NODE_HEIGHT;
		std::cout << std::endl<<"x: "<<trueX;
		std::cout << std::endl<<"y: " << trueY<<std::endl;
		return std::pair<int,int> {trueX,trueY};
	}


	
private:
	void drawRectByNode(int x, int y, CImg<unsigned char> * c) {
		const unsigned char grey[] = { 220,220,220 };
		int cornerPixX = x * PIX_PER_NODE_WIDTH;
		int cornerPixY = y * PIX_PER_NODE_HEIGHT;
		c->draw_rectangle(cornerPixX + SPACING, cornerPixY + SPACING, cornerPixX + PIX_PER_NODE_WIDTH - SPACING, cornerPixY + PIX_PER_NODE_HEIGHT - SPACING, grey, 1);
		


	}

	// draw arrow from box at xy to other box at xy(full size cords not pixles)
	void drawArrowFrom(int fromX, int fromY, int toX, int toY,CImg<unsigned char> * c) {
		const unsigned char black[] = { 0,0,0 };
		int yDif = fromY - toY;
		int xDif = toX - fromX;
		int yAdd;
		int xAdd;
		bool minusX = false;
		bool minusY = false;
		if (yDif < 0) {
			yAdd = SPACING;
		}
		else if(yDif > 0) {
			yAdd = PIX_PER_NODE_HEIGHT - SPACING;
		}
		else if (yDif == 0) {
			yAdd = .5 * PIX_PER_NODE_HEIGHT;
		}
		if (xDif < 0) {
			xAdd = PIX_PER_NODE_WIDTH - SPACING;
		}
		else if (xDif > 0) {
			xAdd = SPACING;
		}
		else if (xDif == 0) {
			xAdd = .5 * PIX_PER_NODE_WIDTH;
		}
		c->draw_arrow((fromX * PIX_PER_NODE_WIDTH) + PIX_PER_NODE_WIDTH/2, fromY * PIX_PER_NODE_HEIGHT + PIX_PER_NODE_HEIGHT / 2, (toX * PIX_PER_NODE_WIDTH) + xAdd, (toY * PIX_PER_NODE_HEIGHT) + yAdd, black);

	}

	int nodesToPixles() {
		pixHeight = nodeHeight * PIX_PER_NODE_HEIGHT;
		pixWidth = nodeWidth * PIX_PER_NODE_WIDTH;
	}

	std::vector < std::string> *getText() {
		std::vector<std::string> ret;
		ret.push_back("testdsf");
		ret.push_back("sdfjsd;lf");
		ret.push_back("uwudsfs");
	}
	
	void printTextOnSquare(int x, int y, std::vector<std::string> textVect) {
		int pixX = x * PIX_PER_NODE_WIDTH;
		int pixY = x * PIX_PER_NODE_HEIGHT;
		int startPixX = pixX + SPACING;
		int startPixY = pixY + SPACING;
		int textSpacing = 15;
		
	}
};

