# Projeto de Processamento de Imagens

Este projeto implementa um conjunto de funcionalidades básicas para processamento de imagens no formato PGM (Portable Gray Map). Ele inclui operações como ajuste de brilho, geração de imagem negativa, binarização, iconização, aplicação de ruído e aplicação de filtros lineares e não-lineares.

## Funcionalidades Implementadas

- **Ler arquivo PGM:** Permite ler uma imagem no formato PGM de um arquivo `.pgm` e carregar seus dados em uma matriz.
- **Ajustar brilho:** Clareia ou escurece a imagem com base em um valor percentual.
- **Imagem negativa:** Gera a versão negativa da imagem.
- **Binarizar imagem:** Converte a imagem para uma versão binária com base em um valor de limiar.
- **Iconizar imagem:** Reduz a imagem para um tamanho de 64x64 pixels.
- **Criar ruído na imagem:** Adiciona ruído aleatório à imagem.
- **Aplicar filtro linear:** Aplica um filtro de suavização linear à imagem.
- **Aplicar filtro não-linear:** Aplica um filtro de mediana não-linear à imagem.

## Pré-requisitos

- Compilador C++ compatível com C++11 ou superior.
- Biblioteca padrão do C++.
- Imagens no formato PGM para teste.

## Como compilar e executar

1. Clone o repositório para sua máquina local:

   ```bash
   git clone https://github.com/FlaviaMarcella/ImageProcess.git
   
2. Navegue até o diretório do projeto:

   ```bash
   cd ImageProcess
   
3. Compile o projeto

   ```bash
   g++ -std=c++11 -o main main.cpp imagem.cpp
   
4. Execute o programa

   ```bash
   ./ImageProcess

## Exemplo de uso

- Execute o programa conforme instruções acima.
- Escolha a opção correspondente à funcionalidade desejada no menu.
- Siga as instruções no console para fornecer os parâmetros necessários (como nome do arquivo de imagem).

  ## Observações
    - As imagens devem ser inseridas no diretório ImageProcess/Imagens/
    - Os arquivos alterados, serão salvos no mesmo diretório.

## Contribuições

Contribuições são bem-vindas! Se você deseja melhorar este projeto, sinta-se à vontade para enviar pull requests.
