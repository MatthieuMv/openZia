# Memory managing
openZia uses the [RAII idiom](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization) for memory managment. It also prefer **std::unique_ptr** and **std::shared_ptr** instead of ugly raw pointers.

# Naming
openZia uses the camelCase naming convention.

Notable C++ naming rules followed are :
```C++
    constexpr int MyConstantInt = 42; // Global constants

    Foo GetSomeFoo(void); // Global scoped functions

    class Foo { // Classes
    public:
        int myInt; // Public members

        void bar(void); // Member functions

        static void Bar(void); // Static functions

    private:
        int _myInt; // Private members

        static int _MyStaticInt; // Private static members
    };
```

# Getter / Setters
If the concerned type is scalar (can be cheaply copied) then get/set functions look like :
```C++
Type getType(void) const noexcept; // Constant getter
void setType(void) noexcept; // Setter
```

If the concerned type isn't scalar (can't be cheaply copied) then get/set functions look like :
```C++
// This allows end-user to choose how to deal with the memory. Best example is copy vs move semantics.
Type &getType(void) noexcept; // Mutable reference getter
const Type &getType(void) const noexcept; // Constant reference getter
```
