#ifndef STARTNODE_H
#define STARTNODE_H

#include "Element.hpp"

using namespace std;

class StartNode : public Element {
	public:
		StartNode(string);
		string getType();
		string getNodeName();
	protected:
		string name;
		bool checkSourceAvailability() override;
		bool checkDestinationAvailability() override;
};

#endif