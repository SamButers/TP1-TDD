#include "Exporter.hpp"

Exporter::Exporter(ActivityDiagram* diagram){
    this->origem = diagram;
}

int Exporter::exportXml(){
	if(this->origem->hasFinal && this->origem->hasStart && this->origem->checkActivities()){
		std::ofstream out;
		auto xml = this->origem->toXML();
		out.open("ActivityDiagram.xml");
		out << xml;
		out.close();
		return 1;
	} else {
		throw std::invalid_argument("ActivityDiagramRuleException");
	}
}
