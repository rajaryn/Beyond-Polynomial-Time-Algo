import sys
import networkx as nx
import matplotlib.pyplot as plt


#skip sys.argv[0] which is script name)
num_vertices = int(sys.argv[1])
num_edges = int(sys.argv[2])

outputFile = "output_" + str(num_vertices) + "_" + str(num_edges) + ".txt"
inputFile = "input_" + str(num_vertices) + "_" + str(num_edges) + ".txt"

# Open and read the file
with open(outputFile, "r") as f:
    lines = f.readlines()

# Find the last "# Results" block
for i in range(len(lines)-1, -1, -1):
    if lines[i].startswith("# Results"):
        latest_block = lines[i:]  # from last "# Results" to end
        break

# Extract only the vertex sets
vertex_covers = []
capture = False
for line in latest_block:
    line = line.strip()
    if line.startswith("Smallest Vertex Cover(s):"):
        capture = True
        continue
    if capture:
        if line.startswith("{") and line.endswith("}"):
            # Remove braces and spaces, split by comma
            vertices = [int(v.strip()) for v in line[1:-1].split(",")]
            vertex_covers.append(vertices)

G = nx.Graph()
vertexList=[i for i in range(num_vertices)]
G.add_nodes_from(vertexList)

edgeList = []
with open(inputFile, "r") as f:
    first_line = f.readline()  # skip the first line
    for line in f:
        parts=line.split()
        if(len(parts)==2):  #if it is not an empty line
         u, v = map(int, line.strip().split())
         edgeList.append((u, v))
G.add_edges_from(edgeList)


# Highlight the first vertex cover
for i in range(len(vertex_covers)):
  
  # Node colors
  node_colors = ['red' if node in vertex_covers[i] else 'lightblue' for node in G.nodes()]

  # Draw the graph
  plt.figure(figsize=(8, 6))
  nx.draw(G, with_labels=True, node_color=node_colors, node_size=600, font_size=12, edge_color='gray')
  plt.title("Graph with Highlighted Vertex Cover")
  plt.text(0.05, 0.95, f"Edges: {G.number_of_edges()}", transform=plt.gca().transAxes,
             fontsize=12, verticalalignment='top', bbox=dict(facecolor='white', alpha=0.7))
  plt.savefig(f"vertex Cover_{i+1}.png")
  plt.close()


