# Language Standards
This project uses the [C++ 17 standard](https://en.cppreference.com/w/cpp/17). Your code must compile with g++ using the included make file and pass [CppCheck](https://github.com/danmar/cppcheck) with all checks enabled. 

# Coding Styles
1. ##### Use Doxygen style comments and don't make useless comments. 
  * ###### Multile Line
    ```cpp
    ///
    ///... text ...
    ///
     ```
     or
     ``` cpp
     /**
     * Text
     */
     ```
   * ###### Single Line
     ```
     /// This is a great comment that is useful
     ```
###### More info about Doxygen can be found [HERE](https://doxygen.nl/manual/docblocks.html)

2. ##### Use tabs instead of white-spaces (we usually set our editors to 4 white-spaces for 1 tab, but the choice is up to you).
3. ##### Always leave one space before and after binary and ternary operators.

  * ###### This:
    ```cpp
    if (a == 10 && b == 42)
    ```

  * ###### Not This:
    ```cpp
    if (a==10&&b==42)
    ```
4. ###### Avoid using hardcoded values when possible. 
5. ###### Use PascalCase for class names, camelCase for method names and variables, and prefix methods and class variables with m_.
  ```cpp
  class ThisIsAClassName()
  {
    int m_thisIsAVariable{ 0 };
    void m_thisIsAMethod();
  };
  ```
6. ###### Use Smart Pointers where possible
7. ###### Don't use "using namespace". 
  * ###### This:
    ``` cpp
    std::cout << "I'm printing something"; 
    ```
  * ###### Not This:
    ``` cpp
    using namespace std;
    cout << "I'm printing something"; 
    ```
