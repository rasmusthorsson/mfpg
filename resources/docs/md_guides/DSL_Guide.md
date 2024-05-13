# DSL Guide
This is a guide on how to write configuration files in the DSL format as defined in 
__src/parser/mfpg_dsl.cf__, see that file for the full grammar.

## Parts
A MFPG DSL file consists of five parts: **Output**, **Attributes**, **Strings**, **Actions**, and 
**Dependencies**. Each of these parts define some required configuration the program will use to 
generate fingering positions, the parts are defined in the above order and separated by their respective 
names followed by a colon:

    Output:
        (Output is defined here)
    Attributes:
        (Attributes are defined here)
    Strings:
        (Strings are defined here)
    Actions:
        (Actions are defined here)
    Dependencies:
        (Dependencies are defined here)

### Output
Output is a single word defining what type of output all Actions should have. Currently the only
supported types are __int__ and __double__, referring to whether the output is to be an **integer**
(whole number such as 1, 5, 23 etc.) or a **double** (number with decimals such as 0.4672, 231.2, 23.36783 
etc).

For example:

    Output: int

### Attributes
An Attribute represents some physical aspect of a note, for example consider that for a bowed string 
instrument a note can only be played by pressing one of four fingers on a string (or in the case of an
open string, pressing no finger on a string) and then bowing that string. Thus Finger could be an Attribute 
with 5 different values (0-4). Another example Attribute could be the physical distance between the note 
being played and the bridge. Generally  
a note can be played in more than one way, Attributes are used to specify the different physical ways of 
playing notes, one note can correspond to multiple different Attribute value combinations, but every note 
will have the same Attributes. In the above first example the same note can use different fingers depending 
on what string it is played on, but every way to play that note will use some finger (0-4).

The Attributes part defines what Attributes may be referred to in later parts. If an Attribute is not defined
in the Attributes part, that Attribute can not be used in the Actions or Dependencies parts. Each Attribute
will correspond to some value when the program is executed and the types of those values must be defined for 
each Attribute here (Here we are not defining what the values are, just what type they have).
For example, consider a configuration with three Attributes; String, Hand Position, and Finger. Then also
consider a note, say __As_3__ on a violin. This __As_3__ note can be played in two ways (as defined by our
attributes!):

	1: String = 1, Finger = 1, Hand Position = 2
	2: String = 1, Finger = 2, Hand Position = 1

Both of these combinations play the same note but use different values for the Attributes. For a 
configuration we will call a combination of __all__ defined Attributes a __Physical Note Representation__
(PNR), so in the above example the PNR type for the notes is the same, differing only in the values of the 
Attributes. As described above, we do not need to define the values for all possible PNRs for all notes in 
this part, but we must define what a PNR looks like for this configuration.

    Attributes:
        (i) "String" ,
        (i) "Finger" ,
        (i) "Hand_Position" ;

(The commas separate the different Attribute definitions and the semi-colon signifies the end
of the Attributes definition.)

The character in the parantheses represents the type of the subsequent Attribute and can be __i__, __d__, 
or __b__, meaning __integer__, __double__ and __boolean__ respectively. __integer__ and __double__ are 
defined as in the output, while __boolean__ means a truth value, either **true** or **false**. Once the 
Attributes have been defined in this part neither the type of an Attribute or the name of an Attribute can 
be changed in later parts.

Here we have defined the PNR type for this example as: String, Finger, and Hand\_Position, each Attribute 
having the type __i__.

### Strings
As this software is designed for string instruments, strings must be defined for an instrument to exist. To 
define a string you define the number of that string (as an integer) and the range of notes that can be 
played on that string:

    Strings:
        1: C_4 -> A_6 ,
        2: C_5 -> Cs_7 ,
        3: G_3 -> C_5 ;

In the above, we define three strings, the first can play all notes (in a chromatic scale) between 
(inclusive) C\_4 and A\_6, the second can play all notes between C\_5 and Cs\_7, and the third can play all 
notes between G\_3 and C\_5. You could also define these notes using the position of the notes relative to 
C\_0 (as position 0):

    Strings:
        1: 48 -> 81 ,
        2: 60 -> 85 ,
        3: 43 -> 60 ;

Which represents the exact same strings as above.

