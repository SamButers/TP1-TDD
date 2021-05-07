#include "StartNode.hpp"

StartNode::StartNode(string name) : Element(name) {this->name = name;}

string StartNode::getType() {
	return "StartNode";
}
string StartNode::getNodeName() {
	return this->name;
}

bool StartNode::checkDestinationAvailability() {
	return false;
}

bool StartNode::checkSourceAvailability() {
	if(this->sourceTransitions == 0) {
		return true;
	} else {
		return false;	
	}
}