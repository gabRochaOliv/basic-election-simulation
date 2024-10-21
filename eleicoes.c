#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include "eleicoes.h"

void limparTela() {
    system(CLEAR);
}


int compararIdade(Chapa c1, Chapa c2) {
    if (c1.anoNascimento < c2.anoNascimento) return 1;
    if (c1.anoNascimento > c2.anoNascimento) return 0;

    if (c1.mesNascimento < c2.mesNascimento) return 1;
    if (c1.mesNascimento > c2.mesNascimento) return 0;

    return c1.diaNascimento < c2.diaNascimento;
}

void cadastrarChapas(Chapa chapas[], int *numChapas, int maxChapas) {
    for (int i = 0; i < *numChapas; i++) {
        printf("==== Cadastro do candidato %d ====\n", i + 1);
        printf("Nome do candidato: ");
        scanf(" %[^\n]", chapas[i].nomeCandidato);
        printf("Numero do candidato (1-99): ");
        scanf("%d", &chapas[i].numeroCandidato);
        printf("Data de nascimento (DD MM AAAA): ");
        scanf("%d %d %d", &chapas[i].diaNascimento, &chapas[i].mesNascimento, &chapas[i].anoNascimento);
        printf("Nome do vice: ");
        scanf(" %[^\n]", chapas[i].nomeVice);
        chapas[i].votosPrimeiroTurno = 0;
        chapas[i].votosSegundoTurno = 0;
        printf("\n");
    }
}

void exibirCandidatos(Chapa chapas[], int numChapas) {
    printf("\nCandidatos disponiveis:\n");
    for (int i = 0; i < numChapas; i++) {
        printf(" [%d] %s com vice %s\n", chapas[i].numeroCandidato, chapas[i].nomeCandidato, chapas[i].nomeVice);
    }
    printf("\n");
}

void exibirCandidatosSegundoTurno(Chapa chapas[], int candidatosSegundoTurno[]) {
    printf("\nCandidatos disponiveis no segundo turno:\n");
    for (int i = 0; i < 2; i++) {
        printf(" [%d] %s com vice %s\n", chapas[candidatosSegundoTurno[i]].numeroCandidato, chapas[candidatosSegundoTurno[i]].nomeCandidato, chapas[candidatosSegundoTurno[i]].nomeVice);
    }
    printf("\n");
}

void registrarVoto(Chapa chapas[], int numChapas, int *brancos, int *nulos) {
    int voto;
    printf("Digite o numero do candidato ou 0 para branco: ");
    scanf("%d", &voto);

    if (voto == 0) {
        (*brancos)++;
        printf("Seu voto em branco foi confirmado!\n");
    } else {
        int votoValido = 0;
        for (int i = 0; i < numChapas; i++) {
            if (chapas[i].numeroCandidato == voto) {
                chapas[i].votosPrimeiroTurno++;
                printf("Seu voto em %s com vice %s foi confirmado!\n", chapas[i].nomeCandidato, chapas[i].nomeVice);
                votoValido = 1;
                break;
            }
        }
        if (!votoValido) {
            (*nulos)++;
            printf("Voto nulo confirmado!\n");
        }
    }

    sleep(2);
    limparTela();
}

void registrarVotoSegundoTurno(Chapa chapas[], int candidatosSegundoTurno[], int *brancos, int *nulos) {
    int voto;
    printf("Digite o numero do candidato ou 0 para branco: ");
    scanf("%d", &voto);

    if (voto == 0) {
        (*brancos)++;
        printf("Seu voto em branco foi confirmado!\n");
    } else {
        int votoValido = 0;
        for (int i = 0; i < 2; i++) {
            if (chapas[candidatosSegundoTurno[i]].numeroCandidato == voto) {
                chapas[candidatosSegundoTurno[i]].votosSegundoTurno++;
                printf("Seu voto em %s com vice %s foi confirmado!\n", chapas[candidatosSegundoTurno[i]].nomeCandidato, chapas[candidatosSegundoTurno[i]].nomeVice);
                votoValido = 1;
                break;
            }
        }
        if (!votoValido) {
            (*nulos)++;
            printf("Voto nulo confirmado!\n");
        }
    }

    sleep(2);
    limparTela();
}