### Actions
Each Action defines a comparison of two PNRs. The Action will consider one PNR for the 
**current** note, and one PNR for the **next** note in the score. This will happen until all PNRs for the 
**current** note have been compared to all PNRs of the **next** note. Let's look at an example: if the 
**current** note is __A_3__ and the **next** note is __G_3__ then an Action will consider (based on our 
Attribute example definitions in the __Attributes__ section) the transition __A_3__ ----> __G_3__:

Transition option 1:
    
    String = 1, Finger = 1, Hand Position = 2 ----> String = 1, Finger = 1, Hand Position = 1

Transition option 2:

	String = 1, Finger = 2, Hand Position = 1 ----> String = 1, Finger = 1, Hand Position = 1

Each action defined will calculate the __distance__ (the cost of the transition between the two notes using
these PNRs) between the PNRs of the **current** and the **next** note for _both_ transition option 1 and 
transition option 2 independently. An action is defined by four components: 

First the _name_ of the action, the name is used as an identifier for the action.

The second part consists of the __condition__ functions, a __condition__ function is the decider function
which determines whether or not the __distance__ functions should be evaluated, this should make more sense
in the example later.

The third part consists of the __distance__ functions, the __distance__ functions calculate the 
__distance__ between the two PNRs under consideration (or, again, the cost of transitioning from the 
**current** note to the **next** note via these PNRs). The output type of each __distance__ function must 
correspond to the __output__ as defined in the __Output__ part. 

The final part is a simple boolean which represents the __default condition__ for the action. It dictates
whether the Action should occur by default, or should only occur if the Dependencies dictate that it occurs.

One can think of an action like this (numbers in parentheses correspond to the order of the components 
described above):

Action Name(1) = if __condition functions__(2) and __default condition__(4) then __distance functions__(3)

As an example, consider Transition option 1. We might decide that we want to apply a cost to switching 
which finger is currently being used to play a note so we add an Action to do so.

    "Finger_Action" = ???

We must then decide what actually constitutes as a finger switch and define that as a __condition 
function__. We can conclude that if a finger switch occurs, then the values of the finger Attribute must be
_different_ in the two PNRs:

    "Finger_Action" = "Finger" - "Finger" > 0 ???

(Note that whenever the subtraction operator is applied the absolute value function is implicitly applied to
the result as it does not make sense to have a negative __distance__ or cost.)

The __condition function__ above calculates the difference between the finger value in the first PNR and
the second PNR (It is implicit that the first Attribute refers to a PNR for the **current** note and the 
second Attribute refers to a PNR for the **next** note.). There are a few different ways to define a
__conditions function__, for a full list see end of this guide.

With a satisfactory __condition function__ set defined, we now need to decide the cost of switching fingers.
A reasonable cost could perhaps be defined as simply 1, this way we are always adding a penalty
of 1 whenever we switch fingers used, but since it does not matter what finger we switch to we do not
differentiate between finger swaps. So we define the __distance function__ as 1.

    "Finger_Action" = "Finger" - "Finger" > 0 : 1 ??? 

(Note that the colon is used to mark the end of __condition function__ definitions and the beginning of
__distance function__ definitions.)

Finally, we need to decide whether this action should always be evaluated by default, or if
it should only be evaluated if it gets activated by some other action via dependency (more on this in the 
next part). For this it makes sense that we should always evaluate this action:

    "Finger_Action" = "Finger" - "Finger" > 0 : 1 (true) ;

We are now done with the action definition, and if we then apply this action to 
Transition option 1 we get (in pseudocode):

    if (abs(1 - 1) > 0) then return 1 

As _abs(1 - 1)_ is 0, the __condition function__ prevents the __distance function__ from being evaluated,
and therefore does not increase or decrease the cost of this transition.

For Transition option 2 we get:

    if (abs(1 - 2) > 0) then return 1

Since _abs(1 - 2)_ is 1, this time the __distance function__ does get evaluated, and returns 1.

Therefore the __distance__ between the PNRs in transition option 1 is shorter than the __distance__ between 
PNRs in transition option 2. However, we can also see that the PNRs differ in another way: the Hand Position
Attribute also changes value, so perhaps it makes sense to add another action to measure that.

    "HP_Action" = "Hand_Position" - "Hand_Position" > 0 : ???

