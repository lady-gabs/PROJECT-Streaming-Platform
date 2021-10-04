#include <stdio.h>
#include <string.h>
///////////////////// CLIENTE /////////////////////
typedef enum{
    inativo, ativo
}STATUS;
typedef struct {
    char cpf[50];
    char nome [50];
    char email[50];
    char telefone[15];
}DADO_CLIENTE;       //maximo 10
typedef struct{
    DADO_CLIENTE cliente;
    STATUS status;
}CLIENTE;

///////////////////// FILME /////////////////////
typedef enum{
    aventura, comedia, drama, terror, acao, romance
}GENERO;
typedef enum{
    livre, mais10, mais12, mais14, mais16, mais18
}CLASSIFICACAO;
typedef struct{
    int codigobusca; //começa em 1001 e se auto incrementa
    char nome[50];
}DADO_FILME;         //maximo 10
typedef struct {
    DADO_FILME filme;
    GENERO genero;
    CLASSIFICACAO classificacao;
}FILME;

///////////////////// PLANO /////////////////////
typedef struct{
    int quantidade; //quantidade de filmes que a pessoa pode assistir
    float valor_base;
    float valor_excedente;
}PLANOBASICO;
typedef struct{
    float valor_base;
}PLANOPREMIUM;
typedef enum{
    plano_basico, plano_premium
}ENUM_PLANO;
typedef struct{
    PLANOBASICO planobasico;
    PLANOPREMIUM planopremium;
}STRUCT_PLANO;
typedef struct{
    ENUM_PLANO opcao_plano;
    STRUCT_PLANO plano;
}PLANO;

///////////////////// CONTRATO /////////////////////
typedef enum{
    debito, credito
}PAGAMENTO;
typedef struct{
    char numero_cartao[50];
}CREDITO;
typedef struct{
    char numero_agencia[50];
    char numero_conta[50];
}DEBITO;
typedef union{
    CREDITO credito;
    DEBITO debito;
}FORMA_PGTO;
typedef struct{
    PAGAMENTO pagamento;
    FORMA_PGTO forma_pgto;
}OPCAO_PGTO;
typedef struct{
    char cpf[50];
    PLANO plano;
    int dia_contrato;
    int mes_contrato;
    int dia_cancelamento;
    int mes_cancelamento;
    OPCAO_PGTO pagamento;
}CONTRATO;

///////////////////// HISTORICO MENSAL /////////////////////
typedef struct{
    int codigo_filme;
    int dia;
    int mes;
}HISTORICO;     // 10 clientes X 30 filmes cada

///////////////////// GENERO /////////////////////
typedef struct{
    int max_cadastrado;
    int identificador_genero;
    int quantidade_assistido[10];
}ASSISTIDO;


///////////////////// SUBROTINAS /////////////////////
int cadastro_cliente(CLIENTE* cliente, int* cont_cliente);
int cadastro_filme(FILME* filme, int* cont_filme, int* codigo_filme, ASSISTIDO* genero);
void cadastro_plano_basico(PLANO* planobasico);
void cadastro_plano_premium(PLANO* planopremium);
int cadastro_contrato(CONTRATO* contrato, int* cont_contrato, int cont_cliente, CLIENTE* cliente, PLANO plano, int mes, float* devido);
int carregar_filme(FILME* filme, int cont_filme, CLIENTE* cliente, int cont_cliente, HISTORICO historico[][30], int* cont_assistir, CONTRATO* contrato, int* excedente, int mes, int frequencia[][10], ASSISTIDO* genero, int cont_contrato, int* total_assistido);
void cancelar_contrato(CONTRATO* contrato, int *cont_contrato, CLIENTE* cliente, int cont_cliente, int mes, float* devido);
void gerar_fatura(CONTRATO* contrato, CLIENTE* cliente, int cont_contrato, int cont_cliente, int* mes, HISTORICO historico[][30], int* excedente, int* cont_assistir, FILME* filme, float* devido, int cont_filme, ASSISTIDO* genero);
void dados_cliente(CLIENTE* cliente, int cont_cliente);
void historico_cliente(CLIENTE* cliente, int cont_cliente, FILME* filme, int cont_filme, HISTORICO historico[][30], int* cont_assistir);
void excederam_cota_mensal(CLIENTE* cliente, int cont_cliente, CONTRATO* contrato, int cont_contrato, int* excedente);
void frequencia_filme(FILME* filme, int cont_filme, int cont_cliente, int frequencia[][10], int total_assistido, int* cont_assistir);
void recomendar_filme(CLIENTE* cliente, int cont_cliente, FILME* filme, int cont_filme, HISTORICO historico[][30], int* cont_assistir, ASSISTIDO* genero);

///////////////////// PROGRAMA /////////////////////

