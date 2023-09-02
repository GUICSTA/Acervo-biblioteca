#include <iostream>
#include <cstdlib>
#include <cctype>
#define TAM 50

using namespace std;

int existePosicao(int ,string[],string);
void inclusao(int &, string [],string[],string[],string[],int[]);
bool conferencia (string);
void dados (int,string[],string[],string[],int[],string);
void aquisicao (int,int[],string,string []);
bool ehDigito(string);
void ordemAlfabetica(int,string[],int[],string[],string[],string[],string[]);
void exclusao(int &,string[],string[],string[],int[],string,string[]);
void relatorio(int,string [], string [],string [],int [],string [],string[],int );

void relatorio(int n,string autor[],string titulo[], string isbn[],int exemplares[],string editora[],string sobrenomes[])
{
    int ultimoNomeTamanho,tamNome,tamUltimoSobrenome;
    string ultimoSobrenome=", ",demaisNomes,nome,preposicoes[11]={" de","de ","dos","das"," e ","e  ","  e","da "," da","do "," do"};

    for(int j=0; j<n; j++)
    {
        nome = autor[j];   //pega primeiro autor do vetor e armazena na variavel simples
        tamNome = nome.length(); //armazena o tamanho do nome na variavel
        // Maiusculiza o ultimo nome
        for (int i = tamNome; i > 0; i--) //for que vai do tamanho do nome ate 0
        {
            if (nome[i] != ' ') //procura do final ate o espaco
            {
                char upperChar = toupper(nome[i]);             //bota o nome em maiusculo
                ultimoSobrenome = upperChar + ultimoSobrenome; //soma nome em maiusculo com uma virgula
                tamUltimoSobrenome = ultimoSobrenome.length(); //armazena o tamanho do ultimo sobrenome
            }
            else
            {
                break; //quando acha o espaço ele quebra o for
            }
        }
        // Trata as demais iniciais
        for (int i = 0; i <= tamNome - tamUltimoSobrenome; i++) //for pra fazer todas as inicias menos a do ultimo sobrenome
        {
            string temp = "";
            temp = temp + nome.at(i) + nome.at(i + 1) + nome.at(i+2); //procurar preposicoes
            bool temPreposicao = false;
            for(int k=0;k<11;k++){                                    //vai varrer o vetor de preposicoes,se achar retorna true
                if (temp == preposicoes[k]) {
                    temPreposicao = true;
                }
            }

            if (!temPreposicao)            //trata vetor de preposicoes se (retornar false)
            {
                if (i == 0 || nome[i - 1] == ' ')
                {
                    char upperChar = toupper(nome[i]); //bota inicial em maiusculo
                    demaisNomes = demaisNomes + upperChar + ". "; //depois soma as iniciais,colocando um .
                }
            }
        }
        sobrenomes[j] = ultimoSobrenome + demaisNomes; //armazena as informacoes nesse vetor
        ultimoSobrenome=", ";
        demaisNomes = "";
    }

}


void exclusao(int &n,string titulo[],string autor[],string editora[],int exemplares[],string cadastro,string isbn[])
{
    cin.ignore();
    cout<<"ISBN para exclusao: "<<endl;
    getline(cin,cadastro); //le isbn numa variavel simples
    bool valido = conferencia(cadastro); //confere se o isbn eh valido
    if(valido)
    {
        int posicao = existePosicao(n,isbn,cadastro); //vai ver se ja possui esse isbn no vetor
        if(posicao!=-1)
        {
            for(int i= posicao; i<n; i++)
            {
                isbn[i] = isbn[i+1];      //bota  a posicao atual do vetor como a proxima
                titulo[i] = titulo[i+1];
                autor[i] = autor[i+1];
                editora[i] = editora[i+1];
                exemplares[i] = exemplares[i+1];
            }
            isbn[n] = "";     //esvazia o vetor naquela posicao
            titulo[n] = "";
            autor[n] ="";
            editora[n]="";
            exemplares[n]=0;
            n--;             //diminui a quantidade de elementos do vetor
            system("cls");
            cout<<"Livro excluido"<<endl;
        }
        else
        {
            system("cls");
            cout<<"Livro inexistente,impossivel excluir"<<endl;
        }
    }
    else
    {
        cout<<"ISBN invalido, ele precisa tem pelo menos um - , o qual nao pode ser na primeira posicao e pelo menos 13 digitos"<<endl;
    }
}