Here we have defined a __condition function__ in the same way as we did with the finger action, since it
is a good way to establish a change in Attribute values. We then want to define a __distance function__ for 
this action, but this time it would make sense to use the difference between Hand positions as part of the
__distance__ calculations in order to get an action that increases the __distance__ if the two hand positions
are physically farther apart:

    "HP_Action" = "Hand_Position" - "Hand_Position" > 0 : "Hand_Position" - "Hand_Position" + 1 (true)

Above we define the __distance function__ to be the difference in hand position + 1, to make it more 
costly to swap hand position than it is to swap fingers.

With this new action added we now have two actions, when we have multiple actions each action is evaluated
individually for each transition and the results are added together to form the final __distance__ between 
the two PNRs under consideration. We now get a different result for the transition options:

Transition option 1:

    (if (abs(1 - 1) > 0) then return 1) + (if (abs(1 - 2) > 0) then return (abs(1 - 2) + 1))
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                Finger_Action                               HP_Action

Where the second part after the + is the new hand position action and the first part is the old finger 
action. The result is now 2.

Transition option 2:

    (if (abs(1 - 2) > 0) then return 1) + (if (abs(1 - 1) > 0) then return (abs(1 - 1) + 1))
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                Finger_Action                               HP_Action

Transition option 2 now only returns 1.

It is also possible to construct an action with _several_ __condition functions__. This is 
done with conjunctions and disjunctions:

__condition function__ && __condition function__

__condition function__ || __condition function__

In the first case _both_ __condition functions__ must evaluate to true for the __distance functions__ to be
evaluated, in the second case only one __condition function__ must evaluate to true.

Similarly multiple __distance functions__ can be joined in the same action:

__distance function__ + __distance function__

__distance function__ - __distance function__

Where the outputs of the functions are added or subtracted (remember that subtraction always applies the 
absolute function since an output can not be less than 0.).

Any number of functions can be joined together and the operators are left associative. For actions there
is no way to mix __condition__ and __distance__ functions, first we must define all __condition 
functions__, then we must add the separator (:) and then define all __distance functions__.

For completeness sake, this is how the Action section looks like for this example:

    Actions:
        "Finger_Action" = "Finger" - "Finger" > 0 : 1 (true) ,
        "HP_Action" = "Hand_Position" - "Hand_Position" > 0 : "Hand_Position" - "Hand_Position" + 1 (true) ;

(Again, note the comma at the end of the first action and the semi-colon at the end of the final action, 
these symbols are a necessity to separate actions and denote the final action.)

### Dependencies
Finally we have the dependencies part. A dependency in this context can be defined as: 

_"If Action A has occurred, Action B should/should not be evaluated."_

This definition also adds an important new facet to the previous section: the _order_ of the action 
definitions matter. If we define the above dependency but _Action A_ is defined __after__ _Action B_, then
the dependency has no effect, since actions are evaluated sequentially for each transition and reset when
a new transition is to be evaluated. 

Let us consider an example. In the previous part we defined two actions, the first action was the finger
action and the second considered costs for changing hand positions. While these are two good actions to 
have, they miss an important case: What happens if we switch strings while playing? from a playability 
perspective it makes sense to impose a cost on changing which strings you're playing on. If we then consider
the case of changing string _and_ finger at the _same time_, it makes sense to consider that to be marginally
more costly than _just_ changing finger. So we can define a simple action for the cost of changing strings:

    "String_Action" = "String" - "String" > 0 : 1 (true) ;

Now, when we change strings we increase the transition cost by 1, and when we also switch fingers we increase
the transition cost by 1 as well. 
**However!** if we now consider the case where we switch strings and do _not_ switch
finger: we are only imposing the cost of switching strings while we are doing something that is (from a 
playability perspective) _more_ difficult than changing strings _and_ finger at the same time. (Consider
what it is like to try to switch strings but not finger; you have to move the finger to the new string 
while simultaneously ensuring this happens at the same time as switching the string you are bowing.)
We can solve this problem by adding another action:

    "Finger_String_Action" = "Finger" - "Finger" == 0 : 2 (false) ;