int main(){
    int opcao;
    const int const_cliente=10, const_filme=10, const_contrato=10, max_assistir=30;
    int cont_assistir[10]={0}; // o quanto cada cliente assistiu
    int codigo_filme=1001;
    ASSISTIDO genero[6];    //6 é o maximo (conta os filmes de cada genero que foram cadastrados)
    int excedente[10]={0}; //  quantos clientes excederam
    int mes=1;
    int frequencia[10][10]={{0}};     //clientes x filmes
    float devido[10]={0};
    HISTORICO historico[const_cliente][max_assistir];
    CLIENTE cliente[const_cliente];
    FILME filme[const_filme];
    PLANO plano;
    CONTRATO contrato[const_contrato];
    int cont_cliente=0, cont_filme=0, cont_contrato=0;
    int verificador, j, i;
    int total_assistido=0;
    
    for (i=0; i<6; i++){
        genero[i].max_cadastrado=0;
        genero[i].identificador_genero=0;
        for(j=0; j<10; j++)
        {
            genero[i].quantidade_assistido[j] = 0;
        }
    }
    do{
        scanf(" %d", &opcao);
        switch (opcao){
            case 1:{
                verificador=cadastro_cliente(cliente, &cont_cliente);
                if (verificador==0){
                    printf("Cliente cadastrado com sucesso\n");
                }
                if (verificador==1){
                    printf("ERRO: CPF do cliente ja cadastrado\n");
                }
                if (verificador==2){
                    printf("ERRO: Numero maximo de clientes no sistema atingido\n");
                }
                break;
            }
            case 2:{
                verificador=cadastro_filme(filme, &cont_filme, &codigo_filme, genero);
                if (verificador==0){
                    printf("Filme cadastrado com sucesso\n");
                }
                if (verificador==1){
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                }
                break;
            }
            case 3:{
                cadastro_plano_basico(&plano);
                break;
            }
            case 4:{
                cadastro_plano_premium(&plano);
                break;
            }
            case 5:{
                verificador=cadastro_contrato(contrato, &cont_contrato, cont_cliente, cliente, plano, mes, devido);
                if (verificador==0){
                    printf("Contrato cadastrado com sucesso\n");
                }
                if (verificador==1){
                    printf("ERRO: Cliente com contrato existente\n");  
                }
                if (verificador==2){
                    printf("ERRO: Cliente nao cadastrado\n");    
                }
                if (verificador==3){
                    printf("ERRO: Numero maximo de contratos no sistema atingido\n");  
                }
                if (verificador==4){
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                }
                break;
            }
            case 6:{
                verificador=carregar_filme(filme, cont_filme, cliente, cont_cliente, historico, cont_assistir, contrato, excedente, mes, frequencia, genero, cont_contrato, &total_assistido);
                if (verificador==0){
                    printf("Filme carregado com sucesso\n");
                }
                if (verificador==1){
                    printf("ERRO: Filme nao encontrado\n");
                }
                if (verificador==2){
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                }
                if (verificador==3){
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                }
                if (verificador==4){
                    printf("ERRO: Taxa adicional negada\n");
                }
                if (verificador==5){
                    printf("ERRO: Cliente nao cadastrado\n");
                }
                if (verificador==6){
                    printf("ERRO: Cliente nao ativo\n");
                }
                break;
            }
            case 7:{
                cancelar_contrato(contrato, &cont_contrato, cliente, cont_cliente, mes, devido);
                break;
            }
            case 8:{
                gerar_fatura(contrato, cliente, cont_contrato, cont_cliente, &mes, historico, excedente, cont_assistir, filme, devido, cont_filme, genero);
                break;
            }
            case 9:{
                dados_cliente(cliente, cont_cliente);
                break;
            }
            case 10:{
                historico_cliente(cliente, cont_cliente, filme, cont_filme, historico, cont_assistir);
                break;
            }
            case 11:{
                excederam_cota_mensal(cliente, cont_cliente, contrato, cont_contrato, excedente);
                break;
            }
            case 12:{
                frequencia_filme(filme, cont_filme, cont_cliente, frequencia, total_assistido, cont_assistir);
                break;
            }
            case 13:{
                recomendar_filme(cliente, cont_cliente, filme, cont_filme, historico, cont_assistir, genero);
                break;
            }
            case 0:{
                printf("Finalizando programa...");
                break;
            }
            default:{
                printf("ERRO: Opcao invalida\n");
                break;
            }
        }
    }while(opcao!=0);
}

int cadastro_cliente(CLIENTE* cliente, int* cont_cliente){
    char cpf[50];
    int i;

    if((*cont_cliente)>=10){
        return 2;
    }
    else{
        scanf(" %[^\n]%*c", cpf);
        for (i=0; i<(*cont_cliente); i++){
            if(strcmp(cpf, cliente[i].cliente.cpf)==0){
                return 1;
            }
        }
        strcpy(cliente[*cont_cliente].cliente.cpf, cpf);
        scanf(" %[^\n]%*c", cliente[*cont_cliente].cliente.nome);
        scanf(" %[^\n]%*c", cliente[*cont_cliente].cliente.email);
        scanf(" %[^\n]%*c", cliente[*cont_cliente].cliente.telefone);
        cliente[*cont_cliente].status=inativo;
        (*cont_cliente)++;
        return 0; 
    }  
}

