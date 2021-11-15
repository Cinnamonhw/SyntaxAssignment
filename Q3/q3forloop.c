//<for_loop> --> for '(' [ <expression> ] ';' [ <expression> ] ';' [ <expression> ] ')' <statement>

void for_loop() {
  if (nextToken != FOR_CODE) {
    error();
  }
  else {
    lex();
    if (nextToken != LEFT_PAREN) {
      error();
    }
    else {
      lex();
      expr();
      if (nextToken != SEMICOLON) {
        error();
      }
      else {
        lex();
        expr();
        if (nextToken != SEMICOLON) {
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
  }
}
