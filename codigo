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
    char codigo_filme[50];
    int dia;
    int mes;
}HISTORICO;     // 10 clientes X 30 filmes cada

///////////////////// SUBROTINAS /////////////////////
int cadastro_cliente(CLIENTE* cliente, int* cont_cliente);
int cadastro_filme(FILME* filme, int* cont_filme);
void cadastro_plano_basico(PLANO planobasico);
void cadastro_plano_premium(PLANO planopremium);
int cadastro_contrato(CONTRATO* contrato, int* cont_contrato, int cont_cliente, CLIENTE* cliente);
void carregar_filme();
void cancelar_contrato();
void gerar_fatura();
void dados_cliente();
void historico_cliente();
void excederam_cota_mensal();
void frequencia_filme();
void recomendar_filme();

///////////////////// PROGRAMA /////////////////////

int main(){
    int opcao;
    CLIENTE cliente[10];
    FILME filme[10];
    HISTORICO historico[10][30];
    PLANO plano;
    CONTRATO contrato[10];
    int cont_cliente=0, cont_filme=0, cont_contrato=0;
    int verificador;

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
                verificador=cadastro_filme(filme, &cont_filme);
                if (verificador==0){
                    printf("Filme cadastrado com sucesso\n");
                }
                if (verificador==1){
                    printf("ERRO: Classificao invalida\n");
                }
                if (verificador==2){
                    printf("ERRO: Genero invalido\n");
                }
                if (verificador==3){
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
                    printf("ERRO: Dia invalido\n");
                }
                if (verificador==2){
                    printf("ERRO: Tipo de pagamento invalido\n");
                }
                if (verificador==3){
                    printf("ERRO: Tipo de plano invalido\n");
                }
                if (verificador==4){
                    printf("ERRO: Cliente com contrato existente\n");
                }
                if (verificador==5){
                    printf("ERRO: Cliente nao cadastrado\n");
                }
                if (verificador==6){
                    printf("ERRO: Numero maximo de contratos no sistema atingido\n");
                }
                if (verificador==7){
                    printf("ERRO: Nenhum cliente cadastrado no sistema\n");
                }
                
                break;
            }
            case 6:{
                carregar_filme();
                break;
            }
            case 7:{
                cancelar_contrato();
                break;
            }
            case 8:{
                gerar_fatura();
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
        cliente[*cont_cliente].status==2;
        (*cont_cliente)++;
        return 0; 
    }  
}
int cadastro_filme(FILME* filme, int* cont_filme){
    if((*cont_filme)==10){
        return 3;
    }
    else{
        scanf(" %d", &filme[*cont_filme].filme.codigobusca);
        scanf(" %[^\n]%*c", filme[*cont_filme].filme.nome);
        scanf(" %d", &filme[*cont_filme].genero);
        if (filme[*cont_filme].genero<0 || filme[*cont_filme].genero>5){
            return 2;
        }
        else{
            scanf(" %d", &filme[*cont_filme].classificacao);
            if (filme[*cont_filme].classificacao<0 || filme[*cont_filme].classificacao>5){
                return 1;
            }
            else{
                (*cont_filme)++;
                return 0;
            }   
        }
    }
}
void cadastro_plano_basico(PLANO planobasico){
    scanf(" %d", &planobasico.plano.planobasico.quantidade);
    scanf(" %f", &planobasico.plano.planobasico.valor_base);
    scanf(" %f", &planobasico.plano.planobasico.valor_excedente);
    printf("Plano Basico cadastrado com sucesso\n");
}
void cadastro_plano_premium(PLANO planopremium){
    scanf(" %f", &planopremium.plano.planopremium.valor_base);
    printf("Plano Premium cadastrado com sucesso\n");
}
int cadastro_contrato(CONTRATO* contrato, int* cont_contrato, int cont_cliente, CLIENTE* cliente){
    char cpf[50];
    int contador_cliente=0, contador_contrato=0;
    int i;

    if (cont_cliente==0){
        return 7;
    }
    if ((*cont_contrato)==cont_cliente){
        return 6;
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
            return 5;
        }
        if (contador_cliente==1){
            for (i=0; i<cont_cliente; i++){
                if (cliente[i].status==1){
                    return 4;
                }   
            }
            scanf(" %d", &contrato[*cont_contrato].plano.opcao_plano);
            if(contrato[*cont_contrato].plano.opcao_plano<0 || contrato[*cont_contrato].plano.opcao_plano>1){
                return 3;
            }
            else{
                scanf(" %d", &contrato[*cont_contrato].pagamento.pagamento);
                if (contrato[*cont_contrato].pagamento.pagamento<0 || contrato[*cont_contrato].pagamento.pagamento>1){
                    return 2;
                }
                else{
                    if (contrato[*cont_contrato].pagamento.pagamento==0){
                        scanf(" %[^\n]%*c", contrato[*cont_contrato].pagamento.forma_pgto.debito.numero_agencia);
                        scanf(" %[^\n]%*c") ; contrato[*cont_contrato].pagamento.forma_pgto.debito.numero_conta;
                        scanf(" %d", &contrato[*cont_contrato].dia_contrato);
                            if (contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31){
                                return 1;
                            }
                            else{
                                contrato[*cont_contrato].dia_cancelamento==0;
                                contrato[*cont_contrato].mes_cancelamento==0;
                                cont_contrato++;
                                return 0;
                            }
                    }
                    if (contrato[*cont_contrato].pagamento.pagamento==1){
                        scanf(" %[^\n]%*c",  contrato[*cont_contrato].pagamento.forma_pgto.credito.numero_cartao);
                        scanf(" %d", &contrato[*cont_contrato].dia_contrato);
                            if (contrato[*cont_contrato].dia_contrato<1 || contrato[*cont_contrato].dia_contrato >31){
                                return 1;
                            }
                            else{
                                contrato[*cont_contrato].dia_cancelamento==0;
                                contrato[*cont_contrato].mes_cancelamento==0;
                                cont_contrato++;
                                return 0;
                            }
                    } 
                }
            } 
        } 
    } 
}
void carregar_filme(){

}
void cancelar_contrato(){

}
void gerar_fatura(){

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