void ordemAlfabetica(int n,string titulo[],int exemplares[],string autor[],string editora[],string isbn[],string sobrenomes[])
{
    string aux,tam;
    char upper;
    int auxInt;
    for(int i=0; i<n; i++)
    {
        upper = toupper(titulo[i].at(0)); //bota a primeira letra do titulo em maiuscula para nao ter problema de organizar com minuscula e maiuscual
        titulo[i].at(0) = upper;
    }
    for(int i=0; i<=n-1; i++)
    {
        int posicao = i;
        for(int j=i+1; j<=n-1; j++)
        {
            if(titulo[j] < titulo[posicao]) //se a posicao com o i armazenado for maior do que a posicao j, a posicao vira o j
            {
                posicao = j;
            }
        }
        aux = titulo[posicao];         //auxiliar recebe a variavel com a posicao que foi atribuida no for
        titulo[posicao] = titulo[i];   //variavel na posicao recebe a variavel em i
        titulo[i] = aux;               //variavel em funcao de i recebe auxiliar
        auxInt = exemplares[posicao];
        exemplares[posicao] = exemplares[i];
        exemplares[i] = auxInt;
        aux = autor[posicao];
        autor[posicao] = autor[i];
        autor[i] = aux;
        aux = editora[posicao];
        editora[posicao] = editora[i];
        editora[i] = aux;
        aux = isbn[posicao];
        isbn[posicao] = isbn[i];
        isbn[i] = aux;
        aux = sobrenomes[posicao];
        sobrenomes[posicao] = sobrenomes[i];
        sobrenomes[i] = aux;
    }
}
void aquisicao (int n,int exemplares[],string cadastro,string isbn[])
{
    int exemplar;
    cin.ignore();
    cout<<"Digite O ISBN-13 do livro que deseja adicionar exemplares"<<endl;
    getline(cin,cadastro);
    bool valido = conferencia(cadastro);
    if(valido)
    {
        int posicao = existePosicao(n,isbn,cadastro);
        if(posicao!=-1)
        {
            system("cls");
            cout<<"Quantidade de exemplares que gostaria de adicionar: "<<endl;
            cin>>exemplar;                                                      //le a quantidade em int
            exemplares[posicao] += exemplar;                                    //soma no vetor
            cout<<"Exemplares incluidos com sucesso!"<<endl;
        }
        else
        {
            system("cls");
            cout<<"Este livro nao consta em nosso sistema!\nPor gentileza, cadastre o livro antes!"<<endl;
        }
    }
    else
    {
        cout<<"ISBN invalido, ele precisa tem pelo menos um - , o qual nao pode ser na primeira posicao e pelo menos 13 digitos"<<endl;
    }
}

bool ehDigito(string cadastro)
{
    for(int i=0; i< cadastro.size(); i++)
    {
        if(isdigit(cadastro.at(i)))
            return true;
    }
    return false;
}

bool conferencia (string cadastro)
{
    int tam = cadastro.size();
    bool temDigito =false, temHifen = false;
    for(int i=0; i<cadastro.size(); i++)
    {
        if(cadastro.at(i) == '-' )
        {
            temHifen = true;
        }
        if(isdigit(cadastro.at(i)))        //confere se o isbn eh digito ou se eh -
        {
           temDigito = true;
        }
    }
    if(temDigito and temHifen and tam>13 and cadastro.at(0) != '-'){
        return true;
    }
    else{
        return false;
    }
}

void dados(int n,string titulo[],string autor[],string editora[],int exemplares[],string cadastro)
{
    bool aviso;
    do
    {
        cout<<"Informe o titulo do livro: ";
        getline(cin,titulo[n]);
    }
    while(titulo[n]=="");
    bool temEspaco,temDigito;
    do
    {
        cout<<"Informe o nome completo do autor: ";
        getline(cin,cadastro);
        temDigito = ehDigito(cadastro);
        temEspaco = false;
        for(int i=0; i<cadastro.size(); i++)
        {
            if(isspace(cadastro.at(i)))
            {
                temEspaco = true;
            }
        }
        if(temEspaco)
        {
            if(!temDigito)
            {
                autor[n] = cadastro;
            }
            else
            {
                cout<<"Nome do autor nao pode ter numeros"<<endl;
            }
        }
        else
        {
            cout<<"Autor tem que ter pelo menos 1 sobrenome e nao pode ter numeros"<<endl;
        }
    }
    while(cadastro=="" or !temEspaco or temDigito);
    do
    {
        cout<<"Informe a editora: ";
        getline(cin,editora[n]);
    }
    while(editora[n]=="");
    do
    {
        cout<<"Informe a quantidade de exemplares: ";
        cin>>exemplares[n];
        cin.ignore();
    }
    while(exemplares[n] <=0);
}
int existePosicao(int n,string isbn[],string cadastro)
{
    for(int i=0; i<n; i++)
    {
        if(cadastro==isbn[i])                           //confere se ja existe um isbn igual no vetor
        {
            return i;
        }
    }
    return -1;
}

