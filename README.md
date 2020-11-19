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
- The spec says there can't be circular dependencies so, or it's acyclic, so we're dealing with a directed acyclic graph or DAG.

- Ok so we need to sort a DAG, hmmm ...
- DuckDuckGO search "c++ sort with dependencies"
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

- I'm using QtCreator IDE, but as I'm already using Boost for the Graph library, I'll use Boost::Test to do the unit testing also, rather than QtTest.  Reduce the dependencies.

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
  - Changed sort_jobs from static to member method. So I can call private members for parsing and then sorting.
  - Created signatures for private methods for parsing the adj list structure and for performing the sort
  - copied prototype code from boost example to topological sort method, changing the the creation of the Edges array and replacing the hard coded 6 as the number of vertices.
  - implemented the code for mapping the sort results back to symbols.
  - moved psuedocode comments on how to parse input string to new private method.
  - added dummy return value from string parsing method.
  - commented out error tests as error handling not considered yet.
  - still only 1 test passing.

Tuesday 17th November - 12:00
- Continuing after numerous interuptions
- Implemented the method to parse the adjacency list string
- mapped output values to back to their symbol equivalents
- tests failing due to thrown logic exception - due to bug in parser
- tests failing due to input to tests not containing newlines - fixed by using the c++ multiline string format eg: R"TAG( string goes here  )TAG"
- tests TestSingleDependancy and TestMultiDependancy failing due to results are being returned in reverse order - fixed by changing results vector to be populated by forward iterator not reverse iterator as from the boost example.
- test TestSingleJob failing due to extra whitespace at end of output - fixed by using boost::algorithm::join()

- 16:43 All tests pass now. TestCircularReferenceError passes but it shouldn't there must be a bug in there somewhere.  No circular reference checking has been implemented yet.
- commiting to show progress.

- So, this code 'works' but is just a first draft really.  There are still many issues :
  - The parsing method is ugly and needs to work to pretty it up. #RefactorWithTests
    - Some of the loops should be cut out to private methods
    - There is possibly some unnescessary work happening within the main parsing loop
    - The spec doesn't define a job 'label' in terms of length, so I've assumed they could be strings eg "payment => work_completed".
    - The spec neither confirms or denys the possibility of the format having multiple levels eg : "payment => work_completed => parts_arrived => parts_ordered".  I initially was going to implement the parsing of this which is why the current method is a little ugly.  However, this may become useful for implementing the circular refernce checking.  Wheat we could do is link the depenancies together eg:

```a => b
b => c
c

could become

a => b => c
```

  - Circular references are as yet unimplemented - boost graph could also possible help here.
  - Error handling & exception safety requires a review
  - As we've made the code a library, we should really sanitise and validate any data coming across the API boundary to ensure we operate on safe data.
  - The current tests are really only user acceptance tests.  We should be able break some of the components apart and unit test them individually
  - An then there is the biggie, the sorting is implemented using library code, perhaps On The Beach want to see it implemented by hand !!!!!!!!!!!!!!!!!!!!

Wednesday 17th November - 14:00
- On investigation, the circular reference test is passing because the boost graph library is throwing an exception when trying to perform a topological sort using a graph with a cycle. It is throwing the boost::not_a_dag exception.
- I've updated the test so that it passes when catching the boost::not_a_dag exception.
- Now then, to detect the circular reference in the graph structure we need to perform a depth first search. 
  - The boost graph manual has an example of performing the depth first search with a visitor to detect cyclic references 
    - "Cyclic Dependencies" at the bottom of https://www.boost.org/doc/libs/1_74_0/libs/graph/doc/file_dependency_example.html
  - However, the topological sort algorithm performs a depth first seach anyway, and throws the exception
  - So is there any point doing the DFS (depth first search) prior to topological_sort just to catch throw the exception for cyclic dependencies?
    - I don't think there is
    - But we can perhaps catch and rethrow with extra information / nicer message.
- So let's implement better exception handling for the OTBLibrary


Thursday 18th November - 14:00
- Define an exception signature for the OTBLibrary, the we can modify tests to use it then we can implement the throwing of the exception
- After a little more investigation, The boost::not_a_dag exception is extended from std::invalid_argument which is extended from std::logic_error. If I were to create a 'OTBException' it too would probably extent std::logic_error. Now, in this case a string has been passed to a method to be processed and it fails because the input is not valid (due to self reference or circular reference). So should OTBException actually extend std::invalid_argument, or is there even any point in creating OTBException when std::invalid_arguement may suffice?   But that still means client code catching std::invalid_arguemnt or boost::not_a_dag.   
- The client code shouldn't really be catching boost::not_a_dag as this is exposing the internal workings and libraries used to the client.  Also the detection of a circular reference could be made during the parsing stage possibly saving some cpu cycles.
- Does the client need the ability to distinguish between a circular reference or self reference ???
  - Or is just returning an exception of uniform type with an error message sufficient
- The spec just says that an error message should suffice
- So let's not implement a OTBException, we'll just catch the boost::not_a_dag exception and throw a std::invalid_arguement exception instead. And we'll change the self reference check to throw a std::invalid_argument exception instead of std::logic_error.
- OK let's go.   - (I think I over complicated in a prior step, but that's the trouble of picking up a project over multiple sessions).
- Done. I've also updated the cli program to catch the correct exceptions and display an error.

