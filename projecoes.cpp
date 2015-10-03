/*
Primeira avaliação de Computação Gráfica: Trabalho de Projeções

Professor: Bruno Schneider

Grupo: Rodrigo Caldas e Thiago Nobre
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

class Vetor;
class Matriz;

/*
Definição da classe Vetor
*/
class Vetor{
    public:
        Vetor(double x_, double y_, double z_);
        double getX();
        double getY();
        double getZ();
        void setXYZ(double x_, double y_, double z_);
        double angulo2Vetores(const Vetor& v);
        void aplicarTranformacao(Matriz tranformacao);

    private:
        double x;
        double y;
        double z;
};

/*
Definição da classe Matriz
*/
class Matriz{
    public:
        double getElemento(int linha, int coluna);
        void nula();
        void identidade();
        void imprimir();
        void multiplicacaoMatrizes(const Matriz& matriz1, const Matriz& matriz2);
        void translacao(Vetor p1, Vetor p2);
        void rotacaoX(double angulo);
        void rotacaoY(double angulo);
        void rotacaoZ(double angulo);
        void cisalhamentoX(Vetor shear);
        void cisalhamentoY(Vetor shear);
        void cisalhamentoZ(Vetor shear);
        void semelhancaTriangulos(double z_);
        void projecaoParalela(Vetor origemProjecao, Vetor vetorX, Vetor vetorY,
        Vetor direcaoProjecao);
        void projecaoPerspectiva(Vetor origemProjecao, Vetor vetorX, Vetor vetorY,
        Vetor centroProjecao);

    private:
        double dados[4][4];
        void rotacoesProjecao(Vetor vetorX, Vetor vetorY);
};


/*
MAIN
*/
int main(){
    short controle;
    double x, y, z;
    Vetor origem(0,0,0), vetorX(0,0,0), vetorY(0,0,0), direcaoProjecao(0,0,0),
    centroProjecao(0,0,0);
    Matriz pre_multiplicacao;

    do{
        cin >> controle;
        if (controle){
            cin >> x >> y >> z;
            origem.setXYZ(x,y,z);

            cin >> x >> y >> z;
            vetorX.setXYZ(x,y,z);

            cin >> x >> y >> z;
            vetorY.setXYZ(x,y,z);

            if (controle == 1){
                cin >> x >> y >> z;
                direcaoProjecao.setXYZ(x,y,z);

                pre_multiplicacao.projecaoParalela(origem, vetorX, vetorY,
                direcaoProjecao);
            } else if (controle == 2){
                cin >> x >> y >> z;
                centroProjecao.setXYZ(x,y,z);

                pre_multiplicacao.projecaoPerspectiva(origem, vetorX, vetorY,
                centroProjecao);
            }

            cout << endl;
            pre_multiplicacao.imprimir();
        }
    }while(controle);

    return 0;
}


/*
Métodos da classe Vetor
*/

Vetor::Vetor (double x_, double y_, double z_)
    :x(x_), y(y_), z(z_)
{
    /*
    Constrói uma instância da classe Vetor e inicializa suas coordenadas X, Y, Z
    */
}

void Vetor::setXYZ (double x_, double y_, double z_){
    /*
    Atribui valores às coordenadas X, Y, Z
    */
    x = x_;
    y = y_;
    z = z_;
}


double Vetor::getX(){
    /*
    Retorna o valor da coordenada X
    */
    return x;
}

double Vetor::getY(){
    /*
    Retorna o valor da coordenada Y
    */
    return y;
}

double Vetor::getZ(){
    /*
    Retorna o valor da coordenada Z
    */
    return z;
}

double Vetor::angulo2Vetores(const Vetor& v){
    /*
    Calcula o angulo entre dois vetores e retorna o resultado
    */

    //cos = (u.v) / (|u|.|v|)
    double uv = (x * v.x) + (y * v.y) + (z * v.z);
    double nu_nv = sqrt((x * x) + (y * y) + (z * z)) * sqrt((v.x * v.x) +
    (v.y * v.y) + (v.z * v.z));

    if (nu_nv)
        return acos(uv / nu_nv);
    else
        return 0;
}

