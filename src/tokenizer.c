#include <types.h>
#include <commons.h>
#include <stdio.h>

char *buffer;
long file_size;

struct Tokenizer{
  int chain_id;
  char lexeme_chain[20];
  int chain_size;
}t[50];

int chain_id=0;

void initialize_token(){
  for(int i=0;i<50;i++){
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
    t[chain_id].chain_id = chain_id;
    chain_id++;
  }
  if(lexeme=='{'||lexeme=='}'||lexeme=='['||lexeme==']'||lexeme=='('||lexeme==')'){
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    t[chain_id].chain_id = chain_id;
    chain_id++;
  }
  if(lexeme==','||lexeme=='.'){
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    t[chain_id].chain_id = chain_id;
    chain_id++;
  }
  if((lexeme>='a'&&lexeme<='z')||(lexeme>='A'&&lexeme<='Z')||(lexeme>='0'&&lexeme<='9')){
    t[chain_id].chain_id = chain_id;
    t[chain_id].lexeme_chain[t[chain_id].chain_size++] = lexeme;
    if(n_lexeme==' ') chain_id++;
    if(n_lexeme=='\n') chain_id++;
    if(n_lexeme==';') chain_id++;
    if(n_lexeme=='+') chain_id++;
    if(n_lexeme=='-') chain_id++;
    if(n_lexeme=='*') chain_id++;
    if(n_lexeme=='/') chain_id++;
    if(n_lexeme=='=') chain_id++;
    if(n_lexeme=='{') chain_id++;
    if(n_lexeme=='}') chain_id++;
    if(n_lexeme=='[') chain_id++;
    if(n_lexeme==']') chain_id++;
    if(n_lexeme=='(') chain_id++;
    if(n_lexeme==')') chain_id++;
    if(n_lexeme==',') chain_id++;
    if(n_lexeme=='.') chain_id++;
  }
}

void tokenizer(){
  printf("\n%s\n","tokens:");
  char lexeme;
  int counter=-1;
  while(true){
    counter++;
    if(counter>file_size) break;
    lexeme = *(buffer+counter);
    supply_lexeme(lexeme,counter);
  }
  for(int i=0;i<50;i++){
    printf("token id:%d::%s\n",t[i].chain_id,t[i].lexeme_chain);
  }
}
