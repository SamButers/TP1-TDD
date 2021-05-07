#include "DecisionNode.hpp"

DecisionNode::DecisionNode(string name) : Element(name) {this->name = name;}

string DecisionNode::getType() {
	return "DecisionNode";
} 

string DecisionNode::getNodeName() {
	return this->name;
}

bool DecisionNode::checkDestinationAvailability() {
	if(this->destinationTransitions)
		return false;
	return true;
}