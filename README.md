# Acquire
![my machine badge](https://forthebadge.com/images/badges/works-on-my-machine.svg)
![workflow badge](https://github.com/itisluiz/Acquire/actions/workflows/cmake-ci.yml/badge.svg)

The `acquire` library is a bite-sized library for dealing with the acquision of addresses 
and functions in a more dynamic fashion, allowing for more verbose intentions and more implicit conversions.
It deals with stuff such as pattern scanning, NT module acquision, NT module section finding, and object vTable 
indexing combining all of those seamlessly into some methods that allow for easy use, specially with literals.

## Main methods

### `acquire::fromPattern`

Matches a pattern in a given section into a typed pointer.

**Usage:**
```cpp
#include <acquire/acquire.hpp>

acquire::Pattern myPattern("AA ?? ?? CC DD");
acquire::Section mySection(".text", "kernel32.dll");

// Implicit bool cast for validation
if (!mySection)
    return;

// Find given pattern in the code section of kernel32.dll
void* result = acquire::fromPattern<void*>(myPattern, mySection);
```

### `acquire::fromExport`

Retrieves a typed pointer to the specified export name or ordinal from a Windows module.

**Usage:**
```cpp
#include <acquire/acquire.hpp>

acquire::WinModule myModule("kernel32.dll");

// Implicit bool cast for validation
if (!myModule)
    return;

// Via export name
void* result = acquire::fromExport<void*>("LoadLibraryA", myModule);

// Via export ordinal
void* result = acquire::fromExport<void*>(42, myModule);
```

### `acquire::fromVTable`

Retrieves a typed pointer from the virtual function table (vtable) of an object at a specified index.

**Usage:**
```cpp
#include <acquire/acquire.hpp>

// Get virtual function index 2 on myObject's virtual table
void* result = acquire::fromVTable<void*>(&myObject, 2);
```

## Flexible Object Construction

The library focuses on ease of use by providing constructors for objects that facilitate calling the functions in various ways. For example, `WinModule` can be constructed as:
```cpp
acquire::WinModule myModule(hModule);
acquire::WinModule myModule("MyModule.dll");
acquire::WinModule myModule(L"MyModule.dll");
acquire::WinModule myModule; // Base module / executable
```
This flexibility extends to other objects in the library, simplifying usage in different scenarios.

## More examples

You may look at the tests in order to see more ways objects can be constructed and what they yield.
