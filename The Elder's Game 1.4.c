#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#define TAMANHO 50
#define ENTER 13
#define ESC 27

//FUNÇÕES GLOBAIS
void TelaInicial(void);
void TelaRegistro(void);
void TelaEscolhaDificuldade(void);
void TelaLogin(void);
void MenuPrincipal(void);
void TelaMenuLogin(void);
void TelaCadastro(void);
void TelaComoJogar(void);
void TelaJogoFacil(void);
void TelaJogoMedio(void);
void TelaJogoDificil(void);
void TelaFinalJogo(void);
void CarregarArquivos(void);
void OrganizarRanking(void);
void TelaRanking(void);

//FUNÇÕES DO JOGO
char Tabuleiro [3][3];
void ZerarTabuleiro(void);
void GerarTabuleiro(void);
void ZerarTabuleiro(void);
void JogadaUsuario(void);
char VerificarGanhador(void);
void JogadaComputadorFacil(void);
void JogadaComputadorMedio(void);
void JogadaComputadorDificil(void);

//VARIAVEIS GLOBAIS
static int jogador=0;
static int Top[10];
int Logado=0;
char Ganhador=' ';
char EscolhaDificuldade=' ';
char DificuldadeEscolhida[50]={' '};
int Computador=0; //imitação de uma variavel booleana hehe
char arquivo_cadastro[]="cadastros.txt";

//VARIAVEIS LOGIN E SENHA
int i;
char Login[11];
char Pass[11];

struct Dados{
	char Nome[11];
	char Senha[11];
	int VitoriasFacil;
	int VitoriasMedio;
	int VitoriasDificil;
	int Empates;
	int Pontuacao;
} CadastroJogador[TAMANHO];


void main(void){
	
	system("color 1F");
	CarregarArquivos();
	TelaInicial();
	TelaMenuLogin();
	
}

void TelaInicial (void){
	
	int aux=0;
	
	do{
		FILE *logo;
		logo=fopen("Logo.txt","r");
		if(logo==NULL){
			printf("Nao foi possivel abrir o arquivo.\n");
			getch();
			exit(0);
		}
		
		char Nome [237];
		while(fgets(Nome,237, logo)!=NULL){
			printf("%s",Nome);	
		}
		aux=getch();
		system("cls");
	}while(aux!=ENTER);
	
}

void TelaMenuLogin(void){
	
	char Escolha=' ';
	
	system("cls");
	FILE *FTela;
	FTela=fopen("FTela.txt","r");
	if(FTela==NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		getch();
		exit(0);
	}
	char firstela [237];
	while(fgets(firstela,237, FTela)!=NULL){
		printf("%s",firstela);	
	}
	fflush(stdin);
	scanf("%c",&Escolha);
	
	switch(Escolha){
		case '1':
            TelaLogin();
            break;
	    
	    case '2':
            TelaCadastro();
            break;
        
        case '0':
        	break;
	    
	    default:
	    	printf("\n\tOp%c%co invalida! ",135,198);
            sleep(1);
        	system("cls");
        	return TelaMenuLogin();
    }
	
}
void TelaLogin(void){
	
	int achou=0, i=0, quantidade=0;
	char Password[256] = {' '};
	char caracter;
	
	fflush(stdin);
	system("cls");
	FILE *menu;
	menu=fopen("TelaLogin.txt","r");
	if(menu==NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		getch();
		exit(0);
	}
	char Meni [237];
	while(fgets(Meni,237, menu)!=NULL){
		printf("%s",Meni);
	}
	
	scanf("%11s",Login);
	
	if(!strcmp(Login,"0")){
		system("cls");
		return TelaMenuLogin();
	}
	printf("                   |Senha: ");
	
	do{
		caracter=getch();
		if((caracter != ENTER) && (caracter != 8)){
			Password[i++] = caracter;
			printf("*");
		}else if(caracter == 8 && i>0){
			printf("\b \b");
			Password[i--] = ' ';
		}
		
	}while(caracter != ENTER);
	
	strcpy(Pass,Password);

	//scanf("%11s",Pass);
	for(i=0;i<TAMANHO;i++){
		achou=0;
		if(!strcmp (Login,CadastroJogador[i].Nome) && !strcmp (Pass,CadastroJogador[i].Senha)){
			achou++;
			Logado=i;
			printf("\n\tLogin efetuado com sucesso!");
			sleep(1);
			system("cls");
			return MenuPrincipal();
		}
	}
	if(achou==0){
		printf("\n\tLogin invalido!");
		sleep(1);
		system("cls");
		return TelaLogin();
	}
}

