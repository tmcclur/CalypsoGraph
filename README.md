# CalypsoGraph

C Program for operating on Graphs and Networks fast

### RULES:
- camelCase only 
- except TypeNames (i.e. struct type id thingys)
- please do things iteratively unless you know recursion is faster in the specific case, as pushing and popping stack frames is expensive
- minimize mallocing and freeing because it's slow
- code as modularly as possible: if we have to update a data structure or algorithm for space/time reqs, we don't want to break everything
- you can use any IDE you want, but it is our official position that using VIM to look cool is the opposite of cool
- 
```
while (opening bracket on a new line)
{
    pleasePutYourBracketsOnCorrectly();      
}
```
- 
- (I might make a style guide eventually)

### TODO:
- [x] fill out makefile
- [ ] implement first builtin functions in `sh.c`
- [x] get a version up and running and make test resize and basic graph functionality
- [ ] build a gameplan for builtin graph functions--> which algorithms, building blocks of graph math, look into category theory?
- [ ] linear algebra
- [ ] command history ^/ gdb style enter, can be output to a file
- [ ] figure out how to visualize graphs and edit them visually: look into energy minimization
- [ ] design scripting lang for graphs: transpiled into c?

### Linear stuff
[lapack/bals stackoverflow](https://stackoverflow.com/questions/17858104/what-is-the-relation-between-blas-lapack-and-atlas)

[linear tutorials](https://github.com/Foadsf/Cmathtuts)

(http://www.mgarland.org/files/papers/sc09-spmv-throughput.pdf)

(https://medium.com/@jmaxg3/101-ways-to-store-a-sparse-matrix-c7f2bf15a229)

(http://www.netlib.org/utk/people/JackDongarra/etemplates/node373.html)

(https://docs.scipy.org/doc/scipy/reference/sparse.html)
