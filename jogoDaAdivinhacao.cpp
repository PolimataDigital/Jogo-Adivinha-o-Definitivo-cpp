#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <limits>
#include <locale.h>
#include <windows.h>
#include<chrono>

using namespace std;

void validacaoDeEntrada(int &numero, const string &mensagem, int comeco, int limiteMaximo){
    while(true){
        cout<<mensagem;
        cout << "Chute um número de " << comeco << " a " << limiteMaximo << ": ";
        if(!(cin>>numero) || numero<comeco || numero>limiteMaximo ){
            cout<<"Digite uma entrada válida que seja de "<<comeco<<" a "<<limiteMaximo<<"!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        break;
    }
}

void validacaoEntradaDificuldade(char &entrada,const string &mensagem){
    while(true){
        cout<<mensagem;
        cout<<"Fácil(F), Médio(M), Difícil(D) \n";
        if(!(cin>>entrada)){
            cout<<"Digite uma dificuldade válida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        entrada=tolower(entrada);
        if(entrada!='f' && entrada!='m' && entrada!='d'){
            cout<<"Digite uma dificuldade válida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        break;
    }
}        

void validarContinuacao (char &entrada,const string &mensagem){
    while(true){
        cout<<mensagem;
        if(!(cin>>entrada)){
            cout<<"Digite somente 's'(sim) ou 'n'(não)!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        entrada=tolower(entrada);
        if(entrada!='s' && entrada!='n'){
            cout<<"Digite uma entrada válida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        break;
    }
}

int sortearNumero(int comeco, int limiteMaximo){
    //mt19937 é o gerador de números aleatórios, bem mais preciso que o rand() antigo do C
    //chrono::steady_clock — usa o tempo atual como semente pra garantir que o número seja diferente toda vez que rodar
    //uniform_int_distribution<int>(1, 100) — garante que os números sejam distribuídos igualmente entre 1 e 100
    mt19937 gerador(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribuicao(comeco, limiteMaximo);
    
    return distribuicao(gerador);
}

void validarContinuacaoParaOComputador(string &entrada, const string &mensagem){
   while(true){
        cout<<mensagem;
        if(!(cin>>entrada)){
            cout<<"Digite apenas: 'sim', 'menor' ou 'maior' !\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);
        if(entrada!="sim" && entrada!="maior" && entrada!="menor"){
            cout<<"Digite uma entrada válida!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        break;
    }
    
}

void computadorAdivinha(int comeco, int limiteMaximo, int &vitorias, int &derrotas, int tentativas){
    int baixo= comeco;
    int alto=limiteMaximo;

    cout << "Pense em um número de " << comeco << " a " << limiteMaximo << " e não me diga!\n";

    while(true){
        if(baixo>alto){
            cout<<"Você trapaceou! Impossível continuar. \n";
            derrotas++;
            break;
        }
        int chute = baixo+(alto-baixo)/2;
        cout<<"Meu chute é: "<<chute<<endl;

        string resposta;
        validarContinuacaoParaOComputador(resposta,"Digite sim se eu acertei: 'sim'. \nCaso eu errei: Me dê dicas: Seu número é MAIOR ou MENOR que meu chute? \n");
        
        if (resposta=="sim"){
            cout<<"Acertei! Sou o cara! \n";
            vitorias++;
            break;

        }else if(resposta=="maior"){
            baixo=chute+1;
            tentativas--;
            cout<<"Tentativas restantes: "<<tentativas<<endl;
        }else if(resposta=="menor"){
            alto= chute-1;
            tentativas--;
            cout<<"Tentativas restantes: "<<tentativas<<endl;
        }
        if(tentativas==0){
            cout<<"Minhas chances acabaram. Perdi :( \n";
            derrotas++;
            break;        
        }

    }
}

void validarModoDeJogo(int &modoDeJogo,const string &mensagem ){
    while(true){
        cout<<mensagem;

        if(!(cin>>modoDeJogo)){
            cout<<"Digite uma entrada válida! \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        if(modoDeJogo!=1 && modoDeJogo!=2){
            cout<<"Digite apenas 1 ou 2 \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        break;
    }
}

int main (){

    setlocale(LC_ALL, "portuguese");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    bool continuarAJogar=true;
    int vitorias=0, derrotas=0;
    int vitoriasMaquina=0, derrotasMaquina=0;
    int modoDeJogo;

    while(continuarAJogar){
        validarModoDeJogo(modoDeJogo,"Escolha o modo de jogo: 1- Você adivinha, 2- Computador adivinha \n");
        cout << "----Seja bem-vindo(a) ao jogo da adivinhação----\n";
        int limiteMaximo=0;
        int tentativas=0;
        int chute=0;
        
        char dificuldade;
        validacaoEntradaDificuldade(dificuldade,"Que dificuldade você quer jogar? \n");
        
        if(dificuldade=='f'){
            tentativas=10;
            limiteMaximo=50;
        }else if(dificuldade=='m'){
            tentativas=5;
            limiteMaximo=100;
        }else if(dificuldade=='d'){
            tentativas=3;
            limiteMaximo=500;
        }

        if(modoDeJogo==1){
            int numeroSorteado = sortearNumero(1, limiteMaximo);// número já sorteado com a função lá encima
            while(true){
                validacaoDeEntrada(chute,"\n", 1,limiteMaximo);
                    
                if(chute!= numeroSorteado){
                    cout<<"Você errou o número, tente novamente! \n";
                    tentativas--;
                    cout<<"Tentativas restantes: "<<tentativas<<endl;
                    if(chute<numeroSorteado){
                        cout<<"Uma dica para te ajudar: O número secreto é maior do que o que você digitou!\n ";
                        } else if(chute > numeroSorteado){
                            cout<<"Uma dica para te ajudar: O número secreto é menor do que o que você digitou!\n ";
                        }
                        
                        if(tentativas==0){
                            cout<<"Suas chances acabaram. Você perdeu! \n";
                            cout<< "O número secreto era: "<<numeroSorteado<<endl;
                            derrotas++;
                            break;
                        }
                        
                    }else{
                        cout<<"Você acertou o número! \n";
                        vitorias++;
                        break;
                    }
                }
                
                
            }else if(modoDeJogo==2){
                computadorAdivinha(1,limiteMaximo, vitoriasMaquina, derrotasMaquina,tentativas);
            }
        cout << "Placar: " << vitorias << " vitórias e " << derrotas << " derrotas\n";
        cout << "Placar maquina: " << vitoriasMaquina << " vitorias e " << derrotasMaquina << " derrotas\n";

        char decisaoContinuar;
        validarContinuacao(decisaoContinuar, "Deseja continuar a jogar? \n");
                
        continuarAJogar= (decisaoContinuar=='s');
        if(decisaoContinuar!='s'){
            cout<<"Fim de jogo! \n";
        }
            
   
    }
    return 0;
}
