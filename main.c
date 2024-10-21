#include <stdio.h>
#include "eleicoes.h"

int main() {
    int numEleitores, numCandidatos = 0;
    int brancos = 0, nulos = 0;
    Chapa chapas[99];

    printf("==== SIMULACAO DE ELEICAO PARA PREFEITO ====\n\n");
    printf("Digite o numero de eleitores: ");
    scanf("%d", &numEleitores);

    printf("Digite o numero de candidatos: ");
    scanf("%d", &numCandidatos);
    printf("\n");

    cadastrarChapas(chapas, &numCandidatos, 99);

    printf("\n=== INICIO DA VOTACAO DO PRIMEIRO TURNO ===\n\n");
    for (int i = 0; i < numEleitores; i++) {
        printf("== Eleitor %d de %d ==\n", i + 1, numEleitores);
        exibirCandidatos(chapas, numCandidatos);
        registrarVoto(chapas, numCandidatos, &brancos, &nulos);
        printf("\n");
    }

    int votosValidos = numEleitores - brancos - nulos;
    int vencedor = calcularSegundoTurno(chapas, numCandidatos, numEleitores, votosValidos);

    int segundoTurno = 0;
    int candidatosSegundoTurno[2];
    int brancosSegundoTurno = 0, nulosSegundoTurno = 0;
    int vencedorFinal = -1;

    if (vencedor == -1) {
        printf("\n=== RESULTADO FINAL ===\n");
        printf("Nenhum candidato obteve mais de 50%% dos votos validos.\n");
        printf("Havera segundo turno!\n");

        segundoTurno = 1;
        encontrarDoisMaisVotados(chapas, numCandidatos, candidatosSegundoTurno);

        printf("\n=== INICIO DA VOTACAO DO SEGUNDO TURNO ===\n\n");
        for (int i = 0; i < numEleitores; i++) {
            printf("== Eleitor %d de %d ==\n", i + 1, numEleitores);
            exibirCandidatosSegundoTurno(chapas, candidatosSegundoTurno);
            registrarVotoSegundoTurno(chapas, candidatosSegundoTurno, &brancosSegundoTurno, &nulosSegundoTurno);
            printf("\n");
        }

        vencedorFinal = encontrarVencedor(chapas, candidatosSegundoTurno);
    } else {
        vencedorFinal = vencedor; // Vencedor do primeiro turno
    }

    gerarBoletimFinal(chapas, numCandidatos, brancos, nulos, brancosSegundoTurno, nulosSegundoTurno, numEleitores, segundoTurno, candidatosSegundoTurno, vencedorFinal);

    printf("\n==========================================\n");
    return 0;
}
