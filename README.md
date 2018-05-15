# graph
This is a graph library that utilizes a hashtable to store the vertices. Each vertices has 2 vectors of incomeing and 
outgoing edges. My goal was to implement the functions below.

Modifying BFS(breadth first seach) so that the NUMBER OF SHORTEST PATHS to each
vertex is recorded.  Recall that in BFS path length is simply 
measured by number of edges.

Path extraction (function: extract_path).
When an algorithm like BFS or DFS(depth first search) (or the critical paths function 
below) is run, the actual paths explored/discovered are encoded 
using "predecessor" information.  Given the predecessor info, 
you will reconstruct paths (see comments for details).

Implement function dag_critical_paths.  This
function takes a DAG and labels each vertex with the length of the
LONGEST input path ("critical-paths" measured by sum of edge
weights) ending at that vertex.  It also encodes the paths 
themselves using the predecessor values (and the paths can be 
extracted using TODO 2 above.

Implement function dag_num_paths.  This function 
labels each vertex with the number of input-to-output paths 
passing through that vertex.  This function does not encode
any particular paths.  It simply records the number of such paths.
See source code for details.
 
Implement function valid_topo_order.  This
function takes a vertex ordering and determines if it is 
indeed a valid topological ordering of the given graph.
(If graph is not even a DAG, the function will return false).
See source code for details.

Implement function enum_paths.  This function
takes a vertex and constructs ALL input-paths ending at that 
vertex.  The paths are represented as strings; a vector of
strings is populated with the paths.