#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ---------------------- DECLARA��O DAS FUN��ES ----------------------
void Cifra(char texto[], int k);
void Decifra(char texto[], int k);
void ForcaBruta(char mensagem[]);
void AnaliseFrequencia(char mensagem[]);

// ---------------------- FUN��O PRINCIPAL ----------------------
int main() {
    char mensagemOriginal[] = "Flamengo e o melhor do mundo";
    char mensagemCifrada[256]; // Buffer para armazenar a cifra
    int k = 3;

    // Copia a mensagem original para o buffer de cifra
    strcpy(mensagemCifrada, mensagemOriginal);

    printf("Mensagem original: %s\n", mensagemOriginal);

    // Cifra a mensagem (usa o buffer separado)
    Cifra(mensagemCifrada, k);
    printf("Mensagem Cifrada: %s\n", mensagemCifrada);

    // Decifra a mensagem (para verifica��o)
    char mensagemDecifrada[256];
    strcpy(mensagemDecifrada, mensagemCifrada);
    Decifra(mensagemDecifrada, k);
    printf("Mensagem Decifrada: %s\n\n", mensagemDecifrada);

    // Ataques usando a mensagem cifrada
    ForcaBruta(mensagemCifrada);
    AnaliseFrequencia(mensagemCifrada);

    return 0;
}

// ---------------------- CIFRA DE C�SAR ----------------------
void Cifra(char texto[], int k) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            char base = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = ((texto[i] - base + k) % 26) + base;
        }
    }
}

// ---------------------- DECIFRA��O C�SAR ----------------------
void Decifra(char texto[], int k) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (isalpha(texto[i])) {
            char base = isupper(texto[i]) ? 'A' : 'a';
            texto[i] = ((texto[i] - base - k + 26) % 26) + base;
        }
    }
}

// ---------------------- FOR�A BRUTA ----------------------
void ForcaBruta(char mensagem[]) {
    printf("\nAtaque por Forca Bruta:\n");
    for (int chave = 1; chave < 26; chave++) {
        char tentativa[256];
        strcpy(tentativa, mensagem);
        Decifra(tentativa, chave);
        printf("Chave %2d: %s\n", chave, tentativa);
    }
}

// ---------------------- AN�LISE DE FREQU�NCIA ----------------------
void AnaliseFrequencia(char mensagem[]) {
    int freq[26] = {0};
    int totalLetras = 0;

    // Conta a frequ�ncia das letras no texto cifrado (case-insensitive)
    for (int i = 0; mensagem[i] != '\0'; i++) {
        if (isalpha(mensagem[i])) {
            char c = tolower(mensagem[i]);
            freq[c - 'a']++;
            totalLetras++;
        }
    }

    // Encontra a letra mais frequente
    int maxFreq = 0;
    char letraMaisFreq = 'a';
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            letraMaisFreq = 'a' + i;
        }
    }

    // Letras mais comuns em portugu�s (ordem decrescente de frequ�ncia)
    char letrasPortugues[] = {'a', 'e', 'o', 's', 'r', 'i', 'n', 'd', 'm', 'u'};

    printf("\nAtaque por Analise de Frequencia:\n");
    printf("Letra mais frequente no texto cifrado: %c\n", letraMaisFreq);
    printf("Frequencia: %d/%d\n", maxFreq, totalLetras);

    // Testa cada letra comum como poss�vel correspondente
    for (int i = 0; i < 10; i++) {
        // Calcula a chave: (letra_cifrada - letra_portugues + 26) % 26
        int chave = (letraMaisFreq - letrasPortugues[i] + 26) % 26;
        char tentativa[256];
        strcpy(tentativa, mensagem);
        Decifra(tentativa, chave);
        printf("Chave %2d (%c->%c): %s\n", chave, letraMaisFreq, letrasPortugues[i], tentativa);
    }
}
