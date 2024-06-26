/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   imagem.h
 * Author: fl-via-gon-alves
 *
 * Created on 24 de junho de 2024, 18:23
 */

#ifndef IMAGEM_H
#define IMAGEM_H

//declaração do tipo de matriz para leitura e gravação da imagem
typedef int TMatriz[1024][1024];


//assinatura das funções desenvolvidas no arquivo imagem.cpp
int ajustar_brilho(TMatriz entrada, TMatriz saida, int linha, int coluna, int *tomCinzaSaida, float modifica, bool clarear);
int imagem_negativa (TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida);
int imagem_binarizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida, int grau);
int imagem_iconizada(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida);
int imagem_ruido(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida);
int filtro_linear(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida);
int filtro_naoLinear(TMatriz entrada, TMatriz saida, int linha, int coluna, int tomCinza, int *tomCinzaSaida);
void bubbleSort(int v[], int tam);

#endif /* IMAGEM_H */

