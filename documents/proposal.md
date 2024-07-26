## Leading Question 

The goal of our project is to create two simple “related topics” recommendation tools. One will take a single Wikipedia page title and find the strongly connected component that the vertex representing the page title belongs to, returning other vertices that are in the strongly connected component. To find the strongly connected component that the input vertex is in, we will use Kosaraju's algorithm to generate all strongly connected components. We will then find the strongly connected component that contains the input vertex and return either all nodes in the component or a subset, depending on how large the component is. The second will take two topics/Wikipedia page titles and return a shared topic related to both. We will use Brandes algorithm to find the betweenness centrality of all vertices, calculating all pairs shortest paths in the process. From there, we will look at the node on the shortest path between the two inputted topics with the highest betweenness centrality, since it should be related to both topics and will be the most relevant. Ideally, the page would be something that a human would think of when given the two initial topics as prompts (e.g. food and Italy might output something like pasta). Both algorithms will return related topics, but vary in the number of inputs that they take. 

These tools could be used to identify topics that might interest a user based on their past search history (similar to the “you might also like…” recommendation algorithms on Netflix or Amazon). Other algorithms like BFS and DFS will be used when parsing and trimming the original data set. 

## Dataset Acquisition
This project will focus on using the “English Wikipedia hyperlink network” dataset from the Stanford Large Network Dataset Collection. 
https://snap.stanford.edu/data/enwiki-2013.html

## Data Format

The “English Wikipedia hyperlink network” is a directed graph where an edge exists from i to j if a hyperlink exists on page i to page j. 
The data set is a downloadable 1.56 GB text file. Each line has a pair of two node IDs. The first index is the “from” node and the second index is the “to” node. The graph has 4,203,323 nodes and 101,311,614 edges, with a corresponding csv file with the titles of each page. The CSV file contains an integer node ID and a string title on each line. Because of the size of the graph, we will trim the number of nodes to around 25,000 by looking at the 10 vertices with the highest in-degree (most linked to pages) and include all vertices within a certain distance from those seed points. This will ensure that our graph is connected, which is required for many of our algorithms. 
## Data Correction
As mentioned in the data format section, we plan on trimming the number of nodes from 4,203,323 to just 25,000 with the highest degree centrality. We will also clean up the page titles by replacing special characters like \u80 to €. To parse the data, we will iterate through each line of the graph data file, checking that there are two valid integer indices on each line and constructing an adjacency matrix in the process. If either of the indices are invalid (i.e. don’t have a corresponding title or correspond to a node that we cut from the graph when taking a subset), we will ignore that edge. 

## Data Storage
We will utilize an adjacency matrix to store the graph. The elements of the matrix will indicate whether an edge connects a pair of vertices in the graph. Since an adjacency matrix will have V columns and V rows, the space complexity of the matrix will be O(V2). From Brandes algorithm, we will also store a 2D matrix with the betweenness centrality of each vertex and a 2D matrix that stores the predecessor of each node on the shortest path. Both of these matrices will be O(V2). 

We will also use a dictionary to map node (vertex) IDs to their Wikipedia page title, which would be O(V).

## Graph Algorithms 

To trim our dataset, we would first calculate the top ten vertices with the highest in-degree by iterating through every edge in the given data set file and updating a dictionary mapping each vertex index to its in-degree. This would run in O(E) time and would require O(V) space for the dictionary. We would then use a partial BFS to traverse a certain distance away from each of the top ten vertices. We will experiment with different distances to try to reach our target of 25,000 vertices. The runtime for BFS is O(V+E) and requires O(V) auxiliary space.

After converting the titles to node IDs, we will use the Brandes algorithm on our graph with no weights to create a matrix that stores the shortest paths between all pairs of nodes. Brandes algorithm takes a directed graph matrix as an input, outputting a 2D matrix with the betweenness centrality of each vertex and a 2D matrix that stores the predecessor of each node on the shortest paths. The runtime of the Brandes algorithm for an unweighted graph is O(V*E).

To find all the strongly connected components we will use Kosaraju’s algorithm. This will perform a DFS traversal on the graph to find all strongly connected components. The algorithm will take a directed graph matrix as input, and output all strongly connected components in the graph. We will run Kosaraju’s on the trimmed graph, after we process and trim down the data. The time complexity of this algorithm is O(V+E), with O(V) space complexity as we have to push all vertices onto a stack. 

The expected inputs for our main program are the titles of either one or two Wikipedia pages which we will first convert to Node IDs using a stored dictionary (dictionaries have O(1) lookup time). If one page title has been inputted, using Kosaraju’s algorithm we can generate all of the strongly connected components of the graph and place them in a vector array. The vector array can then be parsed to find the one with the matching vertex. Then, the subset of strongly connected nodes will be returned as output for a single page input. The expected run time would be O(V+E).

If two page titles have been inputted, using the stored shortest path matrices from the Brandes algorithm, we will be able to output the distance between the two pages in constant time (accessing a stored value in the array) and the full path between the two pages in O(path length) time. The full path is printed by recursively finding the parent of each node in the path. Although the shortest path could be the entire set of vertices in the worst case if the graph were a straight line, the actual length of the path will likely be short given the highly interlinked nature of Wikipedia articles. Therefore, because the paths will be of insignificant length compared to the total number of vertices, the actual runtime of retracing the path should be approximately constant. 

The expected output from these two Wikipedia pages would be the highest betweenness centrality node on the path that should be most related to both pages, which we can find by retracing the path and accessing the stored betweenness centrality values. To visualize the output, we will display the link that represents the middle node topic along with the full path between the two nodes. In summary, converting the title of the Wikipedia pages to integer IDs is O(1), and retracing the full path between two nodes and finding the node with highest betweenness centrality using the computed matrices is O(path length). The overall runtime is then O(path length) which should be constant in most cases. 

Memory and storage efficiency is discussed in “Data Storage.”

## Timeline
Data Acquisition: Completed by November 7th <br />
Data Processing: Completed by November 9th <br />
Completion of BFS Traversal and Makefile: Completed by November 16th <br />
Completion of Strongly Connected Component Kosaraju algorithm: Completed by November 24th <br />
Completion of Brandes algorithm: Completed by November 30th <br />
Code Final Testing and Verification: Completed by December 2nd <br />
Production of Final Deliverables: Completed by December 6th <br />
Final Edits and Minor Changes (if necessary): Completed by December 8th

