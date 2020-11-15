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
