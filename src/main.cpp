#include <iostream>
#include <string>
#include "ActivityDiagram.hpp"
#include "SequenceDiagram.hpp"

using namespace std;

ActivityDiagram cria_diagrama_atividade();
SequenceDiagramXML cria_diagrama_sequencia();

int main() {
  ActivityDiagram activity_diagram = cria_diagrama_atividade();
  SequenceDiagramXML sequence_diagram = cria_diagrama_sequencia();

  activity_diagram.addSequence(&sequence_diagram, "nome da atividade");

  activity_diagram.exportXml();

	return 0;
}

ActivityDiagram cria_diagrama_atividade(){
	string diagramName = "nome do diagrama";
	string startNode = "nome do nodo inicial";
	string activityNode = "nome da atividade";
	string decisionNode = "nome do nodo de decisao";
	string mergeNode = "nome do nodo de fusao";
	string finalNode = "nomde do nodo final";

	ActivityDiagram diagram(diagramName);
	diagram.addElement(startNode,1);
	diagram.addElement(activityNode,2);
	diagram.addElement(decisionNode,3);
	diagram.addElement(mergeNode,4);
	diagram.addElement(finalNode,5);

	diagram.addTransition("nome da transicao",startNode,activityNode,"valor de probabilidade");
	diagram.addTransition("nome da transicao2",activityNode,decisionNode,"valor de probabilidade");

  return diagram;
}

SequenceDiagramXML cria_diagrama_sequencia(){
  SequenceDiagramXML diagram;
  SequenceDiagramXML::SequenceDiagram * seq_sys_iden = new SequenceDiagramXML::SequenceDiagram("System identifies situation");
  SequenceDiagramXML::SequenceDiagram * seq_sql_pers = new SequenceDiagramXML::SequenceDiagram("SQLite Persistence");
  SequenceDiagramXML::SequenceDiagram * seq_memory_p = new SequenceDiagramXML::SequenceDiagram("Memory Persistence");

  seq_sys_iden->addLifelines("Bus");
  seq_sys_iden->addLifelines("Oxygenation");
  seq_sys_iden->addLifelines("Persistence");
  seq_sys_iden->addLifelines("SQLite");
  seq_sys_iden->addLifelines("Memory");

  seq_sql_pers->addLifelines("Persistence");
  seq_sql_pers->addLifelines("SQLite");
  seq_sql_pers->addLifelines("Memory");

  seq_memory_p->addLifelines("Persistence");
  seq_memory_p->addLifelines("SQLite");
  seq_memory_p->addLifelines("Memory");

  diagram.addDiagram(seq_sys_iden);
  diagram.addDiagram(seq_sql_pers);
  diagram.addDiagram(seq_memory_p);


  SequenceDiagramXML::Message message1("register");
  SequenceDiagramXML::Message message2("replyRegister");
  SequenceDiagramXML::Message message3("sendSituation");
  SequenceDiagramXML::Message message4("persist");
  SequenceDiagramXML::Message message5("persist");
  SequenceDiagramXML::Message message6("replyPersist");
  SequenceDiagramXML::Message message7("persist");
  SequenceDiagramXML::Message message8("replyPersist");
  SequenceDiagramXML::Message message9("replyPersist");
  SequenceDiagramXML::Message message10("replySendSituation(Oxygenation)");

  message1.setOrig(diagram, "Oxygenation");
  message1.setDest(diagram, "Bus");
  message1.setProb(0.999);

  message2.setOrig(diagram, "Bus");
  message2.setDest(diagram, "Oxygenation");
  message2.setProb(0.999);

  message3.setOrig(diagram, "Bus");
  message3.setDest(diagram, "Oxygenation");
  message3.setProb(0.999);

  message4.setOrig(diagram, "Oxygenation");
  message4.setDest(diagram, "Persistence");
  message4.setProb(0.999);

  message5.setOrig(diagram, "Persistence");
  message5.setDest(diagram, "SQLite");
  message5.setProb(0.999);

  message6.setOrig(diagram, "SQLite");
  message6.setDest(diagram, "Persistence");
  message6.setProb(0.999);
  
  message7.setOrig(diagram, "Persistence");
  message7.setDest(diagram, "Memory");
  message7.setProb(0.999);

  message8.setOrig(diagram, "Memory");
  message8.setDest(diagram, "Persistence");
  message8.setProb(0.999);

  message9.setOrig(diagram, "Persistence");
  message9.setDest(diagram, "Oxygenation");
  message9.setProb(0.999);

  message10.setOrig(diagram, "Oxygenation");
  message10.setDest(diagram, "Bus");
  message10.setProb(0.999);

  SequenceDiagramXML::Fragment frag("[SQLite]");
  SequenceDiagramXML::Fragment frag1("[Memory]");

  frag.setSeqDiagram(diagram, "SQLite Persistence");
  frag1.setSeqDiagram(diagram, "Memory Persistence");

  seq_sys_iden->addMessage(message1);
  seq_sys_iden->addMessage(message2);
  seq_sys_iden->addMessage(message3);
  seq_sys_iden->addMessage(message4);
  seq_sys_iden->addMessage(message9);
  seq_sys_iden->addMessage(message10);

  seq_sql_pers->addMessage(message5);
  seq_sql_pers->addMessage(message6);

  seq_memory_p->addMessage(message7);
  seq_memory_p->addMessage(message8);

  seq_sys_iden->addFragment(frag);
  seq_sys_iden->addFragment(frag1);

  diagram.exportXML();

  return diagram;
}
