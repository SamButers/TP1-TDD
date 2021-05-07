#include "ActivityDiagram.hpp"
#include "StartNode.hpp"
#include "FinalNode.hpp"
#include "DecisionNode.hpp"
#include "MergeNode.hpp"
#include "Transition.hpp"
#include "Activity.hpp"
#include "SequenceDiagram.hpp"
#include <gtest/gtest.h>
#include <fstream>
#include <ostream>

TEST(ActivityDiagramCreationTest, DiagramCreation) {
	ActivityDiagram diagram("my_diagram");

	EXPECT_EQ("my_diagram", diagram.getName());
}

TEST(ActivityDiagramCreationTest, DiagramCreation2) {
	ActivityDiagram diagram("my_second_diagram");

	EXPECT_EQ("my_second_diagram", diagram.getName());
}

TEST(ActivityDiagramCreationTest, DiagramCreation3) {
	ActivityDiagram diagram("my_last_diagram");

	EXPECT_EQ("my_last_diagram", diagram.getName());
}

TEST(StartNodeCreationTest, StartNodeCreation) {
	StartNode startNode("my_startNode");

	EXPECT_EQ("my_startNode", startNode.getName());
}

TEST(StartNodeCreationTest, StartNodeCreation2) {
	StartNode startNode("my_startNode2");

	EXPECT_EQ("my_startNode2", startNode.getName());
}

TEST(StartNodeCreationTest, StartNodeCreation3) {
	StartNode startNode("my_startNode3");

	EXPECT_EQ("my_startNode3", startNode.getName());
}

TEST(DecisionNodeCreationTest, DecisionNodeCreation) {
	DecisionNode decisionNode("my_decisionNode");

	EXPECT_EQ("my_decisionNode", decisionNode.getName());
}

TEST(DecisionNodeCreationTest, DecisionNodeCreation2) {
	DecisionNode decisionNode("my_decisionNode2");

	EXPECT_EQ("my_decisionNode2", decisionNode.getName());
}

TEST(DecisionNodeCreationTest, DecisionNodeCreation3) {
	DecisionNode decisionNode("my_decisionNode3");

	EXPECT_EQ("my_decisionNode3", decisionNode.getName());
}

TEST(MergeNodeCreationTest, MergeNodeCreation) {
	MergeNode mergeNode("my_mergeNode");

	EXPECT_EQ("my_mergeNode", mergeNode.getName());
}

TEST(MergeNodeCreationTest, MergeNodeCreation2) {
	MergeNode mergeNode("my_mergeNode2");

	EXPECT_EQ("my_mergeNode2", mergeNode.getName());
}

TEST(MergeNodeCreationTest, MergeNodeCreation3) {
	MergeNode mergeNode("my_mergeNode3");

	EXPECT_EQ("my_mergeNode3", mergeNode.getName());
}

TEST(FinalNodeCreationTest, FinalNodeCreation) {
	FinalNode finalNode("final_node");

	EXPECT_EQ("final_node", finalNode.getName());
}

TEST(FinalNodeCreationTest, FinalNodeCreation2) {
	FinalNode finalNode("ln");

	EXPECT_EQ("ln", finalNode.getName());
}

TEST(FinalNodeCreationTest, FinalNodeCreation3) {
	FinalNode finalNode("begone");

	EXPECT_EQ("begone", finalNode.getName());
}

TEST(StartNodeXMLTest, StartNodeXML) {
	StartNode startNode("my_element");

	EXPECT_EQ("<StartNode name=\"my_element\" />", startNode.toXML());
}

TEST(StartNodeXMLTest, StartNodeXML2) {
	StartNode startNode("the_beginning_of_the_end");

	EXPECT_EQ("<StartNode name=\"the_beginning_of_the_end\" />", startNode.toXML());
}

TEST(StartNodeXMLTest, StartNodeXML3) {
	StartNode startNode("wololooo");

	EXPECT_EQ("<StartNode name=\"wololooo\" />", startNode.toXML(0));
}

TEST(DecisionNodeXMLTest, DecisionNodeXML) {
	DecisionNode decisionNode("decision1");

	EXPECT_EQ("<DecisionNode name=\"decision1\" />", decisionNode.toXML());
}