void Vetor::aplicarTranformacao(Matriz tranformacao){
    /*
    Aplica no vetor, as tranformações de uma matriz
    */

    double x_ = this->getX(), y_ = this->getY(), z_ = this->getZ();

    x = tranformacao.getElemento(0,0)*x_ + tranformacao.getElemento(0,1)*y_ +
    tranformacao.getElemento(0,2)*z_ + tranformacao.getElemento(0,3);
    
    y = tranformacao.getElemento(1,0)*x_ + tranformacao.getElemento(1,1)*y_ +
    tranformacao.getElemento(1,2)*z_ + tranformacao.getElemento(1,3);

    z = tranformacao.getElemento(2,0)*x_ + tranformacao.getElemento(2,1)*y_ +
    tranformacao.getElemento(2,2)*z_ + tranformacao.getElemento(2,3);
}


/*
Métodos da classe Matriz
*/

double Matriz::getElemento(int linha, int coluna){
    /*
    Retorna um elemento da matriz contido em uma linha e coluna específica
    */
    return dados[linha][coluna];
}

void Matriz::nula(){
    /*
    Inicializa a matriz como uma matriz nula
    */
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            dados[i][j] = 0;
}

void Matriz::identidade(){
    /*
    Inicializa a matriz como uma matriz identidade
    */
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            dados[i][j] = (i!=j)?0:1;
}

void Matriz::imprimir(){
    /*
    Imprime a matriz
    */
    for (int i = 0 ; i < 4 ; i++){
        for (int j = 0 ; j < 4 ; j++)
            cout << setw(10) << fixed << setprecision(5) << dados[i][j] << ' ';
            
        cout << endl;
    }
}

void Matriz::multiplicacaoMatrizes(const Matriz& matriz1, const Matriz& matriz2){
    /*
    Realiza a multiplicação das matrizes 1 e 2, armazenando o resultado
    na instância que chamou o método
    */

    /*
    Inicializando a matriz que receberá a mutliplicação como nula
    */
    this->nula();

    /*
    Multiplicando as matrizes
    */
    for (int i = 0 ; i < 4 ; i++) //linha da matriz 1
        for (int j = 0 ; j < 4 ; j++) //coluna da matriz 2
            for (int k = 0 ; k < 4 ; k++) //linha da matriz 2
                dados[i][j] += matriz1.dados[i][k] * matriz2.dados[k][j];
}

void Matriz::translacao(Vetor p1, Vetor p2){
    /*
    Gera a matriz de translação a partir de dois pontos
    */

    /*
    Inicializando a matriz de translação como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando a translação
    */
    dados[0][3] = p2.getX() - p1.getX();
    dados[1][3] = p2.getY() - p1.getY();
    dados[2][3] = p2.getZ() - p1.getZ();
}

void Matriz::rotacaoX(double angulo){
    /*
    Gera a matriz de rotação em torno do eixo X, com um ângulo em graus
    */

    /*
    Inicializando a matriz de rotação como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando a rotação
    */
    dados[1][1] = cos(angulo);
    dados[1][2] = -sin(angulo);

    dados[2][1] = sin(angulo);
    dados[2][2] = cos(angulo);
}

void Matriz::rotacaoY(double angulo){
    /*
    Gera a matriz de rotação em torno do eixo Y, com um ângulo em graus
    */

    /*
    Inicializando a matriz de rotação como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando a rotação
    */
    dados[0][0] = cos(angulo);
    dados[0][2] = sin(angulo);

    dados[2][0] = -sin(angulo);
    dados[2][2] = cos(angulo);
}

void Matriz::rotacaoZ(double angulo){
    /*
    Gera a matriz de rotação em torno do eixo Z, com um ângulo em graus
    */

    /*
    Inicializando a matriz de rotação como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando a rotação
    */
    dados[0][0] = cos(angulo);
    dados[0][1] = -sin(angulo);

    dados[1][0] = sin(angulo);
    dados[1][1] = cos(angulo);
}

