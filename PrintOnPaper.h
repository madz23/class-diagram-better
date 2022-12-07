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
	const int PIX_PER_NODE_HEIGHT = 175;
	const int PIX_PER_NODE_WIDTH = 275;
	const int SPACING = 50;
	const int RECT_WIDTH = 100;
	const int RECT_HEIGHT = 40;
	//const int PIX_PER_NODE_HEIGHT = 1000;
	//const int PIX_PER_NODE_WIDTH = 700;
	//const int SPACING = 200;

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

	PrintOnPaper(Graph<ClassInfo> graph, std::unordered_map<int, ImVec2> nodeToPosMap, float scrollX, float scrollY) {
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

		//multiplies the pixle values to better fit the sizing of the image
		int mult = 1;
		for (int i = 0; i < nodes.size(); i++) {
			nodeToPosMap[nodes.at(i).getID()].x *= mult;
			nodeToPosMap[nodes.at(i).getID()].y *= mult;
		}




		nodeHeight = 0;
		nodeWidth = 0; // calculates the needed height and width of the pane
		pixHeight = 0;
		pixWidth = 0;
		for (int i = 0; i < nodes.size(); i++) {

			//std::cout <<"b" << std::endl << nodes.at(i).getX() << std::endl << nodes.at(i).getY();
			if (nodeToPosMap[nodes.at(i).getID()].x  > pixWidth) {
				pixWidth = nodeToPosMap[nodes.at(i).getID()].x;
				//std::cout << std::endl << nodeWidth;
			}
			//std::cout << std::endl << std::endl;
			if (nodeToPosMap[nodes.at(i).getID()].y > pixHeight) {
				pixHeight = nodeToPosMap[nodes.at(i).getID()].y;
				//std::cout << std::endl << nodeHeight;
			}
		}
		pixHeight = pixHeight + (PIX_PER_NODE_HEIGHT * mult);// adds enough to the outside edge to get everything in frame(otherwise would stop at the edge of the farthest square)
		pixWidth = pixWidth + (PIX_PER_NODE_WIDTH * mult);
		/**
		nodeHeight += 1;
		nodeWidth += 1;
		pixHeight = nodeHeight * PIX_PER_NODE_HEIGHT;
		pixWidth = nodeWidth * PIX_PER_NODE_WIDTH;
		**/

		CImg<unsigned char> bg(pixWidth, pixHeight, 2, 3, 255); // I have no idea what the 2 and 3 are but the 255 means a white background
		drawEdges(graph,nodeToPosMap, &bg);
		//actual loop to draw all nodes
		for (int i = 0; i < nodes.size(); i++) {
			drawNode(nodes.at(i),nodeToPosMap[nodes.at(i).getID()], &bg);
			//std::cout << std::endl << getText(node.getData()).at(0);
		}
		//drawArrowFrom(0, 0, 1, 1, &bg);
		

		///* exists as test functionality, dispays pane of image and doesn't save and close until char is entered. Very poor resolution, better to view image manually.
		CImgDisplay dsp(pixWidth, pixHeight, "uwu", 0);
		dsp.display(bg);
		std::getchar();
		//*/
		// C:\\Users\\Lybec\\Documents\\
		bg.save_bmp("test.bmp");
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
			// use the arrowhead line equations with double length to get positioning for the character
			std::pair<double, double> multPosition;
			multPosition.first = endX + (arrowHeadLen* 2) *cos((degOfSlope + 180) * PI / 180);
			multPosition.second = endY + (arrowHeadLen * 2) *sin((degOfSlope + 180) * PI / 180);
			c->draw_text(multPosition.first, multPosition.second, mult.c_str(), 1, white, 1, 15);
		}
	}

	int nodesToPixles() {
		pixHeight = nodeHeight * PIX_PER_NODE_HEIGHT;
		pixWidth = nodeWidth * PIX_PER_NODE_WIDTH;
	}

	//gets the title of a class and wraps as appropriate.each element of the vector is a separate line.
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

	void printTextOnSquare(double x, double y, std::vector<std::string> textVect, CImg<unsigned char>* c) {
		//convert vector of strings to array of const char * , not sure why it doesn't need to be a const char * const as the type declaration says but it works and I no longer care
		std::cout << x << std::endl << y << std::endl;
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
		std::cout << x << std::endl << y << std::endl<<std::endl;
		delete[] corrected;
	}

	void drawNode(Node<ClassInfo> n, ImVec2 nodePos, CImg<unsigned char>* c) {
		//takes node, prints rectangle and writes the text over it
		const unsigned char grey[] = { 220,220,220 };
		//drawRectByNode(std::round(n.getX()/scrollX), std::round(n.getY()/scrollY), c);
		c->draw_rectangle(nodePos.x, nodePos.y, nodePos.x + RECT_WIDTH, nodePos.y + RECT_HEIGHT, grey, 1);
		printTextOnSquare(nodePos.x,nodePos.y, getText(n.getData()), c);
	}
	
	void drawEdges(Graph<ClassInfo> g, std::unordered_map<int, ImVec2> nodeToPosMap,CImg<unsigned char>* c) {
		auto edges = g.getEdges();
		for (Edge e : edges) {
			//edges use an ID value in node instead of pointers for some godawfull reason so I need to search the array for the correct nodes


			ImVec2 startCords;
			ImVec2 endCords;
			int startId = e.getStartNode();
			int endId = e.getEndNode();
			startCords = nodeToPosMap[startId];
			endCords = nodeToPosMap[endId];
			
			/*
			//searches node list for a node of the correct id and takes node coords
			for (Node<ClassInfo> n : g.getNodes()) {
				bool ready = false; // bool exists to see if either end has already been found so when the second has, it knows to break out of the loop.
				if (n.getID() == startId) {
					startCords.x = std::round(n.getX() / scrollX);
					startCords.y = std::round(n.getY() / scrollY);
					if (ready) {
						break;
					}
					else ready = true;
				}
				if(n.getID() == endId) {
					endCords.x = std::round(n.getX() / scrollX);
					endCords.y = std::round(n.getY() / scrollY);
					if (ready) {
						break;
					}
					else ready = true;
				}
			}
			*/
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
			//drawArrowFrom(startCords.x, startCords.y, endCords.x, endCords.y, c);
		}
	}
};

