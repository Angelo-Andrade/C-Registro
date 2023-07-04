#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>

#define RED "\e[1;91m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[0;33m"
#define BLUE "\e[0;34m"
#define PURPLE "\e[0;35m"
#define WHITE "\e[0;37m"
#define CYAN "\e[0;36m"
#define RESET "\e[m"
#define WHITEB "\e[47m"

typedef struct{
    int pacote;
    char nome_Pacote[50];
    char data_Entrega[11];
    char nota_Fiscal[50];
    char funcionario_Recebimento[50];
    char situacao;
    char data_retirada[11];
    char funcionario_retirada[50];
    char nome_cliente[50];
    char cpf_cliente[50];
} Registro;

typedef struct {
    char cpf[12];
    char nome[100];
    char email[100];
    char usuario[20];
    char senha[20];
} Usuario;

Usuario user[100];
Registro cadastro[1000];
int num_pacotes, i=0, numUsuarios=0, encontrado;
FILE *file, *file2;

void pausa(){
    printf(GREEN"\nAperte enter para continuar: "RESET);

    do{
        getchar();
        
    }while(getchar() != '\n');
    
    system("cls");
}

void ler(){
    //setlocale(LC_ALL, "Portuguese");

    i=0;
    file = fopen("regcadastro.txt", "r");

    if(file==NULL){
        printf(RED"\n\tNao abriu o arquivo regcadastro!\n"RESET);
        num_pacotes=0;

    }else{
        while(fscanf(file, "%i;%49[^;];%49[^;];%49[^;];%49[^;];%c;%49[^;];%49[^;];%49[^;];%49[^\n]\n", &cadastro[i].pacote, cadastro[i].nome_Pacote, cadastro[i].data_Entrega, cadastro[i].nota_Fiscal, cadastro[i].funcionario_Recebimento, &cadastro[i].situacao, cadastro[i].data_retirada, cadastro[i].funcionario_retirada, cadastro[i].nome_cliente, cadastro[i].cpf_cliente)!=EOF){
            //printf("%i;%s;%s;%s;%s;%c;%s;%s;%s;%s\n", cadastro[i].pacote, cadastro[i].nome_Pacote, cadastro[i].data_Entrega, cadastro[i].nota_Fiscal, cadastro[i].funcionario_Recebimento, cadastro[i].situacao, cadastro[i].data_retirada, cadastro[i].funcionario_retirada, cadastro[i].nome_cliente, cadastro[i].cpf_cliente);
            num_pacotes=cadastro[i].pacote+1;
            i++;

        }

    }

    i=0;
    file2 = fopen("usuarios.txt", "r");

    if(file2 == NULL){
        printf(RED"\n\tNao abriu o arquivo usuarios!\n"RESET);
        numUsuarios=0;

    }else{
        while(fscanf(file2, "%i;%12[^;];%99[^;];%99[^;];%19[^;];%19[^\n]\n", &numUsuarios, user[i].cpf, user[i].nome, user[i].email, user[i].usuario, user[i].senha)!=EOF){
            //printf("%i;%s;%s;%s;%s;%s\n", numUsuarios, user[i].cpf, user[i].nome, user[i].email, user[i].usuario, user[i].senha);
            i++;

        }

    }
    fclose(file2);
    
    pausa();
}

void salvar(){
    setlocale(LC_ALL, "Portuguese");

    //operação de abrir o arquivo para append
    file = fopen("regcadastro.txt", "w");

    //verificando se a abertura do arquivo não ocorreu com sucesso
    if(file == NULL) {
        printf(RED"\n\tNao abriu o arquivo regcadastro!\n"RESET);
    }
    //arquivo foi aberto com sucesso
    else{
        for(i=0; i<num_pacotes; i++){
            if(cadastro[i].situacao=='P'){
                fprintf(file, "%i;%s;%s;%s;%s;%c\n", cadastro[i].pacote, cadastro[i].nome_Pacote, cadastro[i].data_Entrega, cadastro[i].nota_Fiscal, cadastro[i].funcionario_Recebimento, cadastro[i].situacao);
            }
            else if(cadastro[i].situacao=='R'){
                fprintf(file, "%i;%s;%s;%s;%s;%c;%s;%s;%s;%s\n", cadastro[i].pacote, cadastro[i].nome_Pacote, cadastro[i].data_Entrega, cadastro[i].nota_Fiscal, cadastro[i].funcionario_Recebimento, cadastro[i].situacao, cadastro[i].data_retirada, cadastro[i].funcionario_retirada, cadastro[i].nome_cliente, cadastro[i].cpf_cliente);
            }
        }
    }
    fclose(file);

    file2 = fopen("usuarios.txt", "w");

    //verificando se a abertura do arquivo não ocorreu com sucesso
    if(file2 == NULL) {
        printf(RED"\n\tNao abriu o arquivo usuarios!"RESET);
    }
    //arquivo foi aberto com sucesso
    else{
        for(i=0; i<numUsuarios; i++){
            fprintf(file2, "%i;%s;%s;%s;%s;%s\n", numUsuarios, user[i].cpf, user[i].nome, user[i].email, user[i].usuario, user[i].senha);
        }
    }
    fclose(file2);
    
}