TEST(DecisionNodeXMLTest, DecisionNodeXML2) {
	DecisionNode decisionNode("precise_decision");

	EXPECT_EQ("<DecisionNode name=\"precise_decision\" />", decisionNode.toXML());
}

TEST(DecisionNodeXMLTest, DecisionNodeXML3) {
	DecisionNode decisionNode("hairy_decision");

	EXPECT_EQ("<DecisionNode name=\"hairy_decision\" />", decisionNode.toXML());
}

TEST(MergeNodeXMLTest, MergeNodeXML) {
	MergeNode mergeNode("messy_merge");

	EXPECT_EQ("<MergeNode name=\"messy_merge\" />", mergeNode.toXML());
}

TEST(MergeNodeXMLTest, MergeNodeXML2) {
	MergeNode mergeNode("git_merge_master");

	EXPECT_EQ("<MergeNode name=\"git_merge_master\" />", mergeNode.toXML());
}

TEST(MergeNodeXMLTest, MergeNodeXML3) {
	MergeNode mergeNode("merging");

	EXPECT_EQ("<MergeNode name=\"merging\" />", mergeNode.toXML());
}

TEST(FinalNodeXMLTest, FinalNodeXML) {
	FinalNode finalNode("final_node");

	EXPECT_EQ("<FinalNode name=\"final_node\" />", finalNode.toXML());
}

TEST(FinalNodeXMLTest, FinalNodeXML2) {
	FinalNode finalNode("the_end_of_the_beginning");

	EXPECT_EQ("<FinalNode name=\"the_end_of_the_beginning\" />", finalNode.toXML());
}

TEST(FinalNodeXMLTest, FinalNodeXML3) {
	FinalNode finalNode("third_time_is_the_charm");

	EXPECT_EQ("<FinalNode name=\"third_time_is_the_charm\" />", finalNode.toXML());
}

