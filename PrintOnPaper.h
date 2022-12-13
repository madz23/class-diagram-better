#pragma once
#include <iostream>
#include "CImg.h"
#include "Graph.hh"
#include "Node.hh"
#include "Edge.hh"
#include "ClassInfo.hh"
#include <math.h>
#include <unordered_map>

#define PI 3.14159265

using namespace cimg_library;
class PrintOnPaper
{
	const int RECT_WIDTH = 100;
	const int RECT_HEIGHT = 40;


	//overall size of the screen in pixles
	int pixHeight;
	int pixWidth;


public:

	PrintOnPaper(Graph<ClassInfo> graph, std::unordered_map<int, ImVec2> nodeToPosMap,std::string path) {
		const unsigned char bluegreen[] = { 0,170,255 };
		const unsigned char grey[] = { 220,220,220 };
		const unsigned char black[] = { 0,0,0 };
		const unsigned char white[] = { 255,255,255 };
		const unsigned char red[] = { 255,0,0 };
		const unsigned char green[] = { 0,255,0 };
		const unsigned char blue[] = { 0,0,255 };

		
		auto nodes = graph.getNodes();

		//multiplies the pixle values to better fit the sizing of the image, left commented out in case it's needed by future workers
		int mult = 1;
		/*
		for (int i = 0; i < nodes.size(); i++) {
			nodeToPosMap[nodes.at(i).getID()].x *= mult;
			nodeToPosMap[nodes.at(i).getID()].y *= mult;
		}

		*/


		// calculates the needed height and width of the pane
		pixHeight = 0;
		pixWidth = 0;
		for (int i = 0; i < nodes.size(); i++) {

			if (nodeToPosMap[nodes.at(i).getID()].x  > pixWidth) {
				pixWidth = nodeToPosMap[nodes.at(i).getID()].x;
			}
			if (nodeToPosMap[nodes.at(i).getID()].y > pixHeight) {
				pixHeight = nodeToPosMap[nodes.at(i).getID()].y;
			}
		}
		// adds enough to the outside edge to get everything in frame(otherwise would stop at the edge of the farthest square)
		pixHeight = pixHeight + (RECT_HEIGHT);
		pixWidth = pixWidth + (RECT_WIDTH);

		//creates the image
		CImg<unsigned char> bg(pixWidth, pixHeight, 2, 3, 255); // I have no idea what the 2 and 3 are but the 255 means a white background
		drawEdges(graph,nodeToPosMap, &bg);
		//actual loop to draw all nodes
		for (int i = 0; i < nodes.size(); i++) {
			drawNode(nodes.at(i),nodeToPosMap[nodes.at(i).getID()], &bg);
			//std::cout << std::endl << getText(node.getData()).at(0);
		}
	
		

		/* exists as test functionality, dispays pane of image and doesn't save and close until char is entered. Very poor resolution, better to view image manually.
		CImgDisplay dsp(pixWidth, pixHeight, "uwu", 0);
		dsp.display(bg);
		std::getchar();
		*/
		
		//saves image to path as bmp, other image types pretend to be supported but you really need other libraries
		bg.save_bmp(path.c_str());
	}



private:


	/*
	* draw arrow from box at xy to other box at xy(full size cords not pixles)
	*/ 
	void drawArrowFrom(int fromX, int fromY, int toX, int toY, CImg<unsigned char>* c, bool stdArrow = true, std::string mult = "") {
		const unsigned char black[] = { 0,0,0 };
		const unsigned char white[] = { 255,255,255 };
		int yDif = fromY - toY;
		int xDif = toX - fromX;
		int yAdd;
		int xAdd;
		bool minusX = false;
		bool minusY = false;

		
		//determine whawt side of the end node it is pointing at using the slope, adjust spacing to point at the appropriate side/corner
		if (yDif < 0) {// down
			yAdd = 0;
		}
		else if (yDif > 0) { // up
			yAdd = RECT_HEIGHT;
		}
		else if (yDif == 0) { // horizontal
			yAdd = .5 * RECT_HEIGHT;
		}
		if (xDif < 0) { // left
			xAdd = RECT_WIDTH;
		}
		else if (xDif > 0) { //right
			xAdd = 0;
		}
		else if (xDif == 0) { // vertical
			xAdd = .5 * RECT_WIDTH;
		}
		int startX = fromX + RECT_WIDTH/2;//convert node positions to pixles
		int startY = fromY + RECT_HEIGHT/2;
		int endX = toX + xAdd;
		int endY = toY + yAdd;
		if (stdArrow) {
			c->draw_arrow(startX, startY, endX, endY, black, 1, 30, 20); // standard black arrow, no multiplicity
		}
		else { // two lines arrow with multiplicity
			std::pair<double, double> arrowLineOne; // coordinates of the ends of the arrow lines
			std::pair<double, double> arrowLineTwo;
			int arrowHeadLen = 20;
			//fuck it, no good way to do this like I did the above so I'm converting line slope to degrees then
			//using that to get the angles of the arrowhead lines.
			float degOfSlope = atan2((float)((endY - startY)), (float)(endX - startX)) * 180 / PI;//angle of slope in degrees
			int angleOfArrowhead = 20; // angle of deviation from the line. half of total arrowhead angle
			float angleOne = degOfSlope + 180 - angleOfArrowhead;
			float angleTwo = degOfSlope + 180 + angleOfArrowhead;

			arrowLineOne.first = endX + arrowHeadLen * cos(angleOne* PI/180);
			arrowLineOne.second = endY + arrowHeadLen * sin(angleOne * PI / 180);
			arrowLineTwo.first = endX + arrowHeadLen * cos(angleTwo * PI / 180);
			arrowLineTwo.second = endY + arrowHeadLen * sin(angleTwo * PI / 180);
			c->draw_line(startX,startY,endX,endY, black); // primary line
			c->draw_line(endX, endY, arrowLineOne.first, arrowLineOne.second, black); // arrowhead lines
			c->draw_line(endX, endY, arrowLineTwo.first, arrowLineTwo.second, black);

			// multiplicity
			// use the arrowhead line equations with double length to get positioning for the character(currently uses the angle of the main line, not enough space for branching off with current spacing)
			std::pair<double, double> multPosition;
			multPosition.first = endX + (arrowHeadLen* 2) *cos((degOfSlope + 180) * PI / 180);
			multPosition.second = endY + (arrowHeadLen * 2) *sin((degOfSlope + 180) * PI / 180);
			c->draw_text(multPosition.first, multPosition.second, mult.c_str(), 1, white, 1, 15);
		}
	}

