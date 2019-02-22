(A ∧ ¬B) (alternate: (A && !B))
A     B     result
-------------------
0     0       ?
0     1       ?
1     0       ?
1     1       ?
(¬A ∨ B) ∧ ¬(A ∧ ¬B) (alternate: (!A || B) && !(A && !B))
A     B     result
-------------------
0     0       ?
0     1       ?
1     0       ?
1     1       ?
¬(A ∧ B) ∨ ( (A ∧ C) ∧ ¬(B ∨ ¬C) ) (alternate: !(A && B) || ( (A && C) && !(B || !C) ))
(Hint: Is it possible to calculate this using code?)
A     B     C     result
-------------------------
0     0     0       ?
0     0     1       ?
0     1     0       ?
0     1     1       ?
1     0     0       ?
1     0     1       ?
1     1     0       ?
1     1     1       ?
STRETCH GOAL
The sum of two binary digits can be represented with the following truth table:

A + B
A     B     CARRY   SUM
------------------------
0     0       0      0
0     1       0      1
1     0       0      1
1     1       1      0
This can be represented with boolean algebra like so:

SUM = A ⊕ B (alternate: A ^ B or A xor B)
CARRY = A ∧ B (alternate: A && B)
How can you represent the SUM and CARRY of adding THREE digits with a truth table and in boolean algebra?

A + B + C
A     B     C      carry   sum
--------------------------------
0     0     0        ?      ?
0     0     1        ?      ?
0     1     0        ?      ?
0     1     1        ?      ?
1     0     0        ?      ?
1     0     1        ?      ?
1     1     0        ?      ?
1     1     1        ?      ?
SUM = ?
CARRY = ?
© 2019 GitHub, Inc.
Terms
Privacy
Security
Status
Help
Contact GitHub
Pricing
API
Training
Blog
About
