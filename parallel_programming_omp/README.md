My attempts at the 5 problem statements given in [this website](https://gribblelab.org/teaching/CBootCamp/A2_Parallel_Programming_in_C.html)

Couple of interesting tidbits I've learnt in the process

1. `rand()` is not inherently thread-safe because it relies extensively on state. When I wrote the solution to ex. 5 with `rand()` while seeding the PRNG with a different number across each iteration, the program took 1m 12s without parallelization but 3m with paralleization. Turns out `rand()` was indeed the culprit. Replacing it with `rand_r(%seed)` sped the program execution nearly 12 times because `rand_r()` is thread-safe
2. Both `rand()` and `rand_r()` are old PRNGs dating back to the 1980s. They're not cryptographically secure and follow a poor statistical distribution. The recommended PRNG is `arc4random()` unless you're not concerned about the quality of the results and you need repeatability, according to the man page for `arc4random()`. This is also apparently thread-safe so I will try this method and see how the results are
