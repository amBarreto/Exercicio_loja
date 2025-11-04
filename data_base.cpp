#include <iostream>
#include <fstream> //biblioteca para ler (ifstream) // para criar e escrever (ofstream) ficheiros
#include <sstream> //conversao de string em outros dados
 
using namespace std;

struct Produto
{
    int id;
    char status; // A -> ativo / D -> eliminado   
    string nome;
    float preco;
    int quantidade;
};

//-----------------------------------------------------------------------------------------------------------
const int producaomax = 100;
Produto produtos[producaomax];
int quantidadeAtual = 0; // mantem controlo da quantidade atual dos produtos adicionados no array
int ultimoIDutilizado = 0; // vai manter controlo do ID de cada produto
//------------------------------------------------------------------------------------------------------------
void menu(){
    system("clear");
    cout << "\n==========================" <<endl;
    cout << "          MENU" <<endl;
    cout << "==========================" <<endl;
    cout << "1-Adicionar Produto" <<endl;
    cout << "2-Consultar Produto" <<endl; 
    cout << "3-Alterar Produto" <<endl;
    cout << "4-Eliminar Produto" <<endl;
    cout << "5-SAIR" <<endl;
    cout << "==========================" << endl;
}

int getOpcao(){
    int opcao;
    cout << "Digite a sua opcao: " <<endl;
    cin >> opcao;

    return opcao;
}

//-----------------------------------------------------------------------------------------------------

void iniciarDB(){
    
    ifstream ficheiro("Database.csv");
    
    if(!ficheiro){
        
        char opcao;
        
        cout << "O ficheiro da data base não foi encontrado." << endl;
        
        cout << "Deseja criar uma nova data base? (s/n): ";
        cin >> opcao;

        if(opcao == 's'){
            
            // Cria um novo ficheiro
            ofstream ficheiro("Database.csv");
            
            ficheiro.close();
            
            system("clear");
            
            cout << "\nFicheiro data base criado com sucesso!" << endl;
            
        }else{
            
            system("clear");
            
            cout << "\nA fechar o Programa " << endl;
            
            exit(0); //fecha o programa
        }
    }
}

//-------------------------------------------------------------------------------------------
void lerprodutosDB(Produto produtos[], int& quantidadeAtual, int& ultimoIDutilizado){
 
    ifstream ficheiro("Database.csv");
    
    if (!ficheiro) return; //verficar abertura
    
    quantidadeAtual = 0;
    
    while(ficheiro.good() && quantidadeAtual < producaomax){ //o loop continua enquanto o ficheiro estiver bom e a quantidadeAtual for menor do q a prodmax
        
            Produto prod;
            string linhalida;
            
                if(getline(ficheiro, linhalida)){ // a cada iteraçao ele guarda os dados do ficheiro na linhalida
                    
                stringstream ss(linhalida); //possibilita a leitura de uma linha completa na DB
                string strID, strPreco, strQuant, strStatus;
        
                getline(ss, strID, ','); //cada getline le o seu campo e armazena na sua variavel
                getline(ss, prod.nome, ',');          
                getline(ss, strPreco, ',');           
                getline(ss, strQuant, ',');      
                getline(ss, strStatus, ',');        
            
            
                prod.id = stoi(strID);                
                prod.preco = stof(strPreco);          
                prod.quantidade = stoi(strQuant); //conversões
                prod.status = strStatus[0]; //pega no primeiro caractere na string strstatus e iguala ao primeiro caractere do array

                produtos[quantidadeAtual] = prod; //prod armazenado no array na quantidadeAtual
                quantidadeAtual++; 
            
                if (prod.id > ultimoIDutilizado) {
                    ultimoIDutilizado = prod.id; //atualização
                }
            }
        }
    ficheiro.close();
}
//-------------------------------------------------------------------------------------------

