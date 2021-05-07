#include "MergeNode.hpp"

MergeNode::MergeNode(string name) : Element(name) {this->name = name;}

string MergeNode::getNodeName() {
	return this->name;
}

string MergeNode::getType() {
	return "MergeNode";
} 

bool MergeNode::checkSourceAvailability() {
	if(this->sourceTransitions)
		return false;
	return true;
}