int vCPF(const char cpf[12]){
    int j, digit1 = 0, digit2 = 0;

    // Verifica se a quantidade de caracteres = tamanho do CPF
    if (strlen(cpf) != 11) {    
        printf(RED "Quantidade inválida de dígitos do CPF! Digite novamente.\n" RESET);
        return 0;
    }

    // Verifica se todos os caracteres sao digitos
    for (i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            printf(RED "O CPF apresenta caracteres inválidos! Digite novamente.\n" RESET);
            return 0;
        }
    }

    // Verifica se todos os digitos sao iguais
    if (strcmp(cpf, "00000000000") == 0 || strcmp(cpf, "11111111111") == 0 ||
        strcmp(cpf, "22222222222") == 0 || strcmp(cpf, "33333333333") == 0 ||
        strcmp(cpf, "44444444444") == 0 || strcmp(cpf, "55555555555") == 0 ||
        strcmp(cpf, "66666666666") == 0 || strcmp(cpf, "77777777777") == 0 ||
        strcmp(cpf, "88888888888") == 0 || strcmp(cpf, "99999999999") == 0) {
        printf(RED "O CPF apresenta uma combinação inválida! Digite novamente.\n" RESET);
        return 0;
    }

    // Calculo do primeiro digito verificador
    for (i = 0, j = 10; i < 11 - 2; i++, j--) {
        digit1 += (cpf[i] - '0') * j;
    }
    digit1 = (digit1 % 11 < 2) ? 0 : 11 - (digit1 % 11);

    if ((cpf[9] - '0') != digit1) {
        printf(RED "O CPF apresenta uma combinação inválida! Digite novamente.\n" RESET);
        return 0;
    }

    // Calculo do segundo digito verificador
    for (i = 0, j = 11, digit2 = 0; i < 11 - 1; i++, j--) {
        digit2 += (cpf[i] - '0') * j;
    }
    digit2 = (digit2 % 11 < 2) ? 0 : 11 - (digit2 % 11);

    if ((cpf[10] - '0') != digit2) {
        printf(RED "O CPF apresenta uma combinação inválida! Digite novamente.\n" RESET);
        return 0;
    }

    for(i = 0; i<numUsuarios; i++){
        if(strcmp(user[numUsuarios].cpf, user[i].cpf) == 0){
            printf(RED "CPF já cadastrado!\n" RESET);
            return 0;
        }                    
    }

    return 1;
}

int vNomeUser(const char nome[100]) {
    int tamanho = strlen(nome);

    for (i = 0; i < tamanho; i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i])) {
            printf("O nome apresenta caracteres inválidos! Digite novamente.");
            return 0;
        }
    }
    for(i = 0; i<numUsuarios; i++){
        if(strcmp(user[numUsuarios].nome, user[i].nome) == 0){
            printf(RED "Nome já cadastrado!\n" RESET);
            return 0;
        }                    
    }
    
    return 1;
}

int vNomeCad(const char nome[100]) {
    int tamanho = strlen(nome);

    for (i = 0; i < tamanho; i++) {
        if (!isalpha(nome[i]) && !isspace(nome[i])) {
            printf("\nO nome apresenta caracteres inválidos! Digite novamente.\n");
            return 0;
        }
    }
    return 1;
}

bool vEmail(const char *email) {
    // Verificar se o e-mail contem um unico @
    int countAt = 0;
    const char *p = email;
    while (*p != '\0') {
        if (*p == '@') {
            countAt++;
        }
        p++;
    }
    if (countAt != 1) {
        printf(RED "Texto digitado é incompatível com o formato de um E-mail! Digite novamente.\n" RESET);
        return false;
    }

    // Verificar se o dominio do e-mail = valido
    const char *dominio = strstr(email, "@");
    if (dominio == NULL) {
        printf(RED "Texto digitado é incompatível com o formato de um E-mail! Digite novamente.\n" RESET);
        return false;
    }
    dominio++;  // Apontar para o primeiro caractere apos o @

    // Verificar se o dominio = "americanas.com.br"
    const char *dominioValido = "americanas.com.br";
    if (strcmp(dominio, dominioValido) != 0) {
        printf(RED "E-mail corporativo invalido! Digite novamente.\n" RESET);
        return false;
    }

    for(i = 0; i<numUsuarios; i++){
        if(strcmp(user[numUsuarios].email, user[i].email) == 0){
            printf(RED "Email já cadastrado!\n" RESET);
            return false;
        }                    
    }

    return true;
}

bool vUsuarioSenha(const char usuario[100], const char senha[100]) {
    // Verificar se o usuario e a senha tem comprimento valido
    size_t usuarioLen = strlen(usuario);
    size_t senhaLen = strlen(senha);
    if (usuarioLen != 6 || senhaLen < 4 || senhaLen > 6) {
        printf(RED "Usuário ou senha inválidos!\n" RESET);
        return false;
    }

    // Verificar se a senha contem pelo menos um caractere maiusculo, um caractere minusculo e um digito
    bool temMaiuscula = false;
    bool temMinuscula = false;
    bool temDigito = false;
    const char *p = senha;
    while (*p != '\0') {
        if (isupper(*p)) {
            temMaiuscula = true;
        } else if (islower(*p)) {
            temMinuscula = true;
        } else if (isdigit(*p)) {
            temDigito = true;
        }
        p++;
    }
    if (!temMaiuscula || !temMinuscula || !temDigito) {
        printf(RED "Usuário ou senha inválidos!\n" RESET);
        return false;
    }

    // Verificar se o usuario e a senha sao iguais
    if (strcmp(usuario, senha) == 0) {
        printf(RED "Usuário ou senha inválidos!\n" RESET);
        return false;
    }

    for(i = 0; i<numUsuarios; i++){
        if(strcmp(user[numUsuarios].usuario, user[i].usuario) == 0){
            printf(RED "Usuário já cadastrado!\n" RESET);
            return false;
        }                    
    }

    return true;
}

