Projeções
===================

Implementação de um trabalho da disciplina de Computação Gráfica desenvolvido no semestre de 2013/1, cuja finalidade é calcular as projeções de um ponto num plano, de modo que projeção calculada pode ser perspectiva ou paralela.

#####Observações:

Para a correta execução deste programa é esperado que os valores utilizados para descrever as projeções sejam válidos e que os valores sejam informados da forma correta.

A entrada assume que as coordenadas de pontos e vetores são escritas na ordem x, y, z; que números reais são escritos utilizando o ponto como separador das casas decimais (números inteiros não precisam do ponto); e que cada valor de entrada é separado por espaço.

#####Valores de entrada:

Os valores de entrada devem ser passados seguindo a seguinte ordem:
- Código de controle (0 para finalizar a execução, 1 para projeção paralela e 2 para projeção perspectiva);
- Coordenadas x, y, z do ponto de origem;
- Coordenadas x, y, z do vetor X;
- Coordenadas x, y, z do vetor Y;
- Coordenadas x, y, z da direção de projeção caso seja escolhida a projeção paralela, ou as coordenadas x, y, z do centro de projeção caso a seja escolhida a projeção perspectiva.

Observação: Caso o código de controle seja 0, os outros valores de entrada não são necessários.

#####Exemplos:

Para exemplos de entrada e saída, verifique os arquivos input e output na pasta exemplos.

#####Modo de execução:

Compile com:

~ `g++ projecoes.cpp -o <minha_saida>`

E execute com:

~ `./<minha_saida>`