void inclusao(int &n, string isbn[],string titulo[],string autor[],string editora[],int exemplares[])
{
    string cadastro;
    cin.ignore();
    cout<<"ISBN-13 para cadastro: "<<endl;
    getline(cin,cadastro);
    bool valido = conferencia(cadastro);
    if(valido)
    {
        int posicao = existePosicao(n,isbn,cadastro);
        if(posicao==-1)
        {
            isbn[n]=cadastro;                                   //atribui o isbn armazenado na variavel simples ao vetor
            dados(n,titulo,autor,editora,exemplares,cadastro);  //pede os demais dados
            system("cls");
            cout<<"Inclusao de livro realizada com sucesso!!"<<endl;
            n++;                                                    //soma a quantidade de elementos do vetor
        }
        else
        {
            system("cls");
            cout<<"Este livro ja existe em nosso sistema!"<<endl;
        }
    }
    else
    {
        cout<<"ISBN invalido, ele precisa tem pelo menos um - , o qual nao pode ser na primeira posicao e pelo menos 13 digitos"<<endl;
    }
}

int main()
{
    string isbn[TAM],cadastro,titulo[TAM],autor[TAM],editora[TAM],ultimoSobrenome,demaisNomes,sobrenomes[TAM];
    int opc,n=0,posicao,exemplares[TAM];
    bool valido;
    do
    {
        cout<<"\n=======BIBLIOTECA==========\n0)Sair\n1)Cadastrar novo livro\n2)Consultar um livro\n3)Excluir um livro\n4)Adicionar novo exemplar\n5)Relatorio\nQual a opcao desejada?"<<endl;
        cin>>opc;
        system("cls");
        switch (opc)
        {
        case 1:
            inclusao(n,isbn,titulo,autor,editora,exemplares);
            system("pause");
        break;
        case 2:
            cin.ignore();
            cout<<"ISBN-13 para pesquisa do livro: "<<endl;
            getline(cin,cadastro);
            valido = conferencia(cadastro);
            posicao = existePosicao(n,isbn,cadastro);
            if(posicao != -1 )
            {
                system("cls");
                cout<<"Titulo do livro: " << titulo[posicao] <<endl;
                cout<<"Autor do livro: " << autor[posicao] <<endl;
                cout<<"Editora do livro: " << editora[posicao] <<endl;
                cout<<"Exemplares do livro: "<< exemplares[posicao] <<endl;
            }
            else
            {
                system("cls");
                cout<<"Livro inexistente"<<endl;
            }
            system("pause");
        break;
        case 3:
            exclusao(n,titulo,autor,editora,exemplares,cadastro,isbn);
            system("pause");
        break;
        case 4:
            aquisicao(n,exemplares,cadastro,isbn);
            system("pause");
        break;
        case 5:
            if(autor[0]!="")
            {
                relatorio(n,autor,titulo,isbn,exemplares,editora,sobrenomes);
                ordemAlfabetica(n,titulo,exemplares,autor,editora,isbn,sobrenomes);
                for(int i=0; i<n; i++)
                {
                    cout<<"ISBN: "<<isbn[i]<<" Autor: "<<sobrenomes[i]<<" Titulo: "<<titulo[i]<<" Editora: "<<editora[i]<<" Unidades:"<<exemplares[i]<<endl;
                }
            }
            else
            {
                cout<<"Nao temos nenhum livro no acervo"<<endl;
            }
            system("pause");
        break;
        case 0:
            cout<<"Obrigado pela preferencia, espero te ver por aqui novamente!!!";
        break;
        }
    }
    while(opc !=0);

    return 0;
}