int cadastro_filme(FILME* filme, int* cont_filme, int* codigo_filme, ASSISTIDO* genero){ 
    if((*cont_filme)>=10){
        return 1;
    }

    scanf(" %[^\n]%*c", filme[*cont_filme].filme.nome);
    do{
        scanf(" %u", &filme[*cont_filme].genero);
        if (filme[*cont_filme].genero<0 || filme[*cont_filme].genero>5){
            printf("ERRO: Genero invalido\n");
        }
        else{
            break;
        }
    } while (filme[*cont_filme].genero<0 || filme[*cont_filme].genero>5); 
    if (filme[*cont_filme].genero==aventura){
        genero[0].max_cadastrado++;
        genero[0].identificador_genero=aventura;
    }
    else if (filme[*cont_filme].genero==comedia){
        genero[1].max_cadastrado++;
        genero[1].identificador_genero=comedia;
    }
    else if (filme[*cont_filme].genero==drama){
        genero[2].max_cadastrado++;
        genero[2].identificador_genero=drama;
    }
    else if (filme[*cont_filme].genero==terror){
        genero[3].max_cadastrado++;
        genero[3].identificador_genero=terror;
    }
    else if (filme[*cont_filme].genero==acao){
        genero[4].max_cadastrado++;
        genero[4].identificador_genero=acao;
    }
    else if (filme[*cont_filme].genero==romance){
        genero[5].max_cadastrado++;
        genero[5].identificador_genero=romance;
    }
            
    do{
        scanf(" %u", &filme[*cont_filme].classificacao);
        if (filme[*cont_filme].classificacao<0 || filme[*cont_filme].classificacao>5){
            printf("ERRO: Classificao invalida\n");
        }
        else{
            break;
        }  
    } while (filme[*cont_filme].classificacao<0 || filme[*cont_filme].classificacao>5);
    filme[*cont_filme].filme.codigobusca=(*codigo_filme);
    (*codigo_filme)++;
    (*cont_filme)++;
    return 0;
}

void cadastro_plano_basico(PLANO* planobasico){
    scanf(" %d", &(*planobasico).plano.planobasico.quantidade);
    scanf(" %f", &(*planobasico).plano.planobasico.valor_base);
    scanf(" %f", &(*planobasico).plano.planobasico.valor_excedente);
    printf("Plano Basico cadastrado com sucesso\n");
}

void cadastro_plano_premium(PLANO* planopremium){
    scanf(" %f", &(*planopremium).plano.planopremium.valor_base);
    printf("Plano Premium cadastrado com sucesso\n");
}

int cadastro_contrato(CONTRATO* contrato, int* cont_contrato, int cont_cliente, CLIENTE* cliente, PLANO plano, int mes, float* devido){
    char cpf[50];
    int contador_cliente=0;
    int i;

    if (cont_cliente==0){
        return 4;
    }
    if ((*cont_contrato)>=10){
        return 3;
    }
    scanf(" %[^\n]%*c", cpf);
    for ( i=0; i<cont_cliente; i++){
        if (strcmp(cpf, cliente[i].cliente.cpf)==0){
            if (cliente[i].status==ativo){
                return 1;
            }
            strcpy(contrato[*cont_contrato].cpf, cpf);
            contador_cliente=1; //prova que o cliente ta cadastrado
            do{
                scanf(" %u", &contrato[*cont_contrato].plano.opcao_plano);
                if(contrato[*cont_contrato].plano.opcao_plano<0 || contrato[*cont_contrato].plano.opcao_plano>1){
                    printf("ERRO: Tipo de plano invalido\n");
                }
                else{
                    break;
                } 
            } while (contrato[*cont_contrato].plano.opcao_plano<0 || contrato[*cont_contrato].plano.opcao_plano>1);
            do{
                scanf(" %u", &contrato[*cont_contrato].pagamento.pagamento);
                if (contrato[*cont_contrato].pagamento.pagamento<0 || contrato[*cont_contrato].pagamento.pagamento>1){
                    printf("ERRO: Tipo de pagamento invalido\n");
                }
                else{
                    break;
                }
            }while(contrato[*cont_contrato].pagamento.pagamento<0 || contrato[*cont_contrato].pagamento.pagamento>1);

            if(contrato[*cont_contrato].plano.opcao_plano == 0)
            {
                contrato[*cont_contrato].plano.plano.planobasico.quantidade = plano.plano.planobasico.quantidade;
                contrato[*cont_contrato].plano.plano.planobasico.valor_base = plano.plano.planobasico.valor_base;
                contrato[*cont_contrato].plano.plano.planobasico.valor_excedente = plano.plano.planobasico.valor_excedente;
                devido[i] = contrato[*cont_contrato].plano.plano.planobasico.valor_base;
            }
            else if(contrato[*cont_contrato].plano.opcao_plano == 1)
            {
                contrato[*cont_contrato].plano.plano.planopremium.valor_base = plano.plano.planopremium.valor_base;
                devido[i] = contrato[*cont_contrato].plano.plano.planopremium.valor_base;
            }
            if (contrato[*cont_contrato].pagamento.pagamento==0){
                scanf(" %[^\n]%*c", contrato[*cont_contrato].pagamento.forma_pgto.debito.numero_agencia);
                scanf(" %[^\n]%*c", contrato[*cont_contrato].pagamento.forma_pgto.debito.numero_conta);
            }   
            else if (contrato[*cont_contrato].pagamento.pagamento==1){
                scanf(" %[^\n]%*c", contrato[*cont_contrato].pagamento.forma_pgto.credito.numero_cartao);
            } 
            do{
                scanf(" %d", &contrato[*cont_contrato].dia_contrato);
                if (contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31){
                    printf("ERRO: Dia invalido\n");
                }
                else{
                    break;
                }
            }while(contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31); 
            contrato[*cont_contrato].mes_contrato=mes;
            contrato[*cont_contrato].dia_cancelamento=0;
            contrato[*cont_contrato].mes_cancelamento=0;
            (*cont_contrato)++;
            cliente[i].status=ativo;
            return 0;      
        }
    }
    if (contador_cliente==0){
        return 2;
    }
    return 0;   
}