Here check whether we are switching finger when playing, and if we do _not_ switch finger, we impose a cost
of 2. This action has a __default__ condition of **false** however, because we only want this action to 
trigger if we _also_ switch strings. One could also imagine us adding another __condition function__ which 
checks whether we switched strings and finger at the same time, but because we already have an action which 
checks this we can just define a dependency between the actions.

    Actions:
        "String_Action" = "String" - "String" > 0 : 1 (true) ,
        "Finger_String_Action" = "Finger" - "Finger" == 0 : 2 (false) ,
        "Finger_Action" = "Finger" - "Finger" > 0 : 1 (true) ,
        "HP_Action" = "Hand_Position" - "Hand_Position" > 0 : "Hand_Position" - "Hand_Position" + 1 (true) ;

We can now define our dependency.

    Dependencies:
        "String_Action" "Finger_String_Action" true ;

The dependency above states that:

_"If "String_Action" occurred, then "Finger_String_Action" should be evaluated"_

Let us then consider an example of a transition between the two PNRs:

    String = 1, Finger = 2, Hand Position = 1  ----> String = 2, Finger = 2, Hand Position = 1

In this case, the string action is triggered and adds a cost of 1. Then the finger string action is 
evaluated _because_ the dependency changes the __default condition__ to be **true** instead of **false** 
and the __condition function__ evaluates to **true**, which adds 2 to the transition cost. The next two 
actions do not activate as the __condition function__ evaluates to false in both actions. 

Dependencies allow us to formulate simple actions and join them together without having to write long and
tedious __condition function__ sets which repeat the same __condition__ over and over again. A more extreme
example of its use could be if we imagine multiple actions which should all be disabled if the current or 
next "note" was a rest. We would need to check whether both the current and next PNR were equivalent
to the rest "note" in every single action, this would bloat the __distance function__ set and make it a lot 
more difficult to write and read configurations. In this example one could instead just define a rest 
action that checks whether either of the PNRs are rests and applies no cost regardless, and then we define 
dependencies which disable all other actions if the rest action was triggered.

Our final DSL configuration file looks like this:

    Output: int
    Strings:
        1: C_4 -> A_6 ,
        2: C_5 -> Cs_7 ,
        3: G_3 -> C_5 ;
    Attributes:
        (i) "String" ,
        (i) "Finger" ,
        (i) "Hand_Position" ;
    Actions:
        "String_Action" = "String" - "String" > 0 : 1 (true) ,
        "Finger_String_Action" = "Finger" - "Finger" == 0 : 2 (false) ,
        "Finger_Action" = "Finger" - "Finger" > 0 : 1 (true) ,
        "HP_Action" = "Hand_Position" - "Hand_Position" > 0 : "Hand_Position" - "Hand_Position" + 1 (true) ;
    Dependencies:
        "String_Action" "Finger_String_Action" true ;

## Brief Syntax Overview

Below is a list of all variations of __condition__ and __distance__ functions implemented followed by a
brief explanation of the function purpose. For a more concise view, check out the grammar file referenced
in the beginning.

(For verbosity sake I will only type out one of each of the functions and then list replacable parts below)

### Condition Functions

Compare two combined attributes to some number.
    
    "Attr1" + "Attr2" == Number

Compare the Attribute "Attr1" of the _current_ PNR to some number.
    
    this "Attr1" == Number

Compare the Attribute "Attr1" of the _next_ PNR to some number.
    
    to "Attr1" == Number

A direct truth value, either **true** or **false**.
    
    Boolean

Direct truth value taken from a boolean attribute of the _current_ PNR, can not be applied to **integer**
or **double** attribute values.
    
    this "Attr1" 

Direct truth value taken from a boolean attribute of the _next_ PNR, can not be applied to **integer**
or **double** attribute values.
    
    to "Attr1"

### Distance Functions

Combine the values of "Attr1" and "Attr2" and multiply it by some number
    
    "Attr1" + "Attr2" * Number

Combine the values of "Attr1" and "Attr2"
    
    "Attr1" + "Attr2"

Add a constant cost to __distance__
    
    Number

All instances of "==" can be replaced by either of the following: "<" ">" ">=" "<=" "!="\
All instances of "+" can be replaced by "-"\
Number can refer to either an **integer** or a **double**.
