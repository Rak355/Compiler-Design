/******************************************************************************************************
Lexer for C Compiler.
Author: Rakesh Kumar Lal.

How to use this lexer:
follow the README.md instruction.

Please report bugs by raising an issue on the git repository.
*******************************************************************************************************/

#include <types.h>
#include <commons.h>
#include <stdio.h>
#include <stdlib.h>

FILE *log_file;

char *buffer;
long file_size;
int token_qty = 90000;
int chain_length = 1000;

enum token_type{
  no_type,
  identifier,
  integer_constant,
  floating_constant,
  character_constant,
  string,
  special_symbols
};

enum error_codes{// TODO, implement
  unterminated_string,
  unterminated_character,
  invalid_constant,
};

struct Tokenizer{
  int token_type;
  int chain_id;
  char lexeme_chain[1000];
  int chain_size;
}t[90000];

int chain_id=0;

void initialize_token(){
  for(int i=0;i<token_qty;i++){
    t[i].token_type = no_type;
    t[i].chain_id = i;
    for(int j=0;j<chain_length;j++){
      t[i].lexeme_chain[j] = 0;
    }
    t[i].chain_size = 0;
  }
}
void gen_excp(int line_no){
  printf("ERROR AT LINE NUMBER :%d\n",line_no);
}
void scanner(){
  int counter = -1;
  char lexeme,n_lexeme,p_lexeme;
  int line_no=1;
  while(true){
    counter++;
    if(counter>file_size) break;
    lexeme= *(buffer+counter);
    n_lexeme= *(buffer+counter+1);
    p_lexeme= *(buffer+counter-1);
    //******************************//
    if(lexeme=='\n') line_no++;//increment line number;

    if(lexeme=='"'){//string token
      t[chain_id].token_type = string;
      counter++;
      char temp_lexeme;
      while(true){
        temp_lexeme = *(buffer+counter);
        if(temp_lexeme=='\n'){
          gen_excp(line_no); //unterminated string error
          return;
        }
        if(temp_lexeme=='"'){
          //counter--;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = '\0';
          chain_id++;
          break;
        }

        t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
        counter++;
      }
      continue;
    }//string token ends here

    if(lexeme=='/'&&n_lexeme=='/'){//single line comment
      counter += 2;
      char temp_lexeme;
      while(true){
        temp_lexeme = *(buffer+counter);
        if(temp_lexeme=='\n'){
          //counter--;
          line_no++;
          break;
        }else{
          counter++;
        }
      }
      continue;
    }//single line comment ends here

    if(lexeme=='/'&&n_lexeme=='*'){//multi line comment
      counter += 2;
      char temp_lexeme;
      char n_temp_lexeme;
      while(true){
        temp_lexeme = *(buffer+counter);
        n_temp_lexeme = *(buffer+counter+1);
        if(temp_lexeme=='*'&&n_temp_lexeme=='/'){
          counter++;
          break;
        }else{
          if(temp_lexeme=='\n') line_no++;
          counter++;
        }
      }
      continue;
    }//multi line comment ends here

    switch(lexeme){//special characters
      case '!':
      {
        if(n_lexeme=='='){//not equal operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }
      }
      case '&':
      {
        if(n_lexeme=='&'){//AND operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }
      }
      case '<':
      {
        if(n_lexeme=='<'){//left shift operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }else if(n_lexeme=='='){//smaller than or equal operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }
      }
      case '>':
      {
        if(n_lexeme=='>'){//right shift operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }else if(n_lexeme=='='){//greater than or equal operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }
      }
      case '.':
      {
        if(n_lexeme=='.'&&*(buffer+counter+2)!='.'){
          printf("%c##%c##%c\n",lexeme,n_lexeme,*(buffer+counter+2));
          gen_excp(line_no);//invalid symbol
          return;
        }
        if(n_lexeme=='.'&&*(buffer+counter+2)=='.'){//range operator
          counter++;
          counter++;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = *(buffer+counter);
          chain_id++;
          break;
        }

      }
      case '|':
      {
        if(n_lexeme=='|'){//OR shift operator
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
          counter++;
          chain_id++;
          break;
        }
      }
      case '(':
      case ')':
      case '{':
      case '}':
      case '[':
      case ']':
      case '~':
      case '`':
      case '#':
      case '$':
      case '%':
      case '^':
      case '*':
      case '+':
      case '=':
      case '-':
      case ':':
      case ';':
      case '"':
      case ',':
      case '?':
      case '/':
      case '\\':
      case '_':
      t[chain_id].token_type = special_symbols;
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
      chain_id++;
      continue;
    }//special characters ends here

    if((lexeme>='a'&&lexeme<='z')||(lexeme>='A'&&lexeme<='Z')){//identifier/keyword
      t[chain_id].token_type = identifier;
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
      counter++;
      char temp_lexeme;
      while(true){
        temp_lexeme = *(buffer+counter);
        if((temp_lexeme>='a'&&temp_lexeme<='z')||(temp_lexeme>='A'&&temp_lexeme<='Z')||(temp_lexeme>='0'&&temp_lexeme<='9')||(temp_lexeme=='_')){
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
          counter++;
        }else{
          if(temp_lexeme=='\n') line_no++;
          counter--;
          chain_id++;
          break;
        }
      }
      continue;
    }//identifier/keyword ends here


    if(lexeme=='\''){//character constant
      t[chain_id].token_type = character_constant;
      counter++;
      char temp_lexeme;
      while(true){
        temp_lexeme = *(buffer+counter);
        if(temp_lexeme=='\n'){
          gen_excp(line_no); //unterminated character error
          return;
        }
        //*********************************
        if(temp_lexeme=='\\'){
          if(*(buffer+counter+1)=='\\'){
            if(*(buffer+counter+2)=='\''){
              t[chain_id].lexeme_chain[t[chain_id].chain_size++] = *(buffer+counter+1);
              t[chain_id].lexeme_chain[t[chain_id].chain_size++] = *(buffer+counter+2);
              counter+=2;
              chain_id++;
              break;
            }else{
              gen_excp(line_no);
              return;
            }
          }
          if(*(buffer+counter+1)=='\''){
            if(*(buffer+counter+2)=='\''){
              t[chain_id].lexeme_chain[t[chain_id].chain_size++] = *(buffer+counter+1);
              t[chain_id].lexeme_chain[t[chain_id].chain_size++] = *(buffer+counter+2);
              counter+=2;
              chain_id++;
              break;
            }else{
              gen_excp(line_no);
              return;
            }
          }
        }
        //*********************************
        if(temp_lexeme=='\''){
          //counter--;
          //t[chain_id].lexeme_chain[t[chain_id].chain_size++] = '\0';
          chain_id++;
          break;
        }
        t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
        counter++;
      }
      continue;
    }//character constant ends here

    if(lexeme=='0'&&(n_lexeme=='x'||n_lexeme=='X')){//hexadecimal
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = n_lexeme;
      counter += 2;
      char temp_lexeme = *(buffer+counter);
      while(true){
        temp_lexeme = *(buffer+counter);
        if((temp_lexeme>='0'&&temp_lexeme<='9')||(temp_lexeme>='a'&&temp_lexeme<='f')||(temp_lexeme>='A'&&temp_lexeme<='F')){
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
          counter++;
        }else{
          if(temp_lexeme=='\n') line_no++;
          counter--;
          chain_id++;
          break;
        }
      }
      continue;
    }//hexadecimal ends here.

    if(lexeme=='0'){//octal and decimal numbers (with leading 0s)
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
      counter++;
      char temp_lexeme = *(buffer+counter);
      while(true){
        temp_lexeme = *(buffer+counter);
        if(temp_lexeme=='0'){
          counter++;
        }else break;
      }
      while(true){
        temp_lexeme = *(buffer+counter);
        //*********************************************
        if(temp_lexeme=='.'){
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
          counter++;
          temp_lexeme = *(buffer+counter);
          while(true){
            temp_lexeme = *(buffer+counter);
            if(temp_lexeme>='0'&&temp_lexeme<='9'){
              t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
              counter++;
            }else{
              if(temp_lexeme=='\n') line_no++;
              counter--;
              chain_id++;
              break;
            }
          }
          continue;
        }
        //*********************************************
        if(temp_lexeme>='0'&&temp_lexeme<='7'){
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
          counter++;
        }else{
          if(temp_lexeme=='\n') line_no++;
          counter--;
          chain_id++;
          break;
        }
      }
      continue;
    }//octal and deciamal with leading 0s ends here.

    if(lexeme>='1'&&lexeme<='9'){
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
      counter++;
      char temp_lexeme = *(buffer+counter);
      while(true){
        temp_lexeme = *(buffer+counter);
        if(temp_lexeme>='0'&&temp_lexeme<'9'){
          t[chain_id].lexeme_chain[t[chain_id].chain_size++] = temp_lexeme;
          counter++;
        }else{
          if(temp_lexeme=='\n') line_no++;
          counter--;
          chain_id++;
          break;
        }
      }
    }

    //while loop
  }
}

void print_it(){
    for(int i=0;i<token_qty;i++){
      fprintf(log_file,"token id:%d::%s\n",t[i].chain_id,t[i].lexeme_chain);
      //printf("token id:%d::%s\n",t[i].chain_id,t[i].lexeme_chain);
      //printf("token id:%d::%s::type::%d\n",t[i].chain_id,t[i].lexeme_chain,t[i].token_type);
      //if(t[i].token_type==numeric_constant) printf("type::%s\n\n","numeric_constant");
      if(t[i].token_type==string){
        //fprintf(log_file,"type::%s\n\n","string");
        //printf("type::%s\n\n","string");
      }
      if(t[i].token_type==character_constant){
        //fprintf(log_file,"type::%s\n\n","character_constant");
        //printf("type::%s\n\n","character_constant");
      }

      if(t[i].token_type==identifier){
        //fprintf(log_file,"type::%s\n\n","identifier");
        //printf("type::%s\n\n","identifier");
      }
      if(t[i].token_type==special_symbols){
        //fprintf(log_file,"type::%s\n\n","special_symbols");
        //printf("type::%s\n\n","special_symbols");
      }
    }
}

void lexer(){
  log_file = fopen("log.txt","w");
  initialize_token();
  scanner();
  printf("\n%s\n","tokens:");
  //debugger
  print_it();
}
