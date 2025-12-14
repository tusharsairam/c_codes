My attempts at the 5 problem statements given in [this website](https://gribblelab.org/teaching/CBootCamp/A2_Parallel_Programming_in_C.html)

Using the `time` command in Linux, the timing profiles of Ex. 4 and 5 are as follows (Real time value):
- ex4.c takes 4.146 seconds
- ex5.c takes 0.468 seconds with `rand_r`
- ex5.c (ex5\_norand\_r.c) takes 3 minutes and 20.224 seconds with `rand`! 

Couple of interesting tidbits I've learnt in the process

1. `rand()` is not inherently thread-safe because it relies extensively on state. When I wrote the solution to ex. 5 with `rand()` while seeding the PRNG with a different number across each iteration, the program took just a couple of seconds without parallelization but 3m with paralleization. Turns out `rand()` was indeed the culprit. Replacing it with `rand_r(%seed)` sped the program execution several hundred times because `rand_r()` is thread-safe. 
2. Both `rand()` and `rand_r()` are old PRNGs dating back to the 1980s. They're not cryptographically secure and follow a poor statistical distribution. The recommended PRNG is `arc4random()` unless you're not concerned about the quality of the results and you need repeatability, according to the man page for `arc4random()`. This is also apparently thread-safe so I will try this method and see how the results are
