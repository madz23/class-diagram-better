// Basic grammar to make sure this is working
grammar Hello;
r : 'hello' ID ;
ID : [a-z]+ ;
WS : [ \t\r\n]+ -> skip ;

// assuming you set up your paths correctly, this command will generate a C++ parser (Java is the default)
// antlr4 -Dlanguage-Cpp <name-of-grammar>

