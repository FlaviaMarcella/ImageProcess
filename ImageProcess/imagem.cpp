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

int imagem_negativa (TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida) {

    *tomCinzaSaida = tomCinza;
    
    for (int i = 0; i < linha; i++) {
        for (int j = 0, pixel = 0; j < coluna; j++) {

            pixel = 255 - entrada[i][j];
            
            saida[i][j] = pixel;
            
            if(*tomCinzaSaida < pixel){
                *tomCinzaSaida = pixel;
            }

        }
    }
    

    return 0;
}

int imagem_binarizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida, int grau) {
    for (int i = 0; i < linha; ++i) {
        for (int j = 0; j < coluna; ++j) {
            
            if(entrada[i][j] > grau){
                saida[i][j] = tomCinza;
            }else{
                saida[i][j] = 0;
            }
            
        }
    }
    
    *tomCinzaSaida = tomCinza;
    
    return 0;
}

int imagem_iconizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida){

    int icon[64][64];
    
    double escala_x = linha/64.0;
    double escala_y = coluna/64.0;
    
    *tomCinzaSaida = tomCinza;
    
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            //saida[i][j] = entrada[static_cast<int>(i*escala_x)][static_cast<int>(j*escala_y)];
            
            icon[i][j] = entrada[static_cast<int>(i*escala_x)][static_cast<int>(j*escala_y)];
            
            if(*tomCinzaSaida < icon[i][j]){
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
