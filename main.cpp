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

/* Author: Flávia Marcella Gonalves Moreira RA: 2024.1.08.025
 * Projeto: Processamento de Imagens PGM
 * Descrição: Este projeto implementa diversas operações de processamento de imagem em arquivos PGM,
 *            incluindo ajuste de brilho, criação de imagem negativa, binarização, iconização, adição de ruído,
 *            e aplicação de filtros (linear e não-linear). O usuário pode interagir com o programa por meio
 *            de um menu de opções, permitindo carregar, modificar e salvar imagens.
 * 
 *            Inserir as imagens para modificação no diretório:
 *                 * ImageProcess/Imagens 
 *            Todas as imagens alteradas serão salvos no mesmo diretório.
 */

#include "imagem.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

//Função para ler o arquivo PGM 
int lerArquivo(string nameFile, TMatriz imagem, int *tomCinza, int *coluna, int *linha) {

    char tipo[3];

    // Cria o diretório se não existir
    fs::create_directories("Imagens");

    string filePath = "Imagens/" + nameFile;

    ifstream arquivo(filePath); // Abre o arquivo

    if (!arquivo.is_open()) {
        return 1; // Retorna 1 se não conseguir abrir o arquivo
    }

    arquivo >> tipo; // Lê o tipo do arquivo

    if (strcmp(tipo, "P2") != 0) {
        return 1; // Retorna 1 se o tipo do arquivo não for P2 (PGM)
    }

    arquivo >> *coluna; // Lê o número de colunas
    arquivo >> *linha; // Lê o número de linhas
    arquivo >> *tomCinza; // Lê o valor máximo do tom de cinza

    for (int i = 0; i < *linha; i++) {
        for (int j = 0; j < *coluna; j++) {
            arquivo >> imagem[i][j]; // Lê os pixels da imagem
        }
    }

    arquivo.close(); // Fecha o arquivo

    return 0; // Retorna 0 se a leitura for bem-sucedida
}

//Função para salvar um arquivo PGM
int salvaArquivo(string nameFile, TMatriz imagem, int tomCinza, int coluna, int linha) {

    // Cria o diretório se não existir
    fs::create_directories("Imagens");

    string filePath = "Imagens/" + nameFile + ".pgm";

    ofstream arquivo(filePath); // Abre o arquivo para escrita

    if (!arquivo.is_open()) {
        return 1; // Retorna 1 se não conseguir abrir o arquivo
    }

    arquivo << "P2" << endl; // Escreve o tipo do arquivo

    arquivo << coluna << " " << linha << endl; // Escreve as dimensões da imagem
    arquivo << tomCinza << endl; // Escreve o valor máximo do tom de cinza

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            arquivo << imagem[i][j] << " "; // Escreve os pixels da imagem
        }
        arquivo << "\n"; // Nova linha após cada linha de pixels
    }

    arquivo.close(); // Fecha o arquivo

    return 0; // Retorna 0 se a escrita for bem-sucedida
}

