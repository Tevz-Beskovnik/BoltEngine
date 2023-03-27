CORE
=====

# Contains highest level of abstraction for the graphics API

Contains main ways to interact with the graphics API, UV, shaders, materials, etc...

# API Quality assurance, readability and upkeep

 - For returning errors whenever possible use the `#include<exception>` standard library with bolts built in `BOLT_ERROR`,
 - If it is not possible to use `BOLT_ERROR` use `BOLT_MSG_ERROR`, to show error messages in console with conjuction `Bolt_status_enum` type to return a error status or successfull status if no error is returned
 - If a function can use `constexpr` use it
 - If a function exists with the explicit purpouse of returning a value **ALLWAYS** `[[nodiscard]]`, in general any function that returns a value **should** use `[[nodiscard]]`
 - Do **not return pointers** if possible, return smart pointers, if pointers have to returned **create a type** that **signifies** if the returned memory is the users job to handle or if its being handled by some other class
 - When setting default values to function arguments do that in `.cpp`