# Recommmended Topics Suggestion Tool

## Introduction
This goal of this project was to use the Stanford English Wikipedia Hyperlink Network dataset to create a related topics recommendation tool capable of giving recommended articles similar to an input of either 1 or 2 articles. The following algorithms were used to generate the related topics:
* Graph Breadth-First-Search Algorithm
* Brandes Unweighted Shortest Path & Betweeness Centrality Algorithm
* Kosaraju's Strongly Connected Components Algorithm

## Installation
The first step in the installation of this project is to create a folder on the user's local computer 
that contains the provided CS225 Dockerfile and .devcontainer folder with the "devcontainer" JSON file inside of 
it to duplicate the CS225 environment. The user must now run the following command in this newly created folder:<br>
``` 
git clone https://github.com/zayaanali/cs225-final-project.git
```
Next, navigate into the newly cloned folder in the terminal that contains the source code from the git repository by running the following:<br>
```
cd cs225-final-project
```
Create a new folder titled "data" by running the following after having completed the previous step:<br>
```
mkdir data
```
Download the two zip files at the following link: [Here](https://snap.stanford.edu/data/enwiki-2013.html)<br>
Drag the downloaded files titled "wikidata.txt" and "enwiki-2013-names.txt" into this newly created "data" folder.

## How to Build
Once the installation is complete, ensure that you are inside the "cs225-final-project" directory in your terminal. Then run the following commands:<br>
```
mkdir build
cd build
cmake ..
make
```
To clean the directory of any excess or unwanted object files or executables, run the following:
```
make clean
```

## Data Parsing and Trimming
Warning: For these following data parsing steps, the runtime is quite long so to save time, the parsed files titled "finaladj.txt", "finaltitles.txt", and "betweenness.txt" are also provided at this link (these 3 are the only files necessary to run the main algorithms in this program) and can be directly downloaded and placed into the "data" folder: [Here](https://drive.google.com/drive/folders/1D4qHG6QAGv98keLUF5j7drPEF9_2byoq?usp=sharing)<br>
If the user chooses to save time by downloading from the provided link, these next steps for parsing and preprocessing can be ignored; otherwise, proceed with the following steps to manually run the terminal commands for parsing and preprocessing.
Now that the build files have been created, the first step is to run the data parsing and preprocessing commands in the same order as follows inside the build folder in the terminal:<br>
```
./filter_data
./filter_edges
./filter_titles
./bfs_trim
./brandes
```
To verify that these steps have been completed properly, check the "data" folder that was created and verify that the following files have been added to this folder:<br>
"filteredwiki.txt", "filteredadj.txt", "filteredtitles.txt", "finaladj.txt", "finaltitles.txt", "betweenness.txt"<br>
The data parsing and preprocessing is now complete, either by choosing to download from the google drive link as mentioned before or by manually running the terminal commands mentioned above.
## Using the Related Topics Tool
Next, to find a shared Wikipedia page output for two input Wikipedia page indexes, run the following where topic1 and topic2 are strings that the user can select by opening the "finaltitles.txt" in the "data" folder. We recommend using a "ctrl-f" in the "finaltitles.txt" to find the exact formatting of the topic of interest (e.g. "ctrl-f" for "Beethoven" and use "Ludwig van Beethoven" as the command line argument):
```
./related_topics_two_inputs topic1 topic2
```
For example, a user input of<br>
```
./related_topics_two_inputs "Italy" "Food"
```
<br>will yield a result of "Emilia-Romagna". This is a region in Italy known for its culinary cuisine. Make sure that the command line arguments are wrapped in quotation marks, as this allows for strings with multiple words.

## Using the Strongly Connected Components Tool
To run the code for the strongly connected components algorithm, run the following in the terminal and ensure you are in the build folder:
```
./connectedcomponents
```
After running this, the user can now see the size of each strongly connected component for the "finaltitles.txt" dataset.

## Testing
The code provides a wide variety of testing for the various functions and algorithms utilized within the program. To build and run the test suite, run the following commands:<br>
```
make test
./test
```
The tests being ran along with the sample .txt files that are being used as the testing input files can be found within the "tests" folder in the main directory, "cs225-final-project".

## Description/Features
* The program can run the Brandes betweenness centrality algorithm on any CSV file storing an adjacency list for a graph.
* The program can run BFS on any CSV file storing an adjacency list for a graph.
* The program can run the Kosaraju's strongly connected components algorithm on any CSV file storing an adjacency list for a graph.

## Project Structure

**Algorithms Namespace**
* Graph Breadth-First-Search Algorithm
* Brandes Unweighted Shortest Path & Betweeness Centrality Algorithm
* Kosaraju's Strongly Connected Components Algorithm

**Graph Class**
* Adjacency List Graph Implementation