void TelaCadastro(){
	
	int i=0,achei=0;
	int quantidade=0;
	char caracter;
	char Password[256] = {' '};
	
	fflush(stdin);
	system("cls");
	
	do{
		achei=0;
		do{
			FILE *menu;
			menu=fopen("TelaReg.txt","r");
			if(menu==NULL){
				printf("Nao foi possivel abrir o arquivo.\n");
				getch();
				exit(0);
			}
			char Menu [237];
			while(fgets(Menu,237, menu)!=NULL){
				printf("%s",Menu);	
			}
			scanf("%s",&CadastroJogador[jogador].Nome);
			quantidade = strlen(CadastroJogador[jogador].Nome);//Conta quantos caracteres foram digitados
			
			if(quantidade>10){
				printf("\n\tUltrapassou o numero maximo de caracteres(10).");
				sleep(1);
				system("cls");
				quantidade=0;
				return TelaCadastro();
			}
			
			for(i=0;i<TAMANHO;i++){
				if (!strcmp(CadastroJogador[jogador].Nome ,CadastroJogador[i].Nome)){
                        achei++;
                }
			}
			
			if(achei>1){
                    printf("\n\tNome de jogador j%c cadastrado,por favor insira outro.",160);
                    sleep(1);
					system("cls");
            }
            
		}while(quantidade>10);
		
	}while(achei>1);
	
	do{
		printf("                   |Senha:");
		
		
		i=0;
		do{
			caracter=getch();
			if((caracter != ENTER) && (caracter != 8)){
				Password[i] = caracter;
				printf("*");
				i++;
			}else if(caracter == 8 && i>0){
				printf("\b \b");
				i--;
				Password[i] = ' ';
			}
			
		}while(caracter != ENTER);
		
		strcpy(CadastroJogador[jogador].Senha,Password);

		//scanf("%s",&CadastroJogador[jogador].Senha);
		
		quantidade=strlen(CadastroJogador[jogador].Senha);//Conta quantos caracteres foram digitados
		
		if(quantidade>10){
			printf("\n\tUltrapassou o numero maximo de caracteres(10).");
			sleep(1);
			system("cls");
			quantidade=0;
			TelaCadastro();
		}
		
	}while(quantidade>10);
	
	printf("\n\tCadastrado!");
	sleep(1);
	system("cls");
	
	FILE *arquivo;
	arquivo=fopen(arquivo_cadastro,"a+");
	if(arquivo != NULL){
		fprintf(arquivo,"\n%s \n%s \n%d \n%d \n%d \n%d \n%d",CadastroJogador[jogador].Nome, CadastroJogador[jogador].Senha, CadastroJogador[jogador].VitoriasFacil, CadastroJogador[jogador].VitoriasMedio, CadastroJogador[jogador].VitoriasDificil, CadastroJogador[jogador].Empates, CadastroJogador[jogador].Pontuacao);					//MAGIA DO TXT ACONTECE AQUI
	}
	
	fclose(arquivo);
	jogador++;
	return TelaMenuLogin();
}

void MenuPrincipal (void){
	
	char Escolha=' ';
	FILE *arquivo;
	int i=0;
	
	system("cls");
	FILE *menu;
	menu=fopen("Menu.txt","r");
	if(menu==NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		getch();
		exit(0);
	}
	char Menu [237];
	while(fgets(Menu,237, menu)!=NULL){
		printf("%s",Menu);	
	}
	fflush(stdin);
	scanf("%c",&Escolha);
	switch(Escolha){
		case '1':
			TelaEscolhaDificuldade();
			break;
		case '2':
			TelaRanking();
			break;
		case '3':
			TelaComoJogar();
			break;
		case '0':
			printf("\tObrigado por jogar...");
			
			FILE *arquivo;
			arquivo=fopen(arquivo_cadastro,"w");
			if(arquivo != NULL){
				i=1;
				while(i<=jogador){
					fflush(stdin);
					if(CadastroJogador[i].Nome[0]!=' '){
					fprintf(arquivo,"\n%s \n%s \n%d \n%d \n%d \n%d \n%d", CadastroJogador[i].Nome, CadastroJogador[i].Senha, CadastroJogador[i].VitoriasFacil, CadastroJogador[i].VitoriasMedio, CadastroJogador[i].VitoriasDificil, CadastroJogador[i].Empates, CadastroJogador[i].Pontuacao);					//MAGIA DO TXT ACONTECE AQUI
					i++;
						
					}
				}
			}
	
			fcloseall;
			sleep(1);
			break;
		default:
			printf("\n\tOp%c%co invalida! ",135,198);
			sleep(1);
			MenuPrincipal();
	}
	
}

