def subtract(p1, p2):
    	return [p1.x - p2.x, p1.y - p2.y]

def cross_product(p1, p2):
	return p1[0] * p2[1] - p2[0] * p1[1]

def direction(p1, p2, p3):
	return  cross_product(subtract(p3,p1), subtract(p2,p1))


class graphWithLocation:
    def __init__(self, nodes, edges):
        self.nodes = nodes
        self.edges = edges
    def crossingEdges(self):
        crossings = 0
        for edge1 in self.edges:
            for edge2 in self.edges[self.edges.index(edge1):]:
                crossings += edge1.crossingsWith(edge2)
        return crossings
                    

class node:
    def __init__(self,name,x,y):
       self.name = name
       self.x = x
       self.y = y 
    def __ege__(self, other):
        return self.name == other.name

class edge:
    def __init__(self,node1,node2,corners=[]):
       self.node1 = node1
       self.node2 = node2
       self.corners = corners
    def __eq__(self, other):
        return((self.node1 == other.node1) and (self.node2 == other.node2))
    def crossingsWith(self, other):
        crossings = 0
        if(len(self.corners) == 0 and len(other.corners) == 0):
            d1 = direction(other.node1, other.node2, self.node1)
            d2 = direction(other.node1, other.node2, self.node2)
            d3 = direction(self.node1, self.node2, other.node1)
            d4 = direction(self.node1, self.node2, other.node2)
            if ((d1 > 0 and d2 < 0) or (d1 < 0 and d2 > 0)) and ((d3 > 0 and d4 < 0) or (d3 < 0 and d4 > 0)):
                crossings += 1
        return crossings
    def __str__(self):
        return "("+str(self.node1.name)+" , "+str(self.node2.name)+")"