void encontrarDoisMaisVotados(Chapa chapas[], int numChapas, int candidatosSegundoTurno[]) {
    int maior = -1, segundoMaior = -1;

    for (int i = 0; i < numChapas; i++) {
        if (maior == -1 || chapas[i].votosPrimeiroTurno > chapas[maior].votosPrimeiroTurno ||
            (chapas[i].votosPrimeiroTurno == chapas[maior].votosPrimeiroTurno && compararIdade(chapas[i], chapas[maior]))) {
            segundoMaior = maior;
            maior = i;
        } else if (segundoMaior == -1 || chapas[i].votosPrimeiroTurno > chapas[segundoMaior].votosPrimeiroTurno ||
                   (chapas[i].votosPrimeiroTurno == chapas[segundoMaior].votosPrimeiroTurno && compararIdade(chapas[i], chapas[segundoMaior]))) {
            segundoMaior = i;
        }
    }
    candidatosSegundoTurno[0] = maior;
    candidatosSegundoTurno[1] = segundoMaior;
}

int encontrarVencedor(Chapa chapas[], int candidatosSegundoTurno[]) {
    if (chapas[candidatosSegundoTurno[0]].votosSegundoTurno > chapas[candidatosSegundoTurno[1]].votosSegundoTurno) {
        return candidatosSegundoTurno[0];
    } else if (chapas[candidatosSegundoTurno[0]].votosSegundoTurno < chapas[candidatosSegundoTurno[1]].votosSegundoTurno) {
        return candidatosSegundoTurno[1];
    } else {
        return compararIdade(chapas[candidatosSegundoTurno[0]], chapas[candidatosSegundoTurno[1]]) ? candidatosSegundoTurno[0] : candidatosSegundoTurno[1];
    }
}

int calcularSegundoTurno(Chapa chapas[], int numChapas, int totalEleitores, int votosValidos) {
    for (int i = 0; i < numChapas; i++) {
        if (chapas[i].votosPrimeiroTurno > (votosValidos / 2)) {
            return i;
        }
    }
    return -1;
}

void gerarBoletimFinal(Chapa chapas[], int numChapas, int brancos, int nulos, int brancosSegundoTurno, int nulosSegundoTurno, int totalEleitores, int segundoTurno, int candidatosSegundoTurno[], int vencedorFinal) {
    FILE *boletim;
    boletim = fopen("boletim_final.txt", "w");

    int votosValidosPrimeiroTurno = totalEleitores - brancos - nulos;

    fprintf(boletim, "Boletim de Urna - Final\n");
    fprintf(boletim, "Total de eleitores: %d\n", totalEleitores);
    fprintf(boletim, "Votos validos no primeiro turno: %d\n", votosValidosPrimeiroTurno);
    fprintf(boletim, "Votos brancos no primeiro turno: %d\n", brancos);
    fprintf(boletim, "Votos nulos no primeiro turno: %d\n", nulos);

    for (int i = 0; i < numChapas; i++) {
        float porcentagem = (float)chapas[i].votosPrimeiroTurno / votosValidosPrimeiroTurno * 100;
        fprintf(boletim, "Chapa %d - %s com %s: %d votos (%.2f%%)\n",
                chapas[i].numeroCandidato, chapas[i].nomeCandidato, chapas[i].nomeVice, chapas[i].votosPrimeiroTurno, porcentagem);
    }

    if (segundoTurno) {
        fprintf(boletim, "\n=== SEGUNDO TURNO ===\n");

        int votosValidosSegundoTurno = totalEleitores - brancosSegundoTurno - nulosSegundoTurno;

        fprintf(boletim, "Votos validos no segundo turno: %d\n", votosValidosSegundoTurno);
        fprintf(boletim, "Votos brancos no segundo turno: %d\n", brancosSegundoTurno);
        fprintf(boletim, "Votos nulos no segundo turno: %d\n", nulosSegundoTurno);

        for (int i = 0; i < 2; i++) {

            float porcentagemSegundoTurno = (float)chapas[candidatosSegundoTurno[i]].votosSegundoTurno / votosValidosSegundoTurno * 100;
            fprintf(boletim, "Chapa %d - %s com %s: %d votos (%.2f%%)\n",
                    chapas[candidatosSegundoTurno[i]].numeroCandidato,
                    chapas[candidatosSegundoTurno[i]].nomeCandidato,
                    chapas[candidatosSegundoTurno[i]].nomeVice,
                    chapas[candidatosSegundoTurno[i]].votosSegundoTurno,
                    porcentagemSegundoTurno);
        }

        fprintf(boletim, "\nVencedor do segundo turno: %s com %d votos!\n", chapas[vencedorFinal].nomeCandidato, chapas[vencedorFinal].votosSegundoTurno);
    } else {
        fprintf(boletim, "\nVencedor do primeiro turno: %s com %d votos!\n", chapas[vencedorFinal].nomeCandidato, chapas[vencedorFinal].votosPrimeiroTurno);
    }

    fclose(boletim);
}
