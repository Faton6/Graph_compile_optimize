# Graph compile optimize
Study project with graph traversal bfs to look at compiler optimization possibilities

## Task:

Optimize the graph traversal program automatically or semi-automatically using the compiler, as well as intrinsics. Compare the running time of the following program variants:
- original program, without optimization
- original program optimized only using compiler switches
- program vectorized semi-automatically (using compiler directives and switches and
minor code editing)

In all cases, use the optimization switches that give the shortest program running time,
and the latest (effective) of the available vector extension. If possible,
ensure the use of aligned vector read and write commands. In a program with manual
vectorization, minimize the number of memory accesses. At each stage of manual
optimization, check that the program running time has decreased.
