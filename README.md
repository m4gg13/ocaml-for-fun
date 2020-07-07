## Mastermind Codebreaker

# An agent made to generate and play a classic game of Mastermind!


This lovely agent uses a generational Genetic Algorithm with a Wisdom of the Artificial
Crowd modification. The number of generations per guess, percentage of mutations per
generation, size of the expert group per generation, and more can be easily changed
by an adjustment of the global variables. Perhaps more notably, the number of colors
to choose from and the length of the solution can also be changed by way of a global
variable adjustment.


See the included report for a detailed literature review of work in the field,
a thorough explaination of the structure of the code, and the results of the
experiments surrounding the code. This code was adapted from
[this] (https://github.com/NathanDuran/Mastermind-Five-Guess-Algorithm) Five Guess
Algorithm. I adapted it in the first place for the writing-intensive Introduction to
Artificial Intelligence class, CSCI4511W at the University of Minnesota Twin Cities.


# 6 July 2020

This code is in an unfinished state at the moment. Everything originially was both
a.) working and b.) in one file, but it was in need of revision and could be made
much more concise. I split out one of the most challenging elements of the algorithm
to the mom_neater.cpp file, a more tidy decendant of an original mom.cpp where I laid the
foundation for a Median of Medians algorithm to find the string with the highest rate of
commonality of a collection of strings.

I also intend to refine the fitness function. This is the way in which a permutation
is assigned a value of fitness. Each permutation needs to be compared against a growing
number of rules and this work can certainly be done more efficiently. 

Perhaps it should be noted that this is my first experience writing C++... I may be
ignorant of C++ conventions. 