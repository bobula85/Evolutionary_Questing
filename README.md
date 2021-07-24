# Evolutionary_Questing

Dynamic quest generation system which uses evolutionary mechanisms.

Based on research carried out by Jonathon Doran and Ian Parberry this project aims to use evolutionary mechanisms to procedurally generate quests for rpg games.
The system, using the research mentioned above, breaks down quests into elements and uses these elements as genes in a genetic algorithm.
These genes are then combined, based on player quest completion stats, to create new child quests which are utilized within UE4 to create in game quests

There are areas of discussion based around system set up, such as population configuration, which are necessary but that i will not be discussed here. This information is available
in the report attached to this repo so view/read it at your pleasure. 

The quests generation system is broken down into 5 distinct sections, Evaluation, Selection, Crossover, Mutation and Survival Selection which are listed and explained below:

Evaluation:
This is where each quest is assessed for it's fitness based on player quest completion stats

Selection:
This section selects parent quests which will be used to create the proceeding generation of quests

Crossover:
This section of the algorithm dictates which parts of the parent quests will be used in the creation of the child solutions

Mutation:
this sections of the algorithm is used to reintroduce lost genetic material into the population. this avoids the local optima problem discussed in the attached report

Survival Selection:
This function selects the quests that will make up the next generation of the quest population

There are many ways to modify the functionality of this algorithm, some of which  are discussed in the report that accompanies this project, and there are many ways to 
expand on this work (also discussed in report that accompanies this project)
