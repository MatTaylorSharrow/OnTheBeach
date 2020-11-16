# OnTheBeach
Repo for OnTheBeach interview


Development Log for On The Beach programming test
-------------------------------------------------

Sunday 15th November - 11:40am

- Ok, Lets get cracking.  Re-read spec.
- So we'll create a method to accept the data structure as a string. Therefore, we'll need to parse the string into something more usable. The output should be string or a collection. Well if we return a collection, the conversion to a string would be trivial. So signature will be something like:

```
collection doSort(string);

print doSort("
   a =>
   b => c
   c => f
   d => a
   e => b
   f =>
").toString();

```
- So the input strings looks like an adjacenty list representation, which would imply we have some sort of graph data structure.
- We have dependencies between the nodes of the graph so it's a directed graph.
- The spec says there can't be circular dependancies so, or it's acyclic, so we're dealing with a directed acyclic graph or DAG.

- Ok so we need to sort a DAG, hmmm ...
- DuckDuckGO search "c++ sort with dependancies"
- first result https://stackoverflow.com/questions/40721470/using-stdsort-to-sort-dependency-tre
  - a comment mentions topological sort with link to wiki page.
- 12 Noon.  Bingo, it seems we need to implement a topological sort.

- hmm, does the STL have a topological sort algorithm?
  - Checks cppreference.com - nope.
- hmm well then what about boost? https://www.boost.org/doc/libs/1_74_0/
  - Boost Graphy library sounds promising.
  - Bingo. Topological sort algorithm.

- So lets see if we can get an example up and running. 
- Found an example, created a c++ project, pasted it in. Building fails. Ok, lets get it working.
- 12:40pm - Have got an example but problem with constructing the graph 
- The manual says there are other ways to construct the graph object https://www.boost.org/doc/libs/1_74_0/libs/graph/doc/adjacency_list.html#sec:iterator-constructor
- Nice, that works
- I've commented out the last error and the example builds and runs but no output as I've just commented out the bit that does the output! Back to the manual.
- Ok other examples use an IndexMap and access a variable index as an array. Let's give it a try
- Bingo. We have a working example.
- So, do the results give us the correct answer? Results are 2 5 0 1 4 3
  - Let's draw the graph (see code for annotations)
  - So the rusult "2 5 0 1 4 3" gives us "C F A B E D"
  - A is before B and D. tick.
  - B is after A but before E. tick
  - C is before F and E. tick.
  - D is after A and E. tick.
  - E is after B and C but before D. tick.
  - F is after C. tick
- Ok looks like the example has been sorted successfully.
- 13:10pm - Now let's try one of the examples from the programming task.
 - We get the result:  4 3 1 2 5 0
 - So the result "4 3 1 2 5 0" maps to vertices/nodes "E D B C F A".  Is this correct?
 - A is after D. tick
 - B is after E but before C. tick.
 - C is after B but before F. tick
 - D is before A. tick.
 - E is before B. tick.
 - F is after C. tick.
- OK looks like this will work for us. We'll need to do some mapping from vertex to index and put it into a containing structure but it could work.

- 13:34pm Time for brew.

- 14:00pm Back to it then.  Got caught watching Monty Don looking at gardens in Cuba on the TV!

- So let's create a real project to solve the problem posed in the test along with some automated testing, and the conversions from adjacently list string representation to the list of edges.  If we are to unit test in C++, we'll have to move the core of the code into a library so it can be called from the test runner. So there will also need to be a simple shell program for running the sort, maybe we can make that into something useful like the unix tsort program.

- I'm using QtCreator IDE, but as I'm already using Boost for the Graph library, I'll use Boost::Test to do the unit testing also, rather than QtTest.  Reduce the dependancies.

- Ok so let's start by defining a method signature and some tests for cases from the examples on the programming test sheet

- Had a fight with QtCreator IDE and CMake. Had to create a master project for the unit tests to find the library code successfull and execute.

- 17:00 - Stopped for food

- 18:00 - Commited project structure changes

- 19:00 Forced to spend time with the boss - Watched Les Miserables (TV), followed by Wolf Hall, Dinner, Bed
 

Monday 16th November - 11:00am
- So, let's define those tests.
  - Created a test for each example from the programming test sheet. These will serve as our user acceptance tests.

- Now let's start to implement the functions and turn the red tests to green tests.
  - Added the code for checking for empty strings and returned empty string.  First test passes.
  - Removed dummy test for 'true'
  - Added comments for algorithm to parse the adjaceny list structure and generate the pre-requisites for the sorting algorithm


