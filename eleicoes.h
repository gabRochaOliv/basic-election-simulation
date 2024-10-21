#ifndef ELEICOES_H
#define ELEICOES_H

typedef struct {
    char nomeCandidato[50];
    int numeroCandidato;
    int diaNascimento, mesNascimento, anoNascimento;
    char nomeVice[50];
    int votosPrimeiroTurno;
    int votosSegundoTurno;
} Chapa;

void cadastrarChapas(Chapa chapas[], int *numChapas, int maxChapas);
void exibirCandidatos(Chapa chapas[], int numChapas);
void registrarVoto(Chapa chapas[], int numChapas, int *brancos, int *nulos);
void exibirCandidatosSegundoTurno(Chapa chapas[], int candidatosSegundoTurno[]);
void registrarVotoSegundoTurno(Chapa chapas[], int candidatosSegundoTurno[], int *brancos, int *nulos);
void encontrarDoisMaisVotados(Chapa chapas[], int numChapas, int candidatosSegundoTurno[]);
int calcularSegundoTurno(Chapa chapas[], int numChapas, int totalEleitores, int votosValidos);
int encontrarVencedor(Chapa chapas[], int candidatosSegundoTurno[]);
int compararIdade(Chapa c1, Chapa c2);
void gerarBoletimFinal(Chapa chapas[], int numChapas, int brancos, int nulos, int brancosSegundoTurno, int nulosSegundoTurno, int totalEleitores, int segundoTurno, int candidatosSegundoTurno[], int vencedorFinal);

#endif
