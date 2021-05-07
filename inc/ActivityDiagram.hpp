#ifndef ACTIVITY_DIAGRAM_H
#define ACTIVITY_DIAGRAM_H

#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include <map>
#include "Element.hpp"
#include "Transition.hpp"
#include "SequenceDiagram.hpp"
#include "StartNode.hpp"
#include "FinalNode.hpp"
#include "MergeNode.hpp"
#include "DecisionNode.hpp"

using namespace std;

class ActivityDiagram {
	public:
		ActivityDiagram(string);
		string getName();
		void addElement(string);
		void addElement(StartNode);
		void addElement(DecisionNode);
		void addElement(MergeNode);
		void addElement(FinalNode);
		void addTransition(string, string, string,string);
		string toXML();
		int validateDiagram();
		Element* getElement(string);
		Transition getTransition(string);
		bool checkName(string);
		void addSequence(SequenceDiagramXML*, string);
		bool checkActivities();
		bool hasStart;
		bool hasFinal;
		int exportXml();
	private:
		string name;
		map<string, Element*> elements;
		map<string, Transition> transitions;

};

#endif