int vData(const char data[11]){
    int dia, mes, ano;
    if (strlen(data) != 10) {
        return 0;
    }

    if (sscanf(data, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        return 0;
    }

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano<2023) {
        return 0;
    }
    
    // Verificar anos bissextos
    int bissexto = ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0));
    int diasNoMes = 31;
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        diasNoMes = 30;
        } else if (mes == 2) {
        diasNoMes = bissexto ? 29 : 28;
        }

    if (dia > diasNoMes) {
        return 0;
    }

    // Se chegou ate aqui, a data = valida
    return 1;
}

int cadastrarUsuario() {
    printf("\nVoce esta efetuando o cadastro de um novo usuario.");
    int cpfValido=0, count=0;
    i=0;

    // CPF
    while (!cpfValido && count<3) {
        printf("\nDigite o CPF: ");
        scanf("%s", user[numUsuarios].cpf);
        
        cpfValido = vCPF(user[numUsuarios].cpf);
        count++;
        if(count==3){
            printf(RED"\n\tNúmero de tentativas excedidas!"RESET " Redirecionando para o menu...\n\n");
            return 0;

        }
    }
    count=0;

    // Nome
    int nomeValido = 0;
    while (!nomeValido && count<3) {
        printf("Digite o nome completo: ");
        scanf(" %99[^\n]", user[numUsuarios].nome);

        nomeValido = vNomeUser(user[numUsuarios].nome);
        count++;
        if(count==3){
            printf(RED"\n\tNúmero de tentativas excedidas!"RESET " Redirecionando para o menu...\n\n");
            return 0;
        }
    }
    count=0;

    // Email corporativo
    int emailValido=0;
    while(!emailValido && count<3){
        printf("Digite o Email corporativo: ");
        scanf("%s", user[numUsuarios].email);
    
        emailValido = vEmail(user[numUsuarios].email);
        count++;
        if(count==3){
            printf(RED"\n\tNúmero de tentativas excedidas!"RESET " Redirecionando para o menu...\n\n");
            return 0;
        }
    }
    count=0;

    // Usu�rio e senha
    bool vUsSen = false;
    while(!vUsSen && count<3){
        printf("Digite os seis digitos do seu Prontuario: ");
        scanf("%s", user[numUsuarios].usuario);

        printf("\t(A senha deve possuir pelo menos 4 caracteres e no máximo 6, sendo no mínimo uma maiúscula e um número) \nDigite a senha : ");
        scanf("%s", user[numUsuarios].senha);

        vUsSen = vUsuarioSenha(user[numUsuarios].usuario, user[numUsuarios].senha);
        count++;
        if(count==3){
            printf(RED"\n\tNúmero de tentativas excedidas!"RESET " Redirecionando para o menu...\n\n");
            return 0;
        }
    }
    count=0;

    numUsuarios++;
    printf(GREEN "Cadastro realizado com sucesso!\n" RESET);
    i++;

    pausa();
}

int realizarLogin() {
    char usuario[20];
    char senha[20];

    printf("\n\t--"RED"Login"RESET"--\n");
    printf("Usuario: ");
    scanf("%s", usuario);
    printf("Senha: ");
    scanf("%s", senha);

    for (i = 0; i < numUsuarios; i++){
        if (strcmp(usuario, user[i].usuario) == 0 && strcmp(senha, user[i].senha) == 0) {
            printf(GREEN"Login realizado com sucesso!\n"RESET);
            return 1;
        }
    }

    printf(RED "Usuario ou senha invalidos!\n" RESET);  
    return 0;
    
}

char convM(char letra){
    if (letra >= 'a' && letra <= 'z') {
        return letra - ('a' - 'A');
    }
    return letra;
}

