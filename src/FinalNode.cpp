#include "FinalNode.hpp"

FinalNode::FinalNode(string name) : Element(name) {this->name = name;}

string FinalNode::getNodeName() {
	return this->name;
}

bool FinalNode::checkSourceAvailability(){
	return false;
}

string FinalNode::getType() {
	return "FinalNode";
}

