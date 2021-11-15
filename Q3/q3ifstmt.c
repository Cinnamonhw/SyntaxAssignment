//<if_statement> --> if '(' <expresssion> ')' <statement> [ else <statement> ]

void if_statement() {
  if (nextToken != IF_CODE) {
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
      if (nextToken != RIGHT_PAREN) {
        error();
      }
      else {
        lex();
        statement();
        if (nextToken == ELSE_CODE) {
          lex();
          statement();
        }
      }
    }
  }
}
