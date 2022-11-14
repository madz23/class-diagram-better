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
	//const int PIX_PER_NODE_HEIGHT = 300;
	//const int PIX_PER_NODE_WIDTH = 200;
	//const int SPACING = 50;
	const int PIX_PER_NODE_HEIGHT = 1000;
	const int PIX_PER_NODE_WIDTH = 700;
	const int SPACING = 200;

	//height and width in nodes
	int nodeHeight;
	int nodeWidth;
	//overall size of the screen in pixles
	int pixHeight;
	int pixWidth;
	//CImg<unsigned char> bg;
	//the positioning will be in pixles but I have to convert that so I'm dividing by these values to get simple grid indexing
	int scrollX;
	int scrollY;

public:

	PrintOnPaper(Graph<ClassInfo> graph, float scrollX, float scrollY) {
		const unsigned char bluegreen[] = { 0,170,255 };
		const unsigned char grey[] = { 220,220,220 };
		const unsigned char black[] = { 0,0,0 };
		const unsigned char white[] = { 255,255,255 };
		const unsigned char red[] = { 255,0,0 };
		const unsigned char green[] = { 0,255,0 };
		const unsigned char blue[] = { 0,0,255 };
		this->scrollX = scrollX;
		this->scrollY = scrollY;
		
		auto nodes = graph.getNodes();
		//calculate max and min x and y values:
		/**
		int yy = 0;
		int xx = 0;
		 // delete this shit later
		
		for (int i = 0; i < nodes.size(); i++) {
			std::cout << std::endl << nodes.at(i).getX() << std::endl << nodes.at(i).getY();
			nodes.at(i).setX(xx);
			nodes.at(i).setY(yy);
			std::cout << std::endl << nodes.at(i).getX() << std::endl << nodes.at(i).getY()<<"y";
			xx += 1;
			if (xx >= 5) {
				xx = 0;
				yy += 1;
			}
		}
		**/
		
		nodeHeight = 0;
		nodeWidth = 0; // calculates the needed height and width of the pane
		for (int i = 0; i < nodes.size(); i++) {
			std::cout <<"b" << std::endl << std::round(nodes.at(i).getX() / scrollX) << std::endl << std::round(nodes.at(i).getY() / scrollY);
			if (nodes.at(i).getX()/scrollX > nodeWidth) {
				nodeWidth = std::round(nodes.at(i).getX() / scrollX);

			}
			std::cout << std::endl << std::endl;
			if (nodes.at(i).getY()/scrollY > nodeHeight) {
				nodeHeight = std::round(nodes.at(i).getY()/scrollY);
				std::cout << std::endl << nodeHeight;
			}
		}
		nodeHeight += 1;
		nodeWidth += 1;
		pixHeight = nodeHeight * PIX_PER_NODE_HEIGHT;
		pixWidth = nodeWidth * PIX_PER_NODE_WIDTH;
		CImg<unsigned char> bg(pixWidth, pixHeight, 2, 3, 255); // I have no idea what the 2 and 3 are but the 255 means a white background
		drawEdges(graph, &bg);
		//actual loop to draw all nodes
		for (int i = 0; i < nodes.size(); i++) {
			drawNode(nodes.at(i), &bg);
			//std::cout << std::endl << getText(node.getData()).at(0);
		}
		//drawArrowFrom(0, 0, 1, 1, &bg);
		


		CImgDisplay dsp(pixWidth, pixHeight, "uwu", 0);
		dsp.display(bg);
		std::getchar();

		bg.save_bmp("secondaryTest.bmp");
	}


	// returns coords of top left corner of square x. 
	std::pair<int, int> getCornerOfPosition(int x) {
		int trueX = (x % nodeWidth) * PIX_PER_NODE_WIDTH;
		int trueY = (x / nodeWidth) * PIX_PER_NODE_HEIGHT;
		std::cout << std::endl << "x: " << trueX;
		std::cout << std::endl << "y: " << trueY << std::endl;
		return std::pair<int, int> {trueX, trueY};
	}



