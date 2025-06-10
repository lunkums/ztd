# Conventions

## Names

Main rules:

- Macros shall be `SCREAMING_SNAKE_CASE`
- User-defined types and `typedef`s for user-defined types shall be `UpperCamelCase`
- All other identifiers shall be `snake_case`

Additional rules:

- `camelCase` is forbidden
- URIs shall be `snake_case` (including directories, paths, and file names)
  - Except for directories, paths, and file names that require an existing convention, such as `.clang-format`, `CMakeLists.txt`, and `README.md`
- URLs shall be `kebab-case`
- Avoid suffixing types or `typedef`s with `_t` unless using POSIX types or interfacing with POSIX APIs
- Zeta will occassionally use `flatcase` for `typedef`s of fundamental types and constants intended to be used like keywords
  - i.e. `typedef int anyerror;`
  - This is to maintain stylistic consistency with C++'s built-in types and keywords (i.e. `constexpr`, `sizeof`, `typename`, `nullptr`) and is used sparingly
  - Consider this convention reserved for the C++ language and Zeta

Final remarks:

Despite borrowing heavily from Zig's standard library and design philosophy, these rules are largely based on [the Rust Style Guide](https://doc.rust-lang.org/nightly/style-guide/advice.html) because it's opinionated, unambiguous, and conventional. [Zig's naming rules](https://ziglang.org/documentation/master/#Names) are also opinionated and relatively well-defined, but they are unconventional and stylistically contradicting. Specifically, the mixing of `snake_case` and `camelCase` identifiers is likely to confuse experienced programmers, as most programming languages will only use one but not both.

While Zeta's naming rules are mostly similar to Rust, some rules have been modified to conform with C++ best practice. For example, Zeta reserves `SCREAMING_SNAKE_CASE` solely for macros and is not used for constant and immutable, static data because "ALL_CAPS name are vulnerable to unintended macro substitution" ([C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es9-avoid-all_caps-names)). Additionally, `snake_case` is used for enumerators because each enumerator in a C++ `enum` resolves to a value, while Rust `enum`s represent a set of types (i.e each enumerator is a variant). It makes sense that Rust `enum` variants follow the same convention as Rust types. C++ enumerators, however, are fundamentally more similar to values than types, which is highlighted by the naming rule.

There are lots of high-quality production codebases written in C++; some use `camelCase` identifiers for variable and function names; others use `snake_case`. While there is no right or wrong answer, there are other C++ naming conventions that seem to hint at a bias towards using underscores. For example, C++ programmers often use Hungarian notation to denote class member variables (i.e. `m_data` where `m_` means "member", though it can be expressed as `mData`). A commonly used alternative for indicating private members is by prefixing or postfixing one with an underscore (i.e. `_data` or `data_`). C++ is also commonly used in the engineering community, where some variables are given suffixes to denote their units, separated by an underscore (i.e. `freq_hz`). Finally, the official C++ standard library uses `snake_case` case for most of its identifiers, including type names. Since all these conventions are frequently used in C++ code, it would indicate that consistent naming in C++ code involves underscores, and therefore `snake_case` identifiers instead of `camelCase` ones.
