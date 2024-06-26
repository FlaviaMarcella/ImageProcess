/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   imagem.cpp
 * Author: fl-via-gon-alves
 *
 * Created on 24 de junho de 2024, 18:48
 */

#include <cstdlib>
#include <time.h>
#include "imagem.h"

using namespace std;

/*
 * 
 */

int ajustar_brilho(TMatriz entrada, TMatriz saida, int linha, int coluna, int *tomCinzaSaida, float modifica, bool clarear) {

    //static_cast garante que a multiplicação e divisão vai retornar um número inteiro, uma vez que estamos trabalhando com
    //pixeis e estes devem ser inteiros.

    int pixel = 0;

    if (clarear == true) {
        // Clarear imagem
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                pixel = entrada[i][j] + static_cast<int> (entrada[i][j] * modifica / 100);

                if (pixel > 255) {
                    pixel = 255;
                }

                saida[i][j] = pixel;

                if (*tomCinzaSaida < pixel) {
                    *tomCinzaSaida = pixel;
                }

            }
        }
    } else {

        // Escurecer imagem
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                pixel = entrada[i][j] - static_cast<int> (entrada[i][j] * modifica / 100);

                if (pixel < 0) {
                    pixel = 0;
                }

                saida[i][j] = pixel;

                if (*tomCinzaSaida < pixel) {
                    *tomCinzaSaida = pixel;
                }
            }
        }
    }

    return 0;

}

int imagem_negativa(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    *tomCinzaSaida = tomCinza;

    for (int i = 0; i < linha; i++) {
        for (int j = 0, pixel = 0; j < coluna; j++) {

            pixel = 255 - entrada[i][j];

            saida[i][j] = pixel;

            if (*tomCinzaSaida < pixel) {
                *tomCinzaSaida = pixel;
            }

        }
    }


    return 0;
}

int imagem_binarizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida, int grau) {
    for (int i = 0; i < linha; ++i) {
        for (int j = 0; j < coluna; ++j) {

            if (entrada[i][j] > grau) {
                saida[i][j] = tomCinza;
            } else {
                saida[i][j] = 0;
            }

        }
    }

    *tomCinzaSaida = tomCinza;

    return 0;
}

int imagem_iconizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    int icon[64][64];

    double escala_x = linha / 64.0;
    double escala_y = coluna / 64.0;

    *tomCinzaSaida = tomCinza;

    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            //saida[i][j] = entrada[static_cast<int>(i*escala_x)][static_cast<int>(j*escala_y)];

            icon[i][j] = entrada[static_cast<int> (i * escala_x)][static_cast<int> (j * escala_y)];

            if (*tomCinzaSaida < icon[i][j]) {
                *tomCinzaSaida = icon[i][j];
            }

        }
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            saida[i][j] = 0;
            saida[i][j] = icon[i][j];
        }
    }

    return 0;

}

int imagem_ruido(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    srand(time(0));

    *tomCinzaSaida = tomCinza;

    for (int i = 0; i < linha; i++) {
        for (int j = 0, pixel = 0; j < coluna; j++) {
            
            pixel = entrada[i][j] + (rand() % 61 - 30);
            
            // Garantir que o valor do pixel esteja dentro do intervalo permitido
            if (pixel < 0) pixel = 0;
            if (pixel > *tomCinzaSaida) pixel = *tomCinzaSaida;
            if (*tomCinzaSaida < saida[i][j]) *tomCinzaSaida = saida[i][j];
            
            saida[i][j] = pixel;
            
        }
    }

    return 0;

}

int filtro_linear(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {
    
    int tam = 3;
    int filtro_soma = 9;
    *tomCinzaSaida = tomCinza;

    int filtro[tam][tam] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    for (int i = 1; i < linha - 1; ++i) {
        for (int j = 1; j < coluna - 1; ++j) {
            
            int sum = 0;
            
            for (int k = 0; k < tam; ++k) {
                for (int l = 0; l < tam; ++l) {
                    sum += entrada[i + k - 1][j + l - 1] * filtro[k][l];
                }
            }
            
            saida[i][j] = sum / filtro_soma;
            if (*tomCinzaSaida < saida[i][j]) *tomCinzaSaida = saida[i][j];
        }
    }
    
    return 0;
}

void bubbleSort(int v[], int tam) {

    for (int i = tam; i > 0; i--) {

        for (int k = 0; k < i - 1; k++) {
            if (v[k] > v[k + 1]) {
                int aux = v[k];
                v[k] = v[k + 1];
                v[k + 1] = aux;
            }
        }

    }

}

int filtro_naoLinear(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida){
    
    int tamanhoFiltro = 3;
    int deslocamento = tamanhoFiltro / 2;
    *tomCinzaSaida = tomCinza;

    for (int i = deslocamento; i < linha - deslocamento; i++) {
        for (int j = deslocamento; j < coluna - deslocamento; j++) {
            
            int vizinhanca[9];
            int v = 0;
            
            for (int k = -deslocamento; k <= deslocamento; k++) {
                for (int l = -deslocamento; l <= deslocamento; l++) {
                    vizinhanca[v++] = entrada[i + k][j + l];
                }
            }
            bubbleSort(vizinhanca, 9);
            saida[i][j] = vizinhanca[4]; // Mediana da vizinhança de 3x3
            if (*tomCinzaSaida < saida[i][j]) *tomCinzaSaida = saida[i][j];
        }
    }
    
    return 0;
    
}