int main() {

    int opcao = -1, tomCinza = 0, linha = 0, coluna = 0;
    int mod = -1, tomCinzaSaida = 0;
    double modifica = 0;
    string inputFile, name, ext;
    TMatriz imagem;

    do {

        cout << "\n\t -------------------------------------------";
        cout << "\n\t Menu de Opções";
        cout << "\n\t 1. Ler imagem de entrada (formato PGM) ";
        cout << "\n\t 2. Escurecer ou clarear imagem ";
        cout << "\n\t 3. Encontrar a imagem negativa ";
        cout << "\n\t 4. Binarizar a imagem ";
        cout << "\n\t 5. Iconizar a imagem ";
        cout << "\n\t 6. Criar ruídos na imagem ";
        cout << "\n\t 7. Aplicar filtro para suavizar a imagem ";
        cout << "\n\t 0. Sair";
        cout << "\n\t -------------------------------------------";

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

                    // Encontrando a posição do ponto na string
                    size_t pos = inputFile.find('.');

                    if (pos != std::string::npos) { // Se encontrou o ponto
                        name = inputFile.substr(0, pos); // Parte antes do ponto
                        ext = inputFile.substr(pos + 1); // Parte depois do ponto

                    }

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

                        if (ajustar_brilho(imagem, imagem, linha, coluna, &tomCinzaSaida, modifica, true) == 0) {
                            salvaArquivo(name +"_Clareada", imagem, tomCinzaSaida, coluna, linha);
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);

                            cout << "\n\t Imagem alterada com sucesso!" << endl;
                        } else {
                            cout << "\n\t Erro ao ajustar imagem!" << endl;
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                        }


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
                            salvaArquivo(name +"_Escurecida", imagem, tomCinzaSaida, coluna, linha);
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                            cout << "\n\t Imagem alterada com sucesso!" << endl;
                        } else {
                            cout << "\n\t Erro ao ajustar imagem!" << endl;
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                        }
                        break;
                    default:
                        cout << "\n\t Opção inválida!";
                        break;

                }

                break;
            case 3:

                cout << "\n\t Selecionado: Imagem Negativa" << endl;

                if (imagem_negativa(imagem, imagem, linha, coluna, tomCinza, &tomCinzaSaida) == 0) {
                    salvaArquivo(name +"_Negativa", imagem, tomCinzaSaida, coluna, linha);
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                    cout << "\n\t Imagem criada com sucesso!" << endl;
                } else {
                    cout << "\n\t Erro na criação da imagem!" << endl;
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                }


                break;
            case 4:

                cout << "\n\t Selecionado: Binarizar Imagem" << endl;

                cout << "\n\t Quanto voce deseja, binarizar? ";
                cout << "\n\t | ";
                cin >> modifica;

                if (modifica > 255 || modifica < 0) {
                    cout << "\n\t Valor inválido, insira novamente..." << endl;
                    cout << "\n\t | ";
                    cin >> modifica;
                }

                if (imagem_binarizada(imagem, imagem, linha, coluna, tomCinza, &tomCinzaSaida, modifica) == 0) {
                    salvaArquivo(name +"_Binarizada", imagem, tomCinzaSaida, coluna, linha);
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                    cout << "\n\t Imagem criada com sucesso!" << endl;
                } else {
                    cout << "\n\t Erro na criação da imagem!" << endl;
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                }

                break;
            case 5:

                cout << "\n\t Selecionado: Imagem Iconizada 64x64" << endl;

                if (imagem_iconizada(imagem, imagem, linha, coluna, tomCinza, &tomCinzaSaida) == 0) {
                    salvaArquivo(name +"_Iconizada", imagem, tomCinzaSaida, 64, 64);
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                    cout << "\n\t Imagem criada com sucesso!" << endl;
                } else {
                    cout << "\n\t Erro na criação da imagem!" << endl;
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                }

                break;
            case 6:

                cout << "\n\t Selecionado: Imagem com ruído" << endl;

                if (imagem_ruido(imagem, imagem, linha, coluna, tomCinza, &tomCinzaSaida) == 0) {
                    salvaArquivo(name +"_Ruido", imagem, tomCinzaSaida, coluna, linha);
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                    cout << "\n\t Imagem criada com sucesso!" << endl;
                } else {
                    cout << "\n\t Erro na criação da imagem!" << endl;
                    lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                }


                break;

            case 7:

                cout << "\n\t Selecionado: Filtro" << endl;
                cout << "\n\t   Você deseja: ";
                cout << "\n\t\t 0 - Voltar";
                cout << "\n\t\t 1 - Filtro linear";
                cout << "\n\t\t 2 - Filtro não-linear" << endl;

                cout << "\n\t Opção: ";
                cin >> mod;

                switch (mod) {

                    case 1:

                        cout << "\n\t Opção selecionada: Filtro Linear" << endl;

                        if (filtro_linear(imagem, imagem, linha, coluna, tomCinza, &tomCinzaSaida) == 0) {
                            salvaArquivo(name +"_FiltroLinear", imagem, tomCinzaSaida, coluna, linha);
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                            cout << "\n\t Imagem criada com sucesso!" << endl;
                        } else {
                            cout << "\n\t Erro na criação da imagem!" << endl;
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                        }


                        break;
                    case 2:

                        cout << "\n\t Opção selecionada: Filtro Não-Linear" << endl;

                        if (filtro_naoLinear(imagem, imagem, linha, coluna, tomCinza, &tomCinzaSaida) == 0) {
                            salvaArquivo(name +"_FiltroNaoLinear", imagem, tomCinzaSaida, coluna, linha);
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                            cout << "\n\t Imagem criada com sucesso!" << endl;
                        } else {
                            cout << "\n\t Erro na criação da imagem!" << endl;
                            lerArquivo(inputFile, imagem, &tomCinza, &coluna, &linha);
                        }

                        break;
                    default:
                        cout << "\n\t Opção inválida!";
                        break;

                }

                break;

            default:
                cout << "\n\t Opção inválida..." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}

