# README #

##Question 1: Recursion, Lists and Accumulating Parameters

**(a) Write the following program and compile it: [5 marks]**

% Program: ROYAL

parent(queenmother,elisabeth).  
parent(elisabeth,charles).  
parent(elisabeth,andrew).  
parent(elisabeth,anne).  
parent(elisabeth,edward).  
parent(diana,william).  
parent(diana,harry).   
parent(sarah,beatrice).  
parent(anne,peter).   
parent(anne,zara).  
parent(george,elisabeth).   
parent(philip,charles).  
parent(philip,andrew).   
parent(philip,edward).  
parent(charles,william).  
parent(charles,harry).  
parent(andrew,beatrice).   
parent(andrew,eugene).  
parent(mark,peter).   
parent(mark,zara).  
parent(william,georgejun).   
parent(kate,georgejun).    
  

**Define the following predicates on the persons in the program ROYAL.**  

(1) the_royal_females/1 (a list of all female members of the Royal
Family)  
(2) the_royal_males/1 (a list of all male members of the Royal Family)  
(3) the_royal_family/1 (a list of all members of the Royal Family)  
(4) mother/2  
(5) has_child/1.  
(6) ancestor/2 (use recursion).  
(7) descendant/2 (use recursion or (g)).  
  
Translate the following questions into Prolog queries and try them out:  
(8) Who is the mother of Beatrice?  
(9) Who has a child (one or more)?  
(10) Who is a desencendant of the Queenmother?  