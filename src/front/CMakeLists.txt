add_subdirectory(flex_bison)

add_library(
    Front STATIC
    
    Driver.cpp
    pre.cpp
    lexer.cpp
    parser.cpp
)


target_link_libraries(
    Front PUBLIC 
    Ast
)