void cadastrar(){
    setlocale(LC_ALL, "Portuguese");
    int valido=0, dia1, mes1, ano1, dia2, mes2, ano2;
    encontrado=0, i=0;

    do{
        printf(RED "\n-------------------------");
        printf("\nCadastro de Novo Pacote");
        printf("\n-------------------------\n" RESET);
        printf("\nDigite a Nota Fiscal do Pacote: ");
        scanf(" %49[^\n]", cadastro[num_pacotes].nota_Fiscal);   // indicacao de onde o registro sera armazenado.
        for (i = 0; cadastro[num_pacotes].nota_Fiscal[i] != '\0'; i++) {
            if (!isdigit(cadastro[num_pacotes].nota_Fiscal[i])){
                printf(RED "Nota fiscal invalida!\n" RESET);
                encontrado++;
                break;
            }
            else{
                encontrado=0;
            }
        }
        
        for(i = 0; i<num_pacotes; i++){
            if(strcmp(cadastro[num_pacotes].nota_Fiscal, cadastro[i].nota_Fiscal) == 0){
                printf(RED "Nota fiscal ja cadastrada!\n" RESET);
                encontrado++;
                break;
            }
            else{
                encontrado=0;
            }
        }
    

        if(encontrado==3){
            system("cls");
            printf(RED"\nVoce excedeu o número de tentativas para preencher este campo." RESET);
            printf(GREEN "\nO sistema voltou para o inicio.\n" RESET);
            return 0;
        }
    }while(encontrado!=0);
    
    int vNome, count=0;
    do{
        printf("Nome presente no pacote: ");
        scanf(" %49[^\n]", cadastro[num_pacotes].nome_Pacote);   // indicacao de onde o registro sera armazenado.
        vNome = vNomeCad(cadastro[num_pacotes].nome_Pacote);
        count++;
        if(count==3){
            system("cls");
            printf(RED"\nVoce excedeu o número de tentativas para preencher este campo." RESET);
            printf(GREEN "\nO sistema voltou para o inicio.\n" RESET);
            return 0;
        }
    }while(!vNome && count<3);

    do{
        printf("Digite a data de entrega (dd/mm/aaaa): ");
        scanf(" %49[^\n]", cadastro[num_pacotes].data_Entrega);  // indicacao de onde o registro sera armazenado.
        if(vData(cadastro[num_pacotes].data_Entrega)==0){
            printf(RED "Data invalida!" RESET);
            encontrado++;
        }
        else{
            encontrado=0;
        }
        if(encontrado==3){
            system("cls");
            printf(RED "\nVoce excedeu o número de tentativas para preencher este campo." RESET);
            printf(GREEN "\nO sistema voltou para o inicio.\n" RESET);
            return 0;
        }
    }while(encontrado!=0);

    vNome=0, count=0;
    do{
        printf("Digite o nome do funcionario que recebeu a mercadoria: ");
        scanf(" %49[^\n]", cadastro[num_pacotes].funcionario_Recebimento);
        
        vNome=vNomeCad(cadastro[num_pacotes].funcionario_Recebimento);
    
    }while(!vNome && count<3);

    do{
        printf("\n-------------------------");
        printf(YELLOW "\nP - Pacote Presente" RESET);
        printf(PURPLE "\nR - Pacote Retirado" RESET);
        printf("\nDigite a situacao atual do pacote: ");
        scanf(" %c", &cadastro[num_pacotes].situacao);
        cadastro[num_pacotes].situacao = convM(cadastro[num_pacotes].situacao);
        if(cadastro[num_pacotes].situacao!='P' && cadastro[num_pacotes].situacao!='R'){
            printf(RED "\nCaracter invalido!" RESET);
            encontrado++;
        }
        if(encontrado==3){
            system("cls");
            printf(RED "\nVoce excedeu o numero de tentativas para preencher um determinado campo." RESET);
            printf(BLUE "\nO sistema voltou para o inicio.\n" RESET);
            return 0;
        }
    }while(encontrado!=0);

    if(cadastro[num_pacotes].situacao=='R'){
        time_t t = time(NULL);
        struct tm* tm_info = localtime(&t);
        printf(BLUE "\n-------------------------");
        printf("\nRetirada de Pacote");
        printf("\n-------------------------\n" RESET);
        strftime(cadastro[num_pacotes].data_retirada, sizeof(cadastro[num_pacotes].data_retirada), "%d/%m/%Y", tm_info);
        printf("\nFuncionario Responsavel pela Retirada: ");
        scanf(" %49[^\n]", cadastro[num_pacotes].funcionario_retirada);
        printf("\nNome do solicitante: ");
        scanf(" %49[^\n]", cadastro[num_pacotes].nome_cliente);

        while(!valido){
            printf("\nCPF do Cliente (apenas numeros): ");
            scanf(" %49[^\n]", cadastro[num_pacotes].cpf_cliente);

            valido = vCPF(cadastro[num_pacotes].cpf_cliente);

            if(!valido){
                printf("\nCPF invalido! Digite novamente.\n");
                encontrado++;
            }
            else{
                encontrado=0;
            }
            if(encontrado==3){
                system("cls");
                printf("\nVoce excedeu o numero de tentativas para preencher um determinado campo.");
                printf("\nO sistema voltou para o inicio.\n");
                return 0;
            }
        }
        printf(GREEN"\nCPF valido!"RESET);

        do{
            printf("\nData da Retirada: ");
            scanf(" %49[^\n]", cadastro[num_pacotes].data_retirada);

            sscanf(cadastro[num_pacotes].data_retirada, "%d/%d/%d", &dia1, &mes1, &ano1);
            sscanf(cadastro[num_pacotes].data_Entrega, "%d/%d/%d" , &dia2, &mes2, &ano2);        

            if(vData(cadastro[num_pacotes].data_retirada)==0){
                printf("Data invalida!");
                encontrado++;
            }
            else{
                encontrado=0;
            }

            if(ano1>=ano2){
                encontrado=0;
            }
            else{
                if(mes1>=mes2){
                    encontrado=0;
                }
                else {
                    if(dia1>=dia2){
                        encontrado=0;
                    }
                    else{
                        printf("Data invalida!");
                        encontrado++;
                    }
                
                }
            }
            
            if(encontrado==3){
                system("cls");
                printf("\nVoce excedeu o numero de tentativas para preencher um determinado campo.");
                printf("\nO sistema voltou para o inicio.\n");
                return 0;
            }

            }while(encontrado!=0);

    }

    cadastro[num_pacotes].pacote=num_pacotes;
    num_pacotes++;   //acrescenta um pacote cadastrado no total
    printf(GREEN "\nCadastro realizado com sucesso!\n\n" RESET);
    pausa();
}

