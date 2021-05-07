#ifndef FINALNODE_H
#define FINALNODE_H

#include "Element.hpp"

using namespace std;

class FinalNode : public Element {
	public:
		FinalNode(string);
		string getType();
		string getNodeName();
	protected:
		string name;
		bool checkSourceAvailability() override;
};

#endif