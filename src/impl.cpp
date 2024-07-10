#include "LayerList.cpp"
#include "Action.cpp"
#include "ActionSet.cpp"
#include "LinkException.cpp"
#include "HandPosition.cpp"
#include "Instrument.cpp"
#include "SPSolver.cpp"
#include "TLSSolver.cpp"

//Generation of templated classes possible for outputs.
template class LayerList<int>;
template class LayerList<double>;

template class Action<int>;
template class Action<double>;

template class ActionSet<int>;
template class ActionSet<double>;

template class LinkException<int>;
template class LinkException<double>;

template class HandPosition<int>;
template class HandPosition<double>;

template class Instrument<int>;
template class Instrument<double>;

template class SPSolver<int>;
template class SPSolver<double>;

template class TLSSolver<int>;
template class TLSSolver<double>;
