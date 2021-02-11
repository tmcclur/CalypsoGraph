/* list of commands to be implemented:
    write DONE in front of implemented commands

    new(n) name, additional args: creates a graph that can be referenced later
   by name add(a) graph, additional args: adds either a node or edge delete(d)
   name of object: removes object (graph, node, or edge) query(q) query objects
   by params: searches for and returns objects of the correct type match the
   params visualize(v) graph: launches visual graph editor in a new thread
    run(r) script.txt: takes in script of commands and runs them
    help(h) prints commands
*/

#define BUFS 1024

int new (char *argv[BUFS / 2]);

int help();
