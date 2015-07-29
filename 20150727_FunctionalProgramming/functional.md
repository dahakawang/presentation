class: middle, center, inverse

# Be Functional

### An introduction on metaprogramming and lambda

.footnote[David Wang (From CA team)]

---
# Agenda

1. The Paradigms of Programming
2. Church and Turning
3. LISP in 5 Minutes
4. No Variables? No side effects?
5. Limitation of substitution model
6. The Functional Way
7. Lambda
8. Metaprogramming
    - Java Generics, Reflection
    - C++ Templates, RTTI
    - Ruby Metaprogramming
    - LISP Macro
9. Book Recommondation

---
class: middle, center, inverse

# Paradigms of Programming

---
class: middle, large-list

- Imperative
    - Procedural
    - Object Oriented
- Declarative
    - Functional
    - Logical
    - DSL (Regex, SQL, Configuration etc)

---
count: false
class: middle, large-list

- Imperative
    - Procedural
    - Object Oriented
- Declarative
    -  **Functional**
    - Logical
    - DSL (Regex, SQL, Configuration etc)

---
# Alan Turing
.left-column[

Alan Mathison Turing was a British pioneering computer scientist, mathematician, logician, cryptanalyst, philosopher, mathematical biologist.

Turing is widely considered to be the father of theoretical computer science and artificial intelligence.
]

.right-column[.width41[![Turing](image/turing.jpg)]]

---
# Turing Machine
.width90[.center[![Machine](image/turing_machine.jpg)]]

---
# Alonzo Church (λ-calculus)
.width30[.center[![Church](image/church.jpg)]]

Church was an American mathematician, who is best known for the lambda calculus, Church–Turing thesis, proving the undecidability of the Entscheidungsproblem, Frege–Church ontology, and the Church–Rosser theorem.


---
class: middle, center, inverse
# LISP in 5 Minutes


---
# Core language

```LISP
(+ 2 3) ; => 5


(define (inc_one x)
    (+ x 1))
(inc_one 10) ; => 11


(define (positive? x)
    (cond
        [(> x 0) (1)]
        [else (0)]))
(positive? -12) ; => 0

(cons 1 2) ; (1 . 2)
(car (cons 1 2)) ; => 1
(cdr (cons 1 2)) ; => 2


(cons 1 (cons 2 (cons 3 ())))  ; => (1 2 3)
(list 1 2 3)
(car (list 1 2 3)) ; => 1
(cdr (list 1 2 3)) ; => (2 3)
```

---
# But.. we want the loop

--
count: false

```LISP
; emulate for loop in C/C++
(define (for_loop start end op)
    (cond
            [(< start  end) (op start) (for_loop (+ start 1) end op)]))

(for_loop 1 5 (lambda (x) (display x)))


; iterate a list
(define (sum lst)
    (cond
        [(= lst ()) 0]
        [else (+ (car lst) (sum (cdr lst)))]))
(sum (list 1 2 3 4)) ; => 10
```

---
class: middle, center
# No variables?

---
class: middle, center
# No side effects!
Timing is never an problem now

---
class: middle, center
# So function, is actually a function
in mathematical sense

---
class: middle, center
# Referential Transparency
$$f(12) = f(12)$$


---
# Limitation

How can we model the real world without the state?

--

- Pure FP
- Impure FP

---
# Impure FP

- LISP allows assignment
- Java 8
- C++ 11 or above
- Ruby

---
# Pure FP

How can we emulate state without a variable?

--
count: false
- How can they be a mathematical function?
    - ```print(msg)``` -> what's the return value?
    - ```read()``` -> a function without a arguments is constant?

--
count: false
- Record the history
    - ```(cons new_value previous_values)```, to write a variable
    - ```(car value)```, read a variable

--
count: false
- RealWorld Solution
    - print :: (RealWorld, String) -> (RealWord)
    - read :: RealWord -> (RealWorld, String)

--
count: false
- In Haskell: Monad