void consulta1pac(){
    
    setlocale(LC_ALL, "Portuguese");

    encontrado=0;
    char notafiscal_cliente[20];    //variavel para verificar a NF desejada

    do{
        printf(GREEN "\n-------------------------");
        printf("\nConsulta de Pacotes");
        printf("\n-------------------------\n" RESET);
        printf("\nDigite o numero da Nota Fiscal referente ao pacote: ");
        scanf(" %49[^\n]", notafiscal_cliente);
            for (i = 0; notafiscal_cliente[i] != '\0'; i++) {
                if (!isdigit(notafiscal_cliente[i])){
                    printf("\nNota fiscal invalida!\n\n");
                    encontrado++;
                }
                else{
                    encontrado=0;
                }
            }
            if(encontrado==3){
                system("cls");
                printf("\nVoce excedeu o numero de tentativas para preencher um determinado campo.");
                printf("\nO sistema voltou para o inicio.\n");
                return 0;
            }
    }while(encontrado!=0);

    for (int i = 0; i < num_pacotes; i++){   //loop para nao ler quando nao ha pacotes cadastrados
        if (strcmp(cadastro[i].nota_Fiscal, notafiscal_cliente) == 0){   //criterio para combinar a NF desejada com a do pacote cadastrado
            printf("\n----Pacote %i----", cadastro[i].pacote);
            printf("\nDestinatario: %s", cadastro[i].nome_Pacote);
            printf("\nData de Recebimento: %s", cadastro[i].data_Entrega);
            printf("\nNota Fiscal: %s", cadastro[i].nota_Fiscal);
            printf("\nRecebido por: %s", cadastro[i].funcionario_Recebimento);
            printf("\nSituacao do pacote %c", cadastro[i].situacao );
            if (strcmp(cadastro[i].data_retirada, "") != 0){    //Ele busca identificar se o cadastro foi solicitado para retirada. Se sim, ele adiciona as proximas linhas ao printf. Define tambem a ordem de indicacao das informacoes.
                printf("\nData de Retirada: %s", cadastro[i].data_retirada);
                printf("\nResponsavel pela Retirada: %s", cadastro[i].funcionario_retirada);
                printf("\nNome do Cliente que retirou o pedido: %s", cadastro[i].nome_cliente);
                printf("\nCPF do Cliente: %s", cadastro[i].cpf_cliente);
            }
            printf("\n-------------------------\n");
            encontrado=1;
        }
    }
    if(encontrado==0){
        printf("\nPacote nao cadastrado.\n");
    }
    printf("\n\n");
    pausa();
}

void listarRetirados(){
    encontrado=0;
    printf("\n\t-------Lista de pacotes Retirados-------\n");
    for (int i = 0; i < num_pacotes; i++)
    {
        cadastro[i].situacao = convM(cadastro[i].situacao);
        if (cadastro[i].situacao=='R')
        {
            printf("\n----Pacote %i----", cadastro[i].pacote);
            printf("\nDestinatario: %s", cadastro[i].nome_Pacote);
            printf("\nData de Recebimento: %s", cadastro[i].data_Entrega);
            printf("\nNota Fiscal: %s", cadastro[i].nota_Fiscal);
            printf("\nRecebido por: %s", cadastro[i].funcionario_Recebimento);
            printf("\nSituacao do pacote %c", cadastro[i].situacao );
            printf("\nData de Retirada: %s", cadastro[i].data_retirada);
            printf("\nFuncionario Responsavel pela Retirada: %s", cadastro[i].funcionario_retirada);
            printf("\nCliente que solicitou a retirada: %s", cadastro[i].nome_cliente); // Linha adiciona
            printf("\nCPF do Cliente: %s", cadastro[i].cpf_cliente);
            printf("\n-------------------------------------------------------\n");
            encontrado++;
        }
    }
    if(encontrado==0){
        printf(RED"\nNenhum pacote Retirado registrado no momento!\n"RESET);
    }
    pausa();
}

void listarPresentes(){
    encontrado=0;
    printf("\n\t-------Lista de pacotes Retirados-------\n");
    for (int i = 0; i < num_pacotes; i++)
    {
        cadastro[i].situacao = convM(cadastro[i].situacao);
        if (cadastro[i].situacao=='P')
        {
            printf("\n----Pacote %i----", cadastro[i].pacote);
            printf("\nDestinatario: %s", cadastro[i].nome_Pacote);
            printf("\nData de Recebimento: %s", cadastro[i].data_Entrega);
            printf("\nNota Fiscal: %s", cadastro[i].nota_Fiscal);
            printf("\nRecebido por: %s", cadastro[i].funcionario_Recebimento);
            printf("\nSituacao do pacote %c", cadastro[i].situacao );
            printf("\n-------------------------------------------------------\n");
            encontrado++;
        }
    }
    if(encontrado==0){
        printf(RED"\nNenhum pacote Presente registrado no momento!\n"RESET);
    }

    pausa();
}

