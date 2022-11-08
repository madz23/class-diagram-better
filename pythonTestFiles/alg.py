import math
import graphWithLocation as G
import random as R
#accept a param that will determine which set is used (test set by default)

# build a test set

nodes = [0,1,2,3,4] # makes 5 nodes

edges = [(0,1),(1,2),(3,4),(2,3),(1,3),(1,4)] # makes 5 edges

graph = [nodes,edges]


# build a randomized set
def randomGraph(n,e):
    g = [[i for i in range(n)],[]]
    if(e >= n**2): e = n**2
    i = 0
    while(i < e):
        temp = (g[0][R.randint(0,len(g[0])-1)],g[0][R.randint(0,len(g[0])-1)])
        if temp not in g[1]:
            i += 1
            g[1].append(temp)
        print(e)

    return g

# algorthimize it
def random(n, e, width, height):
    nodeList = []
    edgeList = []
    for node in n:
        x = R.randint(20,width-120)
        x = math.ceil(x / (width/10)) *width/10
        y = R.randint(20,height-120)
        y = math.ceil(y / (width/10)) *width/10
        nodeList.append(G.node(node, x, y))
    for edge in e:
        edgeList.append(G.edge(nodeList[edge[0]],nodeList[edge[1]]))
    return G.graphWithLocation(nodeList, edgeList)

def randomMinEdgeCross(n, e, width, height, iteration = 1000):
    graph = random(n, e, width, height)
    for i in range(iteration):
        tempgraph = random(n, e, width, height)
        if(tempgraph.crossingEdges() < graph.crossingEdges()):
            graph = tempgraph
    return graph

def randomMinStdDev(n, e, width, height, iteration = 1000):
    graph = random(n, e, width, height)
    for i in range(iteration):
        tempgraph = random(n, e, width, height)
        if(tempgraph.deviationOfEdges() < graph.deviationOfEdges()):
            graph = tempgraph
    return graph

def randomMinStdDevAndCross(n, e, width, height, iteration = 1000):
    graph = random(n, e, width, height)
    for i in range(iteration):
        tempgraph = random(n, e, width, height)
        if(tempgraph.crossingEdges() < graph.crossingEdges()):
            graph = tempgraph
        elif (tempgraph.crossingEdges() == graph.crossingEdges()):
            if(tempgraph.deviationOfEdges() < graph.deviationOfEdges()):
                graph = tempgraph

    return graph


def randomOrthogonal(n, e, width, height):
    nodeList = []
    edgeList = []
    for node in n:
        x = R.randint(20,width-120)
        # x = math.ceil(x / (width/10)) *width/10
        y = R.randint(20,height-120)
        # y = math.ceil(y / (width/10)) *width/10
        nodeList.append(G.node(node, x, y))
    for edge in e:
        edgeList.append(G.edge(nodeList[edge[0]],nodeList[edge[1]],[(nodeList[edge[0]].x,nodeList[edge[1]].y)]))
    return G.graphWithLocation(nodeList, edgeList)


