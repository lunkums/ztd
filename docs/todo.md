- Change `anyerror` to be of type `int`
- Change `Result<T, U>` to use `Result<T, anyerror>` by default
- For `Result<T, U>` where `T` and `U` are the same type, don't define a single param constructor
  - Instead, only allow users to convert from `Ok<T>()` and `Error<U>()` to `Result<T, U>()`
