# Source code based on book _Practical C++ design; From programming to architecture by Adam Singer_

The aim of this boot was to decompose well-known problem - a calculator based on Reverse Polish Notation.

## Requirements

* The calculator will be stack-based; the stack size should not be hard
coded.
* The calculator will use RPN to perform operations.
* The calculator will exclusively operate on floating point numbers; a
technique for entering input numbers (including scientific notation)
should be implemented.
* The calculator will have the ability to undo and redo operations; the
undo/redo stack sizes should be unlimited.
* The calculator will have the ability to swap the top two elements of
the stack.
* The calculator will be able to drop (erase) an element from the top of
the stack.
* The calculator will be able to clear the entire stack.
* The calculator will be able to duplicate the element from the top of
the stack.
* The calculator will be able to negate the element from the top of the
stack.
* The calculator will implement the four basic arithmetic operations:
addition, subtraction, multiplication, and division. Division by 0 is
impermissible.
* The calculator will implement the three basic trigonometric functions
and their inverses: sin, cos, tan, arcsin, arccos, and arctan. Arguments
to the trigonometric functions will be given in radians.
* The calculator will implement functions for y^x and y^(1/x)
* The calculator will implement a runtime plugin structure to expand
the operations the calculator can perform.
* The calculator will implement both a command line interface (CLI)
and a graphical user interface (GUI).
* The calculator will not support infinity or imaginary numbers.
* The calculator will be fault tolerant (i.e., will not crash if the
user gives bad input) but does not need to handle floating point
exceptions.
