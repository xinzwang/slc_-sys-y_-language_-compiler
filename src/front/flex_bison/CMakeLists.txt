add_custom_target(DoFlexBison
    flex -+ -o ${CMAKE_CURRENT_SOURCE_DIR}/../lexer.cpp ${CMAKE_CURRENT_SOURCE_DIR}/flex.l
COMMAND
    bison -o ${CMAKE_CURRENT_SOURCE_DIR}/../parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/bison.y)
