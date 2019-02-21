#include <types.h>
#include <commons.h>
#include <stdio.h>

char *buffer;
long file_size;

enum token_type{
  no_type,
  identifier,
  constant, //add more types here
  string
};

struct Tokenizer{
  int token_type;
  int chain_id;
  char lexeme_chain[50];
  int chain_size;
}t[100];

int chain_id=0;

void initialize_token(){
  for(int i=0;i<100;i++){
    t[i].token_type = no_type;
    t[i].chain_id = i;
    for(int j=0;j<20;j++){
      t[i].lexeme_chain[j] = 0;
    }
    t[i].chain_size = 0;
  }
}

void supply_lexeme(char lexeme,int counter){
  char n_lexeme = *(buffer+counter+1);
  if(lexeme==';'||lexeme=='+'||lexeme=='-'||lexeme=='*'||lexeme=='/'||lexeme=='='){
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    if(t[chain_id].token_type!=string){
      chain_id++;
    }
    return;
  }
  if(lexeme=='{'||lexeme=='}'||lexeme=='['||lexeme==']'||lexeme=='('||lexeme==')'){
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    if(t[chain_id].token_type!=string){
      chain_id++;
    }
    return;
  }
  if(lexeme==','||lexeme=='.'){
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    if(t[chain_id].token_type!=string){
      chain_id++;
    }
    return;
  }
  if(lexeme=='"'){
    if(t[chain_id-1].token_type!=string)
    t[chain_id].token_type = string;
    return;
  }
  if(lexeme==' '||lexeme=='\\'||lexeme=='~'||lexeme=='`'||lexeme=='!'||lexeme=='@'||lexeme=='#'||lexeme=='$'||lexeme=='%'||lexeme=='^'||lexeme=='&'||lexeme=='/'||lexeme=='|'||lexeme==':'||lexeme=='?'){
    if(t[chain_id].token_type == string){
      t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    }
    return;
  }
  if((lexeme>='a'&&lexeme<='z')||(lexeme>='A'&&lexeme<='Z')||(lexeme>='0'&&lexeme<='9')){
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    if(t[chain_id].token_type == string){
      switch(n_lexeme){
        case '"' : chain_id++;return;
        default  : return;
      }
    }
    switch(n_lexeme){
      case ' ' :{chain_id++; break;}
      case '\n':{chain_id++; break;}
      case ';' :{chain_id++; break;}
      case '+' :{chain_id++; break;}
      case '-' :{chain_id++; break;}
      case '*' :{chain_id++; break;}
      case '/' :{chain_id++; break;}
      case '=' :{chain_id++; break;}
      case '{' :{chain_id++; break;}
      case '}' :{chain_id++; break;}
      case '[' :{chain_id++; break;}
      case ']' :{chain_id++; break;}
      case '(' :{chain_id++; break;}
      case ')' :{chain_id++; break;}
      case ',' :{chain_id++; break;}
      case '.' :{chain_id++; break;}
      case '"' :{chain_id++; break;}
    }
  }
}

void tokenizer(){
  initialize_token();
  printf("\n%s\n","tokens:");
  char lexeme;
  int counter=-1;
  while(true){
    counter++;
    if(counter>file_size) break;
    lexeme = *(buffer+counter);
    supply_lexeme(lexeme,counter);
  }
  for(int i=0;i<100;i++){
    printf("token id:%d::%s\n",t[i].chain_id,t[i].lexeme_chain);
    //printf("token id:%d::%s::type::%d\n",t[i].chain_id,t[i].lexeme_chain,t[i].token_type);
  }
}