void listar(){
    setlocale(LC_ALL, "Portuguese");

    int max=2, ini=0, pgnum=0, pagina=1, resini=1, resmax=0, maxpaginas=0;
    char pgat;

    maxpaginas = (num_pacotes/3);   //define o maximo de paginas
    if(num_pacotes%3!=0){
        maxpaginas++;
    }

    if(num_pacotes<=0){
        printf(RED"Nao existem pacostes registrados no sistema!" RESET);
        printf(CYAN "\nFaca o cadastro dos pacotes antes de consultar a lista, ou entao de pesquisar algum pacote em especifico \n" RESET);
    }

    //inicio
    while(pagina<=maxpaginas){     //Loop para sempre imprimir a lista e as opcoes
        printf(YELLOW "\n-------------------------");
        printf("\nLista de Pacotes");
        printf("\n-------------------------\n" RESET);
        if((num_pacotes%3)==0||((num_pacotes%3)!=0 && pagina!=maxpaginas)){     //Criterio para nao imprimir quando for a pagina que nao tem 3 pacotes
            for(i=ini; i<=max; i++){    //ini refere-se ao pacote inicial da pagina e max o ultimo pacote da mesma
                printf(YELLOW "\n----Pacote %i----", cadastro[i].pacote);
                printf("\nDestinatario: %s", cadastro[i].nome_Pacote);
                printf("\nData de Recebimento: %s", cadastro[i].data_Entrega);
                printf("\nNota Fiscal: %s", cadastro[i].nota_Fiscal);
                printf("\nRecebido por: %s" RESET, cadastro[i].funcionario_Recebimento);
                printf("\nSituacao do pacote %c", cadastro[i].situacao );
                if (strcmp(cadastro[i].data_retirada, "") != 0) { // Comparacao de Strings - Se identificado que em outra string foi feita a retirada do pedido, ele adiciona as linhas seguintes
                    printf(BLUE "\nData de Retirada: %s", cadastro[i].data_retirada);
                    printf("\nFuncionario Responsavel pela Retirada: %s", cadastro[i].funcionario_retirada);
                    printf("\nCliente que solicitou a retirada: %s", cadastro[i].nome_cliente); // Linha adiciona
                    printf("\nCPF do Cliente: %s" RESET, cadastro[i].cpf_cliente);
                }
                printf(YELLOW "\n-------------------------" RESET);
            }
        }
        if((num_pacotes%3)!=0 && pagina==maxpaginas){   //importante ressaltar que a variavel "maxpaginas" pode tanto se referir ao total de paginas, quanto ao numero da ultima pagina
            resini = num_pacotes-(num_pacotes%3);     //define o pacote inicial na pagina que nao imprime tres pacotes
            resmax = num_pacotes;   //define o maximo de pacotes na pagina que nao imprime tres pacotes
            for(i=resini; i<resmax; i++){      //resini refere-se ao pacote inicial da pagina e resmax o ultimo pacote da mesma
                printf(YELLOW "\n----Pacote %i----", cadastro[i].pacote);
                printf("\nDestinatario: %s", cadastro[i].nome_Pacote);
                printf("\nData de Recebimento: %s", cadastro[i].data_Entrega);
                printf("\nNota Fiscal: %s", cadastro[i].nota_Fiscal);
                printf("\nRecebido por: %s" RESET, cadastro[i].funcionario_Recebimento);
                printf("\nSituacao do pacote %c", cadastro[i].situacao );
                if (strcmp(cadastro[i].data_retirada, "") != 0) { // Comparacao de Strings - Se identificado que em outra string foi feita a retirada do pedido, ele adiciona as linhas seguintes
                    printf(BLUE "\nData de Retirada: %s", cadastro[i].data_retirada);
                    printf("\nFuncionario Responsavel pela Retirada: %s", cadastro[i].funcionario_retirada);
                    printf("\nCliente que solicitou a retirada: %s", cadastro[i].nome_cliente); // Linha adiciona
                    printf("\nCPF do Cliente: %s" RESET, cadastro[i].cpf_cliente);
                }
                printf(YELLOW "\n-------------------------" RESET);
            }
        }

        if(ini==0 && maxpaginas>1){     //Sempre que ini for igual o pacote inicial e impresso que nao e possivel retroceder
            printf("\n-->\n");
            printf(" %i\n", pagina+1);      //mostra a pagina seguinte
            printf("Atual: %i\n", pagina);  //mostra a pagina atual


        }else if(ini!=0 && pagina!=maxpaginas){      //Sempre que ini for diferente do primeiro pacote e nao for a ultima pagina e impresso que e possivel avancar e retroceder
            printf("\n <-- / -->\n");
            printf("%i   /   %i\n", pagina-1, pagina+1);    //mostra as pagina anterior e a seguinte respectivamente
            printf("Atual: %i\n", pagina);      //mostra a pagina atual


        }else if(pagina==maxpaginas){     //sempre que for a ultima pagina e impresso que nao e possivel avancar
            if(pagina>1){
                printf("\n<--\n");
                printf(" %i\n", pagina-1);      //mostra a pagina anterior
                printf("Atual: %i\n", pagina);  //mostra a pagina atual
            }else{
                printf(BLUE "\nSó existe uma página. Não é possível avançar nem retroceder!\n" RESET);

            }
        }else{
            system("cls");      //comando para limpar a tela
            printf(RED "Página inválida!\n" RESET);
            printf( "Por favor, digite uma página válida: ");
            goto paginaN;       //retorna para o ponto onde o "titulo" foi inserido
        }
        printf("\n-------------------------");
        printf(YELLOW "\nA - Avançar" RESET);
        printf(CYAN "\nR - Retroceder" RESET);
        printf(PURPLE "\nN - Pagina Especifica" RESET);
        printf(YELLOW "\nM - MENU" RESET);
        printf(CYAN "\nP - Pesquisar Pacote" RESET);
        printf(PURPLE "\nC - Cadastrar Pacote" RESET);
        printf("\n-------------------------\n");
        printf("Digite o caracter de acordo com a funcao que deseja: ");
        scanf(" %c", &pgat);    //variavel utilizada no switch
        pgat = convM(pgat);

        switch(pgat){
            case 'A':
                pagina++;   //avanca uma pagina
                ini+=3;     //aumenta o pacote inicial em tres
                max+=3;     //aumenta o maximo de pacotes na pagina em tres
                system("cls");

                if(pagina>maxpaginas){     //if para impedir que o while seja interrompido
                    printf(RED "\nNão é possível avançar!\n\n" RESET);
                    max=2, ini=0;
                    pagina=1;
                }
                break;  //termina o switch

            case 'R':
                pagina--;   //retrocede uma pagina
                ini-=3;     //diminui o pacote inicial em tres
                max-=3;     //diminui o maximo de pacotes em tres
                system("cls");

                if(pagina<=0){     //if para impedir que o while seja interrompido
                    printf(RED "\nNão é possível retroceder!\n\n" RESET);
                    max=2, ini=0;
                    pagina=1;
                }
                break;  //termina o switch

            case 'N':
                paginaN:    //Esse "titulo" funciona como um chekpoint
                scanf("%i", &pgnum);    //leitura da pagina que o usuario que ir

                if(pgnum<=maxpaginas && pgnum>0){      //criterio para que nao seja uma pagina invalida
                    pagina = pgnum;     //"pagina" e a variavel utilizada para imprimir a pagina atual, a seguinte e a anterior. Nesta linha, a pagina atual e definida de acordo com a pagina lida pelo programa
                    ini=pgnum-1;    //define o pacote inicial da pagina de acordo com o maximo de pacotes por pagina
                    max=ini+2;    //define o maximo de pacotes com base na pagina escolhida
                    system("cls");
                }
                else{
                    printf(RED "Pagina invalida!\n" RESET);
                    printf(YELLOW "Por favor, digite uma pagina valida: " RESET);
                    goto paginaN;   //retorna para o ponto onde o titulo foi inserido
                }

                break;  //termina o switch

            case 'M':   //funcao menu
                pagina+=10;
                system("cls");
                printf(GREEN"Redirecionando para o menu..."RESET);
                pausa();
                break;

            case 'P':   //funcao pesquisar pacote
                pagina+=10;
                system("cls");
                printf(GREEN"Redirecionando para o consultar pacote..."RESET);
                pausa();
                consulta1pac();
                break;

            case 'C':
                pagina+=10;
                system("cls");
                printf(GREEN"Redirecionando para o cadastrar pacote..."RESET);
                pausa();
                cadastrar();
                break;
        }
    }
}

