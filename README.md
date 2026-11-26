# VULRIX

A tiny lisp-inspired polish notation repl calculator.


## Goal

The goal of this project is to create a very straightforward and simple parser.

That's why I am taking such inspiration from Lisp (its syntax basically looks like an AST).


## Features
- [ ] Add parser
  - [ ] Value stack
  - [ ] Operator stack (storing the bytecode)
- [ ] Add a sensible stack-based backend
    - [ ] Operators as function tables
    - [ ] Add sensible defaults [e.g. (+) = 0; (*) = 1]
- [ ] Evaluate Expressions in a nested way [e.g. (+ (* 2 3) 6)]
- [ ] Boolean Type and Expression Support
- [ ] Define Variables
- [ ] Implement Jumps
- [ ] Define Functions
- [ ] Evaluate Files

## Future Goals
If I deem this project to be worthwhile, I can certainly see myself implementing a little standard library for it. It should still be focused on maths however, and (though turing complete) not strive to be a general purpose programming language. 
