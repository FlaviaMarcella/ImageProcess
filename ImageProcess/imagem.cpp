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
                pixel = entrada[i][j] + static_cast<int>(entrada[i][j] * modifica / 100);
                
                if (pixel > 255) {
                    pixel = 255;
                }
                
                saida[i][j] = pixel;
                
                if(*tomCinzaSaida < pixel){
                    *tomCinzaSaida = pixel;
                }
                
            }
        }
    } else {
        
        // Escurecer imagem
        for (int i = 0; i < linha; i++) {
            for (int j = 0; j < coluna; j++) {
                pixel = entrada[i][j] - static_cast<int>(entrada[i][j] * modifica / 100);
                
                if (pixel < 0) {
                    pixel = 0;
                }
                
                saida[i][j] = pixel;
                
                if(*tomCinzaSaida < pixel){
                    *tomCinzaSaida = pixel;
                }
            }
        }
    }
    
    return 0;
    
}

/*int ajustar_brilho(TMatriz entrada, TMatriz saida, int linha, int coluna, double modifica) {
    
    //static_cast garante que a multiplicação e divisão vai retornar um número inteiro, uma vez que estamos trabalhando com
    //pixeis e estes devem ser inteiros.
    
        
        for (int i = 0; i < linha; i++) {
            for (int j = 0, pixel = 0; j < coluna; j++) {
                
                pixel = entrada[i][j] + (entrada[i][j] * modifica / 100);
                
                if (pixel > 255) {
                    pixel = 255;
                }
                
                saida[i][j] = pixel;
                
            }
        }
    
    return 0;
    
}*/

int brilho (TMatriz imagem, int coluna, int linha, TMatriz saida) {

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {

            saida[i][j] = imagem[i][j] + 1;
            //saida[i][j] = imagem[i][j] + (imagem[i][j] * mod/100);

        }
    }

    return 0;
}