int carregar_filme(FILME* filme, int cont_filme, CLIENTE* cliente, int cont_cliente, HISTORICO historico[][30], int* cont_assistir, CONTRATO* contrato, int* excedente, int mes, int frequencia[][10], ASSISTIDO* genero, int cont_contrato, int* total_assistido){
    char cpf[50];
    int i, j, k, codigo_filme, dia, opcao, genero_var, classificacao_var, taxa;
    int conferir;

    if(cont_cliente==0){
        return 3;
    }
    scanf(" %[^\n]%*c", cpf);
    for(i=0; i<cont_cliente; i++){
        if(strcmp(cpf, cliente[i].cliente.cpf)==0){
            if (cliente[i].status==ativo){
                if (cont_assistir[i]==30){
                    return 2;
                }
                do{
                    scanf(" %d", &dia);
                    if (dia<1 || dia>31){
                        printf("ERRO: Dia invalido\n");
                    }
                    else{
                        break;
                    }
                }while(1);
                do{
                    scanf(" %d", &opcao);  //genero ou classificacao
                    if (opcao<0 || opcao>1){
                        printf("ERRO: Escolha invalida\n");
                    }
                    else{
                        break;
                    }
                } while (1);           
                if(opcao==0){
                    do{
                        scanf(" %d", &genero_var);
                        if (genero_var<0 || genero_var>5){
                            printf("ERRO: Escolha invalida\n");
                        }
                        else{
                            break;
                        }
                    } while (1);
                    for ( j=0; j<cont_filme; j++){
                        if (genero_var==filme[j].genero){
                            printf("Codigo: %d\n", filme[j].filme.codigobusca);
                            printf("Nome: %s\n", filme[j].filme.nome);
                        } 
                    } 
                }
                if (opcao==1){
                    do{
                        scanf(" %d", &classificacao_var);
                        if (classificacao_var<0 || classificacao_var>5){
                            printf("ERRO: Escolha invalida\n");
                        }
                        else{
                            break;
                        }  
                    } while (1);
                    for ( j=0; j<cont_filme; j++){
                        if (classificacao_var==filme[j].classificacao){
                            printf("Codigo: %d\n", filme[j].filme.codigobusca);
                            printf("Nome: %s\n", filme[j].filme.nome);
                        }
                    }
                }  
                scanf(" %d", &codigo_filme);
                for(j=0; j<cont_filme; j++){
                    if (codigo_filme==filme[j].filme.codigobusca){
                        for ( k=0; k<cont_contrato; k++){ 
                            if (strcmp(cliente[i].cliente.cpf, contrato[k].cpf)==0){
                                if (contrato[k].plano.opcao_plano == plano_basico){
                                    if(cont_assistir[i] < contrato[k].plano.plano.planobasico.quantidade){
                                        break;
                                    }
                                    else if (cont_assistir[i] >= contrato[k].plano.plano.planobasico.quantidade){
                                        do{
                                            scanf(" %d", &taxa);
                                            if (taxa<0 || taxa>1){
                                                printf("ERRO: Escolha invalida\n");
                                            }
                                            else{
                                                break;
                                            }
                                        }while (taxa<0 || taxa>1);
                                        if (taxa==0){
                                            return 4;
                                        }
                                        if (taxa==1){
                                            excedente[i]++;
                                            break;
                                        }                                                        
                                    }
                                }
                                else if (contrato[k].plano.opcao_plano==plano_premium){
                                    break;
                                }   
                            }
                        }
                        conferir = 0;
                        for(k=0; k<cont_assistir[i]; k++)
                        {
                            if(filme[j].filme.codigobusca == historico[i][k].codigo_filme)
                            {
                                conferir = 1;
                            }
                        }
                        if(conferir == 0)
                        {
                            if (filme[j].genero==aventura){    
                                genero[0].quantidade_assistido[i]++;
                            }
                            else if (filme[j].genero==comedia){   
                                genero[1].quantidade_assistido[i]++;
                            }
                            else if (filme[j].genero==drama){   
                                genero[2].quantidade_assistido[i]++;
                            }
                            else if (filme[j].genero==terror){   
                                genero[3].quantidade_assistido[i]++;
                            }
                            else if (filme[j].genero==acao){  
                                genero[4].quantidade_assistido[i]++;
                            }
                            else if (filme[j].genero==romance){   
                                genero[5].quantidade_assistido[i]++;
                            }
                        }
                        historico[i][cont_assistir[i]].codigo_filme = filme[j].filme.codigobusca; 
                        historico[i][cont_assistir[i]].dia = dia;
                        historico[i][cont_assistir[i]].mes = mes;
                        (*total_assistido)++;
                        frequencia[i][j]++;
                        cont_assistir[i]++;
                        return 0;
                    }   
                }
                return 1;
            }
            return 6;
        }
    }
    return 5;
    //return 0;
}

