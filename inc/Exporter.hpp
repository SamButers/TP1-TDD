#ifndef EXPORTER_H
#define EXPORTER_H

#include <string>
#include <ostream>
#include <sstream>
#include <fstream>
#include "ActivityDiagram.hpp"
#include "SequenceDiagram.hpp"

using namespace std;

class Exporter {
	public:
		Exporter(ActivityDiagram *);
		int exportXml();

	private:
	ActivityDiagram * origem;

};

#endif
