#ifndef DECISIONNODE_H
#define DECISIONNODE_H

#include "Element.hpp"

using namespace std;

class DecisionNode : public Element {
	public:
		DecisionNode(string);
		string getType();
		string getNodeName();

	private:
		string name;
		bool checkDestinationAvailability();
};

#endif