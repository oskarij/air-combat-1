
# Review form for project Air Combat 1
**Names of reviewers:**
Jussi


## 1. Overall design and functionality (0-6p)
  * 1.1: The implementation corresponds to the selected topic and
scope. The extent of project is large enough to accommodate work for
everyone (2p)
The requirements were very well fulfilled in this project. 2p
  * 1.2: The software structure is appropriate, clear and well
documented. e.g. class structure is justified, inheritance used where
appropriate, information hiding is implemented as appropriate. (2p)
The structure is well done, and it would be easy to expand further. 2p
  * 1.3: Use of external libraries is justified and well documented. (2p)
There's even a bit too much libraries used; the logging library was somewhat 
useless, as it only logged a couple of events. For this kind of simple task 
maybe even a simple cout would've worked. 1.5p

Total 5.5p


## 2. Working practices (0-6p)
  * 2.1: Git is used appropriately (e.g., commits are logical and
frequent enough, commit logs are descriptive). (2 p)
Commits are very frequent, and at least most of the commits are descriptive 
also. You have pushed to 2 different branches, but it works when people are working 
on different modules. But pushing straight to master creates this issue of many, 
many (merge) commits. 1.5p
  * 2.2: Work is distributed and organised well. Everyone contributes
to the project and has a relevant role that matches his/her skills.
The distribution of roles is described well enough. (2p)
Work is distributed clearly. Even though some people did more than others, 
seems like everybody had enough to do, and learned during the project. 2p
  * 2.3: Quality assurance is appropriate. Implementation is tested
comprehensively and those testing principles are well documented. (2p)
Appropriate unit tests! woohoo.. Also valgrind is used to test for 
memory leaks 2p

Total 5.5p

## 3. Implementation aspects (0-8p)
  * 3.1: Building the software is easy and well documented. CMake or
such tool is highly recommended. (2p)
Building was easy using makefile, and the required libraries and their 
versions are clearly told in the readme 2p
  * 3.2: Memory management is robust, well-organised and
coherent. E.g., smart pointers are used where appropriate or RO3/5 is
followed. The memory management practices should be documented. (2p)
No complaints. SFML has some internal leaks, but that's not your fault. 2p
  * 3.3: C++ standard library is used where appropriate. For example,
containers are used instead of own solutions where it makes sense. (2p)
STL Containers are used appropriately 2p
  * 3.4: Implementation works robustly also in exceptional
situations. E.g., functions can survive invalid inputs and exception
handling is used where appropriate. (2p)
Assert is used at some points where a throw could've been used instead. 
Assert failure will close the program, whereas a throw could instead just 
show an error message on screen and be much more descriptive. 1p

Total 7p

## 4. Project extensiveness (0-10p)
  * Project contains features beyond the minimal requirements: Most of
the projects list additional features which can be implemented for
more points. Teams can also suggest their own custom features, though
they have to be in the scope of the project and approved by the course
assistant who is overseeing the project. (0-10p)
This projects would get a full 10 points, but because the very main thing, 
the physics engine, isn't top notch, I'll remove one point from the extensiveness.

Total 9p

## 4. Project plan (0-3p)
Schedule missing.

Total 2.5p

### Grand total 29.5 points