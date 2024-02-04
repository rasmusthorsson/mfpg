# Music Fingering Position Generator

A personal project with the goal of creating software to automically construct a 
fingering position sequence for a given	music score (for a single bowed string 
instrument). By using user defined preferences and instrument definitions the 
software should be able to give a good base of fingering positions when fed a sheet 
music MusicXML file. Uses the mx library (found at https://github.com/webern/mx) for 
MusicXML parsing.

# Program Explanation

## Graphical Representation

Below is an image of how the graph is represented in the program.
![Program graph.](resources/docs/Layers.png "Program graph")

The tuples in the Layers represent the nodes in the graph and the costs in the 
transition map represent the weights on the edges. The edges are defined as going
between the tuple that is the key in the transition map and the tuple in the *n'th* 
position in the layer of the next LayerList, where *n* is the index of the vector
in the mapped value.

## Program Structure

The program takes a musicXML score as input which is parsed by the mx library. The 
structure created by the mx library is then converted to a notelist of simplified 
notes. An instrument is then constructed by defining strings, actions, and a 
notemapper, which is used to define all possible physical definitions for all possible
notes. The notelist is then combined with the instrument to generate a linked list
of layers, where each layer represents one note in the notelist and contains all
physical ways to play that note. The actions are then used in combination with the
layerlist to calculate the cost of each transition between the physical representations
in subsequent layers. Once the costs have been calculated a shortest path solver is 
used to find the shortest path through the graph, which results in the *best* way to
play the score.