void TelaEscolhaDificuldade(void){
	
	char Escolha=' ';
	
	system("cls");
	FILE *difi;
	difi=fopen("Dificuldades.txt","r");
	if(difi==NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		getch();
		exit(0);
	}
	char Difi [237];
	while(fgets(Difi,237, difi)!=NULL){
		printf("%s",Difi);	
	}
	fflush(stdin);
	scanf("%c",&Escolha);
	switch(Escolha){
		case '1':
			EscolhaDificuldade='1';
			strcpy(DificuldadeEscolhida,"FACIL");
			TelaJogoFacil();
			break;
		case '2':
			EscolhaDificuldade='2';
			strcpy(DificuldadeEscolhida,"MEDIO");
			TelaJogoMedio();
			break;
		case '3':
			EscolhaDificuldade='3';
			strcpy(DificuldadeEscolhida,"DIFICIL");
			TelaJogoDificil();
			break;
		case '0':
			return MenuPrincipal();
		default:
			printf("\n\tOp%c%co invalida! ",135,198);
			sleep(1);
			TelaEscolhaDificuldade();
	}
	
}

void TelaJogoFacil(void){
	
	int Jogadas=0, ComputadorAux=Computador;		//variavel auxiliar recebe o valor da varial global para definir quem irá iniciar o jogo
	int i=0;
	
	Ganhador=' ';
	ZerarTabuleiro();
	
	do{
		if(ComputadorAux){
			system("cls");
			//printf("\n\t\tTHE ELDER'S GAME");
			GerarTabuleiro();
			printf("\n\n\tComputador realizando jogada...");
			sleep(1);
			JogadaComputadorFacil();
			ComputadorAux=0;
			Jogadas++;
		}
		
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		GerarTabuleiro();
		JogadaUsuario();
		Jogadas++;
		Ganhador=VerificarGanhador();
		if(Ganhador!=' ' || Jogadas==9)	break;
		
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		GerarTabuleiro();
		printf("\n\n\tComputador realizando jogada...");
		sleep(1);
		JogadaComputadorFacil();
		Jogadas++;
		Ganhador=VerificarGanhador();
		if(Ganhador!=' ' || Jogadas==9) break;
	
	}while((Ganhador==' ')&&(Jogadas<9));
	
	if(Computador){
		Computador=0;
	}else Computador=1;
	
	for(i=0;i<=jogador;i++){
		if(!strcmp(CadastroJogador[i].Nome,Login)){
			if(Ganhador=='X'){
				CadastroJogador[i].VitoriasFacil+=1;
				CadastroJogador[i].Pontuacao+=1;
			}else if(Jogadas==9 && Ganhador==' '){
			Ganhador='E';
			CadastroJogador[i].Empates+=1;
			break;
			}
		}
	}
		
			
	TelaFinalJogo();
}

void TelaJogoMedio(void){
	
	int Jogadas=0, ComputadorAux=Computador;		//variavel auxiliar recebe o valor da varial global para definir quem irá iniciar o jogo
	int i=0;
	
	Ganhador=' ';
	ZerarTabuleiro();
	
	do{
		if(ComputadorAux){
			system("cls");
			//printf("\n\t\tTHE ELDER'S GAME");
			GerarTabuleiro();
			printf("\n\n\tComputador realizando jogada...");
			sleep(1);
			JogadaComputadorMedio();
			ComputadorAux=0;
			Jogadas++;
		}
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		GerarTabuleiro();
		JogadaUsuario();
		Jogadas++;
		Ganhador=VerificarGanhador();
		if(Ganhador!=' ' || Jogadas==9) break;
		
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		GerarTabuleiro();
		printf("\n\n\tComputador realizando jogada...");
		sleep(1);
		JogadaComputadorMedio();
		Jogadas++;
		Ganhador=VerificarGanhador();
		if(Ganhador!=' ' || Jogadas==9) break;
	
	}while((Ganhador==' ')&&(Jogadas<9));
	
	if(Computador){
		Computador=0;
	}else Computador=1;
	
	for(i=0;i<=jogador;i++){
		if(!strcmp(CadastroJogador[i].Nome,Login)){
			if(Ganhador=='X'){
				CadastroJogador[i].VitoriasMedio+=1;
				CadastroJogador[i].Pontuacao+=100;
			}else if(Jogadas==9 && Ganhador==' '){
			Ganhador='E';
			CadastroJogador[i].Empates+=1;
			break;
			}
		}
	}
	
	TelaFinalJogo();
}

void TelaJogoDificil(void){
	
	int Jogadas=0, ComputadorAux=Computador;		//variavel auxiliar recebe o valor da varial global para definir quem irá iniciar o jogo
	int i=0;
	
	Ganhador=' ';
	ZerarTabuleiro();
	
	do{
		if(ComputadorAux){
			system("cls");
			//printf("\n\t\tTHE ELDER'S GAME");
			GerarTabuleiro();
			printf("\n\n\tComputador realizando jogada...");
			sleep(1);
			JogadaComputadorDificil();
			ComputadorAux=0;
			Jogadas++;
		}
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		GerarTabuleiro();
		JogadaUsuario();
		Jogadas++;
		Ganhador=VerificarGanhador();
		if(Ganhador!=' ' || Jogadas==9) break;
		
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		GerarTabuleiro();
		printf("\n\n\tComputador realizando jogada...");
		sleep(1);
		JogadaComputadorDificil();
		Jogadas++;
		Ganhador=VerificarGanhador();
		if(Ganhador!=' ' || Jogadas==9) break;
	
	}while((Ganhador==' ')&&(Jogadas<9));
	
	if(Computador){
		Computador=0;
	}else Computador=1;
	
	for(i=0;i<=jogador;i++){
		if(!strcmp(CadastroJogador[i].Nome,Login)){
			if(Ganhador=='X'){
				CadastroJogador[i].VitoriasDificil+=1;
				CadastroJogador[i].Pontuacao+=1000;
			}else if(Jogadas==9 && Ganhador==' '){
			Ganhador='E';
			CadastroJogador[i].Empates+=1;
			break;
			}
		}
	}
	
	TelaFinalJogo();
}


