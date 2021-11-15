//<while_loop> --> while '(' <expression> ')' <statement>

void while_loop() {
  if(nextToken != WHILE_CODE) {
    error();
  }
  else {
    lex();
    if(nextToken != LEFT_PAREN) {
      error();
    }
    else {
      lex();
      expr();
      if (nextToken != RIGHT_PAREN) {
        error();
      }
      else {
        lex();
        statement();
      }
    }
  }
}
