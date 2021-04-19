# Projeto 2 - 2020/2

#### Aluno: Eduardo Vieira Lima
#### Matrícula: 17/0102343

## Instrucões de uso
- Para compilar o projeto é necessário possuir os módulos ncurses e wiringPi instalados no sistema
- O comando para compilar o projeto é ``` make```, a partir da pasta Trabalho2/central para o servidor central
 e Trabalho2/distribuido para o servidor distribuído
- Após compilar, basta executar ``` make run```
- Para limpar os binários gerados, execute ``` make clean```

## Importante

- É necessário executar primeiro o servidor central e então o distribuído.
- Para desligar o servidor distribuído basta enviar um sinal (ou CTRL + C no terminal);
- Os endereços de IP configurados no projeto mudaram durante testes, talvez seja necessário validá-los em caso de erro