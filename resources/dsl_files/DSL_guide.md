# DSL Guide
This is a guide on how to write configuration files in the DSL format as defined in 
__src/parser/mfpg_dsl.cf__, see that file for the full grammar.

## Parts
A MFPG DSL file currently consists of five parts: Output, Attributes, Strings, Actions, and Dependencies.
Each of these parts define some required configuration part the program will use to generate fingering
positions, the parts are defined in the above order and separated by their respective names followed by a 
colon, like so:

    Output:\
        (Output is defined here)\
    Attributes:\
    (Attributes are defined here)\
    Strings:\
        (Strings are defined here)\
    Actions:\
        (Actions are defined here)\
    Dependencies:\
        (Dependencies are defined here)\

### Output
The Output is a single word defining what type the output of each Action should have. Currently the only
supported types are __int__ and __double__, referring to whether the output is to be an integer
(whole number such as 1, 5, 23 etc.) or a double (number with decimals such as 0.4672, 231.2, 23.36783 etc).

For example:\
Output: int

### Attributes
An Attribute represents some physical aspect of a note, for example consider that for a bowed string 
instrument a note can only be played by pressing one of four fingers on a string or in the case of an
open string, pressing no finger on a string. Thus Finger could be an Attribute with 5 different values (0-4).
Another example Attribute could be the distance between the note being played and the bridge. Generally, 
notes can be played in more than one way, Attributes are used to specify the different physical ways of 
playing notes, one note will correspond to multiple different Attribute value combinations, but every note 
will have the same Attributes. In the above first example the same note can use different fingers depending 
on what string it is played on, but every way to play that note will use some finger.

The Attributes part defines what __variables__ may be used in later sections. If an Attribute is not defined
in the Attributes part, that Attribute can not be used in the Actions or Dependencies parts. The Attributes
themselves will correspond to some value when the program is executed and, while these values will not need 
to be defined for each note in this part, the types of the values must be defined for each Attribute here.
For example, consider a configuration with three Attributes; String, Hand Position, and Finger. Then also
consider a note, say __As_3__ on a violin. This __As_3__ note can be played in two ways (as defined by our
attributes!):

String = 1, Finger = 1, Hand Position = 2\
String = 1, Finger = 2, Hand Position = 1

Both of these combinations play the same note but use different values for the Attributes. For a 
configuration we will call a combination of __all__ defined Attributes a __Physical Note Representation__
(PNR), so in the above example the PNR type for the notes is the same, differing only in the values of the 
Attributes. As described above, we do not need to define the values for all possible PNRs for all notes in 
this part, but we must define what a PNR looks like for this configuration.

Attributes:\
    (i) "String" ,\
    (i) "Finger" ,\
    (i) "Hand\_Position" ;\

(Note the commas separating the different Attribute definitions and the semi-colon which signifies the end
of the Attributes definition.)

The character in the parantheses represents the type of the subsequent Attribute and can be __i__, __d__, 
or __b__, meaning __integer__, __double__ and __boolean__ respectively. integer and double are 
defined as in the output, while boolean means a truth value, either true or false. Once the Attributes have 
been defined in this part, neither the type of an Attribute or the name of an Attribute may be changed.

We have then defined the PNR type for this example as: String, Finger, Hand\_Position, each Attribute having
the type __i__.

### Strings
As this software is designed for string instruments, strings must be defined for an instrument. To 
define a string you define the number of that string (as an integer) and what range of notes can be played
on that string:

Strings:\
    1: C\_4 -> A\_6 ,\
    2: C\_5 -> Cs\_7 ,\
    3: G\_3 -> C\_5 ;\

In the above, we define three strings, the first can play all notes between (inclusive) C\_4 and A\_6, the 
second can play all notes between C\_5 and Cs\_7, and the third can play all notes between G\_3 and C\_5. 
You could also define these notes using the position of the notes relative to C\_0 (as position 0):