private:
	void drawRectByNode(int x, int y, CImg<unsigned char>* c) {
		const unsigned char grey[] = { 220,220,220 };
		int cornerPixX = x * PIX_PER_NODE_WIDTH;
		int cornerPixY = y * PIX_PER_NODE_HEIGHT;
		c->draw_rectangle(cornerPixX + SPACING, cornerPixY + SPACING, cornerPixX + PIX_PER_NODE_WIDTH - SPACING, cornerPixY + PIX_PER_NODE_HEIGHT - SPACING, grey, 1);



	}

	// draw arrow from box at xy to other box at xy(full size cords not pixles)
	void drawArrowFrom(int fromX, int fromY, int toX, int toY, CImg<unsigned char>* c) {
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
		else if (yDif > 0) {
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
		int startX = (fromX * PIX_PER_NODE_WIDTH) + PIX_PER_NODE_WIDTH / 2;
		int startY = fromY * PIX_PER_NODE_HEIGHT + PIX_PER_NODE_HEIGHT / 2;
		int endX = (toX * PIX_PER_NODE_WIDTH) + xAdd;
		int endY = (toY * PIX_PER_NODE_HEIGHT) + yAdd;
		c->draw_arrow(startX, startY,endX ,endY , black,1,30,20);

	}

	int nodesToPixles() {
		pixHeight = nodeHeight * PIX_PER_NODE_HEIGHT;
		pixWidth = nodeWidth * PIX_PER_NODE_WIDTH;
	}


	std::vector <std::string> getText(ClassInfo classInfo) {
		std::vector<std::string> ret;
		// Name
		ret.push_back(classInfo.getName());

		// Fields
		ret.push_back("Fields:");
		for (Field field : classInfo.getFields()) {
			std::string fieldText;
			if (field.getScope() == "public") {
				fieldText = "+ " + field.getName() + " : " + field.getType().toString();
			}
			else if (field.getScope() == "private") {
				fieldText = "- " + field.getName() + " : " + field.getType().toString();
			}
			else {
				fieldText = field.getName() + " : " + field.getType().toString();
			}
			ret.push_back(fieldText);
		}
		// Methods
		ret.push_back("Methods:");
		for (Method method : classInfo.getMethods()) {
			std::string methodText;
			if (method.getScope() == "public") {
				methodText = "+ " + method.getName() + " : " + method.getType().toString();
			}
			else if (method.getScope() == "private") {
				methodText = "- " + method.getName() + " : " + method.getType().toString();
			}
			else {
				methodText = method.getName() + " : " + method.getType().toString();
			}
			ret.push_back(methodText);
		}
		return ret;
	}

	void printTextOnSquare(double x, double y, std::vector<std::string> textVect, CImg<unsigned char>* c) {
		//convert vector of strings to array of const char * , not sure why it doesn't need to be a const char * const but it works and I no longer care

		const int size = textVect.size();
		const char** corrected = new const char* [size];

		std::vector<std::string>::iterator iter;
		for (int i = 0; i < size; i++) {
			corrected[i] = textVect.at(i).c_str();
		}


		const unsigned char grey[] = { 220,220,220 };
		const unsigned char black[] = { 0,0,0 };
		double startPixX = x * PIX_PER_NODE_WIDTH;
		double startPixY = y * PIX_PER_NODE_HEIGHT;
		double pixX = startPixX + SPACING;
		double pixY = startPixY + SPACING;
		int textSpacing = 15;
		for (int x = 0; x < size; x++) {
			c->draw_text(pixX, pixY, corrected[x], black, grey, 1, 14);
			pixY += textSpacing;
		}
		delete[] corrected;
	}

	void drawNode(Node<ClassInfo> n, CImg<unsigned char>* c) {
		//takes node, prints rectangle and writes the text over it

		drawRectByNode(std::round(n.getX()/scrollX), std::round(n.getY()/scrollY), c);
		printTextOnSquare(std::round(n.getX()/scrollX), std::round(n.getY()/scrollY), getText(n.getData()), c);
	}
	
	void drawEdges(Graph<ClassInfo> g,CImg<unsigned char>* c) { // the nodeOverride should be deleted once the algorithm is functional
		auto edges = g.getEdges();
		for (Edge e : edges) {
			//edges use an ID value in node instead of pointers for some godawfull reason so I need to search the array for the correct nodes


			std::pair<int, int> startCords;
			std::pair<int, int> endCords;
			int startId = e.getStartNode();
			int endId = e.getEndNode();
			
			//searches node list for a node of the correct id and takes node coords
			for (Node<ClassInfo> n : g.getNodes()) {
				if (n.getID() == startId) {
					startCords.first = std::round(n.getX() / scrollX);
					startCords.second = std::round(n.getY() / scrollY);
				}
				if(n.getID() == endId) {
					endCords.first = std::round(n.getX() / scrollX);
					endCords.second = std::round(n.getY() / scrollY);
				}
			}
			drawArrowFrom(startCords.first, startCords.second, endCords.first, endCords.second, c);
		}
	}
};