void Matriz::cisalhamentoX(Vetor shear){
    /*
    Gera a matriz de cisalhamento no eixo X
    */

    /*
    Inicializando a matriz de cisalhamento como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando o cisalhamento
    */
    if (shear.getX()){
        dados[1][0] = (-shear.getY()) / shear.getX();
        dados[2][0] = (-shear.getZ()) / shear.getX();
    }
}

void Matriz::cisalhamentoY(Vetor shear){
    /*
    Gera a matriz de cisalhamento no eixo Y
    */

    /*
    Inicializando a matriz de cisalhamento como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando o cisalhamento
    */
    if (shear.getY()){
        dados[0][1] = (-shear.getX()) / shear.getY();
        dados[2][1] = (-shear.getZ()) / shear.getY();
    }
}

void Matriz::cisalhamentoZ(Vetor shear){
    /*
    Gera a matriz de cisalhamento no eixo Z
    */

    /*
    Inicializando a matriz de cisalhamento como uma matriz identidade
    */
    this->identidade();

    /*
    Calculando o cisalhamento
    */
    if (shear.getZ()){
        dados[0][2] = (-shear.getX()) / shear.getZ();
        dados[1][2] = (-shear.getY()) / shear.getZ();
    }
}

void Matriz::semelhancaTriangulos(double z_){
    /*
    Gera a matriz de semelhança de triângulos a partir de z'
    */
    this->identidade();

    if (z_){
        this->dados[3][2] = 1.0/z_;
        this->dados[3][3] = 0;
    }
}

void Matriz::rotacoesProjecao(Vetor vetorX, Vetor vetorY){
    /*
    Gera a matriz de transformação das três rotações de uma projeção genérica
    */


    Matriz matrizRotacao[3], matrizAuxiliar;
    Vetor vetorAuxiliar(0, 0, 0), vetorProjetado(0, 0, 0);
    double angulo;


    //eixoX do SCM
    vetorAuxiliar.setXYZ(1, 0, 0);
    //vetorX do SCA projetado no plano XZ
    vetorProjetado.setXYZ(vetorX.getX(), 0, vetorX.getZ());
    /*
    Calcula o ângulo entre o eixoX (SCM) e o vetorX (SCA) projetado no plano XZ
    */
    angulo = vetorAuxiliar.angulo2Vetores(vetorProjetado);
    if (vetorX.getZ() < 0)
        angulo = - angulo;


    //eixoY do SCM
    vetorAuxiliar.setXYZ(0, 1, 0);
    /*
    Gera a matriz de rotação no eixo y (SCM) e aplica a transformação no
    vetor x (SCA) e no vetor y (SCA)
    */
    matrizRotacao[0].rotacaoY(angulo);
    vetorX.aplicarTranformacao(matrizRotacao[0]);
    vetorY.aplicarTranformacao(matrizRotacao[0]);


    /*
    Calcula o ângulo entre o eixoX (SCM) e o vetorX (SCA) projetado no plano XY
    */
    vetorAuxiliar.setXYZ(1, 0, 0); //eixoX do SCM
    angulo = vetorAuxiliar.angulo2Vetores(vetorX);
    if (vetorX.getY() > 0)
        angulo = - angulo;
    /*
    Gera a matriz de rotação no eixo z (SCM) e aplica a transformação no
    vetor y (SCA)
    */
    vetorAuxiliar.setXYZ(0, 0, 1); //eixoY do SCM
    matrizRotacao[1].rotacaoZ(angulo);
    vetorY.aplicarTranformacao(matrizRotacao[1]);


    //eixoY do SCM
    vetorAuxiliar.setXYZ(0, 1, 0);
    /*
    Calcula o ângulo entre o eixoY (SCM) e o vetorY (SCA) projetado no plano YZ
    */
    angulo = vetorAuxiliar.angulo2Vetores(vetorY);
    if (vetorY.getZ() > 0)
        angulo = - angulo;
    /*
    Gera a matriz de rotação no eixo x (SCM)
    */
    vetorAuxiliar.setXYZ(1, 0, 0); //eixoY do SCM
    matrizRotacao[2].rotacaoX(angulo);


    /*
    Gera a matriz de pré-multiplicação
    */
    matrizAuxiliar.multiplicacaoMatrizes(matrizRotacao[2], matrizRotacao[1]);
    this->multiplicacaoMatrizes(matrizAuxiliar, matrizRotacao[0]);
}