Strings:\
    1: 48 -> 81 ,\
    2: 60 -> 85 ,\
    3: 43 -> 60 ;\

Which represents the exact same strings as above.

### Actions
Each Action defines a calculation between two PNRs. The Action will consider one PNR for the **current** 
note, and one PNR for the **next** note in the score, for example if the **current** note 
is __A_3__ and the **next** note is __G_3__ then an Action will consider (based on our Attribute
example definitions in the __Attributes__ section) the transitions:

Transition option 1:\
/------------------------- __A_3__ ------------------------\      /------------------------- __G_3__ ------------------------\ \
String = 1, Finger = 1, Hand Position = 2 ----> String = 1, Finger = 1, Hand Position = 1

Transition option 2: \
/------------------------- __A_3__ ------------------------\      /------------------------- __G_3__ ------------------------\ \
String = 1, Finger = 2, Hand Position = 1 ----> String = 1, Finger = 1, Hand Position = 1

Note the different PNRs for the __A_3__ note.

Each action defined will calculate the __distance__ between the two physical representations of the notes
for __both__ transition option 1 and transition option 2 individually. An action is defined using four 
different components: 
First the name of the action, this name is the name used in the Dependencies section.

The second part consists of the __condition__ functions, a __condition__ function is the decider function
which determines whether or not the __distance__ functions should be evaluated, this should make more sense
in the example later.

The third part consists of the __distance__ functions, the __distance__ functions calculate the output cost 
of a certain action (or __distance__ between the two PNRs under consideration). The output type of each
__distance__ function must correspond to the __output__ as defined in the first part of this document. 

The final part is a simple boolean which represents the default condition for the action. It dictates
whether the Action should occur by default, or should only occur if the Dependencies dictate that it occurs.

As an example, consider the evaluation of Transition option 1. We might decide that we want to 
apply a cost to switching which finger is currently being used to play a note (for bowed string instruments,
commonly only one note is played at a time so only one finger is active at a time.), so we add an Action 
to do so.

"Finger\_Action" = ???

We must then decide what actually constitutes as a finger switch and define that as a __condition__
function. We can conclude that if a finger switch occurs, then the values of the 
Hand Position Attribute must be _different_ in the two PNRs:

"Finger\_Action" = "Finger" - "Finger" > 0 ???

(Note that whenever the subtraction operator is applied the absolute value function is implicitly applied to
the result.)

The __condition__ function above calcualates the difference between the finger in the first note and
the second note (remember that each action is applied to two subsequent notes, the current note and the
next note, so we dont have to specify what notes we are operating on, it is implicit that the first
Attribute refers to the current note and the second Attribute refers to the next note.). There are a few
different ways to define __conditions__, for a full list see end of this document.

With a satisfactory __condition__ function set defined, we now need to decide the cost of switching fingers.
A reasonable __distance__ could perhaps be defined as simply 1, this way we are always adding a penalty
of 1 whenever we switch fingers used, but since it does not matter what finger we switch to we do not
differentiate between finger swaps.

"Finger\_Action" = "Finger" - "Finger" > 0 : 1 ??? 

Note that the colon is used to mark the end of __condition__ function definitions and the beginning of
__distance__ function definitions.

Finally, we need to decide whether or not this action should always be evaluated as a default, or if
it should only be active if it gets activated by some other action via dependency (more on this in the next
part). For this it makes sense that we should always evaluate this action:

"Finger\_Action" = "Finger" - "Finger" > 0 : 1 (true)

We are now done with the action, and if we then apply this action to Transition option 1 we get (in 
pseudocode):

_if (abs(1 - 1) > 0) then return 1 (implicit: else return 0)_

As _abs(1 - 1)_ is 0, the __condition__ function prevents the __distance__ function from being evaluated,
and therefore defaults to returning 0.

For Transition option 2 we get:

_if (abs(1 - 2) > 0) then return 1 (implicit: else return 0)_

