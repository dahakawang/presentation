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


---
# The functional way

```LISP
(define (factorial n)
  (if (= n 1)
      1
      ( * n (factorial (- n 1)))))

(factorial 4)
```

--
count: false
$$f(x)=\begin{cases}1 & x = 1 \\ x \times f(x-1) & x > 1\end{cases}, x\in (0, +\infty)$$

---
# The non-functional way

```C
// okay if you don't think imperatively
int factorial(int x) {
    if (x == 1) {
        return 1;
    } else {
        return x*factorial(x-1);
    }
}

// uses destructive update
int factorial(int x) {
    int result = 1;
    for (int i = 1; i <= x; i++) {
        result *= i;
    }

    return result;
}
```

---
# The substitution model

```LISP
; expansion
(factorial 4)
(* 4 (factorial (- 4 1)))
(* 4 (* (- 4 1) (factorial (- (- 4 1) 1))))
(* 4 (* (- 4 1) (* (- (- 4 1) 1) (factorial (- (- (- 4 1) 1) 1)))))

; reducing
(* 4 (* (- 4 1) (* (- (- 4 1) 1) (factorial (- (- 3 1) 1)))))
(* 4 (* (- 4 1) (* (- (- 4 1) 1) (factorial (- 2 1)))))
(* 4 (* (- 4 1) (* (- (- 4 1) 1) (factorial 1))))
(* 4 (* (- 4 1) (* (- (- 4 1) 1) 1)))
(* 4 (* (- 4 1) (* (- 3 1) 1)))
(* 4 (* (- 4 1) (* 2 1)))
(* 4 (* (- 4 1) 2))
(* 4 (* 3 2))
(* 4 6)
24
```

LISP == LISt Processing

---
class: middle, center, inverse 

# Closure

---

# Many alias

- Closure
- Lambda
- Anonymous function
--
count: false
- lexically scoped name binding

---
# So what the heck is lexical scope?

In javascript
```js
var p1 = 1

function sub1() {
    var p2 = 2

    function sub2() {
        var p3 = 2

        function sub3() {
            var p4 = 2
            return "hello";
        }

        return sub3;
    }

    return sub2;
}
```

---
# Not be confused with calling stack

.left-column[
```js
// the function that returns a closure
function generator() {
    var private_var = 1234;

    return function() {
        console.log(private_var);
    }
}


// the caller that calls a closure
function caller(f) {
    f();
}


caller(generator());






// EOF
```
]


---
class: middle, center, inverse
# Closure = Function + Environment
requires that function is just like a primitive data type (first class), and can be passed back and forth as parameters to other function.(higher order function)

---
# Lambda Expression

- Borrowed name from Lambda Calculus
- Java 8, C++ 11, python name after this


---
# Anonymous Function isn't a good name

Also an example from js

```js
function closure_but_not_anonymous() {
    var im_private_env1 = 1;

    function i_have_a_name() {
        console.log("i have a name");
    };

    return i_have_a_name;
}


function closure_with_anonymoous_function() {
    var im_private_env2 = 2;

    return () {
        console.log("i'm anonymous");
    };
}
```

---
class: center, middle
# Javascript has closure from the first day

---
# Remember java's anonymous class?

It's impressive if you've developed a Android app

```java
public class MyAndroidAppActivity extends Activity {

    int counter = 0; //dont't need to be final

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Button button = (Button) findViewById(R.id.button1);
        // need to be final
        final Button button2 = (Button) findViewById(R.id.button2);  

        button.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View arg0) {
                // access counter and button2
            }
        });
    }
}
```


---
# Lambda In Java 8 ;-)

```java
(arguments) -> { body }

// Can convert automatically to a functional interface
// (An interface with exactly one abstract method)
// So Runnable with only run is a functional interface
Runnable r = () -> System.out.println("hello"); 
r.run();
```

translated into a method
```java
class B {
    public void foo() {
        List<Person> list = ...
        final int bottom = ..., top = ...;
        list.removeIf( p -> (p.size >= bottom && p.size <= top) );
    }

    static boolean lambda$1(int bottom, int top, Person p) {
        return (p.size >= bottom && p.size <= top;
    }
}
```


---
# invokedynamic to metafactory

