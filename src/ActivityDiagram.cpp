#include "ActivityDiagram.hpp"
#include "StartNode.hpp"
#include "MergeNode.hpp"
#include "FinalNode.hpp"
#include "DecisionNode.hpp"
#include "Activity.hpp"
#include <stdexcept>
#include <iostream>

ActivityDiagram::ActivityDiagram(string name) {
	this->name = name;
}

string ActivityDiagram::getName() {
	return this->name;
}

void ActivityDiagram::addElement(string name, int type) {
	switch(type){
		case 1:
			this->elements.insert(pair<string, Element*>(name, new StartNode(name)));
			break;
		case 2:
			this->elements.insert(pair<string, Element*>(name, new Activity(name)));
			break;
		case 3:
			this->elements.insert(pair<string, Element*>(name, new DecisionNode(name)));
			break;
		case 4:
			this->elements.insert(pair<string, Element*>(name, new MergeNode(name)));
			break;
		case 5:
			this->elements.insert(pair<string, Element*>(name, new FinalNode(name)));
			break;
	}
}

Element* ActivityDiagram::getElement(string name) {
	return this->elements.find(name)->second;
}

void ActivityDiagram::addTransition(string name, string src, string dest) {
	auto srcE = this->elements.find(src)->second;
	auto destE = this->elements.find(dest)->second;
	srcE->addTransition(0);
	destE->addTransition(1);
	this->transitions.insert(pair<string, Transition>(name, Transition(name, src, dest)));
}

Transition ActivityDiagram::getTransition(string name) {
	return this->transitions.find(name)->second;
}

string ActivityDiagram::toXML() {
    std::stringstream strStream;

    strStream << "<ActivityDiagram name=\"" << this->name << "\">" << endl;

    strStream << "\t<ActivityDiagramElements>" << endl;
    for(map<string, Element*>::iterator it=this->elements.begin(); it != this->elements.end(); ++it)
        strStream << it->second->toXML(2) << endl;

    strStream << "\t</ActivityDiagramElements>" << endl;

    strStream << "\t<ActivityDiagramTransitions>" << endl;
    for(map<string, Transition>::iterator it=this->transitions.begin(); it != this->transitions.end(); ++it)
        strStream << it->second.toXML(2) << endl;

    strStream << "\t</ActivityDiagramTransitions>" << endl;

    strStream << "</ActivityDiagram>";

    return strStream.str();
}

int ActivityDiagram::exportXML(){
	std::ofstream out;
	auto xml = this->toXML();
	out.open("ActivityDiagram.xml");
	out << xml;
	out.close();
	return 1;
}