void ZerarTabuleiro (void){
	
	int l=0,c=0;
	
	for(l=0;l<3;l++){
		for(c=0;c<3;c++){
			Tabuleiro[l][c]=' ';
		}
	}
	
}


void GerarTabuleiro(void){
	
	int i=0;
	FILE *ljogando;
	ljogando=fopen("TelaJogando.txt","r");
	if(ljogando==NULL){
		printf("Nao foi possivel abrir o arquivo.\n");
		getch();
		exit(0);
	}
	char Difi [237];
	while(fgets(Difi,237, ljogando)!=NULL){
		printf("%s",Difi);	
	}
	printf("%s",DificuldadeEscolhida);
	
	printf("\n\n\n\n\t\t\t\t   A   B   C \n");
	for(i=0;i<=2;i++){
		printf("\t\t\t\t%d  %c | %c | %c ",i+1,Tabuleiro[i][0],Tabuleiro[i][1],Tabuleiro[i][2]);
		if(i!=2){
			printf("\n\t\t\t\t  ---|---|---\n");
		}
	}
	
}

void JogadaUsuario(void){
	
	int Coluna=-1, Linha=-1;
	char ColunaAux, LinhaAux;


	printf("\n\n\t\t\t\tDigite a coluna: ");
	fflush(stdin);
	scanf("%c",&ColunaAux);
	
	if((ColunaAux=='A')||(ColunaAux=='a')){
		Coluna=0;
	}else if((ColunaAux=='B')||(ColunaAux=='b')){
		Coluna=1;
	}else if((ColunaAux=='C')||(ColunaAux=='c')){
		Coluna=2;
	}else{
		printf("\t\t\tColuna invalida, tente novamente!\n");
		sleep(1);
		return JogadaUsuario();
	}
	
	if((Coluna>=0)&&(Coluna<=2)){
		
		printf("\t\t\t\tDigite a linha: ");
		fflush(stdin);
		scanf("%c",&LinhaAux);
		
		if(LinhaAux=='1'){
			Linha=0;
		}else if(LinhaAux=='2'){
			Linha=1;
		}else if(LinhaAux=='3'){
			Linha=2;
		}
	}

	if(Tabuleiro[Linha][Coluna]!=' '){
		printf("\n\t\t\tJogada invalida, tente novamente!\n");
		sleep(1);
		return JogadaUsuario();
	}else{
		Tabuleiro[Linha][Coluna]='X';
	}	
}

char VerificarGanhador (void){
	
	int i=0;
	
	
	//VERIFICAR AS LINHAS
	for(i=0;i<3;i++){ 
		if((Tabuleiro[i][0]==Tabuleiro[i][1])&&(Tabuleiro[i][0]==Tabuleiro[i][2])){
			return Tabuleiro[i][0];
		}
	}
	
	//VERIRICAR AS COLUNAS
	for(i=0;i<3;i++){
		if((Tabuleiro[0][i]==Tabuleiro[1][i])&&(Tabuleiro[0][i]==Tabuleiro[2][i])){
			return Tabuleiro[0][i];
		}
	}
	
	//VERIFICAR AS DIAGONAIS
	if((Tabuleiro[0][0]==Tabuleiro[1][1])&&(Tabuleiro[0][0]==Tabuleiro[2][2])){
		return Tabuleiro[0][0];
	}
	
	if((Tabuleiro[0][2]==Tabuleiro[1][1])&&(Tabuleiro[0][2]==Tabuleiro[2][0])){
		return Tabuleiro[0][2];
	}
	
	return ' ';
}

void TelaFinalJogo(void){
	
	char Escolha=' ';
	
	system("cls");
	//printf("\n\t\tTHE ELDER'S GAME");
	GerarTabuleiro();
	if(Ganhador=='X'){
		fflush(stdin);
		printf("\n\n\n\tVoc%c Ganhou!",234);
	}else if(Ganhador=='O'){
		fflush(stdin);
		printf("\n\n\n\tVoc%c perdeu!",234);
	}else{
		printf("\n\n\n\tEmpatou!");
	}
	
	printf("\n\n\tDeseja jogar novamente?");
	printf("\n\t1 - Sim");
	printf("\n\t0 - Nao");
	printf("\n\tOpcao: ");
	fflush(stdin);
	scanf("%c",&Escolha);
	switch(Escolha){
		case '1':
			if(EscolhaDificuldade=='1'){
				TelaJogoFacil();
			}else if(EscolhaDificuldade=='2'){
				TelaJogoMedio();
			}else{
				TelaJogoDificil();
			}
			break;
		case '0':
			MenuPrincipal();
			break;
		default:
			printf("\nOp%c%co invalida, tente novamente!",135,198);
			sleep(1);
			TelaFinalJogo();
	}
	
}

