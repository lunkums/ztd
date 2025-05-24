# ztd

A total C++ standard library replacement, inspired by [Zig](https://ziglang.org/).

This library is meant to be used **instead of** the C++ library, not to complement it.

## Goals

- Emphasis on explicit control
  - Avoiding hidden behavior where possible (i.e constructors and destructors)
  - Errors as values instead of exceptions
  - No implicit allocations, save for optional, "managed" types
- Functionality on par with the C++ standard library, but without the technical debt of `libc`
- Minimal use of `libc`, and only when absolutely necessary
- Readable implementation
- Support for the C++98 standard

## Reasoning

Observations:

- Zig has been gaining a lot of traction for its elegance and simplicity
- While neither as elegant nor simplistic as Zig, people still generally like C for the same reasons
- People often shoehorn modern language features into C such as OOP, namespaces, and generics using rudimentary techniques like `void*`, function prefixes, and macros, respectively
  - Even old standards of C++ formally support these features
- For modern projects, people who choose C++ over C will choose so because C++ is more expressive and featureful
- People gripe about modern C++'s complexity

Fact:

- The initial trajectory of C++'s evolution was heavily influenced by C
  - "C++ began as a fork of an early, pre-standardized C, and was designed to be mostly source-and-link compatible with C compilers of the time" [source: Wikipedia](https://en.wikipedia.org/wiki/Compatibility_of_C_and_C++)

Theories:

- The C++ standard library carried forward the shortcomings of the C standard library
  - The C++ standard library was built on an unstable foundation
- The current trajectory of C++'s evolution is, in part, dictated by the development of the C++ standard library
- The C++ standard library commonly hides memory management behind implicit allocations happening in constructors and destructors
  - The benefit, in the best case, is that when your resources go out of scope, they are automatically cleaned up for you
  - The drawback is that allocations are harder to keep track of because you are discouraged from explicitly making them
- The C++98 standard lacks the complexity of modern C++ (r-value references, move semantics, smart pointers, attributes, noexcept) [source: cppreference.com](https://en.cppreference.com/w/cpp/11)
  - This is a double-edged sword, as it also lacks nice modern features such as lambdas, iterators, the `auto` keyword, and `nullptr`
- The C++98 standard still makes much-needed improvements over C (templates, namespaces, typecasting, OOP) [source: cplusplus.com](https://cplusplus.com/doc/oldtutorial/)
  - Some may argue OOP is actually a detriment to programming, but bad OOP is possible in both C and C++, C++ just gives you a way to express it succinctly

Conclusion:

- People still like C because it's simple
- C++98 is about as simple as C, but with helpful syntatic sugar for features that programmers already hack into C
- C++ standards beyond C++98 didn't need more complex language features, they just needed a better standard library to work from
- We may not need a "better C++" (i.e. Rust, Zig, Carbon), but a better library for C++98

## Etymology

Take `std` and flip the `s` around. You get `ztd`.

You could also argue `ztd` is short for `Zig-std`.