TEST(ElementExceptionTest, StartNodeException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);

	try {
		diagram.addTransition("faulty_transition", "activity1", "start","0.5");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, MergeNodeException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);
	diagram.addElement("merge1", 4);
	diagram.addElement("activity2", 2);
	diagram.addElement("activity3", 2);

	diagram.addTransition("transition1", "start", "activity1","0.5");
	diagram.addTransition("transition2", "activity1", "merge1","0.5");
	diagram.addTransition("transition3", "merge1", "activity2","0.5");

	try {
		diagram.addTransition("faulty_transition", "merge1", "activity3","0.5");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, FinalNodeException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("final", 5);
	diagram.addElement("activity1", 2);

	diagram.addTransition("transition1", "start", "final","0.5");

	try {
		diagram.addTransition("faulty_transition", "final", "activity1","0.5");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, FinalNodeExportException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);

	diagram.addTransition("transition1", "start", "activity1","0.5");

	try {
		diagram.exportXml();
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, StartNodeCreationException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);

	diagram.addTransition("transition1", "start", "activity1","0.5");

	try {
		diagram.addElement("start_again",1);
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, StartNodeExportException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("activity1", 2);
	diagram.addElement("final",5);
	diagram.addTransition("transition1", "activity1", "final","0.5");

	try {
		diagram.exportXml();
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, ElementNameException) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);
	diagram.addElement("final",5);
	diagram.addTransition("transition1", "activity1", "final","0.5");

	try {
		diagram.addElement("activity1",2);
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, ElementNameException2) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);
	diagram.addElement("final",5);
	diagram.addTransition("transition1", "activity1", "final","0.5");

	try {
		diagram.addElement("final",2);
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, ElementNameException3) {
	ActivityDiagram diagram("test_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);
	diagram.addElement("final",5);
	diagram.addTransition("transition1", "activity1", "final","0.5");

	try {
		diagram.addElement("start",2);
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, ElementSequenceAdditionException) {
	ActivityDiagram diagram("my_diagram");
	SequenceDiagramXML my_sequence;
	SequenceDiagramXML my_sequence2;

	diagram.addElement("my_activity", 2);

	diagram.addSequence(&my_sequence, "my_activity");

	try {
		diagram.addSequence(&my_sequence2, "my_activity");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(ElementExceptionTest, ElementSequenceAdditionException2) {
	ActivityDiagram diagram("diagram");
	SequenceDiagramXML sequence;

	diagram.addElement("start_node", 1);

	try {
		diagram.addSequence(&sequence, "start_node");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(TransitionExceptionTest, DiagramTransitionAdditionException) {
	ActivityDiagram diagram("my_diagram");
	
	try {
		diagram.addTransition("my_transition", "my_src","my_dest","0.5");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(TransitionExceptionTest, DiagramTransitionAdditionException2) {
	ActivityDiagram diagram("my_diagram2");

	try {
		diagram.addTransition("my_transition2", "my_src2","my_dest2","0.5");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(DiagramTransitionAdditionTest, DiagramTransitionAdditionException3) {
	ActivityDiagram diagram("my_diagram3");

	try {
		diagram.addTransition("my_transition3", "my_src3","my_dest3","0.5");
		FAIL();
	} catch(std::invalid_argument &e) {
		EXPECT_STREQ("ActivityDiagramRuleException", e.what());
	}
}

TEST(TransitionCreationTest, TransitionCreation) {
	Transition transition("my_transition", "my_src_element","my_dest_element","0.5");

	EXPECT_EQ("my_transition", transition.getName());
	EXPECT_EQ("my_src_element", transition.getSrc());
	EXPECT_EQ("my_dest_element", transition.getDest());
}

TEST(TransitionCreationTest, TransitionCreation2) {
	Transition transition("my_transition2", "my_src_element2","my_dest_element2","0.5");

	EXPECT_EQ("my_transition2", transition.getName());
	EXPECT_EQ("my_src_element2", transition.getSrc());
	EXPECT_EQ("my_dest_element2", transition.getDest());
}

TEST(TransitionCreationTest, TransitionCreation3) {
	Transition transition("my_transition3", "my_src_element3","my_dest_element3","0.5");

	EXPECT_EQ("my_transition3", transition.getName());
	EXPECT_EQ("my_src_element3", transition.getSrc());
	EXPECT_EQ("my_dest_element3", transition.getDest());
}

TEST(TransitionXMLTest, TransitionXML) {
	Transition transition("my_transition", "my_src_element","my_dest_element","0.5");

	EXPECT_EQ("<Transition name=\"my_transition\" src=\"my_src_element\" dest=\"my_dest_element\" prob=\"0.5\" />", transition.toXML(0));
}

TEST(TransitionXMLTest, TransitionXML2) {
	Transition transition("my_transition2", "my_src_element2","my_dest_element2","0.5");

	EXPECT_EQ("<Transition name=\"my_transition2\" src=\"my_src_element2\" dest=\"my_dest_element2\" prob=\"0.5\" />", transition.toXML(0));
}

TEST(TransitionXMLTest, TransitionXML3) {
	Transition transition("my_transition3", "my_src_element3","my_dest_element3","0.5");

	EXPECT_EQ("<Transition name=\"my_transition3\" src=\"my_src_element3\" dest=\"my_dest_element3\" prob=\"0.5\" />", transition.toXML(0));
}

TEST(DiagramElementAdditionTest, DiagramElementAddition) {
	ActivityDiagram diagram("my_diagram");
	diagram.addElement("start", 1);

	Element *element = diagram.getElement("start");

	EXPECT_EQ("start", element->getName());
}

TEST(DiagramElementAdditionTest, DiagramElementAddition2) {
	ActivityDiagram diagram("my_diagram");
	diagram.addElement("start", 1);
	diagram.addElement("activity", 3);

	Element *element = diagram.getElement("activity");

	EXPECT_EQ("activity", element->getName());
}

TEST(DiagramElementAdditionTest, DiagramElementAddition3) {
	ActivityDiagram diagram("my_diagram");
	diagram.addElement("merge", 4);

	Element *element = diagram.getElement("merge");

	EXPECT_EQ("merge", element->getName());
}

TEST(DiagramTransitionAdditionTest, DiagramTransitionAddition) {
	ActivityDiagram diagram("my_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("final", 5);

	diagram.addTransition("my_transition", "start", "final","0.5");

	Transition transition = diagram.getTransition("my_transition");

	EXPECT_EQ("my_transition", transition.getName());
	EXPECT_EQ("start", transition.getSrc());
	EXPECT_EQ("final", transition.getDest());
}

TEST(DiagramTransitionAdditionTest, DiagramTransitionAddition2) {
	ActivityDiagram diagram("my_diagram2");

	diagram.addElement("start", 1);
	diagram.addElement("activity", 2);
	diagram.addElement("final", 5);

	diagram.addTransition("my_transition", "start", "activity","0.5");
	diagram.addTransition("my_transition2", "activity", "final","0.5");

	Transition transition = diagram.getTransition("my_transition");
	Transition transition2 = diagram.getTransition("my_transition2");

	EXPECT_EQ("my_transition", transition.getName());
	EXPECT_EQ("start", transition.getSrc());
	EXPECT_EQ("activity", transition.getDest());

	EXPECT_EQ("my_transition2", transition2.getName());
	EXPECT_EQ("activity", transition2.getSrc());
	EXPECT_EQ("final", transition2.getDest());
}

TEST(DiagramTransitionAdditionTest, DiagramTransitionAddition3) {
	ActivityDiagram diagram("my_diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity", 2);
	diagram.addElement("merge", 4);
	diagram.addElement("final", 5);

	diagram.addTransition("my_transition", "activity", "merge","0.5");

	Transition transition = diagram.getTransition("my_transition");

	EXPECT_EQ("my_transition", transition.getName());
	EXPECT_EQ("activity", transition.getSrc());
	EXPECT_EQ("merge", transition.getDest());
}

TEST(DiagramXMLTest, DiagramXML) {
	ActivityDiagram diagram("diagrama_mio");

	diagram.addElement("partida", 1);
	diagram.addElement("finale", 5);

	diagram.addTransition("transition1", "partida", "finale","0.5");

	EXPECT_EQ("<ActivityDiagram name=\"diagrama_mio\">\n\t<ActivityDiagramElements>\n\t\t<FinalNode name=\"finale\" />\n\t\t<StartNode name=\"partida\" />\n\t</ActivityDiagramElements>\n\t<ActivityDiagramTransitions>\n\t\t<Transition name=\"transition1\" src=\"partida\" dest=\"finale\" prob=\"0.5\" />\n\t</ActivityDiagramTransitions>\n</ActivityDiagram>",
			  diagram.toXML()
			 );
}

TEST(DiagramXMLTest, DiagramXML2) {
	ActivityDiagram diagram("diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);
	diagram.addElement("end", 5);

	diagram.addTransition("transition1", "start", "activity1","0.5");
	diagram.addTransition("transition2", "activity1", "end","0.5");

	EXPECT_EQ("<ActivityDiagram name=\"diagram\">\n\t<ActivityDiagramElements>\n\t\t<Activity name=\"activity1\" />\n\t\t<FinalNode name=\"end\" />\n\t\t<StartNode name=\"start\" />\n\t</ActivityDiagramElements>\n\t<ActivityDiagramTransitions>\n\t\t<Transition name=\"transition1\" src=\"start\" dest=\"activity1\" prob=\"0.5\" />\n\t\t<Transition name=\"transition2\" src=\"activity1\" dest=\"end\" prob=\"0.5\" />\n\t</ActivityDiagramTransitions>\n</ActivityDiagram>",
			  diagram.toXML()
			 );
}

TEST(DiagramXMLTest, DiagramXML3) {
	ActivityDiagram diagram("diagram");

	diagram.addElement("start", 1);
	diagram.addElement("activity1", 2);
	diagram.addElement("activity2",2);
	diagram.addElement("end", 5);

	diagram.addTransition("transition1", "start", "activity1","0.5");
	diagram.addTransition("transition2", "activity1", "activity2","0.5");

	EXPECT_EQ("<ActivityDiagram name=\"diagram\">\n\t<ActivityDiagramElements>\n\t\t<Activity name=\"activity1\" />\n\t\t<Activity name=\"activity2\" />\n\t\t<FinalNode name=\"end\" />\n\t\t<StartNode name=\"start\" />\n\t</ActivityDiagramElements>\n\t<ActivityDiagramTransitions>\n\t\t<Transition name=\"transition1\" src=\"start\" dest=\"activity1\" prob=\"0.5\" />\n\t\t<Transition name=\"transition2\" src=\"activity1\" dest=\"activity2\" prob=\"0.5\" />\n\t</ActivityDiagramTransitions>\n</ActivityDiagram>",
			  diagram.toXML()
			 );
}

TEST(DiagramExportXMLTest, DiagramExportXML) {
	std::ifstream in;
	ActivityDiagram diagram("diagrama_mio");

	diagram.addElement("partida", 1);
	diagram.addElement("finale", 5);

	diagram.addTransition("transition1", "partida", "finale","0.5");

	diagram.exportXml();

	in.open("ActivityDiagram.xml");
	auto ss = ostringstream{};
	ss << in.rdbuf();
	
	EXPECT_EQ("<ActivityDiagram name=\"diagrama_mio\">\n\t<ActivityDiagramElements>\n\t\t<FinalNode name=\"finale\" />\n\t\t<StartNode name=\"partida\" />\n\t</ActivityDiagramElements>\n\t<ActivityDiagramTransitions>\n\t\t<Transition name=\"transition1\" src=\"partida\" dest=\"finale\" prob=\"0.5\" />\n\t</ActivityDiagramTransitions>\n</ActivityDiagram>",
			  ss.str()
			 );
}

TEST(DiagramSequenceAdditionTest, DiagramSequenceAddition) {
	ActivityDiagram diagram("diagrama_mio");
	SequenceDiagramXML sequence;

	diagram.addElement("partida", 1);
	diagram.addElement("activity", 2);
	diagram.addElement("finale", 5);

	diagram.addSequence(&sequence, "activity");

	Activity *activity = (Activity*) diagram.getElement("activity");
	
	EXPECT_EQ(&sequence, activity->getDiagram());
}

TEST(DiagramSequenceAdditionTest, DiagramSequenceAddition2) {
	ActivityDiagram diagram("diagram");
	SequenceDiagramXML sequence;
	SequenceDiagramXML sequence2;

	diagram.addElement("partida", 1);
	diagram.addElement("activity", 2);
	diagram.addElement("activity2", 2);
	diagram.addElement("finale", 5);

	diagram.addSequence(&sequence, "activity");
	diagram.addSequence(&sequence2, "activity2");

	Activity *activity = (Activity*) diagram.getElement("activity");
	Activity *activity2 = (Activity*) diagram.getElement("activity2");
	
	EXPECT_EQ(&sequence, activity->getDiagram());
	EXPECT_EQ(&sequence2, activity2->getDiagram());
}

TEST(DiagramSequenceAdditionTest, DiagramSequenceAddition3) {
	ActivityDiagram diagram("my_diagram");
	SequenceDiagramXML my_sequence;

	diagram.addElement("my_activity", 2);

	diagram.addSequence(&my_sequence, "my_activity");

	Activity *my_activity = (Activity*) diagram.getElement("my_activity");
	
	EXPECT_EQ(&my_sequence, my_activity->getDiagram());
}

TEST(DiagramActivitySequenceCheckTest, DiagramActivitySequenceCheck) {
	ActivityDiagram diagram("my_diagram");
	SequenceDiagramXML my_sequence;

	diagram.addElement("my_activity", 2);

	diagram.addSequence(&my_sequence, "my_activity");
	
	EXPECT_EQ(true, diagram.checkActivities());
}

TEST(DiagramActivitySequenceCheckTest, DiagramActivitySequenceCheck2) {
	ActivityDiagram diagram("diagram");
	SequenceDiagramXML sequence;

	diagram.addElement("partida", 1);
	diagram.addElement("activity", 2);
	diagram.addElement("activity2", 2);
	diagram.addElement("finale", 5);

	diagram.addSequence(&sequence, "activity");
	
	EXPECT_EQ(false, diagram.checkActivities());
}

TEST(DiagramActivitySequenceCheckTest, DiagramActivitySequenceCheck3) {
	ActivityDiagram diagram("diagrama_mio");
	SequenceDiagramXML sequence;

	diagram.addElement("partida", 1);
	diagram.addElement("activity", 2);
	diagram.addElement("finale", 5);
	
	EXPECT_EQ(false, diagram.checkActivities());

	diagram.addSequence(&sequence, "activity");

	EXPECT_EQ(true, diagram.checkActivities());
}