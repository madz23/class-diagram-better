class graphWithLocation:
  def __init__(self, nodes, edges):
    self.nodes = nodes
    self.edges = edges

class node:
    def __init__(self,name,x,y):
       self.name = name
       self.x = x
       self.y = y 

class edge:
    def __init__(self,node1,node2):
       self.node1 = node1
       self.node2 = node2