void retirar(){
    char nome[50];
    int jretirados=0, numero, valido=0, dia1, mes1, ano1, dia2, mes2, ano2;    // Variavel para contar o numero de cadastros encontrado com o mesmo nome e variavel para escolher o pacote para alteracao
    encontrado = 0;
    printf(BLUE "\n-------------------------");
    printf("\n Retirada de Pacote");
    printf("\n-------------------------\n" RESET);
    printf("Digite o nome do pacote para retirada do pedido: ");
    scanf(" %49[^\n]", nome);

    for (int i=0; i<num_pacotes; i++) {
        if (strcmp(cadastro[i].nome_Pacote, nome) == 0 && cadastro[i].situacao=='P') {
            printf("----Pacote %i----", cadastro[i].pacote);
            printf("\nDestinatario: %s",cadastro[i].nome_Pacote);
            printf("\nData de Recebimento: %s",cadastro[i].data_Entrega);
            printf("\nNota Fiscal: %s",cadastro[i].nota_Fiscal);
            printf("\nRecebido por: %s",cadastro[i].funcionario_Recebimento);
            printf("\n-------------------------\n\n");
            encontrado++;
        }
        else if(strcmp(cadastro[i].nome_Pacote, nome) == 0 && cadastro[i].situacao=='R'){
            jretirados++;
        }
    }

    if(jretirados==1){
        printf(RED "%i pacote encontrado que ja foi retirado!" RESET, jretirados);
    }
    else if(jretirados>1){
        printf(RED "%i pacotes encontrados que ja foram retirados!" RESET, jretirados);
    }

    if(encontrado==0 && jretirados==0) {
        printf(RED "Cadastro nao encontrado.\n" RESET);
    }
    else if(encontrado==1){
        printf(BLUE "\nFoi encontrado %d cadastro com o nome '%s' que ainda nao foi retirado.\n" RESET, encontrado, nome); // Listar os cadastros com o mesmo nome encontrado
        printf("Digite o numero do pacote que deseja retirar: ");
        scanf("%d", &numero);
    }
    else if(encontrado>1){
        printf(BLUE "\nForam encontrados %d cadastros com o nome '%s' que ainda nao foram retirados.\n" RESET, encontrado, nome); // Listar os cadastros com o mesmo nome encontrado
        printf("Digite o numero do pacote que deseja retirar: ");
        scanf("%d", &numero);
    }

    if (numero==cadastro[numero].pacote) {
        time_t t = time(NULL);
        struct tm* tm_info = localtime(&t);

        strftime(cadastro[numero].data_retirada, sizeof(cadastro[numero].data_retirada), "%d/%m/%Y", tm_info);
        printf("\nFuncionario Responsavel pela Retirada: ");
        scanf(" %49[^\n]", cadastro[numero].funcionario_retirada);
        printf("\nNome do solicitante: ");
        scanf(" %49[^\n]", cadastro[numero].nome_cliente);

        while(!valido){
            printf("\nCPF do Cliente (apenas numeros): ");
            scanf(" %49[^\n]", cadastro[numero].cpf_cliente);

            valido = vCPF(cadastro[numero].cpf_cliente);

            if(!valido){
                printf("\nCPF invalido! Digite novamente.\n");
                encontrado++;
            }
            else{
                encontrado=0;
            }
            if(encontrado==3){
                system("cls");
                printf(RED "\nVoce excedeu o numero de tentativas para preencher um determinado campo." RESET);
                printf(BLUE "\nO sistema voltou para o inicio.\n" BLUE);
                return 0;
            }
        }
        printf(GREEN "\nCPF valido!" RESET);

        do{
            printf("\nData da Retirada: ");
            scanf(" %49[^\n]", cadastro[numero].data_retirada);

            sscanf(cadastro[numero].data_retirada, "%d/%d/%d", &dia1, &mes1, &ano1);
            sscanf(cadastro[numero].data_Entrega, "%d/%d/%d" , &dia2, &mes2, &ano2);


            if(vData(cadastro[numero].data_retirada)==0){
                printf("Data invalida!");
                encontrado++;
            }
            else{
                encontrado=0;
            }

            if(ano1>=ano2){
                encontrado=0;
            }
            else{
                if(mes1>=mes2){
                    encontrado=0;
                }
                else {
                    if(dia1>=dia2){
                        encontrado=0;
                    }
                    else{
                        printf("Data invalida!");
                        encontrado++;
                    }
                
                }
            }
            
            

            if(encontrado==3){
                system("cls");
                printf(RED "\nVoce excedeu o numero de tentativas para preencher um determinado campo." RESET);
                printf(BLUE "\nO sistema voltou para o inicio.\n" RESET);
                return 0;
            }

            }while(encontrado!=0);

        cadastro[numero].situacao='R';
        printf(GREEN "\n\nRetirada efetuada com sucesso!\n" RESET);

        pausa();
    }   
}

