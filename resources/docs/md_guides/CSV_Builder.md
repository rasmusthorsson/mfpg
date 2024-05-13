# CSV Note Mapper File Generator

In order to use physical attributes in actionset definitions via the DSL these 
attributes must be mapped to notes. This guide gives a brief overview on how generate
CSV files with mappings from physical attributes to notes such that they can be used
in the DSL.

**This is an advanced section and requires some knowledge of programming**

## Attributes

An **Attribute** is some physical aspect of a *way* to play a note, for example every
note is played on a string (or precisely played on no string). We could thus define
**STRING** as an attribute. Therefore if
a note is played on the D-String on a violin, you would have an attribute value for 
that exact way of playing that note as *This way to play the note is on String 2*. 
This allows us to define multiple ways of playing the same note by differentiating the 
ways that note is played. This also allows us to reason about transitions between 
ways of playing notes in a more concrete manner and assign *costs* to these 
transitions. 

To **map** a list of attributes to a note means to specify that *Note x can be played
with attribute values: a, b, c ...*. These mappings are then used when the program
is calculating the most effective way to play a piece of music. The mappings define
the possible phyiscal ways to play a note, and how that physical way looks.

## Existing Attributes

Currently a few different attributes have been mapped for the violin in the default
CSV file available:

- String: The string being played, 0-4.
- Finger: The finger used to play the note, 0-4.
- Hand Position: The position of the hand when playing the note: 1-12.

These attributes are mapped in the CSV format:

`Note,STRING,FINGER,HAND_POS`

With the following rows as the mapped values, e.g:

`G_4,1,3,4`

The attribute names in the CSV file must be exactly the same as the attribute names 
defined in the DSL when defining an action set, and they are case sensitive.
Each Note is generally not exclusive in the mapping, for example in the same file
you would have the CSV values:

`G_4,1,4,3`

As they are both valid ways of playing the G 4 note on the violin.

## Defining Attributes

Attributes should often be 
defined in relation to other attributes. For example, in the previous section the
two examples of the G 4 mappings are not random, the increase in the value of the
**FINGER** attribute from 3 to 4 is synchronized with the decrease in the value of the
**HAND_POS** attribute from 4 to 3. This is due to the relation between the two 
attributes: in reality, the G 4 note when played on the same string will be played
in the same location on that string, but the hand can move depending on which position
is more beneficial in regards to previous or subsequent notes. Therefore we consider
every possible hand position for that note on that string, and subsequently the finger
used changes in sync with the hand position changes to allow for that.

One could imagine an attribute which represents the distance between
the note played and the bridge. This attribute could be useful for certain purposes, 
even though it does not capture the important aspect of the hand position or which 
finger is used and thus cannot substitute these two attributes. Therefore to add this 
attribute we would need to add it as a standalone column in the CSV file.

`Note,STRING,FINGER,HAND_POS,DISTANCE(mm)`\
`G_4,1,4,3,160`\
`G_4,1,3,4,160`

We can here see that the new distance attribute does not seem to have any direct 
relation to the hand position or the finger attributes respectively, but could 
possibly relate to their combined values. For example, if you consider the same 
finger and hand position values but for string 4, you would have a similar distance 
value.

## Developing new Attribute definitions

For any new attributes to be defined first we should establish the relationship with
other attributes, as done above. Once the relationship is established (assuming there 
is one), all possible values of the attribute must be calculated. This can be done
either by defining them individually (as a list of possible values) or done indirectly
by defining some function to caluclate the values possibly as a result of the 
relationships to other attributes (which is why it can be more effective to establish 
the relationships if there are any, you could just define the values manually but 
that can take some time to do.).

In this case you could look at sample values of distances between full steps of notes
on the same string and define how the distance decreases as you get
closer to the bridge as a function of the note location on the string (i.e, the finger
 + the hand position attribute values).

## Implementing new Attribute definitions

The next step is to write
a program to generate CSV files where this attribute is present. In the GitHub repo
for this project there is a skeleton program which generates CSV files, found in 
**resources/csv_note_map_builder/**. The **Builder.cpp** file contains two functions
named *build_file()* and *build_file_CUSTOM()*, *build_file()* has a basic 
implementation for generating **STRING**, **FINGER**, and **HAND_POS** attribute 
values for all playable notes on a violin.

To create your own implementation you can copy over the code from 
*build_file()* to *build_file_CUSTOM()* (alternatively build your custom function
from scratch) and then add the code for generating the new attribute there. To
activate the custom function you also need to go into the **Builder.h** file in the
same directory and uncomment the line *#define CUSTOM*, which will enable the custom
function instead of the default one. The default function contains some documentation
in the form of comments on what the different lines are meant to accomplish, which
might help with the implementation of a new attribute addition. 

## Usage

**Only tested on Linux**

Once the attribute addition is implemented you need to compile the code (only the 
files in **resources/csv_note_map_builder/** need to be compiled.). This can be done
by simply running **make** in the directory. If you do not want/can not use **make** 
you will need to manually compile the files using a C++ compiler of your choice. With
the program compiled you can then execute the program with a file name as an
argument to direct the output. The output CSV file (if built correctly) can then
be used as input to the CLI or the GUI main program using the CSV Notemapper. With
this you can now use the attributes you added when writing the DSL file.
