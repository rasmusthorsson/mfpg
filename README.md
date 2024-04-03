![ubuntu](https://github.com/rasmusthorsson/mfpg/actions/workflows/ubuntu.yml/badge.svg)
![windows](https://github.com/rasmusthorsson/mfpg/actions/workflows/windows.yml/badge.svg)

# Music Fingering Position Generator

A personal project with the goal of creating software to automically construct a 
fingering position sequence for a given	music score (for a single bowed string 
instrument currently). By using user defined preferences and instrument definitions 
the software should be able to give a good base of fingering positions when fed a sheet 
music MusicXML file. Uses the **mx** library (found at https://github.com/webern/mx) for 
MusicXML parsing. Also uses the **cxxopts** library for parsing inputs and managing
options (https://github.com/jarro2783/cxxopts). **gtest** is used for unit- and integration
tests.

**Note that this program is not yet ready for Release**

# Program Explanation

The program works by constructing a _layered_ weighted DAG and running a shortest path 
algorithm on it.

## Graphical Representation

Below is an image of how the graph is represented in the program.

![Program graph.](resources/docs/Layers.png "Program graph")

The Physical Note Representation (__PNR__) (Called _Node Tuples_ in the above image) 
in the layers represent the nodes in the graph and the costs in the 
transition matrix represent the weights on the edges between PNRs in adjacent layers.
The edges are defined as going between the PNR that is the *n'th* PNR in the current 
layer (by index) and the PNR that is the *m'th* PNR in the layer of the next 
LayerList (again by index). The cost in the transition matrix for that transition is 
then found at row *n*, column *m*.

## Program Structure

The program takes a musicXML score as input which is parsed by the mx library. The 
structure created by the mx library is then converted to a _notelist_ of simplified 
notes. An _instrument_ is then constructed by defining _strings_ and _actions_, a _notemapper_ 
is also built which defines all possible PNR for the defined instruments strings for all 
possible notes. The notelist is then combined with the notemapper to generate a _linked 
list of layers_, where each layer represents one note in the notelist and contains all
physical ways to play that note (PNRs). The actions are then used in combination with the
layerlist to calculate the cost of each transition between the PNRs 
in connected layers. Once the costs have been calculated a shortest path solver is 
used to find the shortest path through the graph, which results in the *best* way
to play the score according to the action setup.

## User Inputs

The user will need to select and/or supply a few different input arguments to the program.

### Music Score

First and foremost the user must supply the score they are intending to play. Currently tests only exist for
scores with one voice and only MusicXML files are accepted. In the future further formats will be supported.

### Note Mapper

As musical notes are too abstract to be used directly for any useful cost calculations
for transitions, a notemapper is required to map the abstract notes to PNRs 
of those notes. Since there are many different physical metrics which
could be used to represent notes the notemapper will be definable by the user, but 
basic notemappers will be supplied if the user has no need for anything specific.

Currently there are two notemappers, the basic notemapper hardcoded in the program, and the CSV notemapper.
The CSV notemapper takes a CSV file in the format of a *Note,ATTRIBUTE1,ATTRIBUTE2,...* CSV file and
directly constructs a notemapper using that CSV file. There is a smaller program in the 
_resources/csv_note_map_builder/_ directory which can be used to generate the basic notemapper but in CSV
format. This program can be altered to add various attributes _without_ having to recompile the MFPG program
or add new structures to the MFPG program directly, since this smaller generator program simply generates
CSV files, which can be used as input to MFPG.

In the future a more comprehensive CSV file containing 
a large amount of different attributes will be available and the user will be able to select attributes out
of that CSV file to use if they do not want/can not construct their own notemapper using the smaller 
CSV notemapper generator program.

### Instrument

In order to generate fingering positions an _instrument_ must be defined. An instrument consists of two
components: Strings and an ActionSet. To define an instrument you use the DSL (See the DSL\_Guide.md file
for a guide on how this is done in detail.).

#### Strings

Strings can be considered close to their physical counterparts (Strings as in Strings of an Instrument), and
are defined with a string position (first string, second string, third string, etc.), and the playable notes
on that string. Playable notes can be defined using a range of notes, for example the D-String on a violin 
can play the notes *D\_4* to *Ds\_6* and is the second string on the instrument, thus we define that string 
as _(2, D\_4, Ds\_6)_.

#### Action Set

To calculate costs of transitions between PNRs of notes an action set must
be defined. This set will consist of smaller constraints and the cost of the transition
if those constraints are fulfilled. An action could be defined such that if the first note is played on 
*String 1*, and the second note is played on *String 2* the cost could increase by 1 for example.

The actions are to be defined in order of when they are checked, they can also be defined as 
either occurring by default or only occurring if some other specific action has
occurred. This means actions can also have dependencies defined between eachother, 
with some actions disabling later actions if they do occur. 

For a complete description of actions, see the DSL guide file.
