#include "ActivityDiagram.hpp"

#include <iostream>
#include "Exporter.hpp"
#include <stdexcept>

#include "Activity.hpp"
#include "DecisionNode.hpp"

bool ActivityDiagram::checkName(string name) {
  if (this->elements.find(name) == this->elements.end()) {
    return true;
  } else {
    return false;
  }
}

ActivityDiagram::ActivityDiagram(string name) {
  this->name = name;
  this->hasStart = false;
  this->hasFinal = false;
}

string ActivityDiagram::getName() { return this->name; }

void ActivityDiagram::addElement(StartNode name) {
  bool check = this->checkName(name.getNodeName());
  if (check) {
    if (this->hasStart)
      throw std::invalid_argument("ActivityDiagramRuleException");

    this->elements.insert(pair<string, Element*>(
        name.getNodeName(), new StartNode(name.getNodeName())));
    this->hasStart = true;
  } else {
    throw std::invalid_argument("ActivityDiagramRuleException");
  }
}

void ActivityDiagram::addElement(string name) {
  bool check = this->checkName(name);
  if (check) {
    this->elements.insert(pair<string, Element*>(name, new Activity(name)));

  } else {
    throw std::invalid_argument("ActivityDiagramRuleException");
  }
}

void ActivityDiagram::addElement(DecisionNode name) {
  bool check = this->checkName(name.getNodeName());
  if (check) {
    this->elements.insert(pair<string, Element*>(
        name.getNodeName(), new DecisionNode(name.getNodeName())));

  } else {
    throw std::invalid_argument("ActivityDiagramRuleException");
  }
}

void ActivityDiagram::addElement(MergeNode name) {
  bool check = this->checkName(name.getNodeName());
  if (check) {
    this->elements.insert(pair<string, Element*>(
        name.getNodeName(), new MergeNode(name.getNodeName())));

  } else {
    throw std::invalid_argument("ActivityDiagramRuleException");
  }
}

void ActivityDiagram::addElement(FinalNode name) {
  bool check = this->checkName(name.getNodeName());
  if (check) {
    this->elements.insert(pair<string, Element*>(
        name.getNodeName(), new FinalNode(name.getNodeName())));
    this->hasFinal = true;

  } else {
    throw std::invalid_argument("ActivityDiagramRuleException");
  }
}

Element* ActivityDiagram::getElement(string name) {
  return this->elements.find(name)->second;
}

void ActivityDiagram::addTransition(string name, string src, string dest,
                                    string prob) {
  auto srcE = this->elements.find(src);
  auto destE = this->elements.find(dest);

  if (srcE == this->elements.end() || destE == this->elements.end()) {
    throw std::invalid_argument("ActivityDiagramRuleException");
  }

  srcE->second->addTransition(0);
  destE->second->addTransition(1);
  this->transitions.insert(
      pair<string, Transition>(name, Transition(name, src, dest, prob)));
}

Transition ActivityDiagram::getTransition(string name) {
  return this->transitions.find(name)->second;
}

string ActivityDiagram::toXML() {
  std::stringstream strStream;

  strStream << "<ActivityDiagram name=\"" << this->name << "\">" << endl;

  strStream << "\t<ActivityDiagramElements>" << endl;
  for (map<string, Element*>::iterator it = this->elements.begin();
       it != this->elements.end(); ++it)
    strStream << it->second->toXML(2) << endl;

  strStream << "\t</ActivityDiagramElements>" << endl;

  strStream << "\t<ActivityDiagramTransitions>" << endl;
  for (map<string, Transition>::iterator it = this->transitions.begin();
       it != this->transitions.end(); ++it)
    strStream << it->second.toXML(2) << endl;

  strStream << "\t</ActivityDiagramTransitions>" << endl;

  strStream << "</ActivityDiagram>";

  return strStream.str();
}

bool ActivityDiagram::checkActivities() {
  for (map<string, Element*>::iterator it = this->elements.begin();
       it != this->elements.end(); ++it)
    if (it->second->getType() == "Activity")
      if (((Activity*)it->second)->getDiagram() == NULL) return false;
  return true;
}

void ActivityDiagram::addSequence(SequenceDiagramXML* diagram, string name) {
  Element* e = this->getElement(name);
  if (e->getType() != "Activity")
    throw std::invalid_argument("ActivityDiagramRuleException");

  Activity* activity = (Activity*)e;

  if (activity->getDiagram() == NULL)
    activity->setDiagram(diagram);

  else
    throw std::invalid_argument("ActivityDiagramRuleException");
}

int ActivityDiagram::exportXml(){
	Exporter exporter = Exporter(this);
	return exporter.exportXml();
}
