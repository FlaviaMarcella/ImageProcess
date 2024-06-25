/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: fl-via-gon-alves
 *
 * Created on 24 de junho de 2024, 17:58
 */

#include "imagem.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <filesystem>

using namespace std;

/*
 * 
 */

int lerArquivo(string nameFile, TMatriz imagem, int *tomCinza, int *coluna, int *linha) {

    char tipo[3];

    ifstream arquivo(nameFile);

    if (!arquivo.is_open()) {
        return 1;
    }

    arquivo >> tipo;

    //if (tipo != "P2") {
    if (strcmp(tipo, "P2") != 0) {
        return 1;
    }

    arquivo >> *coluna;
    arquivo >> *linha;
    arquivo >> *tomCinza;

    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {

            arquivo >> imagem[i][j];

        }
    }

    arquivo.close();

    return 0;

}

int salvaArquivo(string nameFile, TMatriz imagem, int tomCinza, int coluna, int linha) {

    ofstream arquivo(nameFile);

    if (!arquivo.is_open()) {
        return 1;
    }

    arquivo << "P2" << endl;

    arquivo << coluna << " " << linha << endl;
    arquivo << tomCinza << endl;

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {

            arquivo << imagem[i][j] << " ";

        }
        arquivo << "\n";
    }

    arquivo.close();

    return 0;
}

int main() {

    int opcao = -1, tomCinza = 0, linha = 0, coluna = 0;
    int mod = -1, tomCinzaSaida = 0;
    double modifica = 0;
    string inputFile;
    TMatriz imagem;

    do {

        cout << "\n\t Opção: ";
        cin >> opcao;

        if (opcao == 0) {
            cout << "\n\t Encerrando execução do programa...";
        }

        switch (opcao) {
            case 0:
                break;
            case 1:

                cout << "\n\t Insira o nome do arquivo (.txt): \n\t | ";
                cin >> inputFile;
                
                if (lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha) == 0) {
                    cout << "\n\t Arquivo lido com sucesso!" << endl;
                } else {
                    cout << "\n\t Erro na leitura do arquivo!" << endl;
                }

                break;
            case 2:

                cout << "\n\t Selecionado: Tratamento de Imagem" << endl;
                cout << "\n\t   Você deseja: ";
                cout << "\n\t\t 0 - Voltar";
                cout << "\n\t\t 1 - Clarear";
                cout << "\n\t\t 2 - Escurecer" << endl;

                cout << "\n\t Opção: ";
                cin >> mod;

                switch (mod) {

                    case 1:
                        
                        cout << "\n\t Opção selecionada: Clarear imagem" << endl;
                        cout << "\n\t Quanto voce deseja, clarear (0.0%)? ";
                        cout << "\n\t | ";
                        cin >> modifica;

                        if (modifica > 100 || modifica < 0) {
                            cout << "\n\t Valor inválido, insira novamente..." << endl;
                            cout << "\n\t | ";
                            cin >> modifica;
                        }

                        if ( ajustar_brilho(imagem, imagem, linha, coluna, &tomCinzaSaida, modifica, true) == 0) {
                            cout << "\n\t Imagem alterada com sucesso!" << endl;
                        } else {
                            cout << "\n\t Erro ao ajustar imagem!" << endl;
                        }

                        salvaArquivo("imagemClareada.pgm", imagem, tomCinzaSaida, coluna, linha);
                        lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);

                        break;
                    case 2:

                        cout << "\n\t Opção selecionada: Escurecer imagem";
                        cout << "\n\t Quanto voce deseja, Escurecer (0.0%)? ";
                        cout << "\n\t | ";
                        cin >> modifica;

                        if (modifica > 100 || modifica < 0) {
                            cout << "\n\t Valor inválido, insira novamente..." << endl;
                            cout << "\n\t | ";
                            cin >> modifica;
                        }
                        
                        if (ajustar_brilho(imagem, imagem, linha, coluna, &tomCinzaSaida, modifica, false) == 0) {
                            cout << "\n\t Imagem alterada com sucesso!" << endl;
                        } else {
                            cout << "\n\t Erro ao ajustar imagem!" << endl;
                        }


                        salvaArquivo("imagemEscurecida.pgm", imagem, tomCinzaSaida, coluna, linha);
                        lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);

                        break;
                    default:
                        cout << "\n\t Opção inválida!";
                        break;

                }
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                cout << "\n\t Opção inválida..." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}

