#include <stdio.h>
#include <string.h>
#include <stdlib.h>
///////////////////// CLIENTE /////////////////////
typedef enum{
    ativo=1, inativo
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
typedef union{
    PLANOBASICO planobasico;
    PLANOPREMIUM planopremium;
}UNION_PLANO;
typedef struct{
    ENUM_PLANO opcao_plano;
    UNION_PLANO plano;
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

typedef struct{
    CLIENTE cliente;
    FILME filme;
    CONTRATO contrato;
    PLANO plano;
}INFORMACOES;

///////////////////// SUBROTINAS /////////////////////
int cadastro_cliente(CLIENTE* cliente, int* cont_cliente);
int cadastro_filme(FILME* filme, int* cont_filme, int* codigo_filme);
void cadastro_plano_basico(PLANO* planobasico);
void cadastro_plano_premium(PLANO* planopremium);
int cadastro_contrato(CONTRATO* contrato, int* cont_contrato, int cont_cliente, CLIENTE* cliente);
int carregar_filme(FILME* filme, int cont_filme, CLIENTE* cliente, int cont_cliente, HISTORICO historico[][30], int* cont_assistir, PLANO* plano, CONTRATO* contrato, int* excedente, int mes);
int cancelar_contrato(CONTRATO* contrato, int cont_contrato, CLIENTE* cliente, int cont_cliente, int mes, float* devido[10]);
int gerar_fatura(CONTRATO* contrato, CLIENTE* cliente, int cont_contrato, int cont_cliente, int mes, HISTORICO historico[][30], int* excedente, int* cont_assistir, FILME* filme, float* devido[10]);
void dados_cliente();
void historico_cliente();
void excederam_cota_mensal();
void frequencia_filme();
void recomendar_filme();

///////////////////// PROGRAMA /////////////////////

int main(){
    int opcao;
    const int const_cliente=10, const_filme=10, const_contrato=10, max_assistir=30;
    int cont_assistir[10]={0}; // o quanto cada cliente assistiu
    int codigo_filme=1001;
    int excedente[10]={0}; //  quantos clientes excederam
    int mes=1;
    float devido[10];
    INFORMACOES informacoes[10];
    HISTORICO historico[const_cliente][max_assistir];
    CLIENTE cliente[const_cliente];
    FILME filme[const_filme];
    PLANO plano[10];
    CONTRATO contrato[const_contrato];
    int cont_cliente=0, cont_filme=0, cont_contrato=0;
    int verificador;

    do{
        printf("oizin");
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
                verificador=cadastro_filme(filme, &cont_filme, &codigo_filme);
                if (verificador==0){
                    printf("Filme cadastrado com sucesso\n");
                }
                if (verificador==1){
                    printf("ERRO: Numero maximo de filmes no sistema atingido\n");
                }
                break;
            }
            case 3:{
                cadastro_plano_basico(plano);
                break;
            }
            case 4:{
                cadastro_plano_premium(plano);
                break;
            }
            case 5:{
                verificador=cadastro_contrato(contrato, &cont_contrato, cont_cliente, cliente);
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
                verificador=carregar_filme(filme, cont_filme, cliente, cont_cliente, historico, cont_assistir, plano, contrato, excedente, mes);
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
                verificador=cancelar_contrato(contrato, cont_contrato, cliente, cont_cliente, mes, devido);
                break;
            }
            case 8:{
                verificador=gerar_fatura(contrato, cliente, cont_contrato, cont_cliente, mes, historico, excedente, cont_assistir, filme, devido);
                
                break;
            }
            case 9:{
                dados_cliente();
                break;
            }
            case 10:{
                historico_cliente();
                break;
            }
            case 11:{
                excederam_cota_mensal();
                break;
            }
            case 12:{
                frequencia_filme();
                break;
            }
            case 13:{
                recomendar_filme();
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

    if((*cont_cliente)==10){
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
        cliente[*cont_cliente].status==inativo;
        (*cont_cliente)++;
        return 0; 
    }  
}
int cadastro_filme(FILME* filme, int* cont_filme, int* codigo_filme){ 
    if((*cont_filme)==10){
        return 1;
    }
    else{
        scanf(" %[^\n]%*c", filme[*cont_filme].filme.nome);
        do{
            scanf(" %d", &filme[*cont_filme].genero);
            if (filme[*cont_filme].genero<0 || filme[*cont_filme].genero>5){
                printf("ERRO: Genero invalido\n");
            }
            else{
                do{
                    scanf(" %d", &filme[*cont_filme].classificacao);
                    if (filme[*cont_filme].classificacao<0 || filme[*cont_filme].classificacao>5){
                        printf("ERRO: Classificao invalida\n");
                    }
                    else{
                        filme[*cont_filme].filme.codigobusca=(*codigo_filme);
                        codigo_filme++;
                        (*cont_filme)++;
                        return 0;
                    }   
                } while (filme[*cont_filme].classificacao<0 || filme[*cont_filme].classificacao>5);
                
            }
        } while (filme[*cont_filme].genero<0 || filme[*cont_filme].genero>5); 
    }
}
void cadastro_plano_basico(PLANO* planobasico){
    scanf(" %d", &planobasico[0].plano.planobasico.quantidade);
    scanf(" %f", &planobasico[0].plano.planobasico.valor_base);
    scanf(" %f", &planobasico[0].plano.planobasico.valor_excedente);
    printf("Plano Basico cadastrado com sucesso\n");
}
void cadastro_plano_premium(PLANO* planopremium){
    scanf(" %f", &planopremium[1].plano.planopremium.valor_base);
    printf("Plano Premium cadastrado com sucesso\n");
}
int cadastro_contrato(CONTRATO* contrato, int* cont_contrato, int cont_cliente, CLIENTE* cliente){
    char cpf[50];
    int contador_cliente=0;
    int i;

    if (cont_cliente==0){
        return 4;
    }
    if ((*cont_contrato)==cont_cliente){
        return 3;
    }
    else{
        scanf(" %[^\n]%*c", cpf);
        for ( i=0; i<cont_cliente; i++){
            if (strcmp(cpf, cliente[i].cliente.cpf)==0){
                strcpy(contrato[*cont_contrato].cpf, cpf);
                contador_cliente=1; //prova que o cliente ta cadastrado
                break;
            }
        }
        if (contador_cliente==0){
            return 2;
        }
        if (contador_cliente==1){
            for (i=0; i<cont_cliente; i++){
                if (cliente[i].status==1){
                    return 1;
                }   
            }
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
            
            if (contrato[*cont_contrato].pagamento.pagamento==0){
                scanf(" %[^\n]%*c", contrato[*cont_contrato].pagamento.forma_pgto.debito.numero_agencia);
                scanf(" %[^\n]%*c") ; contrato[*cont_contrato].pagamento.forma_pgto.debito.numero_conta;
                do{
                    scanf(" %d", &contrato[*cont_contrato].dia_contrato);
                    if (contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31){
                        printf("ERRO: Dia invalido\n");
                    }
                    else{
                        break;
                    }
                }while(contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31);
                
                contrato[*cont_contrato].dia_cancelamento=0;
                contrato[*cont_contrato].mes_cancelamento=0;
                cont_contrato++;
                for (i=0; i<cont_cliente; i++){
                    if (strcmp(cpf, cliente[i].cliente.cpf)==0){
                        cliente[i].status=ativo;
                    }  
                }
                
                return 0;
                
            }
            if (contrato[*cont_contrato].pagamento.pagamento==1){
                scanf(" %[^\n]%*c",  contrato[*cont_contrato].pagamento.forma_pgto.credito.numero_cartao);
                do{
                    scanf(" %d", &contrato[*cont_contrato].dia_contrato);
                    if (contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31){
                        printf("ERRO: Dia invalido\n");
                    }
                    else{
                        break;
                    }
                }while(contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31); 
                contrato[*cont_contrato].dia_cancelamento=0;
                contrato[*cont_contrato].mes_cancelamento=0;
                cont_contrato++;
                for (i=0; i<cont_cliente; i++){
                    if (strcmp(cpf, cliente[i].cliente.cpf)==0){
                        cliente[i].status=ativo;
                    }  
                }
                return 0;      
            } 
        } 
    } 
}
int carregar_filme(FILME* filme, int cont_filme, CLIENTE* cliente, int cont_cliente, HISTORICO historico[][30], int* cont_assistir, PLANO* plano, CONTRATO* contrato, int* excedente, int mes){
    char cpf[50];
    int i, j, k, codigo_filme, dia, opcao, genero, classificacao, taxa;
    int verifica_cliente=0, verifica_ativo=0, verifica_filme=0;

    if(cont_cliente==0){
        return 3;
    }
    scanf(" %[^\n]%*c", cpf);
    for(i=0; i<cont_cliente; i++){
        if(strcmp(cpf, cliente[i].cliente.cpf)==0){
            verifica_cliente=1;
            if (cliente[i].status==ativo){
                verifica_ativo=1;
                if (cont_assistir[i]==30){
                    return 2;
                }
                
                do{
                    scanf(" %d", &dia);
                    if (dia<1 || dia>31){
                        printf("ERRO: Dia invalido\n");
                    }
                    else{
                        historico[i][cont_assistir[i]].dia=dia;
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
                        scanf(" %d", &genero);
                        if (genero<0 || genero>5){
                            printf("ERRO: Escolha invalida\n");
                        }
                        else{
                            break;
                        }
                    } while (1);
                    for ( j=0; j<cont_filme; j++){
                        if (genero==filme[j].genero){
                            printf("Codigo: %d\n", filme[j].filme.codigobusca); //ta printando lixo
                            printf("Nome: %s\n", filme[j].filme.nome);
                        } 
                    } 
                }
                if (opcao==1){
                    do{
                        scanf(" %d", &classificacao);
                        if (classificacao<0 || classificacao>5){
                            printf("ERRO: Escolha invalida\n");
                        }
                        else{
                            break;
                        }  
                    } while (1);
                    for ( j=0; j<cont_filme; j++){
                        if (classificacao==filme[j].classificacao){
                            printf("Codigo: %d\n", filme[j].filme.codigobusca); //ta printando lixo
                            printf("Nome: %s\n", filme[j].filme.nome);
                        }
                    }
                }  
                scanf(" %d", &codigo_filme);
                for(j=0; j<cont_filme; j++){
                    if (codigo_filme==filme[j].filme.codigobusca){
                        verifica_filme=1;
                        for ( k=0; k<cont_cliente; k++){    
                            if (strcmp(cliente[i].cliente.cpf,contrato[k].cpf)==0){
                                if (contrato[k].plano.opcao_plano==plano_basico){
                                    if (cont_assistir[i]>contrato[k].plano.plano.planobasico.quantidade){
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
                                            historico[i][cont_assistir[i]].codigo_filme=codigo_filme;
                                            historico[i][cont_assistir[i]].dia = dia;
                                            historico[i][cont_assistir[i]].mes = mes;
                                            excedente[i]++;
                                            cont_assistir[i]++;
                                            //cont_freqfilm[i][j]++;
                                            return 0;
                                        }                                                        
                                    }                                                    
                                }
                                if (contrato[k].plano.opcao_plano==plano_premium){
                                    historico[i][cont_assistir[i]].codigo_filme=codigo_filme;
                                    historico[i][cont_assistir[i]].dia = dia;
                                    historico[i][cont_assistir[i]].mes = mes;
                                    cont_assistir[i]++;
                                    //cont_freqfilm[i][j]++;
                                    return 0;
                                }   
                            }
                        }
                        break;
                    }   
                }
                if(verifica_filme==0){
                    return 1;  //RETURN
                }     
                
            }
        }
    }
    if(verifica_cliente==0){
        return 5;  //RETURN
    }
    if(verifica_ativo==0){
        return 6; //RETURN
    }
}
int cancelar_contrato(CONTRATO* contrato, int cont_contrato, CLIENTE* cliente, int cont_cliente, int mes, float* devido[10]){
    int i, dia;
    int contador_ativo=0, contador_cliente=0; 
    char cpf[50];

    if (cont_contrato==0){
        printf("ERRO: Nenhum contrato cadastrado no sistema\n");    //RETURN
    }
    scanf(" %[^\n]%*c", cpf);
    for (i=0; i<cont_contrato; i++){
        if (strcmp(cpf, cliente[i].cliente.cpf)==0){
            contador_cliente=1;
            if(cliente[i].status==ativo){
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
                if (dia>contrato[i].dia_contrato){
                    contrato[i].dia_cancelamento=dia;
                }
                else{
                    printf("ERRO: Data de cancelamente anteiror a data de contratacao\n");
                }
                // VERIFICA VALOR DEVIDO (FUNÇÃO 8)
                //printf("Valor devido: %.2f\n", devido[i]);
                contrato[i].dia_cancelamento=dia;
                contrato[i].mes_cancelamento=mes;
                cliente[i].status=inativo;
                printf("Cancelamento feito com sucesso\n"); //RETURN
            }
        }
        
    }
    if (contador_cliente==0){
        printf("ERRO: Cliente nao cadastrado\n");   //RETURN
    }
    if (contador_ativo==0){
        printf("ERRO: Cliente inativo\n");  //RETURN
    }
}
int gerar_fatura(CONTRATO* contrato, CLIENTE* cliente, int cont_contrato, int cont_cliente, int mes, HISTORICO historico[][30], int* excedente, int* cont_assistir, FILME* filme, float* devido[10]){
    int i, j, opcao;
    char cpf[50];
    int contador_cliente=0,  contador_contrato=0;

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
            printf("ERRO: Nenhum cliente cadastrado no sistema\n"); //RETURN
        }
        if (cont_contrato==0){
            printf("ERRO: Nenhum contrato cadastrado no sistema\n"); //RETURN
        }
        scanf(" %[^\n]%*c", cpf);
        for ( i=0; i<cont_cliente; i++){
            if (strcmp(cpf, cliente[i].cliente.cpf)==0){
                contador_cliente=1; //cliente existe
                if (cliente[i].status==ativo){
                    contador_contrato=1; //cliente tem contrato
                    if (filme[i].filme.codigobusca==historico[i][cont_assistir[i]].codigo_filme){ //?????????
                        printf("Nome: %s\n", filme[i].filme.nome); //nome do filme
                        printf("Data: %d/%d\n", historico[i][cont_assistir[i]].dia, historico[i][cont_assistir[i]].mes); //data do carregamento
                        if (contrato[i].plano.opcao_plano==0){   //basico
                            //devido[i]= contrato[i].plano.plano.planobasico.valor_base+(excedente[i]*contrato[i].plano.plano.planobasico.valor_excedente);
                            printf("Valor devido: %.2f\n", devido[i]);
                        }
                        if (contrato[i].plano.opcao_plano==1){
                            //devido[i]=contrato[i].plano.plano.planopremium.valor_base;
                            printf("Valor devido: %.2f\n", devido[i]);
                        }  
                    }  
                } 
            }  
        } 
    }
    if (opcao==1){
        for (i=0; i<cont_cliente; i++){
            printf("CPF: %s\n", contrato[i].cpf);
            //fazer um for, fazer um  if verificar se cpf do contrato é igual cpf do cliente
            printf("Nome: %s\n", cliente[i].cliente.nome); //nome do cliente
            printf("Valor devido: %.2f\n", devido);
            printf("Mes vigente apos a fatura: %d\n", mes);
            
        }
        
    }
    
    
}
void dados_cliente(){

}
void historico_cliente(){

}
void excederam_cota_mensal(){

}
void frequencia_filme(){

}
void recomendar_filme(){

}
