import networkx as nx
import matplotlib.pyplot as plt
import subprocess



num_vertices = int(input("Enter number of vertices: ")) 
num_edges = int(input("Enter number of edges: ")) 


# edgeList=[(0, 1), (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 7), (7, 8), (8, 9), (9, 0)]

# edgeList = [(0, 1), (0, 2), (0, 3), (1, 2), (1, 4), (2, 5), (3, 5), (3, 6), (4, 5), (4, 7),
#          (5, 6), (5, 8), (6, 8), (6, 9), (7, 8), (7, 9), (8, 9), (1, 3), (2, 4), (0, 9)]

# edgeList = [
#     (0, 1), (0, 2), (0, 3), (0, 4), (1, 2), (1, 3), (1, 5), (1, 6),
#     (2, 4), (2, 5), (2, 7), (3, 6), (3, 7), (3, 8), (4, 5), (4, 8),
#     (4, 9), (5, 6), (5, 9), (6, 7), (6, 8), (7, 8), (7, 9), (8, 9),
#     (0, 5), (1, 7), (2, 8), (3, 9), (0, 6), (1, 9)
# ]

edgeList = [
    (0, 1), (0, 2), (0, 3), (0, 4), (0, 5), (0, 6), (0, 7), (0, 8), (0, 9),
    (1, 2), (1, 3), (1, 4), (1, 5), (1, 6), (1, 7), (1, 8), (1, 9),
    (2, 3), (2, 4), (2, 5), (2, 6), (2, 7), (2, 8), (2, 9),
    (3, 4), (3, 5), (3, 6), (3, 7), (3, 8), (3, 9),
    (4, 5), (4, 6), (4, 7), (4, 8), (4, 9),
    (5, 6), (5, 7), (5, 8), (5, 9),
    (6, 9)
]



""" edgeList = []
for i in range(num_edges):
    edge_input = input(f"Enter edge (vertex1,vertex2): ")
    u, v = edge_input.split(",")
    edgeList.append((u.strip(), v.strip()))  """


# Choose output filename based on input
input_file = f"input_{num_vertices}_{num_edges}.txt"


with open(input_file, 'w') as f:
    # Write number of vertices and edges on first line
    f.write(f"{num_vertices} {num_edges}\n")
    
    # Write edges line by line
    for u, v in edgeList:
        f.write(f"{u} {v}\n")
    
    # Blank line (optional)
    f.write("\n")

G = nx.Graph()
vertexList=[]
for i in range(num_vertices):
    vertexList.append(i)


G.add_nodes_from(vertexList)
G.add_edges_from(edgeList)
nx.draw(G, with_labels=True, node_color='lightblue', edge_color='gray', node_size=500)
plt.text(0.05, 0.95, f"Edges: {G.number_of_edges()}", transform=plt.gca().transAxes,
             fontsize=12, verticalalignment='top', bbox=dict(facecolor='white', alpha=0.7))
plt.savefig("graph.png")

print("Graph saved as graph.png")

# Pass values as arguments to C++ executable
subprocess.run(["./vertexCover", str(num_vertices), str(num_edges)])


# Pass values as arguments to output.py
subprocess.run(["python3", "output.py", str(num_vertices), str(num_edges)])


