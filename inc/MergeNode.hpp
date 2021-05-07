#ifndef MERGENODE_H
#define MERGENODE_H

#include "Element.hpp"

using namespace std;

class MergeNode : public Element {
	public:
		MergeNode(string);
		string getType();
		string getNodeName();

	private:
		string name;
		bool checkSourceAvailability() override;
};

#endif