Since _abs(1 - 2)_ is 1, this time the __distance__ function does get evaluated, and returns 1.

Therefore the distance between the PNRs in transition option 1 is lower than the distance between PNRs in
transition option 2. However, we can also see that the PNRs differ in another way; the Hand Position 
Attribute also changes, so it makes sense to perhaps add another action to measure that.

"HP\_Action" = "Hand\_Position" - "Hand\_Position" > 0 : ???

Here we have defined a __condition__ function in the same way as we did with the finger action, since it
is a good way to measure a change in Attribute values. We then want to define a __distance__ function for 
this action, but this time it would make sense to use the difference between Hand positions as part of the
__distance__ calculations in order to get an action that increases in __distance__ if the two hand positions
are farther apart:

"HP\_Action" = "Hand\_Position" - "Hand\_Position" > 0 : "Hand\_Position" - "Hand\_Position" + 1 (true)

Above we define the __distance__ function to be the difference in hand position + 1, to make it more 
costly to swap hand position than it is to swap fingers.

With this new action added we get a different result for the Transition options:

Transition option 1:

_(if (abs(1 - 1) > 0) then return 1)_ + _(if (abs(1 - 2) > 0) then return (abs(1 - 2) + 1))_

Where the second part after the + is the new hand position action and the first part is the old finger 
action. The result is now 2.

Transition option 2:

_(if (abs(1 - 2) > 0) then return 1)_ + _(if (abs(1 - 1) > 0) then return (abs(1 - 1) + 1))_

Which only returns 1 from the first part.

It is also possible to construct an action with _several_ __condition__ functions. This is 
done like this:

__condition function__ && __condition function__
or
__condition function__ || __condition function__

In the first case _both_ __condition__ functions must evaluate to true for the __distance__ functions to be
evaluated, in the second case only one __condition__ function must evaluate to true.

Similarly multiple __distance__ functions can be added to the same action:

__distance function__ + __distance function__
or
__distance function__ - __distance function__

Where the outputs of the functions are added or subtracted (remember that subtraction always applies the 
absolute function since an output can not be less than 0.).

Any number of functions can be joined together and the operators are left associative. For actions there
is no way to mix __condition__ and __distance__ functions, first we must defined all __condition__ 
functions, then we must add the separator (:) and then define all __distance__ functions.

For completeness sake, this is how the Action section looks like for this example:

Actions:
    "Finger\_Action" = "Finger" - "Finger" > 0 : 1 (true) ,
    "HP\_Action" = "Hand\_Position" - "Hand\_Position" > 0 : "Hand\_Position" - "Hand\_Position" + 1 (true) ;

(Again, note the comma at the end of the first action and the semi-colon at the end of the final action, 
these symbols are a necessity to separate actions and denote the final action.)

### Dependencies
Finally we have the dependencies part. A dependency is defined loosely as: 

_"If Action A has occurred, Action B should/should not occur."_

This definition also adds an important new facet to the previous section; the _order_ of the action 
definitions matter. If we define the above dependency but _Action A_ is defined __after__ _Action B_, then
the dependency has no effect, since actions are evaluated sequentially for each transition, and reset when
a new transition is to be evaluated. 

Let us consider an example. In the previous part we defined two actions, the first action was the finger
action. In that action we said that we only care to evaluate the distance function if we switched fingers.
While this is a good action to have, it does miss an important case; What happens if we switch which
string we are playing on but we do _not_ switch finger? In this case we would have no cost applied, even
though we need to _effectively_ move our finger (We would also have to switch strings which would require
its own actions, but for this simple example we do not care about that.). We _could_ redefine our finger
action to take into account this swap, but we could instead fix it by adding a dependency (in many cases
adding another __condition__ function or redefining an action can solve the same problem that adding a 
dependency can solve, in general it is easier to try to keep actions _simple_ and add more dependencies.).

So, in order to create this new dependency, we will want to add a new action first:

