#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Estrutura para representar uma coordenada
typedef struct {
    int x;
    int y;
} Coordenada;

// Função para inicializar o tabuleiro
void inicializarTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = '~'; // Água
        }
    }
}

// Função para verificar se uma posição está livre
int posicaoLivre(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y) {
    if (x < 0 || x >= TAMANHO_TABULEIRO || y < 0 || y >= TAMANHO_TABULEIRO) {
        return 0; // Fora dos limites
    }
    return tabuleiro[x][y] == '~'; // Retorna 1 se a posição está livre (água)
}

// Função para validar posicionamento horizontal
int validarNavioHorizontal(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y) {
    // Verificar se o navio cabe no tabuleiro
    if (y + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;
    }
    
    // Verificar se todas as posições estão livres
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, x, y + i)) {
            return 0;
        }
    }
    return 1;
}

// Função para validar posicionamento vertical
int validarNavioVertical(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int x, int y) {
    // Verificar se o navio cabe no tabuleiro
    if (x + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        return 0;
    }
    
    // Verificar se todas as posições estão livres
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (!posicaoLivre(tabuleiro, x + i, y)) {
            return 0;
        }
    }
    return 1;
}

// Função para posicionar navio horizontalmente
int posicionarNavioHorizontal(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                               Coordenada coordenadas[], int x, int y, char simbolo) {
    if (!validarNavioHorizontal(tabuleiro, x, y)) {
        printf("ERRO: Não é possível posicionar o navio horizontal na posição (%d, %d)\n", x, y);
        return 0; // Falha no posicionamento
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[x][y + i] = simbolo;
        coordenadas[i].x = x;
        coordenadas[i].y = y + i;
    }
    printf("Navio horizontal posicionado com sucesso na posição (%d, %d)\n", x, y);
    return 1; // Sucesso
}

// Função para posicionar navio verticalmente
int posicionarNavioVertical(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                             Coordenada coordenadas[], int x, int y, char simbolo) {
    if (!validarNavioVertical(tabuleiro, x, y)) {
        printf("ERRO: Não é possível posicionar o navio vertical na posição (%d, %d)\n", x, y);
        return 0; // Falha no posicionamento
    }
    
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[x + i][y] = simbolo;
        coordenadas[i].x = x + i;
        coordenadas[i].y = y;
    }
    printf("Navio vertical posicionado com sucesso na posição (%d, %d)\n", x, y);
    return 1; // Sucesso
}

// Função para exibir as coordenadas do navio
void exibirCoordenadas(Coordenada coordenadas[], char tipo[], char simbolo) {
    printf("\n=== COORDENADAS DO NAVIO %s (%c) ===\n", tipo, simbolo);
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        printf("Parte %d: X=%d, Y=%d\n", i + 1, coordenadas[i].x, coordenadas[i].y);
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d  ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    Coordenada navio1[TAMANHO_NAVIO]; // Navio horizontal
    Coordenada navio2[TAMANHO_NAVIO]; // Navio vertical
    Coordenada navio3[TAMANHO_NAVIO]; // Navio vertical
    
    // Entrada de dados manual (coordenadas dos navios)
    int navio1_x = 2, navio1_y = 1; // Posição inicial do primeiro navio (horizontal)
    int navio2_x = 2, navio2_y = 2; // Posição inicial do segundo navio (vertical) - vai sobrepor para testar
    int navio3_x = 5, navio3_y = 5; // Posição inicial do terceiro navio (vertical)
    
    printf("=== JOGO DE BATALHA NAVAL ===\n");
    printf("Inicializando tabuleiro...\n");
    
    // Inicializar tabuleiro0
    inicializarTabuleiro(tabuleiro);
    
    // Posicionar navios com validação
    printf("Posicionando navios...\n");
    int navio1_ok = posicionarNavioHorizontal(tabuleiro, navio1, navio1_x, navio1_y, 'H');
    int navio2_ok = posicionarNavioVertical(tabuleiro, navio2, navio2_x, navio2_y, 'V');
    int navio3_ok = posicionarNavioVertical(tabuleiro, navio3, navio3_x, navio3_y, 'V');    
    // Exibir coordenadas apenas dos navios posicionados com sucesso
    if (navio1_ok) {
        exibirCoordenadas(navio1, "HORIZONTAL", 'H');
    }
    if (navio2_ok) {
        exibirCoordenadas(navio2, "VERTICAL", 'V');
    }
    if (navio3_ok) {
        exibirCoordenadas(navio3, "VERTICAL", 'V');
    }
    
    // Exibir tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    printf("\nLegenda:\n");
    printf("~ = Água\n");
    printf("H = Navio Horizontal\n");
    printf("V = Navio Vertical\n");
    
    return 0;
}
