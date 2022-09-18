#pip install tk
import tkinter as T
from turtle import fillcolor;
import alg
import random

def find(list, filter):
    for x in list:
        if filter(x):
            return x

screen = T.Tk()
canvas = T.Canvas(screen, bg="white", height=1000, width=1000)
# random.seed(1)


graph = alg.algorithm_1(alg.nodes,alg.edges,1000,1000)

width = 100
height = 100
fillColor = "red"

for node in graph.nodes:
    canvas.create_rectangle(node.x,node.y,node.x+width,node.y+height,fill=fillColor)

for edge in graph.edges:
    node1 = find(graph.nodes, lambda x: x.name == edge.node1)
    node2 = find(graph.nodes, lambda x: x.name == edge.node2)
    canvas.create_line(node1.x,node1.y,node2.x,node2.y,arrow = T.LAST, width = 5)




canvas.pack()
screen.mainloop()