```java
metaFactory(MethodHandles.Lookup caller, // provided by VM
            String invokedName,          // provided by VM
            MethodType invokedType,      // provided by VM
            MethodHandle descriptor,     // lambda descriptor
            MethodHandle impl)           // lambda body
```

---
# Old days with C
```C
// This is not closure, since it can't capture the environment
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int values[] = { 88, 56, 100, 2, 25 };
qsort(array, 5, sizeof(int), cmpfunc);

```

--
We can only capture the environment manually.

```C
void *inc_x(void *x_void_ptr) {
    int* x = (int*)x_void_ptr;
}

int main() {
    pthread_t inc_x_thread;
    int x;
    if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
}
```

---
# A better time with C++ functor

```c++
class Adder {
public:
    Adder(int n):num(n) {};
    int operator()(int x) { return x + num; }

pricate:
    int num;
};

template<typename T>
void caller(T& callback) {
    callback(12); 
}

int x = 10;
Adder adder(x); // capture value manually
caller(adder);

```

---
# C++ Lambda

```c++
[capture](args) { expresions; };

// pass in an lambda
for_each(v.begin(), v.end(), [](const T& item) { cout << item << endl; });

// return a lambda
function(void(int)> get();


string str = "hello"
// capture by value
[str]() { str = "change not propagate to outside"; };

// capture by reference
[&str]() { str = "change propagate to outside"; };

// capture all used
[=]() { cout << "all used variables will be captured" };
```

---
class: middle, center, inverse
# Metaprogramming

---
# Definition
Once we regard code as a kind of data, we can have ability to inspect the properties of code, and also manipulate it.


---
# Java
- Reflection
- Generics

---
# C++ 

- Template
- RTTI

---
# Template

It's a way to implements Generics

```c++
template<typename T>
class List {
public:
    blah..
private:
    T* pData;
}

template<typename T>
T add(T& x, T& y) {
    return x + y;
}

add(3+6);  // add<int>(int&, int&) initialized
add(string("abd") + string("dds")); // add<string>(string&, string&) is initialized
```
The C++ template is all about **compile time** code generation

---
# Static Polymophism

We all know Polymorphism can be achieved by virtual keywords in C++. And at runtime, it involves looking up the vtable. But Polymorphism can also be achieved at compile time.

```C++
template <typename T>
struct Base{
    void foo() {
         static_cast<T*>(this)->implement_foo();
    }
};

struct Derived1 : Base<Derived1> {
     void implement_foo() {
     }
};

struct Derived2 : Base<Derived2> {
     void implement_foo() {
     }
};

Derived1 d1; Derived2 d2;
d1.foo(); // Base<Derived1>::foo is generated by compiler
d2.foo(); // Base<Derived2>::foo is generated by compiler
```

---
# Taking Advantages of Specialization Rules

```c++
template <class T>
class Foo {
public:
    void function() { std::cout << "Default\n"; }
};

template <>
void Foo<int>::function() { std::cout << "int\n"; }

int main() {
    Foo<std::string>().function();   // => Default
    Foo<int>().function();          // => int
}
```


---
class: middle, center, inverse
# C++ Templates are Turing Complete


---
# Prolog

Fact, Rule, Query, KnowledgeBase

```prolog
happy(david).
happy(kevin).
praised(kevin).
party.
?- happy(david). % yes
?- happy(sam).   % no
?- party.        % yes

sing(david):- happy(david),praised(david).
sing(kevin):- happy(kevin),praised(kevin).
?- sing(david).  % no
?- sing(kevin).  % yes

loves(ken,marry). 
loves(vincent ,marry). 
loves(sam, jun). 
jealous(X,Y):-  loves(X,Z),  loves(Y,Z).
?- jealous(vincent, W).  % W = ken

?-  8  is  6+2.  % yes
?-  X  is  6+2.  % X = 8
```
We are not computing, we are reasoning.


---
# Ruby

Ruby's metaprogramming learns from LISP

```ruby
# open a class
class Array
    def third
        size > 2 ? self[2] : nil
    end
end

# register the hook, and add new method on the fly
self.method_missing
```
Ruby on Rails (Active Record)

---
# LISP Macro

---
class: middle, center, inverse
# Thank you
