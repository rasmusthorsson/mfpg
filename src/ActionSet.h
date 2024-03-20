#ifndef ACTION_SET_H_MFPG
#define ACTION_SET_H_MFPG

#include "Action.h"

#include <map>
#include <algorithm>
#include <vector>

//Class for a set of actions to be considered when calculating the transition between
//two states, each action is considered individually for the state transition but 
//is only executed if there are no dependencies preventing it from doing so (as 
//defined by the user).
template <OutputViable OutputValue> class ActionSet {
	typedef OutputValue (distfun) (PhysAttrMap, PhysAttrMap);
	typedef bool (condfun) (PhysAttrMap, PhysAttrMap);
	private:
		//Actions with their respective default running configuration, 
		//false = do not run by default, true = run by default.
		std::vector<std::tuple<Action<OutputValue>, bool>> actions;
		//Multimap of dependencies, the key is the dependent, the values
		//are the dependency actions with the boolean adjustment as a tuple.
		//For Example: "action1", {"action2", true} means that if action2 
		//occurred then action1 should occur.
		std::multimap<std::string, std::tuple<std::string, bool>> dependencies;
		//Check whether an action is to be taken or not with respect to the
		//dependencies in the dependencies multimap, the default action in the 
		//action set, and with the previous actions already taken.
		bool checkAction(std::string, bool, std::vector<std::string>&) const; 
		//Checks whether a specific action is part of the actionset via ID.
		bool checkUnique(const Action<OutputValue>&);
	public:
		ActionSet();
		ActionSet(std::vector<std::tuple<Action<OutputValue>, bool>>);
		ActionSet(Action<OutputValue>, bool);
		ActionSet(std::initializer_list<std::tuple<Action<OutputValue>, bool>>);
		~ActionSet();
		
		void addAction(Action<OutputValue>, bool);
		//Attempts to make a new action and add it to the actionsset, returns -1 if duplicate of 
		//already existing action.
		int makeAction(condfun, distfun, std::string, bool);
		//Adds a condition function to an action.
		void addCondToAction(condfun, std::string);
		//Adds a distance function to an action.
		void addDistToAction(distfun, std::string);
		//Adds a dependency, if dependent then dependency is subjected to adjustment. returns
		//-1 on failure to insert.
		int addDependency(std::string, std::string, bool); 
		//Applies the actionset to two tuples; n1 to n2.
		OutputValue apply(const PhysAttrMap&, const PhysAttrMap&) const;
};
#endif
