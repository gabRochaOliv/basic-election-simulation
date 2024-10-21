
# Simulação de Eleição 

Este projeto é uma simulação de um sistema eleitoral para eleição de prefeito com suporte a dois turnos e desempate por idade. O sistema permite o cadastro de chapas, a realização de votação no primeiro turno, a geração de boletim de urna, e, se necessário, a realização de um segundo turno entre os dois candidatos mais votados. O critério de desempate entre candidatos empatados em votos é a idade, sendo eleito o candidato mais velho.

## Funcionalidades

- Cadastro de candidatos (nome, número, data de nascimento e nome do vice).
- Votação no primeiro turno com verificação de votos brancos e nulos.
- Geração de boletim de urna com os resultados do primeiro turno.
- Verificação se um candidato obteve mais de 50% dos votos válidos no primeiro turno.
- Realização de segundo turno entre os dois candidatos mais votados (se necessário).
- Geração de boletim de urna final com os resultados do segundo turno (se houver).
- Critério de desempate por idade em caso de candidatos empatados em votos.

## Estrutura de Dados

A estrutura principal utilizada no projeto é a estrutura `Chapa`, que armazena as seguintes informações:
- Nome do candidato
- Número do candidato
- Data de nascimento do candidato
- Nome do vice
- Contagem de votos no primeiro turno
- Contagem de votos no segundo turno

## Como executar

Para compilar e executar o programa, siga os passos abaixo:

1. Clone o repositório:
   ```
   git clone https://github.com/seu-usuario/simulacao-eleicao-prefeito.git
   ```
   
2. Compile os arquivos C:
   ```
   gcc main.c eleicoes.c -o simulacao_eleicao
   ```
   
3. Execute o programa:
   ```
   ./simulacao_eleicao
   ```

## Estrutura do Projeto

- `main.c`: Arquivo principal do programa, responsável pela execução da lógica principal.
- `eleicoes.c`: Implementação das funções relacionadas à simulação da eleição, como o cadastro de chapas, votação e geração do boletim de urna.
- `eleicoes.h`: Cabeçalhos das funções e definição da estrutura `Chapa`.

## Exemplo de Uso

Durante a execução, o programa solicitará o número de eleitores e candidatos, e então procederá com o cadastro das chapas. Em seguida, os eleitores poderão votar em seus candidatos, e o sistema calculará se haverá ou não um segundo turno.

Exemplo de execução:

```
==== SIMULACAO DE ELEICAO PARA PREFEITO ====

Digite o numero de eleitores: 5
Digite o numero de candidatos: 3

==== Cadastro do candidato 1 ====
Nome do candidato: Gabriel
Numero do candidato (1-99): 20
Data de nascimento (DD MM AAAA): 08 10 2000
Nome do vice: João

==== Cadastro do candidato 2 ====
Nome do candidato: Laura
Numero do candidato (1-99): 15
Data de nascimento (DD MM AAAA): 25 12 1995
Nome do vice: Maria

==== Cadastro do candidato 3 ====
Nome do candidato: Pedro
Numero do candidato (1-99): 30
Data de nascimento (DD MM AAAA): 17 07 1980
Nome do vice: Marcos

=== INICIO DA VOTACAO DO PRIMEIRO TURNO ===
...
```


