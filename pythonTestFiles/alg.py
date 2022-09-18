import graphWithLocation as G
import random as R
#accept a param that will determine which set is used (test set by default)

# build a test set

nodes = [0,1,2,3,4] # makes 5 nodes

edges = [(0,1),(1,2),(3,4),(2,3),(1,3),(1,4)] # makes 5 edges

graph = [nodes,edges]


# build a randomized set

# algorthimize it
def algorithm_1(n, e, width, height):
    nodeList = []
    edgeList = []
    for node in n:
        x = R.randint(20,width-120)
        y = R.randint(20,height-120)
        nodeList.append(G.node(node, x, y))
    for edge in e:
        edgeList.append(G.edge(edge[0],edge[1]))
    return G.graphWithLocation(nodeList, edgeList)