	/* 
	* gets the title of a class and wraps as appropriate. each element of the vector is a separate line.
	*/
	std::vector <std::string> getText(ClassInfo classInfo) {
		int maxLen = 10;
		int maxlines = 2; // box is 40 pixles high, text at size 20
		std::vector<std::string> ret;
		// Name
		std::string temp = classInfo.getName();
		int line = 1;
		while (temp.length() > maxLen && line < maxlines) {
			ret.push_back(temp.substr(0, maxLen));
			temp = temp.substr(maxLen, temp.length());
			line++;
		}
		ret.push_back(temp.substr(0,maxLen));
		//commented out section just adds full info as displayed in the click open box in the main gui. removed to simplify the image. if replaced, sizing will need to be adjusted to match

		/**
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
		*/
		return ret;
	}

	/*
	* Given a set of coordinates, it prints two lines of text 
	*/
	void printTextOnSquare(double x, double y, std::vector<std::string> textVect, CImg<unsigned char>* c) {
		//convert vector of strings to array of const char * , not sure why it doesn't need to be a const char * const as the type declaration says but it works and I no longer care
		const int size = textVect.size();
		const char** corrected = new const char* [size];

		std::vector<std::string>::iterator iter;
		for (int i = 0; i < size; i++) {
			corrected[i] = textVect.at(i).c_str();
		}


		const unsigned char grey[] = { 220,220,220 };
		const unsigned char black[] = { 0,0,0 };
		int textSpacing = 21;
		for (int i = 0; i < size; i++) {
			c->draw_text(x,y, corrected[i], black, grey, 1, 20);
			y += textSpacing;
		}
		delete[] corrected;
	}

	/*
	* Given a node and it's position, draw a grey rectangle at it and then write text over it
	*/
	void drawNode(Node<ClassInfo> n, ImVec2 nodePos, CImg<unsigned char>* c) {
		//takes node, prints rectangle and writes the text over it
		const unsigned char grey[] = { 220,220,220 };
		c->draw_rectangle(nodePos.x, nodePos.y, nodePos.x + RECT_WIDTH, nodePos.y + RECT_HEIGHT, grey, 1);
		printTextOnSquare(nodePos.x,nodePos.y, getText(n.getData()), c);
	}
	
	/*
	* Takes all edges, parses out the coordinates and multiplicity, and sends them to a function to draw the arrows
	*/
	void drawEdges(Graph<ClassInfo> g, std::unordered_map<int, ImVec2> nodeToPosMap,CImg<unsigned char>* c) {
		auto edges = g.getEdges();
		for (Edge e : edges) {
			ImVec2 startCords;
			ImVec2 endCords;
			int startId = e.getStartNode();
			int endId = e.getEndNode();
			startCords = nodeToPosMap[startId];
			endCords = nodeToPosMap[endId];
			
			if (e.getType() == Edge<ClassInfo>::Type::INHERITANCE) {
				drawArrowFrom(startCords.x, startCords.y, endCords.x, endCords.y, c);
			}
			else {
				if (e.getMultiplicity() == Edge<ClassInfo>::Multiplicity::ONE_TO_ONE) {
					drawArrowFrom(startCords.x, startCords.y, endCords.x, endCords.y, c, false, "1");
				}
				else if (e.getMultiplicity() == Edge<ClassInfo>::Multiplicity::ONE_TO_MANY) {
					drawArrowFrom(startCords.x, startCords.y, endCords.x, endCords.y, c, false, "n");
				}
			}
		}
	}
};