int menuR(){
    setlocale(LC_ALL, "Portuguese");
    
    int operacao=0;
    system ("color 00");
    while(operacao!=7){
        printf(WHITE "\n\t--" RESET RED "MENU" RESET WHITE "--\n" RESET);
        printf(RED "1 -"RESET WHITE " Cadastrar Pacotes\n" RESET);
        printf(RED "2 -"RESET WHITE " Consultar Pacotes\n" RESET);
        printf(RED "3 -"RESET WHITE " Lista de Pacotes Retirados\n" RESET);
        printf(RED "4 -"RESET WHITE " Lista de Pacotes Presentes\n" RESET);            
        printf(RED "5 -"RESET WHITE " Listar Todos os Pacotes\n" RESET);
        printf(RED "6 -"RESET WHITE " Retirar Pacotes\n" RESET);
        printf(RED "7 -"RESET WHITE " Sair\n" RESET);
        printf("Digite o numero referente a operacao que deseja: ");
        scanf("%i", &operacao);

        switch (operacao){
            case 1:
                system("cls");
                cadastrar();
                break;
            case 2:
                system("cls");
                consulta1pac();
                break;
            case 3:
                system("cls");
                listarRetirados();
                break;            
            case 4:
                system("cls");
                listarPresentes();
                break;
            case 5:
                system("cls");
                listar();
                break;
            case 6:
                system("cls");
                retirar();
                break;
                case 7:
                system("cls");
                printf("\n\tVoltando para a tela inicial...");
                break;
            default:
                printf("Opcao invalida!");
                break;
        }
    }
    return 0;
}

int main(){
    setlocale(LC_ALL, "Portuguese");
    system("color 00");

    ler();
    system("cls");

    int opcao;

    do {
        printf(WHITE"\t--"RESET RED"Tela Inicial"RESET WHITE"--\n"RESET );
        printf(RED"1."RESET WHITE" Cadastro\n"RESET);
        printf(RED"2."RESET WHITE" Login\n"RESET);
        printf(RED"3."RESET WHITE" Sair\n"RESET);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        

        switch (opcao){
            case 1:
                system("cls");
                cadastrarUsuario();
                break;
            case 2:
                if (realizarLogin()==1){
                    menuR();  
                    system("cls");
                    break;
                }
                break;
            case 3:
                printf("\n\tSaindo...\n");
                salvar();
                break;
            default:
                printf(RED"Opcao invalida!\n"RESET);
                break;
        }
    } while (opcao != 3);

    return 0;

}
