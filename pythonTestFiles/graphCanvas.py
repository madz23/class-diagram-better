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

graph = alg.randomGraph(10, 20)

visgraph = alg.randomMinStdDevAndCross(graph[0],graph[1],1000,1000,1000)

width = 100
height = 100
fillColor = "red"

for node in visgraph.nodes:
    canvas.create_rectangle(node.x,node.y,node.x+width,node.y+height,fill=fillColor)
    canvas.create_text((node.x+width/2, node.y+height/2), text=node.name)

for edge in visgraph.edges:
    node1 = edge.node1
    node2 = edge.node2
    if(len(edge.corners) == 0):
        canvas.create_line(node1.x,node1.y,node2.x,node2.y,arrow = T.LAST, width = 5)
    else:
        x1 = node1.x
        y1 = node1.y
        for i in range(len(edge.corners)):
            x2 = edge.corners[i][0]
            y2 = edge.corners[i][1]
            canvas.create_line(x1,y1,x2,y2,arrow = T.LAST, width = 5)
            x1 = x2
            y1 = y2
        x2 = node2.x
        y2 = node2.y
        canvas.create_line(x1,y1,x2,y2,arrow = T.LAST, width = 5)
            
print(len(graph[1]))

canvas.pack()
screen.mainloop()