void cancelar_contrato(CONTRATO* contrato, int *cont_contrato, CLIENTE* cliente, int cont_cliente, int mes, float* devido){
    int i, j, k, dia;
    int contador_ativo=0, contador_cliente=0; 
    char cpf[50];

    if (*cont_contrato==0){
        printf("ERRO: Nenhum contrato cadastrado no sistema\n");
        return;
    }

    scanf(" %[^\n]%*c", cpf);
    for (i=0; i<cont_cliente; i++){
        if (strcmp(cpf, cliente[i].cliente.cpf)==0){
            contador_cliente=1;
            for(j=0; j<*cont_contrato; j++){
                if(strcmp(cliente[i].cliente.cpf, contrato[j].cpf)==0){
                    contador_ativo=1;
                    do{
                        scanf(" %d", &dia);
                        if (dia<1 || dia>31){
                            printf("ERRO: Dia invalido\n");
                        }
                        else{
                            break;
                        }
                    } while (dia<1 || dia>31);
                    if(mes > contrato[j].mes_contrato){
                        printf("Valor devido: %.2f\n", devido[i]);
                        contrato[j].dia_cancelamento=dia;
                        contrato[j].mes_cancelamento=mes;
                        cliente[i].status=inativo;
                        printf("Cancelamento feito com sucesso\n");
                        for ( k = j; k < *cont_contrato; k++){
                            strcpy(contrato[k].cpf, contrato[k+1].cpf);
                            contrato[k].plano.opcao_plano=contrato[k+1].plano.opcao_plano;
                            contrato[k].plano.plano=contrato[k+1].plano.plano;
                            contrato[k].dia_contrato=contrato[k+1].dia_contrato;
                            contrato[k].mes_contrato=contrato[k+1].mes_contrato;
                            contrato[k].dia_cancelamento=contrato[k+1].dia_cancelamento;
                            contrato[k].mes_cancelamento=contrato[k+1].mes_cancelamento;
                            contrato[k].pagamento=contrato[k+1].pagamento;
                        }
                        (*cont_contrato)--;
                        return;
                    }
                    else if (dia>=contrato[j].dia_contrato){
                        printf("Valor devido: %.2f\n", devido[i]);
                        contrato[j].dia_cancelamento=dia;
                        contrato[j].mes_cancelamento=mes;
                        cliente[i].status=inativo;
                        printf("Cancelamento feito com sucesso\n");
                        for ( k = j; k < *cont_contrato; k++){
                            strcpy(contrato[k].cpf, contrato[k+1].cpf);
                            contrato[k].plano.opcao_plano=contrato[k+1].plano.opcao_plano;
                            contrato[k].dia_contrato=contrato[k+1].dia_contrato;
                            contrato[k].mes_contrato=contrato[k+1].mes_contrato;
                            contrato[k].dia_cancelamento=contrato[k+1].dia_cancelamento;
                            contrato[k].mes_cancelamento=contrato[k+1].mes_cancelamento;
                            contrato[k].pagamento=contrato[k+1].pagamento;
                        }
                        (*cont_contrato)--;
                        return;
                    }
                    
                    else{
                        printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                        return;
                    }
                }
            }
        }   
    }
    if (contador_cliente==0){
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
    if (contador_ativo==0){
        printf("ERRO: Cliente inativo\n");
        return;
    }
}

void gerar_fatura(CONTRATO* contrato, CLIENTE* cliente, int cont_contrato, int cont_cliente, int* mes, HISTORICO historico[][30], int* excedente, int* cont_assistir, FILME* filme, float* devido, int cont_filme, ASSISTIDO* genero){
    int i, j, k, n, opcao;
    char cpf[50];
    int contador_cliente=0;

    do{
        scanf(" %d", &opcao);
        if (opcao<0 || opcao>1){
            printf("ERRO: Escolha invalida\n");
        }
        else{
            break;
        }
    }while (opcao<0 || opcao>1);
    if (opcao==0){
        if (cont_cliente==0){
            printf("ERRO: Nenhum cliente cadastrado no sistema\n");
            return;
        }
        if (cont_contrato==0){
            printf("ERRO: Nenhum contrato cadastrado no sistema\n");
            return;
        }
        scanf(" %[^\n]%*c", cpf);
        for ( i=0; i<cont_cliente; i++){
            if (strcmp(cpf, cliente[i].cliente.cpf)==0){
                contador_cliente=1; //cliente existe
                if (cliente[i].status==ativo){
                    for ( n = 0; n < cont_assistir[i]; n++){
                        for ( j=0; j<cont_filme; j++){
                            if (historico[i][n].codigo_filme==filme[j].filme.codigobusca){
                                printf("Nome: %s\n", filme[j].filme.nome); //nome do filme
                                printf("Data: %d/%d\n", historico[i][n].dia, historico[i][n].mes); //data do carregamento
                            }  
                        }
                    }
                    for ( k = i; k < cont_contrato; k++){
                        if (contrato[k].plano.opcao_plano==0){   //basico
                            devido[i] = contrato[k].plano.plano.planobasico.valor_base+(excedente[i]*contrato[k].plano.plano.planobasico.valor_excedente);
                            printf("Valor devido: %.2f\n", devido[i]);
                            return;
                        }
                        if (contrato[k].plano.opcao_plano==1){
                            devido[i]=contrato[k].plano.plano.planopremium.valor_base;
                            printf("Valor devido: %.2f\n", devido[i]);
                            return;
                        } 
                    }
                    
                    
                }
                if (cliente[i].status==inativo){
                    printf("ERRO: Cliente nao possui contrato\n");
                    return;
                }
                 
            }  
        } 
    }
    if (opcao==1){
        for (i=0; i<cont_cliente; i++){
            if (cliente[i].status==ativo){
                for ( j = 0; j < cont_contrato; j++){
                    if (strcmp(cliente[i].cliente.cpf, contrato[j].cpf)==0){
                        if (contrato[j].plano.opcao_plano==plano_basico){
                            devido[i]=contrato[j].plano.plano.planobasico.valor_base+(excedente[i]*contrato[j].plano.plano.planobasico.valor_excedente);
                            excedente[i]=0;
                        }
                        if (contrato[j].plano.opcao_plano==plano_premium){
                            devido[i]=contrato[j].plano.plano.planopremium.valor_base;
                        }
                    }
                }
                printf("CPF: %s\n", cliente[i].cliente.cpf);
                printf("Nome: %s\n", cliente[i].cliente.nome); //nome do cliente
                printf("Valor devido: %.2f\n", devido[i]);
                
                for ( j = 0; j < cont_assistir[i]; j++){
                    historico[i][j].codigo_filme=0;
                }
                cont_assistir[i]=0;
                for(j=0; j<6; j++)
                {
                    genero[j].quantidade_assistido[i] = 0;
                }
            } 
        } 
        (*mes)++;
        printf("Mes vigente apos a fatura: %d\n", *mes);
        return;
    }
    if(contador_cliente==0){
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
}

void dados_cliente(CLIENTE* cliente, int cont_cliente){
    char cpf[50];
    int i, contador_cliente=0;

    if (cont_cliente==0){
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    scanf(" %[^\n]%*c", cpf);
    for (i=0; i<cont_cliente; i++){
        if (strcmp(cpf, cliente[i].cliente.cpf)==0){
            contador_cliente=1; //cliente existe no sistema
            printf("Nome: %s\n", cliente[i].cliente.nome);
            printf("Email: %s\n", cliente[i].cliente.email);
            printf("Telefone: %s\n", cliente[i].cliente.telefone);
            printf("Status: %d\n", cliente[i].status);
        }
    }
    if (contador_cliente==0){
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    } 
}

void historico_cliente(CLIENTE* cliente, int cont_cliente, FILME* filme, int cont_filme, HISTORICO historico[][30], int* cont_assistir){
    int i, j, k;
    char cpf[50];
    int contador_cliente=0;

    if (cont_cliente==0){
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    scanf(" %[^\n]%*c", cpf);
    for ( i=0; i<cont_cliente; i++){
        if (strcmp(cpf, cliente[i].cliente.cpf)==0){
            contador_cliente=1;     //cliente existe
            if(cliente[i].status==inativo){
                printf("Estado: Inativo\n");
            }
            if(cliente[i].status==ativo){
                printf("Estado: Ativo\n");
            }
            if (cont_assistir[i]==0){
                printf("ERRO: Nenhum filme assistido\n");
                return;
            }
            if (cont_assistir[i]!=0){
                for ( j = 0; j < cont_assistir[i]; j++){
                    for ( k=0; k<cont_filme; k++){ 
                        if (historico[i][j].codigo_filme==filme[k].filme.codigobusca){
                            printf("Codigo: %d\n",filme[k].filme.codigobusca); //codigo do filme
                            printf("Nome: %s\n",filme[k].filme.nome); //nome do filme
                            if (filme[k].genero==aventura){
                                printf("Genero: aventura\n");
                            }
                            if (filme[k].genero==comedia){
                                printf("Genero: comedia\n");
                            }
                            if (filme[k].genero==drama){
                                printf("Genero: drama\n");
                            }
                            if (filme[k].genero==terror){
                                printf("Genero: terror\n");
                            }
                            if (filme[k].genero==acao){
                                printf("Genero: acao\n");
                            }
                            if (filme[k].genero==romance){
                                printf("Genero: romance\n");
                            }
                            if (filme[k].classificacao==livre){
                                printf("Classificacao: livre\n");
                            }
                            if (filme[k].classificacao==mais10){
                                printf("Classificacao: +10\n");
                            }
                            if (filme[k].classificacao==mais12){
                                printf("Classificacao: +12\n");
                            }
                            if (filme[k].classificacao==mais14){
                                printf("Classificacao: +14\n");
                            }
                            if (filme[k].classificacao==mais16){
                                printf("Classificacao: +16\n");
                            }
                            if (filme[k].classificacao==mais18){
                                printf("Classificacao: +18\n");
                            }
                            printf("Data do carregamento: %d/%d\n\n", historico[i][j].dia, historico[i][j].mes);
                        }
                    }
                }
                return;
            }
        }
    }
    if (contador_cliente==0){
        printf("ERRO: Cliente nao cadastrado\n");
        return;
    }
}

void excederam_cota_mensal(CLIENTE* cliente, int cont_cliente, CONTRATO* contrato, int cont_contrato, int* excedente){
    int i, j;
    float excesso;
    int verifica_excesso=0;

    for (i=0; i<cont_contrato; i++){
        for ( j = 0; j < cont_cliente; j++){
            if (strcmp(cliente[j].cliente.cpf, contrato[i].cpf)==0){    //cliente ativo
                if (contrato[i].plano.opcao_plano==plano_basico){
                    if (excedente[j]!=0){
                        verifica_excesso=1;
                            printf("CPF: %s\n", cliente[j].cliente.cpf);
                            printf("Nome: %s\n",cliente[j].cliente.nome);
                            excesso=(float)(contrato[i].plano.plano.planobasico.valor_excedente)*(excedente[j]);
                            printf("Valor excedente: %.2f\n\n",excesso);
                            return; 
                    }
                }
            }
        }
    }
    if (verifica_excesso==0){
        printf("ERRO: Nenhum cliente excedente\n");
        return;
    }
}

void frequencia_filme(FILME* filme, int cont_filme, int cont_cliente, int frequencia[][10], int total_assistido, int* cont_assistir){
    int i, j;
    int codigo_filme, verifica_filme=0;

    if (cont_filme==0){
        printf("ERRO: Nenhum filme cadastrado no sistema\n");
        return;
    }
    scanf(" %d", &codigo_filme);
    for ( i=0; i<cont_cliente; i++){
        for ( j=0; j<cont_filme; j++){
            if (codigo_filme==filme[j].filme.codigobusca){
                verifica_filme=1;
                if (cont_assistir[i]==0){
                    printf("ERRO: Nenhum filme assistido\n");
                    return;
                }
                if (cont_assistir[i]!=0){
                    printf("Frequencia: %.2f%%\n",(float)(frequencia[i][j]*100/total_assistido));
                    return;
                }
            }
        }
    }
    if (verifica_filme==0){
        printf("ERRO: Codigo invalido\n");
        return;
    }
}

void recomendar_filme(CLIENTE* cliente, int cont_cliente, FILME* filme, int cont_filme, HISTORICO historico[][30], int* cont_assistir, ASSISTIDO* genero){
    int i, j, k, m;
    ASSISTIDO mais_assistido;
    char cpf[50];
    int filme_ta_hist=0, empate=0, genero_empate[6]={0};


    if(cont_cliente==0){
        printf("ERRO: Nenhum cliente cadastrado no sistema\n");
        return;
    }
    scanf(" %[^\n]%*c", cpf);
    for ( i=0; i<cont_cliente; i++){
        if(strcmp(cpf, cliente[i].cliente.cpf)==0){
            if (cliente[i].status==ativo){
                if (cont_assistir[i]==0){
                    printf("ERRO: Nenhum filme assistido\n");
                    return;
                }
                mais_assistido.quantidade_assistido[i] = genero[0].quantidade_assistido[i];
                mais_assistido.identificador_genero = genero[0].identificador_genero;
                for ( m=0; m<6; m++){
                    if (genero[m].quantidade_assistido[i] > mais_assistido.quantidade_assistido[i]){ 
                        mais_assistido.quantidade_assistido[i] = genero[m].quantidade_assistido[i];
                        mais_assistido.identificador_genero = genero[m].identificador_genero;
                    }
                }
                for ( j = 0; j < 6; j++){
                    
                    if (mais_assistido.identificador_genero == genero[j].identificador_genero && mais_assistido.quantidade_assistido[i] == genero[j].max_cadastrado){
                        printf("ERRO: Todos os filmes do(s) genero(s) foram assistidos\n");
                        return;
                    }
                }
                for(k=0; k<6; k++)
                {
                    if(mais_assistido.quantidade_assistido[i] == genero[k].quantidade_assistido[i] && mais_assistido.identificador_genero != genero[k].identificador_genero)
                    {
                        genero_empate[empate] = k;
                        empate++;
                    }
                }
                if(empate == 0)
                {
                    for(j=0; j<cont_filme; j++)
                    {
                        filme_ta_hist = 0;   //verifica se filme esta no historico
                        for(m=0; m<cont_assistir[i]; m++)
                        {
                            if(filme[j].filme.codigobusca == historico[i][m].codigo_filme)
                            {
                                filme_ta_hist = 1;
                            }
                        }
                        if(filme_ta_hist == 0)
                        {
                            if(filme[j].genero == mais_assistido.identificador_genero)
                            {
                                printf("Codigo: %d\n", filme[j].filme.codigobusca);
                                printf("Nome: %s\n", filme[j].filme.nome);
                                if (filme[j].genero==aventura){    
                                    printf("Genero: aventura\n");
                                }                          
                                else if (filme[j].genero==comedia){   
                                    printf("Genero: comedia\n");
                                }
                                else if (filme[j].genero==drama){ 
                                    printf("Genero: drama\n");
                                }
                                else if (filme[j].genero==terror){ 
                                    printf("Genero: terror\n");
                                }
                                else if (filme[j].genero==acao){   
                                    printf("Genero: acao\n");
                                }
                                else if (filme[j].genero==romance){  
                                    printf("Genero: romance\n");
                                }
                                if (filme[j].classificacao==livre){
                                    printf("Classificacao: livre\n");
                                }
                                else if (filme[j].classificacao==mais10){
                                    printf("Classificacao: +10\n");
                                }
                                else if (filme[j].classificacao==mais12){
                                    printf("Classificacao: +12\n");
                                }
                                else if (filme[j].classificacao==mais14){
                                    printf("Classificacao: +14\n");
                                }
                                else if (filme[j].classificacao==mais16){
                                    printf("Classificacao: +16\n");
                                }
                                else if (filme[j].classificacao==mais18){
                                    printf("Classificacao: +18\n");
                                }    
                            }
                        }  
                    }
                    return;
                }
                if(empate!=0){
                    for(j=0; j<cont_filme; j++)
                    {
                         
                    filme_ta_hist = 0;   //verifica se filme esta no historico
                    for(m=0; m<cont_assistir[i]; m++)
                    {
                        if(filme[j].filme.codigobusca == historico[i][m].codigo_filme)
                        {
                            filme_ta_hist = 1;
                        }
                    }
                    if(filme_ta_hist == 0)
                    {
                        if(filme[j].genero == mais_assistido.identificador_genero)
                        {
                            printf("Codigo: %d\n", filme[j].filme.codigobusca);
                            printf("Nome: %s\n", filme[j].filme.nome);
                            if (filme[j].genero==aventura){    
                                printf("Genero: aventura\n");
                            }                          
                            else if (filme[j].genero==comedia){   
                                printf("Genero: comedia\n");
                            }
                            else if (filme[j].genero==drama){ 
                                printf("Genero: drama\n");
                            }
                            else if (filme[j].genero==terror){ 
                                printf("Genero: terror\n");
                            }
                            else if (filme[j].genero==acao){   
                                printf("Genero: acao\n");
                            }
                            else if (filme[j].genero==romance){  
                                printf("Genero: romance\n");
                            }
                            if (filme[j].classificacao==livre){
                                printf("Classificacao: livre\n");
                            }
                            else if (filme[j].classificacao==mais10){
                                printf("Classificacao: +10\n");
                            }
                            else if (filme[j].classificacao==mais12){
                                printf("Classificacao: +12\n");
                            }
                            else if (filme[j].classificacao==mais14){
                                printf("Classificacao: +14\n");
                            }
                            else if (filme[j].classificacao==mais16){
                                printf("Classificacao: +16\n");
                            }
                            else if (filme[j].classificacao==mais18){
                                printf("Classificacao: +18\n");
                            }  
                        }
                    }  
                        
                    }
                    for(j=0; j<cont_filme; j++)
                    {
                        for(k=0; k<empate; k++)
                        { 
                            filme_ta_hist = 0;   //verifica se filme esta no historico
                            for(m=0; m<cont_assistir[i]; m++)
                            {
                                if(filme[j].filme.codigobusca == historico[i][m].codigo_filme)
                                {
                                    filme_ta_hist = 1;
                                }
                            }
                            if(filme_ta_hist == 0)
                            {
                                if(filme[j].genero == genero_empate[k])
                                {
                                    printf("Codigo: %d\n", filme[j].filme.codigobusca);
                                    printf("Nome: %s\n", filme[j].filme.nome);
                                    if (filme[j].genero==aventura){    
                                        printf("Genero: aventura\n");
                                    }                          
                                    else if (filme[j].genero==comedia){   
                                        printf("Genero: comedia\n");
                                    }
                                    else if (filme[j].genero==drama){ 
                                        printf("Genero: drama\n");
                                    }
                                    else if (filme[j].genero==terror){ 
                                        printf("Genero: terror\n");
                                    }
                                    else if (filme[j].genero==acao){   
                                        printf("Genero: acao\n");
                                    }
                                    else if (filme[j].genero==romance){  
                                        printf("Genero: romance\n");
                                    }
                                    if (filme[j].classificacao==livre){
                                        printf("Classificacao: livre\n");
                                    }
                                    else if (filme[j].classificacao==mais10){
                                        printf("Classificacao: +10\n");
                                    }
                                    else if (filme[j].classificacao==mais12){
                                        printf("Classificacao: +12\n");
                                    }
                                    else if (filme[j].classificacao==mais14){
                                        printf("Classificacao: +14\n");
                                    }
                                    else if (filme[j].classificacao==mais16){
                                        printf("Classificacao: +16\n");
                                    }
                                    else if (filme[j].classificacao==mais18){
                                        printf("Classificacao: +18\n");
                                    }    
                                }
                            }  
                        }               
                    }
                    return;
                }
            }
            else{
                printf("ERRO: Cliente nao ativo\n");
                return;
            }
            
        }
    }
    printf("ERRO: Cliente nao cadastrado\n");
    return;
}