"Finger\_String\_Action" = "Finger" - "Finger" == 0 : 2 (false) ;

In the above action, we say that if the finger does not change, we add 2 to the __distance__. This action 
on its own does not solve our problem, we do not want this action to happen by default since it encapsulates 
the case where no finger or string change is made, which is why the action is _not_ to be evaluated by
default and instead must be _activated_ by some other function via dependency. We can accomplish our goal
by adding a final fourth action:

"String\_Activation\_Action" = "String" - "String" > 0 : 0 (true) ;

Notice how the __distance__ function of this action is 0, it does not add any __distance__ cost on its own,
it is solely used to determine whether or not a shift in strings has occurred. We then place this action
definition at the top of our actions definition: 

Actions:
    "String\_Activation\_Action" = "String" - "String" > 0 : 0 (true) ,
    "Finger\_String\_Action" = "Finger" - "Finger" == 0 : 2 (false) ,
    "Finger\_Action" = "Finger" - "Finger" > 0 : 1 (true) ,
    "HP\_Action" = "Hand\_Position" - "Hand\_Position" > 0 : "Hand\_Position" - "Hand\_Position" + 1 (true) ;

And then we can define the dependency:

Dependencies:
    "String\_Activation\_Action" "Finger\_String\_Action" true ;

Let us then consider an example of a transition between the two PNRs:

String = 1, Finger = 2, Hand Position = 1  ----> String = 2, Finger = 2, Hand Position = 1

In this case, the string activation action is triggered, but applies no __distance__ cost. Then the
finger string action is evaluated _because_ the dependency changes the default activation boolean to be true
and the __condition__ function evaluates to true, which adds 2 to the __distance__ cost. The next
two actions do not activate as the __conditions__ evaluate to false. As mentioned earlier, there are
multiple ways one could achieve this effect, but dependencies allows for more complex action flows to be
created.

The final DSL file in this example looks like this:

Output: int
Strings:
    1: C\_4 -> A\_6 ,
    2: C\_5 -> Cs\_7 ,
    3: G\_3 -> C\_5 ;
Attributes:
    (i) "String",
    (i) "Finger",
    (i) "Hand\_Position";
Actions:
    "String\_Activation\_Action" = "String" - "String" > 0 : 0 (true) ,
    "Finger\_String\_Action" = "Finger" - "Finger" == 0 : 2 (false) ,
    "Finger\_Action" = "Finger" - "Finger" > 0 : 1 (true) ,
    "HP\_Action" = "Hand\_Position" - "Hand\_Position" > 0 : "Hand\_Position" - "Hand\_Position" + 1 (true) ;
Dependencies:
    "String\_Activation\_Action" "Finger\_String\_Action" true ;

Below is a list of all variations of __condition__ and __distance__ functions implemented followed by a
brief explanation of the function purpose.

(For verbosity sake I will only type out one of each of the functions and then list replacable parts below)

__conditions__

"Attr1" + "Attr2" == Number
Used to compare two attributes combined to some number.

this "Attr1" == Number
Used to compare the Attribute "Attr1" of the _current_ PNR to some number.

to "Attr1" == Number
Used to compare the Attribute "Attr1" of the _next_ PNR to some number.

Bool
This is a direct truth value, either true or false.

this "Attr1" 
Direct truth value taking from a boolean attribute of the _current_ PNR, can not be applied to integer or 
double attribute values.

to "Attr1"
same as above but for the _next_ PNR.

__distance__

"Attr1" + "Attr2" * Number
Combines the values of "Attr1" and "Attr2" and multiplies it by some number

"Attr1" + "Attr2"
Combines the values of "Attr1" and "Attr2"

Number
Direct adding of cost to __distance__

All instances of "==" can be replaced by either of the following: "<" ">" ">=" "<=" "!="
All instances of "+" can be replaced by "-"
Number can refer to either an integer or a double.