void adicionarProdutoDB(Produto produtos[], int quantidadeAtual){ //pronto
    ofstream ficheiro("Database.csv"); // estamos a guardar dados no ficheiro Database.csv


    if(ficheiro.is_open()){
    for(int x = 0; x < quantidadeAtual; x ++){ //produtos armazenados
        ficheiro << produtos[x].id << "," 
                 << produtos[x].nome << ","
                 << produtos[x].preco << ","
                 << produtos[x].quantidade << ","
                 << produtos[x].status <<endl;
    }
    ficheiro.close(); //fecha o ficheiro garantindo que esta td guardado em condiçoes
    }
}
//----------------------------------------------------------------------------------------
void adicionarProduto(Produto produtos[], int& quantidadeAtual, int& ultimoIDutilizado){ //pronto
    
    produtos[quantidadeAtual].id = ++ultimoIDutilizado; // fazemos uma encrementaçao para adicionar o ID a cada produto id = 0
    
    cout << "\nQual o Nome do Produto: " << endl;
    cin.ignore(); //limpa o ENTER a seguir do cin e premite q o getline funcione
    getline(cin,produtos[quantidadeAtual].nome); //vai ler o cin e possibilita a escrita de um nome com espaços
    
    cout << "Qual o Preço do Produto: " <<endl ;
    cin >> produtos[quantidadeAtual].preco; 

    cout << "Qual a Quantidade do Produto: " <<endl;
    cin >> produtos[quantidadeAtual].quantidade; 
    
    produtos[quantidadeAtual].status = 'A';

    quantidadeAtual++;
    
    adicionarProdutoDB(produtos,quantidadeAtual); //invocaçao da funçao superior para elas funcionarem ao mesmo tempo
    
    cout << "\nProduto Adicionado Com Sucesso!" <<endl;

}
//-----------------------------------------------------------------------------------------
void modificarProduto(Produto produtos[], int quantidadeAtual){ //pronto
    
    int id;
    cout << "\nQual o ID do produto que deseja Modificar: " <<endl;
    cin >> id;
    
    for(int x = 0; x < quantidadeAtual; x++){
        
        if(id == produtos[x].id){ //igualar o id ao id do array produtos 
    
            cout << "Qual o Novo Preço do Produto: " <<endl ;
            cin >> produtos[x].preco;

            cout << "Qual a Nova Quantidade do Produto: " <<endl;
            cin >> produtos[x].quantidade;
        
            adicionarProdutoDB(produtos,quantidadeAtual);
        
        }
    }
}
//-----------------------------------------------------------------------------------------
void eliminarProduto(Produto produtos[], int quantidadeAtual){ //pronto
    
    int id;
    cout << "\nQual o ID do produto que deseja Excluir: " <<endl;
    cin >> id;
    
    for(int x = 0; x < quantidadeAtual; x++){
        
        if(id == produtos[x].id){ //igualar o id ao id do array produtos
            
            produtos[x].status = 'D'; //automaticamente muda o status para D
            
            adicionarProdutoDB(produtos,quantidadeAtual);
            
            cout << "O Produto Foi Excluido com Sucesso!" <<endl;
        }
    }
}
//------------------------------------------------------------------------------------------
void consultarProduto(Produto produtos[], int quantidadeAtual){ //pronto
    
    if(quantidadeAtual == 0){
        
        cout << "\nNenhum Produto encontrado" <<endl; 
    }
    
    for(int x = 0; x < quantidadeAtual; x++){
        
        cout << "\nO ID do Produto é: " << produtos[x].id << endl;
        cout << "O Nome do Produto é: " << produtos[x].nome << endl;
        cout << "O Preco do Produto é " << produtos[x].preco << endl;
        cout << "A Quantidade do Produto é: " << produtos[x].quantidade << endl;
        cout << "O Status do Produto é: " <<produtos[x].status << endl;
    }
}

//-----------------------------------------------------------------------------------------
int main(){
    
    int opcao;
    
    iniciarDB();
    
    lerprodutosDB(produtos, quantidadeAtual, ultimoIDutilizado);
    
do{
    
    menu();
  
    opcao = getOpcao(); // tem que ser assim senao o while nao reconhece a opcao de sair

    switch (opcao){
        
    case 1: //adicionar
        adicionarProduto (produtos,quantidadeAtual, ultimoIDutilizado);
        break;

    case 2://consultar
        consultarProduto(produtos,quantidadeAtual);
        break;

    case 3://alterar
       modificarProduto(produtos,quantidadeAtual);
        break;

    case 4://eliminar
        eliminarProduto(produtos,quantidadeAtual);
        break;
        
    case 5://sair
        cout << "\n Saindo do Programa (freaky.....) " <<endl;
        break;

    default:
        break;
    }

}while (opcao !=5);

    return 0;
}