void Matriz::projecaoParalela(Vetor origemProjecao, Vetor vetorX, Vetor vetorY,
Vetor direcaoProjecao){
    /*
    Gera a matriz de pré-multiplicação de uma projeção paralela genérica
    */


    Matriz matrizTranslacao, matrizCisalhamento, matrizAuxiliar[2];
    Vetor vetorAuxiliar(0, 0, 0);


    /*
    Gera a matriz de translação que translada a origem da projeção para a origem
    do SCM
    OBS.: aqui vetorAuxiliar ainda é equivalente a origem do SCM (0,0,0)
    */
    matrizTranslacao.translacao(origemProjecao, vetorAuxiliar);


    /*
    Gera a matriz de transformação das rotações da projeção paralela
    */
    matrizAuxiliar[0].rotacoesProjecao(vetorX, vetorY);


    /*
    Gera a matriz de cisalhamento, mas antes aplica as transformações de rotação
    calculadas, nas coordenadas da direcaoProjecao
    */
    direcaoProjecao.aplicarTranformacao(matrizAuxiliar[0]);
    matrizCisalhamento.cisalhamentoZ(direcaoProjecao);


    /*
    Gera a matriz de pré-multiplicação
    */
    matrizAuxiliar[1].multiplicacaoMatrizes(matrizCisalhamento,matrizAuxiliar[0]);
    this->multiplicacaoMatrizes(matrizAuxiliar[1], matrizTranslacao);
}

void Matriz::projecaoPerspectiva(Vetor origemProjecao, Vetor vetorX, Vetor vetorY,
Vetor centroProjecao){
    /*
    Gera a matriz de pré-multiplicação de uma projeção paralela genérica
    */


    Matriz matrizTranslacao, matrizCisalhamento, matrizSemelhancaTriangulos,
    matrizAuxiliar[3];
    Vetor vetorAuxiliar(0, 0, 0);


    /*
    Gera a matriz de translação que translada o centro da projeção para a origem
    do SCM
    OBS.: aqui vetorAuxiliar ainda é equivalente a origem do SCM (0,0,0)
    */
    matrizTranslacao.translacao(centroProjecao, vetorAuxiliar);

    /*
    Gera a matriz de transformação de rotações da projeção perspectiva
    */
    matrizAuxiliar[0].rotacoesProjecao(vetorX, vetorY);


    /*
    Gera a matriz de cisalhamento, mas antes aplica as transformações de rotação
    e de translação calculadas,    nas coordenadas de origemProjecao
    */
    origemProjecao.aplicarTranformacao(matrizTranslacao);
    origemProjecao.aplicarTranformacao(matrizAuxiliar[0]);
    matrizCisalhamento.cisalhamentoZ(origemProjecao);


    /*
    Gera a matriz de semelhança de triângulos, mas antes aplica a transformação
    de cisalhamento    calculada,    nas coordenadas de origemProjecao
    */
    origemProjecao.aplicarTranformacao(matrizCisalhamento);
    matrizSemelhancaTriangulos.semelhancaTriangulos(origemProjecao.getZ());


    /*
    Gera a matriz de pré-multiplicação
    */
    matrizAuxiliar[1].multiplicacaoMatrizes(matrizSemelhancaTriangulos,
    matrizCisalhamento);
    matrizAuxiliar[2].multiplicacaoMatrizes(matrizAuxiliar[1], matrizAuxiliar[0]);
    this->multiplicacaoMatrizes(matrizAuxiliar[2], matrizTranslacao);
}