void TelaComoJogar(void){
	
	int aux=0;
	
	do{
		system("cls");
		//printf("\n\t\tTHE ELDER'S GAME");
		printf("\n\n\tComo Jogar:\n");
		printf("\n\t1 - O Jogador devera informar a coluna, posteriormente a sua linha\n\t\tpara realizar a jogada.\n\n");
		printf("\t2 - O jogador jogara apenas com o 'X'.\n\n");
		printf("\t3 - O jogo so termina quando um jogador conseguir marcar uma seguencia\n\t\tde 'X ou 'O' nas linhas, colunas ou diagonais, ou entao quando\n\t\ttodas as casas forem preenchidas.");
		printf("\n\n\n\tApenter ESC para voltar");
		aux=getch();
	}while(aux!=ESC);
	
	MenuPrincipal();
}

void JogadaComputadorFacil (void){																					//JOGADA COMPUTADOR FACIL
	
	int l=0,c=0, pode=1;
	
	do{
			
		l=(rand()%3);
		c =(rand()%3);
		
		if(Tabuleiro[l][c]==' '){
			Tabuleiro[l][c]='O';
			pode=0;
		}
		
	}while(pode==1);
	
}


void JogadaComputadorMedio(void){																					//JOGADA COMPUTADOR MEDIO
	
	int l=0,c=0, pode=1;
	
	
	
	
	if(pode){																				//PRIMEIRA LINHA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[0][1]=='X')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[0][2]=='X')&&(Tabuleiro[0][1]==' ')){
			Tabuleiro[0][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][1]=='X')&&(Tabuleiro[0][2]=='X')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	
	if(pode){																				//SEGUNDA LINHA
		if((Tabuleiro[1][0]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[1][2]==' ')){
			Tabuleiro[1][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][0]=='X')&&(Tabuleiro[1][2]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[1][2]=='X')&&(Tabuleiro[1][0]==' ')){
			Tabuleiro[1][0]='O';
			pode=0;
		}
	}
	if(pode){																				//TERCEIRA LINHA
		if((Tabuleiro[2][0]=='X')&&(Tabuleiro[2][1]=='X')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[2][0]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[2][1]==' ')){
			Tabuleiro[2][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[2][1]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){																				//PRIMEIRA COLUNA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[1][0]=='X')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[1][0]==' ')){
			Tabuleiro[1][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][0]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	if(pode){																				//SEGUNDA COLUNA
		if((Tabuleiro[0][1]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[2][1]==' ')){
			Tabuleiro[2][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][1]=='X')&&(Tabuleiro[2][1]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[2][1]=='X')&&(Tabuleiro[0][1]==' ')){
			Tabuleiro[0][1]='O';
			pode=0;
		}
	}
	if(pode){																				//TERCEIRA COLUNA
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[1][2]=='X')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[1][2]==' ')){
			Tabuleiro[1][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][2]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	if(pode){																				//DIAGONAL DA ESQUERDA PARA A DIRETIRA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	if(pode){																			//DIAGONAL DA DIREITA PARA A ESQUERDA
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
		
	while(pode==1){
			
		l=(rand()%3);
		c =(rand()%3);
		
		if(Tabuleiro[l][c]==' '){
			Tabuleiro[l][c]='O';
			pode=0;
		}
	
	}
	
}

void JogadaComputadorDificil(void){																								//JOGADA COMPUTADOR DIFICIL
	
	int i=0, j=0, pode=1;
																							//CÓDIGO PARA ATACAR
	if(pode){																				//PRIMEIRA LINHA
		if((Tabuleiro[0][0]=='O')&&(Tabuleiro[0][1]=='O')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='O')&&(Tabuleiro[0][2]=='O')&&(Tabuleiro[0][1]==' ')){
			Tabuleiro[0][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][1]=='O')&&(Tabuleiro[0][2]=='O')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	
	if(pode){																				//SEGUNDA LINHA
		if((Tabuleiro[1][0]=='O')&&(Tabuleiro[1][1]=='O')&&(Tabuleiro[1][2]==' ')){
			Tabuleiro[1][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][0]=='O')&&(Tabuleiro[1][2]=='O')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='O')&&(Tabuleiro[1][2]=='O')&&(Tabuleiro[1][0]==' ')){
			Tabuleiro[1][0]='O';
			pode=0;
		}
	}
	if(pode){																				//TERCEIRA LINHA
		if((Tabuleiro[2][0]=='O')&&(Tabuleiro[2][1]=='O')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[2][0]=='O')&&(Tabuleiro[2][2]=='O')&&(Tabuleiro[2][1]==' ')){
			Tabuleiro[2][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[2][1]=='O')&&(Tabuleiro[2][2]=='O')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){																				//PRIMEIRA COLUNA
		if((Tabuleiro[0][0]=='O')&&(Tabuleiro[1][0]=='O')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='O')&&(Tabuleiro[2][0]=='O')&&(Tabuleiro[1][0]==' ')){
			Tabuleiro[1][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][0]=='O')&&(Tabuleiro[2][0]=='O')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	if(pode){																				//SEGUNDA COLUNA
		if((Tabuleiro[0][1]=='O')&&(Tabuleiro[1][1]=='O')&&(Tabuleiro[2][1]==' ')){
			Tabuleiro[2][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][1]=='O')&&(Tabuleiro[2][1]=='O')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='O')&&(Tabuleiro[2][1]=='O')&&(Tabuleiro[0][1]==' ')){
			Tabuleiro[0][1]='O';
			pode=0;
		}
	}
	if(pode){																				//TERCEIRA COLUNA
		if((Tabuleiro[0][2]=='O')&&(Tabuleiro[1][2]=='O')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][2]=='O')&&(Tabuleiro[2][2]=='O')&&(Tabuleiro[1][2]==' ')){
			Tabuleiro[1][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][2]=='O')&&(Tabuleiro[2][2]=='O')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	if(pode){																				//DIAGONAL DA ESQUERDA PARA A DIRETIRA
		if((Tabuleiro[0][0]=='O')&&(Tabuleiro[1][1]=='O')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='O')&&(Tabuleiro[2][2]=='O')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='O')&&(Tabuleiro[2][2]=='O')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	if(pode){																				//DIAGONAL DA DIREITA PARA A ESQUERDA
		if((Tabuleiro[0][2]=='O')&&(Tabuleiro[1][1]=='O')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][2]=='O')&&(Tabuleiro[2][0]=='O')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='O')&&(Tabuleiro[2][0]=='O')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	
																							//CÓDIGO PARA DEFENDER
	if(pode){																				//PRIMEIRA LINHA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[0][1]=='X')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[0][2]=='X')&&(Tabuleiro[0][1]==' ')){
			Tabuleiro[0][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][1]=='X')&&(Tabuleiro[0][2]=='X')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	
	if(pode){																				//SEGUNDA LINHA
		if((Tabuleiro[1][0]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[1][2]==' ')){
			Tabuleiro[1][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][0]=='X')&&(Tabuleiro[1][2]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[1][2]=='X')&&(Tabuleiro[1][0]==' ')){
			Tabuleiro[1][0]='O';
			pode=0;
		}
	}
	if(pode){																				//TERCEIRA LINHA
		if((Tabuleiro[2][0]=='X')&&(Tabuleiro[2][1]=='X')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[2][0]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[2][1]==' ')){
			Tabuleiro[2][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[2][1]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){																				//PRIMEIRA COLUNA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[1][0]=='X')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[1][0]==' ')){
			Tabuleiro[1][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][0]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	if(pode){																				//SEGUNDA COLUNA
		if((Tabuleiro[0][1]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[2][1]==' ')){
			Tabuleiro[2][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][1]=='X')&&(Tabuleiro[2][1]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[2][1]=='X')&&(Tabuleiro[0][1]==' ')){
			Tabuleiro[0][1]='O';
			pode=0;
		}
	}
	if(pode){																				//TERCEIRA COLUNA
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[1][2]=='X')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[1][2]==' ')){
			Tabuleiro[1][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][2]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	if(pode){																				//DIAGONAL DA ESQUERDA PARA A DIRETIRA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[2][2]==' ')){
			Tabuleiro[2][2]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[2][2]=='X')&&(Tabuleiro[0][0]==' ')){
			Tabuleiro[0][0]='O';
			pode=0;
		}
	}
	if(pode){																			//DIAGONAL DA DIREITA PARA A ESQUERDA
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[1][1]=='X')&&(Tabuleiro[2][0]==' ')){
			Tabuleiro[2][0]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[0][2]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[1][1]==' ')){
			Tabuleiro[1][1]='O';
			pode=0;
		}
	}
	if(pode){
		if((Tabuleiro[1][1]=='X')&&(Tabuleiro[2][0]=='X')&&(Tabuleiro[0][2]==' ')){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	
	if(pode){																				//PRIMEIRA JOGADA PRÉ-DEFINIDA
		if(Tabuleiro[1][1]==' '){
			Tabuleiro[1][1]='O';
			pode=0;
		}else if (Tabuleiro[0][2]==' ' && Tabuleiro[1][1]!='O'){
			Tabuleiro[0][2]='O';
			pode=0;
		}
	}
	
	if(pode){																				//SEGUNDA JOGADA PRÉ-DEFINIDA
		if(Tabuleiro[0][2]=='O'){
			if(Tabuleiro[2][2]==' '){
				Tabuleiro[2][2]='O';
				pode=0;
			}else if(Tabuleiro[0][0]==' '){
				Tabuleiro[0][0]='O';
				pode=0;
			}else if(Tabuleiro[1][1]==' '){
				Tabuleiro[1][1]='O';
				pode=0;
			}
		}else{
			if((Tabuleiro[1][0]==' ')&&(Tabuleiro[1][2]==' ')){
				Tabuleiro[1][0]='O';
				pode=0;
			}else if((Tabuleiro[0][1]==' ')&&(Tabuleiro[2][1]==' ')){
				Tabuleiro[0][1]='O';
				pode=0;
			}else if((Tabuleiro[2][0]==' ')&&(Tabuleiro[0][2]==' ')){
				Tabuleiro[2][0]='O';
				pode=0;
			}else if((Tabuleiro[2][2]==' ')&&(Tabuleiro[0][0]==' ')){
				Tabuleiro[2][2]='O';
				pode=0;
			}
		}
	}
	
	if(pode){																				//TERCEIRA JOGADA PRÉ-DEFINIDA
		if((Tabuleiro[0][0]=='X')&&(Tabuleiro[2][2]=='X')){
			if(Tabuleiro[1][0]==' '){
				Tabuleiro[1][0]='O';
				pode=0;
			}else if(Tabuleiro[2][1]==' '){
				Tabuleiro[2][1]='O';
				pode=0;
			}
		}else if((Tabuleiro[0][2]=='X')&&(Tabuleiro[2][0]=='X')){
			if(Tabuleiro[0][1]==' '){
				Tabuleiro[0][1]='O';
				pode=0;
			}else if(Tabuleiro[1][2]==' '){
				Tabuleiro[1][2]='O';
				pode=0;
			}
		}
	}
	
	while(pode==1){
		
		i=(rand()%3);
		j =(rand()%3);
		
		if(Tabuleiro[i][j]==' '){
			Tabuleiro[i][j]='O';
			pode=0;
		}
	
	}
	
}

void OrganizarRanking(void){

int i=0, j=0;
	char NomeAux[50], SenhaAux[50];
	int FacilAux=0, MedioAux=0, DificilAux=0, EmpatesAux=0, PontuacaoAux=0;
	
	for(j=0;j<=jogador;j++){
		for(i=0;i<jogador;i++){
			
			if(CadastroJogador[i].Pontuacao>CadastroJogador[i+1].Pontuacao){
				strcpy(NomeAux,CadastroJogador[i].Nome);
				strcpy(SenhaAux,CadastroJogador[i].Senha);
				FacilAux=CadastroJogador[i].VitoriasFacil;
				MedioAux=CadastroJogador[i].VitoriasMedio;
				DificilAux=CadastroJogador[i].VitoriasDificil;
				EmpatesAux=CadastroJogador[i].Empates;
				PontuacaoAux=CadastroJogador[i].Pontuacao;
				
				strcpy(CadastroJogador[i].Nome,CadastroJogador[i+1].Nome);
				strcpy(CadastroJogador[i].Senha,CadastroJogador[i+1].Senha);
				CadastroJogador[i].VitoriasFacil=CadastroJogador[i+1].VitoriasFacil;
				CadastroJogador[i].VitoriasMedio=CadastroJogador[i+1].VitoriasMedio;
				CadastroJogador[i].VitoriasDificil=CadastroJogador[i+1].VitoriasDificil;
				CadastroJogador[i].Empates=CadastroJogador[i+1].Empates;
				CadastroJogador[i].Pontuacao=CadastroJogador[i+1].Pontuacao;
				
				strcpy(CadastroJogador[i+1].Nome,NomeAux);
				strcpy(CadastroJogador[i+1].Senha,SenhaAux);
				CadastroJogador[i+1].VitoriasFacil=FacilAux;
				CadastroJogador[i+1].VitoriasMedio=MedioAux;
				CadastroJogador[i+1].VitoriasDificil=DificilAux;
				CadastroJogador[i+1].Empates=EmpatesAux;
				CadastroJogador[i+1].Pontuacao=PontuacaoAux;
			}	
		}
	}
	
	for(j=0;j<=jogador;j++){
		for(i=0;i<jogador;i++){
			if(CadastroJogador[i].Pontuacao==0){									//CASO A PONTUAÇÃO SEJA 0, ORGANIZARÁ PELO NOME
				if(CadastroJogador[i].Nome[0]>CadastroJogador[i+1].Nome[0]){
					strcpy(NomeAux,CadastroJogador[i].Nome);
					strcpy(SenhaAux,CadastroJogador[i].Senha);
					FacilAux=CadastroJogador[i].VitoriasFacil;
					MedioAux=CadastroJogador[i].VitoriasMedio;
					DificilAux=CadastroJogador[i].VitoriasDificil;
					EmpatesAux=CadastroJogador[i].Empates;
					PontuacaoAux=CadastroJogador[i].Pontuacao;
					
					strcpy(CadastroJogador[i].Nome,CadastroJogador[i+1].Nome);
					strcpy(CadastroJogador[i].Senha,CadastroJogador[i+1].Senha);
					CadastroJogador[i].VitoriasFacil=CadastroJogador[i+1].VitoriasFacil;
					CadastroJogador[i].VitoriasMedio=CadastroJogador[i+1].VitoriasMedio;
					CadastroJogador[i].VitoriasDificil=CadastroJogador[i+1].VitoriasDificil;
					CadastroJogador[i].Empates=CadastroJogador[i+1].Empates;
					CadastroJogador[i].Pontuacao=CadastroJogador[i+1].Pontuacao;
					
					strcpy(CadastroJogador[i+1].Nome,NomeAux);
					strcpy(CadastroJogador[i+1].Senha,SenhaAux);
					CadastroJogador[i+1].VitoriasFacil=FacilAux;
					CadastroJogador[i+1].VitoriasMedio=MedioAux;
					CadastroJogador[i+1].VitoriasDificil=DificilAux;
					CadastroJogador[i+1].Empates=EmpatesAux;
					CadastroJogador[i+1].Pontuacao=PontuacaoAux;
				}	
			}
		}
	}
		
}


void TelaRanking(void){
	
	
	int aux=0, i=0, QuantidadeChar=0;
	
	do{
		OrganizarRanking();
		system("cls");
		printf("\n\t\tTHE ELDER'S GAME");
		printf("\n\n\tRANKING\n");
		printf("\n\tNome\t\tFacil\tMedio\tDificil\tEmpates\tPontuacao\n\n\n");
		
		if(jogador>10){
			for(i=0;i<10;i++){
				QuantidadeChar=strlen(CadastroJogador[jogador-i].Nome);
				if(QuantidadeChar>7){
					printf("\t%s\t%d\t%d\t%d\t%d\t%d\n",CadastroJogador[jogador-i].Nome,CadastroJogador[jogador-i].VitoriasFacil,CadastroJogador[jogador-i].VitoriasMedio,CadastroJogador[jogador-i].VitoriasDificil,CadastroJogador[jogador-i].Empates, CadastroJogador[jogador-i].Pontuacao);	
				}else{
					printf("\t%s\t\t%d\t%d\t%d\t%d\t%d\n",CadastroJogador[jogador-i].Nome,CadastroJogador[jogador-i].VitoriasFacil,CadastroJogador[jogador-i].VitoriasMedio,CadastroJogador[jogador-i].VitoriasDificil,CadastroJogador[jogador-i].Empates, CadastroJogador[jogador-i].Pontuacao);	
				}
			}
		}else{
			for(i=0;i<=jogador;i++){
				QuantidadeChar=strlen(CadastroJogador[jogador-i].Nome);
				if(QuantidadeChar>7){
					printf("\t%s\t%d\t%d\t%d\t%d\t%d\n",CadastroJogador[jogador-i].Nome,CadastroJogador[jogador-i].VitoriasFacil,CadastroJogador[jogador-i].VitoriasMedio,CadastroJogador[jogador-i].VitoriasDificil,CadastroJogador[jogador-i].Empates, CadastroJogador[jogador-i].Pontuacao);	
				}else{
					printf("\t%s\t\t%d\t%d\t%d\t%d\t%d\n",CadastroJogador[jogador-i].Nome,CadastroJogador[jogador-i].VitoriasFacil,CadastroJogador[jogador-i].VitoriasMedio,CadastroJogador[jogador-i].VitoriasDificil,CadastroJogador[jogador-i].Empates, CadastroJogador[jogador-i].Pontuacao);	
				}
			}
		}
	
		printf("\n\n\n\tPressione ESC para voltar");
		aux=getch();
	}while(aux!=ESC);
	
	MenuPrincipal();
		
}

	
void CarregarArquivos(void){
	
	FILE *arquivo;
	
	arquivo=fopen(arquivo_cadastro,"r");
	
	if(arquivo != NULL){
		while(fscanf(arquivo,"%s%s%d%d%d%d%d", &CadastroJogador[jogador].Nome, &CadastroJogador[jogador].Senha, &CadastroJogador[jogador].VitoriasFacil, &CadastroJogador[jogador].VitoriasMedio, &CadastroJogador[jogador].VitoriasDificil, &CadastroJogador[jogador].Empates, &CadastroJogador[jogador].Pontuacao)!= EOF){			//grava os dados do txt nas variaveis até dar End Of File
			jogador++;
			
		}
	}
	
	fclose(arquivo);
	
}

