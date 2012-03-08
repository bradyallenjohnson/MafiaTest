
Compilation:
A Makefile has been included with the following targets:
  all <default target>
  clean

I sent the code compiled, but do the following to recompile on your system:
(compiles on Linux, but probably wont compile on windows)
  make clean all

Development environment:
- Ubuntu Linux 09 04
- Netbeans IDE with jVi plugin

Basic class structure:
- MafiaMember
    A representation of a Mafia Member that stores all pertinant info, including its boss,
    relocatedBoss, subordinates, and relocatedSubordinates
- MafiaMembersManager
    A class that manages and stores a MafiaMember hierarchy
    Performs the following operations:
    - findMemberByName
    - findMemberByAlias
    - setMemberInJail
    - releaseMemberInJail


Things I would like to have completed in the 2 hours:
- I dont ever like to send code untested, I would have liked to create some unit test cases
- I would liked to have been able to be able to specify the Mafia structure in a text file that would be read in by main() and then create the corresponding hierarchy via the MafiaMembersManager.
- Ideally the entire hierarchy should be a tree structure, not a binary tree, but something like a B-Spanning Tree. Since time was limited, instead I created a map of subordinates for each member.
