#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <windows.h>

////////////////////////////// Structures de la File /////////////////////////////////////////

////////////////////////////////////// Structure Element /////////////////////////////////////

typedef struct Element Element;
struct Element{
    int nombre;
    Element *suivant;
};

/////////////////////////////////////// Structure File /////////////////////////////////////// 

typedef struct File File;
struct File{
    Element *premier;
};

//////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////// Structure des Dates //////////////////////////////////// 

typedef struct{
	int d;
	int m;
	int y;
}date;


///////////////////////////////////////// PROTOTYPES /////////////////////////////////////////
void gotoxy(int x,int y);
void SetColor(int ForgC);
void printChar(char ch, int n);
void titre();
int ext();
void present();
void enfiler(File *file, int nvNombre);
int defiler(File *file);
int main();
void entreprise();
void home_entreprise();
void entreprise_login();
int id_entreprise();
void nouvl_entreprise();
void postuler();
void marche_postuler();
void mesinfo_entreprise();
void info_base_marche(int id);
void marche_gagne();
void home_admin();
void admin_login();
void nouv_marche();
int id_marche();
void supp_marche(int id_supp);
void affichage_marche();
void affichage_marche_cur();
void affichage_marchedetail(int id_affichage);
int date_cmp(date d1,date d2);
void affichage_entreprise();
void affichage(File *file);
void afficher_entreprise();
void marche_terminer();
void auto_expe();
int etatmarche(int id_marche);
int cheack_apply(int id_marche, int id_entreprise);
void ouverture(int id_marche);
void envoi_email_au_gagnant(int id_entreprise,int marche_gagne);

int  id_session;           // Id de l'entreprise connectée

///////////////////////////////////// Structure des Marches ////////////////////////////////////

typedef struct {
	int id_marche;
	char nom_marche[50];
	int budget;
	char secteur[50];    // menu secteur activite
	char description[100];
	int etat;
	char ch_charge[20];
	date date_expir;
}marche;

///////////////////////////////// Structure des Entreprises ///////////////////////////////////

typedef struct {
	int id_entreprise;
    char nom_entreprise[50];
    char sect_activite[50];
    long tel_entreprise;
    char email_entreprise[50];
    char adresse[100];
    long CA;
    int annee_experience;
}Entreprise;


/////////////////////////////////////// Structure Login ////////////////////////////////////// 

typedef struct {
	int id_entreprise;
	char username[20];
	char password[20];
}login;

//////////////////////////// Les information d'admin par defaut //////////////////////////////
login defaultadmin = {0,"admin","admin"};

/////////////////////////////////// Structure m_postuler /////////////////////////////////////

typedef struct {
	int id_marche;
	int id_entreprise;
}m_postuler;


///// Fonction gotoxy pour positionner le curseur dans la console à une position definie /////
void gotoxy(int x,int y){
	COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}


//////////////////// Fonction SetColor pour determiner la couleur du text ////////////////////
void SetColor(int ForgC) {
  WORD wColor;
  //We will need this handle to get the current background attribute
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  //We use csbi for the wAttributes word.
  if (GetConsoleScreenBufferInfo(hStdOut, & csbi)) {
    //Mask out all but the background attribute, and add in the forgournd color
    wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
    SetConsoleTextAttribute(hStdOut, wColor);
  }
  return;
}


//////////////////// Fonction printChar pour afficher un char (ch) n fois ////////////////////
void printChar(char ch,int n){
    while(n--)
    {
        putchar(ch);
    }
}


///////////////////////// Fonction pour afficher le titre du projet //////////////////////////
void titre(){
    system("cls");
    system("COLOR 03");
    printf("\n\n\t\t\t");
    printChar('=',19);
    printf("\tE-supply RIA | APP\t ");
    system("COLOR 03");
    printChar('=',19);
    printf("\n");
}


////////////////////////////////////// Quitter une page //////////////////////////////////////
int ext() {
  system("cls");
  char c_exit;
  titre();
  SetColor(6);
  printf("\n\n\t\t\t\t\t");
  printChar('=',34);
  printf("\n\t\t\t\t\t||        Quitter la page \t||\n");
  printf("\t\t\t\t\t||                        \t||");
  printf("\n\t\t\t\t\t|| ==> 1. Revenir au Menu\t||\n");
  printf("\t\t\t\t\t|| ==> 2. Quitter APP\t\t||\n");
  printf("\t\t\t\t\t");
  printChar('=',34);
  printf("\n\n");
  SetColor(11);
  printf("\t\t\t\t\t Select an Option:");
  SetColor(12);
  gotoxy(70, 25);
  printf(" Developed By Ali Rim Imane");
  SetColor(45);
  gotoxy(59, 12);
  c_exit = getche();
  switch (c_exit) {
  case '1':
    main();						//Menu principal pour choisir son identité ( admin ou entreprise)
    break;
  case '2':
    SetColor(3);
    printf("\n\n\n\t\t\t\t\t  Merci d'utilisez notre APP\n");
    printf("\t\t\t\t\t  Press Any Key To EXIT......");
    _getch();
    exit(EXIT_SUCCESS);
    break;						//pour quitter toute l'application
  default:
    printf("INVALID\n");
    Sleep(1000);
    ext();                      //Appel récursif de la fonction ext() 
  }
  return 0;
}


/////////////////////////////////////// Page D'accueil ///////////////////////////////////////
void present(){
    titre();
    printf("\n\n\t\t\t\t\t  Project in C programming 2021");
    printf("\n\n\t\t\t\t\t        Ali / Imane / Rim ");
    printf("\n\n\t\t\t\t\t Ecole Superieure De Technologie\n");
    printf("\t\t\t\t\t\t      Meknes\n\t\t\t\t\t");
    printChar('=',33);
    printf("\n\n\n\t\t\t\t\t       Clicker sur une touche\n\n\n");
    gotoxy(25,17);
    printChar('=',66);
    gotoxy(70,14);
    getch();
    system("cls");
}


////////////////////////////////// Les Fontions de La File ///////////////////////////////////
void enfiler(File *file, int nvNombre){
    Element *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre;
    nouveau->suivant = NULL;
    if (file->premier != NULL) //La file n'est pas vide
    {
        // On se positionne à la fin de la file
        Element *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else // La file est vide, notre élément est le premier
    {
        file->premier = nouveau;
    }
}


int defiler(File *file){
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    // On vérifie s'il y a quelque chose à défiler
    if (file->premier != NULL)
    {
        Element *elementDefile = file->premier;

        nombreDefile = elementDefile->nombre;
        file->premier = elementDefile->suivant;
        free(elementDefile);
    }

    return nombreDefile;
}


//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////// Main ////////////////////////////////////////////
int main(){
    int chx;
    SetConsoleTitle("E-supply RIA | APP");         //donner le titre (E-supply RIA | APP) a la console 
	FILE * fp;
    auto_expe();      // Changer l'etat des marches que leurs dates ont été expirées
    present();        
    titre();
    SetColor(6);
    printf("\n\n\t\t\t\t\t");
    printChar('=',34);
    printf("\n\t\t\t\t\t|| ==> 1. Admin\t\t\t||\n");
    printf("\t\t\t\t\t|| ==> 2. Entreprise\t\t||\n");
    printf("\t\t\t\t\t|| ==> 3. Quitter APP\t\t||\n");
    printf("\t\t\t\t\t");
    printChar('=',34);
    printf("\n\n");
    SetColor(11);
    printf("\t\t\t\t\t Select an Option:");
    SetColor(12);
    gotoxy(70, 25);
    printf(" Developed By Ali Rim Imane");
    SetColor(45);
    gotoxy(59, 11);
    fflush(stdin);                   // flasher l'entrée standard
    scanf("%d",&chx);
    getchar();
    switch(chx){
    case 1 :
        admin_login();				
        break;
    case 2 :
        entreprise();
        break;
    case 3 :
        ext();
        break;
    default :
        printf("\n\n\n \t\t\t Invalid\n");
        Sleep(1000);
        main();
    }
    return 0;
}


//********************************* FONCTIONS D'ENTREPRISE *********************************//


///////////////////////////// Page D'accueil D'Entreprise ////////////////////////////////////
void entreprise(){
    char chx;
    titre();
    SetColor(6);
    printf("\n\n\t\t\t\t\t");
    printChar('=',34);
    printf("\n\t\t\t\t\t|| ==> 1. Se Connecter\t\t||\n");
    printf("\t\t\t\t\t|| ==> 2. Nouveau Compte\t||\n");
    printf("\t\t\t\t\t|| ==> 3. Quitter APP\t\t||\n");
    printf("\t\t\t\t\t");
    printChar('=',34);
    printf("\n\n");
    SetColor(11);
    printf("\t\t\t\t\t Select an Option:");
    SetColor(12);
    gotoxy(70, 25);
    printf(" Developed By Ali Rim Imane");
    SetColor(45);
    gotoxy(59, 11);
    fflush(stdin);                  // flasher l'entrée standard
    chx = getchar();
    getchar();
    switch(chx){
    case '1' :
        entreprise_login();         //appel de la fonction de connexion de l'entreprise
        break;
    case '2' :
        nouvl_entreprise();         //appel de la fonction d'inscription de l'entreprise
        break;
    case '3' :
        ext();                      //appel de la fonction pour quitter la page
        break;
    default :
        printf("\n\n\n \t\t\t Invalide\n");
        Sleep(1000);
        entreprise();               //Appel récursif de la fonction entreprise()
    }
}


////////////////////////////// Menu principal pour l'Entreprise //////////////////////////////
void home_entreprise(){
    int i;
    char chx;
    system("cls");
    titre();
    printf("\n\t\t\t||\t\t\t1  - Les marches ouverts \t\t  ||");
    printf("\n\n\t\t\t||\t\t\t2  - Les marches postule \t\t  ||");
    printf("\n\n\t\t\t||\t\t\t3  - Les marches accomplie \t\t  ||");
    printf("\n\n\t\t\t||\t\t\t4  - Informations sur entreprise \t  ||");
    printf("\n\n\t\t\t||\t\t\t5 - Logout \t\t\t\t  ||\n\t\t\t");
    printChar('=',68);
    SetColor(6);
    printf("\n\n\t\t\t Merci d'entre votre choix : ");
    fflush(stdin);                       // Flacher l'entrée standard
	chx= getchar();
	switch(chx){
		case '1':
			system("cls");
			postuler();					// Afficher les marches valables à postuler
			system("pause");
			home_entreprise();          
			break;
		case '2':
			marche_postuler();          // Les marches déja postulés
			break;
		case '3':
			marche_gagne();             // Les marchés gagnés
			getch();
			home_entreprise();
			break;
		case '4':
			mesinfo_entreprise();       // les informations De L'entreprise
			getch();
			home_entreprise();
			break;
		default:
			main();
	}
}


/////////////////////////// Fonction de connexion de l'entreprise ////////////////////////////
void entreprise_login(){
	int repetition=0;
	while(repetition<3){              //3 est le nombre d'essais pour se connecter
		login entreprise;
		login entrep;
		char p;
		int s=0,i;
		FILE *tp;
		titre();
	    SetColor(6);
	    printf("\n\n\t\t\t\t\t");
	    printChar('=',34);
	    printf("\n\t\t\t\t\t|| ==> Username :\t\t||\n");
	    printf("\t\t\t\t\t|| ==> Password : \t\t||\n");
	    printf("\t\t\t\t\t");
	    printChar('=',34);
	    printf("\n\n");
	    SetColor(12);
	    gotoxy(70, 25);
	    printf(" Developed By Ali Rim Imane");
		gotoxy(58, 6);
		scanf("%s",entrep.username);//scanner username
		gotoxy(58, 7);
		while(s<10)//le password doit contenir au max 10 caractéres 
			{
			    fct1 : entrep.password[s]=getch();//getch() pour scanner le password qui est une chaine de caractéres 
			    p=entrep.password[s];
			    if(p==13)//13 est le code ASCII de la tocuhe ENTRE du clavier
				 break;//si un caractére du password est égale à ENTRER->break
				else if(p==8){//8 est le code ASCII de la tocuhe BACKSPACE du clavier
					s--;//supprimer le dernier caractére 
					printf("\b \b");// \b est un back-space
					//-> \b \b : back-space + espace pour mettre l'étoile * en espace(supprimer*) + back-space pour revenir à la bonne place du curseur
					goto fct1;// sauter vers l'étiquette fct1 pour continer d'écrire le password 
				}
			    else printf("*");// mettre le caractére à * comme sécurité du password d'utilisateur 
			    s++;// incrémentation
		}
		entrep.password[s]='\0';// \0:le caractère de fin de chaîne qui permet d'indiquer à l'ordinateur que la chaîne se termine là
		tp=fopen("Password.bin","r+b");//ouverture du fichier binaire tp en lecture et écriture
		do{
			fread(&entreprise,sizeof(login),1,tp);//lire le fichier dont on a met les données de l'entreprise lors son inscription
			if(!strcmp(entreprise.username,entrep.username))//comparer username de connexion et celui d'inscription pour s'assurer si ce compte a été crée
				break;//càd ce compte n'existe pas
		}while(!feof(tp));
	    if(strcmp(entreprise.username,entrep.username)==0)//on comprend donc qu'il y a déja un compte déjà avec ce username
		{
			if(strcmp(entreprise.password,entrep.password)==0){//si le password de connexion et celui d'inscription sont égaux->connexion avec succée
				system("cls");
				gotoxy(10,3);
				printf("<<<< Loading Please Wait >>>>");
				for(i=0; i<5; i++)
		        {
		            printf("\t(*_*)");
		            Sleep(500);
		        }
		        printf(" \n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
				printf("\n\n\t\t\t\t\t     *                    *");
				printf("\n\n\t\t\t\t\t     *       Welcome %c    *",3);
				printf("\n\n\t\t\t\t\t     *                    *");
				printf("\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
				SetColor(12);
	   			gotoxy(70, 25);
	    		printf(" Developed By Ali Rim Imane");
		    	gotoxy(80,18);
				printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
				getch();
				id_session = entreprise.id_entreprise;         //sauvegarder l'ID de cette entreprise connectée à id_session
				fclose(tp);
				return home_entreprise();
	    	}else{                                //si le password de connexion et celui d'inscription ne sont pas égaux
	    		SetColor(4);
	    		printf("\n\n\t\t\t\tPlease Enter Correct Password\n");
	    		Sleep(3000);
	    		SetColor(45);
	    		fclose(tp);
	    		repetition++;                   // faute lors la connexion donc incrémenter repetition
			}
		}else{
			SetColor(4);
	    	printf("\n\n\t\t\t\tCette username n'existe pas! Verifiez\n");
	    	Sleep(3000);
	    	SetColor(45);
	    	repetition++;                      // faute lors la connexion donc incrémenter repetition
		}
	}
printf("\n\n\n \t\t\t Vous avez essayer plus de 3 tentatives\n");
Sleep(2000);
main();                     //Menu principal pour choisir son identité ( admin ou entreprise)
}


/////////////// Fonction d'affectation d'ID pour chaque entreprise inscrite //////////////////
int id_entreprise(){
	FILE *fp = fopen("Password.bin","a+b");
	login Login;
	long int res;   
	// tester si le fichier est vide
	fseek(fp, 0L, SEEK_END);
	res = ftell(fp);
	if(res == 0){
		fclose(fp);
		return 1;
	}
	else{
		fseek(fp,(long)-sizeof(login), SEEK_END);
		fread(&Login,sizeof(login),1,fp);
		fclose(fp);
		return (Login.id_entreprise + 1);
	}
}


/////////////////// Saisie et enregistrement des informations d'Entreprise /////////////////// 
void nouvl_entreprise(){
	FILE *pf,*pf1;
    Entreprise entreprise;
    login entrepr;
    pf = fopen("Registration.bin","a+b");
    pf1 = fopen("Password.bin","a+b");
    
    if(pf1==NULL){
    	pf1 = fopen("Password.bin","wb"); //Cas ou le fichier n'existe pas
    	if(pf1==NULL)
    	  printf("\aErreurr\n");
	}
    
    if(pf==NULL){
    	pf = fopen("Registration.bin","wb"); //Cas ou le fichier n'existe pas
    	if(pf==NULL)
    	  printf("\aErreurr\n");
    	  else
    	     goto etq; // Saut inconditionnel vers "etq"
	}
       
    else{
    etq:
    	
	    titre();
	    SetColor(6);
	    printf("\n\n\t\t\t");
	    printChar('=',69);
	    printf("\n\t\t\t|| ==> Nom de l\'entreprise :\t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Secteur d\'activite : \t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Tel : \t\t\t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Email : \t\t\t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Adresse : \t\t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Chiffre d\'affaire : \t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Annees d\'experience : \t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Username : \t\t\t\t\t\t   ||\n");
	    printf("\t\t\t|| ==> Password : \t\t\t\t\t\t   ||\n");
	    printf("\t\t\t");
	    printChar('=',69);
	    printf("\n\n");
	    SetColor(12);
	    gotoxy(70, 17);
	    printf(" Developed By Ali Rim Imane");
	    
	    gotoxy(53,6);
	    fflush(stdin);
	    gets(entreprise.nom_entreprise);
	    gotoxy(52,7);
	    fflush(stdin);
	    gets(entreprise.sect_activite);
	    gotoxy(37,8);
	    scanf("%ld",&entreprise.tel_entreprise);
	    gotoxy(39,9);
	    fflush(stdin);
	    gets(entreprise.email_entreprise);
	    gotoxy(41,10);
	    fflush(stdin);
	    gets(entreprise.adresse);
	    gotoxy(51,11);
	    scanf("%ld",&entreprise.CA);
	    gotoxy(53,12);
	    scanf("%ld",&entreprise.annee_experience);
	    gotoxy(42,13);
	    fflush(stdin);
	    gets(entrepr.username);
	    gotoxy(42,14);
	    fflush(stdin);
	    gets(entrepr.password);
	    
	    entreprise.id_entreprise = id_entreprise();
	    entrepr.id_entreprise = entreprise.id_entreprise;
	    id_session = entreprise.id_entreprise;
	    fwrite(&entreprise,sizeof(Entreprise),1,pf);
	    fwrite(&entrepr,sizeof(login),1,pf1);
	    fclose(pf);
	    fclose(pf1);   
		}
		printf("\n\t\t     Felicitations , votre inscription a ete validee avec succes ! Votre id = %d \n",entrepr.id_entreprise);
		getch();
		home_entreprise();
}


int validation_de_postulation(int id_marche,int id_entreprise){
	m_postuler cheack;
	FILE *fp=fopen("postuler.bin","rb");
	while(!feof(fp)){
		fread(&cheack,sizeof(m_postuler),1,fp);
		if(id_marche == cheack.id_marche && id_entreprise == cheack.id_entreprise){
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}

///////////////////////// Fonction pour postuler à Un marché valable /////////////////////////
void postuler(){
	int chx,id_marche;
	char nom[50];
	char accept;
	m_postuler postule;
	FILE *fp = fopen("postuler.bin","ab");
	if(fp==NULL){
		fp= fopen("postuler.bin","wb");
	}
	affichage_marche_cur();          // Affichage abrégé d'informations des marchés courants (valables)
	gotoxy(70,9);
	printChar('=',15);
	printf("Menu");
	printChar('=',15);
	gotoxy(70,10);
	printf("1 - Postuler");
	gotoxy(70,11);
	printf("2 - Revenir au menu");
	gotoxy(70,13);
	printChar('=',34);
	gotoxy(70,15);
	printf("Choix : ");
	scanf("%d",&chx);
	system("cls");
	switch(chx){
		case 1:
			printf("Merci d'entrez ID du marche : ");
			scanf("%d",&id_marche);
			while(etatmarche(id_marche) != 1){
				printf("\n\n\nLe marche n'existe pas dans la liste\n");
				fclose(fp);
				postuler();
			}
			if(validation_de_postulation(id_marche,id_session)){
				printf("\n\n Vous avez deja postuler a ce marche\n\n");
				fclose(fp);
				postuler();
			}
			affichage_marchedetail(id_marche); // Affichage détaillé d'informations du marché saisi (id_marche)
			postule.id_entreprise = id_session;
			postule.id_marche = id_marche;
			system("cls");
			printf("\n\n\n\n\t\t\t\t --> Acceptez vous les exigences du Projet (y/n): ");
			fflush(stdin);                         //flacher l'entrée standard
			accept=getchar();
			if(accept == 'Y' || accept == 'y'){        // accepter pour postuler au marché 
				fwrite(&postule,sizeof(m_postuler),1,fp);  // si oui remplir la structure m_postuler avec l'ID d'entreprise et l'ID du marché dont elle a postulé
				fclose(fp);
				system("cls");
				postuler();
			}else{  // si l'entreprise n'accepte pas 
				system("cls");
				fclose(fp);
				postuler(); // Appel récursif de la fonction postuler()
			}
			system("cls");
		default :
			fclose(fp);
			home_entreprise();
	}
}


/////////////// Fonction d'Affichage des marchés postulés par une Entreprise /////////////////
void marche_postuler(){
	m_postuler postule;
	marche marcher;
	FILE *fp=fopen("postuler.bin","r+b");
	if(fp==NULL){
		fp = fopen("postuler.bin","w+b");
	}
	FILE *fp1=fopen("marche.bin","rb");
	///////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	///////////////////////////////////
	fseek(fp1, 0, SEEK_END);
	long size1 = ftell(fp1);
	fseek(fp1, 0, SEEK_SET);
	///////////////////////////////////
	
	printf("Les Marche Postuler\n");
	
	while(1){
		if(ftell(fp) == size) break;
		fread(&postule,sizeof(m_postuler),1,fp);
		if(id_session == postule.id_entreprise){  // voir si l'entreprise connecté d'id_session a déjà postulé à un marché d'après la structure m_postuler 
			fseek(fp1, 0, SEEK_SET);
			while(1){
				if(ftell(fp1) == size1) break;
				fread(&marcher,sizeof(marche),1,fp1);
				if(marcher.id_marche == postule.id_marche){
					printf("==============Marche id %d ==============\n",marcher.id_marche);
					SetColor(11);
					printf("Nom = %s\n",marcher.nom_marche);
					printf("Secteur D\'activite : %s\n",marcher.secteur);
					printf("Date D\'expiration : %d / %d / %d\n\n",marcher.date_expir.d,marcher.date_expir.m,marcher.date_expir.y);
				}
			}
		}
	}
	fclose(fp);
	fclose(fp1);
	printf("Suivant -> ");
	getch();
	system("cls");
	home_entreprise();
}


/////////////////////// Fonction d'Affichage détaillé de l'entreprise ///////////////////////
void mesinfo_entreprise(){
	
	FILE *fp = fopen("Registration.bin","r+b");
	Entreprise monentreprise;
	
	while(!feof(fp)){
		fread(&monentreprise,sizeof(Entreprise),1,fp);
		if(id_session == monentreprise.id_entreprise){ // comparaison pour trouver les informations enregistrées de l'entreprise connéctée 
			printf("\t\t\t *********************  Mon Entreprise id = %d *******************\n",id_session);
			printf("\t\t\t *                                                              *\n");
			printf("\t\t\t * \t\t\t Id Entreprise : %d \t\t\t*\n",monentreprise.id_entreprise);
			printf("\t\t\t * \t\t\t Nom Entreprise : %s \t\t\t*\n",monentreprise.nom_entreprise);
			printf("\t\t\t * \t\t\t Secteur d'activite : %s  \t\t*\n",monentreprise.sect_activite);
			printf("\t\t\t * \t\t\t Tele Entreprise : 0%ld \t\t\t*\n",monentreprise.tel_entreprise);
			printf("\t\t\t * \t\t\t Adresse Entreprise : %s \t\t*\n",monentreprise.adresse);
			printf("\t\t\t * \t\t\t Chiffre d'affaire Entreprise : %ld \t*\n",monentreprise.CA);
			printf("\t\t\t * \t\t\t Annee Experience : %d\t\t\t*\n",monentreprise.annee_experience);
			printf("\t\t\t *                                                              *\n");
			printf("\t\t\t ****************************************************************\n");
			break;
		}
	}
	fclose(fp);
}

// pas encore commentée ; fct en relat° vc la fct marche_gagne
void info_base_marche(int id){ //prend comme argument le fichier pf et un entier ((id))
	marche mar;
	FILE *pf=fopen("marche.bin","rb");
	if(pf==NULL)
	      printf("\aAttention la liste des marche est vide !!\n");
	else
	{
		while(!feof(pf)){
			fread(&mar,sizeof(marche),1,pf);
		    if(mar.id_marche==id){
		    	SetColor(3);
		    	printf("============== Marche id %d ==============\n",mar.id_marche);
		    	SetColor(11);
				printf("Nom = %s\n",mar.nom_marche);
	            printf("budget = %d\n",mar.budget);
	            printf("date d'expiration = %d / %d / %d \n",mar.date_expir.d,mar.date_expir.m,mar.date_expir.y);
		        fclose(pf);
		        break;
	        }
		}
	}
}

// pas encore commentée
void marche_gagne(){
	m_postuler post;
	system("cls");
	printf("\n \t\t\t\t\t\t Les marches accomplie\n\n\n\n");
	
	FILE *fp = fopen("win.bin","rb");
	if(fp==NULL){
		fp = fopen("win.bin","r+b");
	}
	
	///////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	
	while (1){
		if(ftell(fp) == size) break;
		fread(&post,sizeof(m_postuler),1,fp);
		if(id_session == post.id_entreprise){
			info_base_marche(post.id_marche);
			printf("=========================================\n");
		}
	}
	printf("\n\n==> Suivant");
}



//*****************************************************************************************//


//*********************************** FONCTIONS D'ADMIN ***********************************//

//////////////////////////////// Menu principal pour l'Admin ////////////////////////////////
void home_admin(){
    int i,id_select,id_mar;
    char chx;
    auto_expe();
    system("cls");
    titre();
    printf("\n\t\t\t||\t\t\t1  - Nouveau marche\t\t\t  ||");
    printf("\n\n\t\t\t||\t\t\t2  - Les marches courants \t\t  ||");
    printf("\n\n\t\t\t||\t\t\t3  - Tous Les marches \t\t\t  ||");
    printf("\n\n\t\t\t||\t\t\t4  - Supprimer un marche     \t\t  ||");
    printf("\n\n\t\t\t||\t\t\t5  - les Entreprises \t\t\t  ||");
    printf("\n\n\t\t\t||\t\t\t6  - Ouvertures des Marches \t\t  ||");
    printf("\n\n\t\t\t||\t\t\t7 - Logout \t\t\t\t  ||\n\t\t\t");
    printChar('=',68);
    SetColor(6);
    do{
    	printf("\n\n\t\t\t Merci d'entre votre choix : ");
		scanf("%d",&chx);
	}while(chx<1 || chx>7);
	system("cls");
	switch(chx){
		case 1:
			nouv_marche();             // Creation d'un nouveau marché
			home_admin();
			break;
		case 2:
			affichage_marche_cur();    // Affichage des marchés valables
			gotoxy(70,9);
			printChar('=',15);
			printf("Menu");
			printChar('=',15);
			gotoxy(70,10);
			printf("1 - Details");
			gotoxy(70,11);
			printf("2 - Revenir au menu");
			gotoxy(70,13);
			printChar('=',34);
			gotoxy(70,15);
			printf("Choix : ");
			scanf("%d",&chx);
			switch(chx){
				case 1:
					system("cls");
					gotoxy(40,10);
					printf("Merci de saisir l\'id du marche : ");
					scanf("%d",&id_select);
					while(etatmarche(id_select) != 1){        //Verifier que le marche est courant!
						printf("\t\t\t Le marche n'est pas valable\n");
						system("pause");
						system("cls");
						home_admin();
					}
					system("cls");
					affichage_marchedetail(id_select);       // Affichage des informations détaillées du marché valable saisi
					home_admin();
					break;
				default:
					home_admin();
			}
			break;
		case 3:
			system("cls");
			affichage_marche();             // Affichage abrégé (court) des informations de tous les marchés ( valables et non valables )
			gotoxy(70,9);
			printChar('=',15);
			printf("Menu");
			printChar('=',15);
			gotoxy(70,10);
			printf("1 - Details");
			gotoxy(70,11);
			printf("2 - Revenir au menu");
			gotoxy(70,13);
			printChar('=',34);
			gotoxy(70,15);
			printf("Choix : ");
			scanf("%d",&chx);
			switch(chx){
				case 1:
					system("cls");
					gotoxy(40,10);
					printf("Merci de saisir l\'id du marche : ");
					scanf("%d",&id_select);
					system("cls");
					affichage_marchedetail(id_select);    // Affichage détaillé du marché saisi ( valables et non valables )
					home_admin();
					break;
				default:
					home_admin();
			}
			break;
		case 4:
			printf("Merci de saisie id du marche a supprimer : ");
			scanf("%d",&id_select);
			supp_marche(id_select);          // Suppression manuelle d'un marché saisi
			getch();
			home_admin();
			break;
		case 5:
			afficher_entreprise();           // Affichage détaillé de tous les Entreprises qui ont postulé 
			system("pause");
			home_admin();
			break; 
		case 6:
			marche_terminer();               // Affichage abrégé (court) des marchés non valables 
			gotoxy(70,9);
			printChar('=',15);
			printf("Menu");
			printChar('=',15);
			gotoxy(70,10);
			printf("1 - Ouvrir Un Marche");
			gotoxy(70,11);
			printf("2 - Revenir Au Menu");
			gotoxy(70,13);
			printChar('=',34);
			gotoxy(70,15);
			printf("Choix : ");
			scanf("%d",&chx);
			switch(chx){
				case 1:
					system("cls");
					gotoxy(40,10);
					printf("Merci de saisir l\'id du marche : ");
					scanf("%d",&id_mar);
					while(etatmarche(id_mar) != 0){      // S'assurer si la date du marché a expirée 
						printf("\t\t Ce marche ne peux pas etre ouvert\n");
						system("pause");
						system("cls");
						home_admin();
					}
					system("cls");
					ouverture(id_mar);             // Selection d'une entreperise parmi ceux qui ont postulé au marché ( id_mar)
					home_admin();
					break;
				default:
					home_admin();
			}
			break; 
		default:
			main();
	}
}


/////////////////////////////// Fonction de connexion d'Admin ///////////////////////////////
void admin_login(){
	int repetition=0;
	while(repetition<3){
		login admin;
		char p;
		int s=0,i;
		FILE *tp;
		titre();
	    SetColor(6);
	    printf("\n\n\t\t\t\t\t");
	    printChar('=',34);
	    printf("\n\t\t\t\t\t|| ==> Username :\t\t||\n");
	    printf("\t\t\t\t\t|| ==> Password : \t\t||\n");
	    printf("\t\t\t\t\t");
	    printChar('=',34);
	    printf("\n\n");
	    SetColor(12);
	    gotoxy(70, 25);
	    printf(" Developed By Ali Rim Imane");
		gotoxy(58, 6);
		scanf("%s",admin.username);         //scanner username 
		gotoxy(58, 7);
		while(s<10)
			{
			    fct1 : admin.password[s]=getch();
			    p=admin.password[s];
			    if(p==13)                    // Si le char est la touche ENTRE du clavier
				 break;
				else if(p==8 && s>0){
					s--;
					printf("\b \b");         // supprimer un char
					goto fct1;
				}
			    else printf("*");            
			    s++;
		}
		admin.password[s]='\0';
	    if(strcmp(defaultadmin.username,admin.username)==0)                 // Comparer
		{
			if(strcmp(defaultadmin.password,admin.password)==0){
				system("cls");
				gotoxy(10,3);
				printf("<<<< Loading Please Wait >>>>");
				for(i=0; i<5; i++)
		        {
		            printf("\t(*_*)");
		            Sleep(500);
		        }
		        printf(" \n\n\n\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
				printf("\n\n\t\t\t\t\t     *                    *");
				printf("\n\n\t\t\t\t\t     *       Welcome %c    *",3);
				printf("\n\n\t\t\t\t\t     *                    *");
				printf("\n\n\t\t\t\t\t     *  *  *  *  *  *  *  *");
				SetColor(12);
	   			gotoxy(70, 25);
	    		printf(" Developed By Ali Rim Imane");
		    	gotoxy(80,18);
				printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
				getch();
				fflush(stdin);          // flacher l'entrée standard
				
				return home_admin();
	    	}else{
	    		SetColor(4);
	    		printf("\n\n\t\t\t\tPlease Enter Correct Password\n");
	    		Sleep(3000);
	    		SetColor(45);
	    		repetition++;
			}
		}else{
			SetColor(4);
	    	printf("\n\n\t\t\t\tCette username n'existe pas! Verifiez\n");
	    	Sleep(3000);
	    	SetColor(45);
	    	repetition++;
		}	
	}
	printf("\n\n\n \t\t\t Vous avez essayer plus de 3 tentatives\n");
	sleep(2000);
	main();
}


//////////////////// Saisie et enregistrement des informations du Marché ////////////////////
void nouv_marche(){
	int i;
	marche Marche;
    int num_secteur;
    FILE *ch;
	FILE *fp=fopen("marche.bin","a+b");
	if(fp==NULL){
		fp=fopen("marche.bin","w+b");
	}
	fflush(stdin);
	SetColor(4);
	printf("\n\n\n\t\t\t");
	printChar('=',31);
	printf("New Market");
	printChar('=',32);
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	gotoxy(24,6);
	printf("||   Nom marche : \t\t\t\t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	gotoxy(24,8);
	printf("||   Budget : \t\t\t\t\t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	gotoxy(24,10);
	printf("||   Description :  \t\t\t\t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	gotoxy(24,12);
	printf("||   Date d'expiration :  /  / \t\t\t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	gotoxy(24,14);
	printf("||   le Nom du Fichier de Cahier de Charge :  \t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||\n\t\t\t");
	printChar('=',73);
	gotoxy(42,6);
	gets(Marche.nom_marche);
	gotoxy(38,8);
	scanf("%d",&Marche.budget);
	fflush(stdin);
	gotoxy(43,10);
	gets(Marche.description);
	gotoxy(48,12);
	scanf("%d",&Marche.date_expir.d);
	gotoxy(51,12);
	scanf("%d",&Marche.date_expir.m);
	gotoxy(54,12);
	scanf("%d",&Marche.date_expir.y);
	fflush(stdin);                          // flacher l'entrée standard
	gotoxy(69,14);
	gets(Marche.ch_charge);
	gotoxy(24,16);
	printf("\n\n Suivant ->");
	getch();
	//verification
	system("cls");
	gotoxy(20,3);
	printf("\t\tVeuillez inserer le cahier de cherge vers chemin ==> de ==> programme ==> main\n");
	gotoxy(20,7);
	printf("<<<< Loading Please Wait >>>>");
	for(i=0; i<5; i++)
	{
	    printf("\t(*_*)");
	    Sleep(500);
	}
    Verification:
    do{

    system("cls");
    ch=fopen(Marche.ch_charge,"r");
    if(ch==NULL){
        gotoxy(20,7);
        printf("Ereuur le cahier de charge n\'existe pas ! \n");
        gotoxy(20,8);
        system("cls");
			gotoxy(10,3);
			printf("<<<< Loading Please Wait >>>>");
			for(i=0; i<5; i++)
	        {
	            printf("\t(*_*)");
	            Sleep(500);
	        }
        goto Verification;

    }
    else{
            gotoxy(14,7);
            printf("Le cahier de charge est inserer avec succes ! \n");
    }
    }while(ch==NULL);
	fclose(ch);
	/////////////
    system("cls");
    printf("\n\n\n\t\t\t");
	printChar('=',31);
	printf("New Market");
	printChar('=',32);
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
	printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
    gotoxy(24,6);
    printf("||  1- Informatique / Telecoms \t\t\t\t\t\t||");
    gotoxy(24,7);
    printf("||  2- Finances / Gestion / Comptabilite\t\t\t\t||");
    gotoxy(24,8);
    printf("||  3- Qualite / Securite / Environnement\t\t\t\t||");
    gotoxy(24,9);
    printf("||  4- Electronique / Electricite\t\t\t\t\t||");
    gotoxy(24,10);
    printf("||  5- Transports / Logistique\t\t\t\t\t\t||");
    gotoxy(24,11);
    printf("||  6- Services aux entreprises\t\t\t\t\t\t||");
    gotoxy(24,12);
    printf("||  7- BTP / Materiaux de construction\t\t\t\t\t||");
    gotoxy(24,13);
    printf("||  8-  Machines et equipements / Automobile\t\t\t\t||");
    printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
    printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
    gotoxy(24,16);
    printf("||  Veuillez choisir un secteur d\'activite :  \t\t\t\t||");
    printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||");
    printf("\n\t\t\t||\t\t\t\t\t\t\t\t\t||\n\t\t\t");
	printChar('=',73);
	gotoxy(68,16);
    scanf("%d",&num_secteur);
    do{
        switch(num_secteur){
        case 1: strcpy(Marche.secteur,"Informatique / Telecoms");   break;
        case 2: strcpy(Marche.secteur,"Finances / Gestion / Comptabilite");  break;
        case 3: strcpy(Marche.secteur,"Qualite / Securite / Environnement"); break;
        case 4: strcpy(Marche.secteur,"Electronique / Electricite"); break;
        case 5: strcpy(Marche.secteur,"Transports / Logistique");  break;
        case 6: strcpy(Marche.secteur,"Services aux entreprises"); break;
        case 7: strcpy(Marche.secteur,"BTP / Materiaux de construction"); break;
        case 8: strcpy(Marche.secteur,"Machines et equipements / Automobile");  break;
        default: printf("Veuillez choisir un secteur convenable !!\n"); scanf("%d",&num_secteur);
    }
    }while(num_secteur<1 && num_secteur>8);
    Marche.id_marche = id_marche(fp);
    fseek(fp, 0L, SEEK_END);
    Marche.etat = 1;
    fwrite(&Marche, sizeof(marche), 1, fp);
    fclose(fp);
    auto_expe();
}


/////////////////// Fonction d'affectation d'ID pour chaque marché entré ////////////////////
int id_marche(FILE *fp){
	marche Marche;
	long int res;
	// tester si le fichier est vide
	fseek(fp, 0L, SEEK_END);
	res = ftell(fp);
	if(res == 0){
		return 1;
	}
	else{
		fseek(fp,(long)-sizeof(marche), SEEK_END);
		fread(&Marche,sizeof(marche),1,fp);
		return (Marche.id_marche)+1;
	}
	fclose(fp);
}


///////////////////// Fonction de la suppression automatique d'un marché ////////////////////
void supp_marche(int id_supp){
	marche Marche;
	int rmv;
	FILE *fp = fopen("marche.bin","rb");//ouverture d’un fichier binaire fp en lecture
	FILE *nfp = fopen("nmarche.bin","wb");//ouverture d’un fichier binaire nfp en écriture
	
	/////////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//////////////////////////////////////
	
	while (1) {
		if(ftell(fp) == size) break;
		fread(&Marche,sizeof(marche),1,fp);
		if (Marche.id_marche!=id_supp){
			fwrite(&Marche, sizeof(marche), 1, nfp);//mettre les marchés qu'on ne veut pas supprimer dans le fichier nfp "nmarche.bin"
		}
	}
	fclose(fp);
	fclose(nfp);
	remove("marche.bin");//supprimer le fichier fp "marche.bin"
	rename("nmarche.bin","marche.bin");// renommer le fichier "nmarcher.bin" en "marche.bin"
	printf("Le marche a ete supprimer avec succe\n");
}


//////////////////////////////// Affichage abrégé du marché /////////////////////////////////
void affichage_marche(){
	marche Marche;
	FILE *fp = fopen("marche.bin","rb");
	
	///////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	
	while (1){
		if(ftell(fp) == size) break;
		fread(&Marche,sizeof(marche),1,fp);
		SetColor(3);
		printf("============== Marche id %d ==============\n",Marche.id_marche);
		SetColor(11);
		printf("Nom = %s\n",Marche.nom_marche);
		printf("Secteur D\'activite : %s\n",Marche.secteur);
		printf("Date D\'expiration : %d / %d / %d\n\n",Marche.date_expir.d,Marche.date_expir.m,Marche.date_expir.y);
		printf("etat : %d\n\n",Marche.etat);
	}
	fclose(fp);
}


//////////////////////////// Affichage abrégé du marché valable /////////////////////////////
void affichage_marche_cur(){
	marche Marche;
	FILE *fp = fopen("marche.bin","rb");
	
	///////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	
	while (1){
		if(ftell(fp) == size) break;
		fread(&Marche,sizeof(marche),1,fp);
		SetColor(3);
		if(Marche.etat == 1){ //s'assurer si le marché est valable
			printf("============== Marche id %d ==============\n",Marche.id_marche);
			SetColor(11);
			printf("Nom = %s\n",Marche.nom_marche);
			printf("Secteur D\'activite : %s\n",Marche.secteur);
			printf("Date D\'expiration : %d / %d / %d\n\n",Marche.date_expir.d,Marche.date_expir.m,Marche.date_expir.y);
		}
	}
	fclose(fp);
}


//////////////////////////// Affichage détaillé du marché valable ///////////////////////////
void affichage_marchedetail(int id_affichage){
	char chx;
	marche Marche;
	FILE *fp = fopen("marche.bin","rb");
	while ( !feof(fp) ){
		fread(&Marche,sizeof(marche),1,fp);
		if (Marche.id_marche==id_affichage){
			printf("\n========== Marche id %d ==========\n",Marche.id_marche);
			printf("\t Secteur D\'activite : %s\n",Marche.secteur);
			printf("\t Nom = %s\n",Marche.nom_marche);
			printf("\t Budget : %d\n",Marche.budget);
			printf("\t Date D\'expiration : %d / %d / %d\n",Marche.date_expir.d,Marche.date_expir.m,Marche.date_expir.y);
			printf("\t Ouvrir le Cahier de Charge (y/n) : ");
			scanf(" %c",&chx);
			if(chx == 'y' || chx == 'Y'){
				system(Marche.ch_charge);
			}
			break;
		}
	}
	fclose(fp);
}


///// Fonction de comparaison entre la date d'expiration du marché avec la date actuelle ////
int date_cmp(date d1,date d2) {
 if (d1.d == d2.d && d1.m == d2.m && d1.y ==d2.y)
    return 0;
 else if (d1.y > d2.y || d1.y == d2.y && d1.m > d2.m || d1.y == d2.y && d1.m == d2.m && d1.d > d2.d)
    return 1;
 else return -1;
}


/////////////////////// Affichage des informations d'une entreprise //////////////////////////
void affichage_entreprise(int id_entreprise){
	
	Entreprise entreprise;
	
	FILE *fp = fopen("Registration.bin","r");           // Ouvrir le fichier Registration.bin en mode lecture (r) pour extraire les donnés de l'entreprise
	if(fp == NULL){
		fp = fopen("Registration.bin","r+");
	}
	
	///////////////////////////////////                // Determiner la derniere position du fichier Registration.bin
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	
	while (1){
		if(ftell(fp) == size) break;                   // Arrete la boucle while a la fin du fichier
		fread(&entreprise,sizeof(Entreprise),1,fp);
		SetColor(3);
		if(entreprise.id_entreprise == id_entreprise){
			printf("============== Entreprise %s  id = %d ==============\n",entreprise.nom_entreprise,entreprise.id_entreprise);
			SetColor(11);
			printf("Nom = %s\n",entreprise.nom_entreprise);
			printf("Secteur D\'activite : %s\n",entreprise.sect_activite);
			printf("Chiffre D\'affaire : %d\n",entreprise.CA);
			printf("Tele : 0%ld\n",entreprise.tel_entreprise);
			printf("Adresse : %s\n",entreprise.adresse);
			printf("Annees D\'experience : %d ans\n\n",entreprise.annee_experience);
			break;	
		}
	}
	fclose(fp);
}


//////////////////////////////////// Affichage de la File ////////////////////////////////////
void affichage(File *file){
	Element *current = file->premier;
	while(current != NULL){                      // boucle while jusqu'a la fin de la File
		affichage_entreprise(current->nombre);
		current = current->suivant;
	}
}


//////////////////////// Fonction d'affichage détaillé d'Entreprise /////////////////////////
void afficher_entreprise(){
	
	Entreprise entreprise;
	
	FILE *fp = fopen("Registration.bin","r");
	if(fp == NULL){
		fp = fopen("Registration.bin","r+");
	}
	
	///////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	
	while (1){
		if(ftell(fp) == size) break;
		fread(&entreprise,sizeof(Entreprise),1,fp);
		SetColor(3);
		printf("============== Entreprise %s  id = %d ==============\n",entreprise.nom_entreprise,entreprise.id_entreprise);
		SetColor(11);
		printf("Nom = %s\n",entreprise.nom_entreprise);
		printf("Secteur D\'activite : %s\n",entreprise.sect_activite);
		printf("Chiffre D\'affaire : %d\n",entreprise.CA);
		printf("Tele : 0%ld\n",entreprise.tel_entreprise);
		printf("Adresse : %s\n",entreprise.adresse);
		printf("Annees D\'experience : %d ans\n\n",entreprise.annee_experience);
	}
	fclose(fp);
}


////// Fonction d'Affichage abrégé des marchés dont la date est expirée ( non valable) //////
void marche_terminer(){
	marche Marche;
	FILE *pt = fopen("marche.bin","rb");
	
	///////////////////////////////////
	fseek(pt, 0, SEEK_END);
	long size = ftell(pt);
	fseek(pt, 0, SEEK_SET);
	///////////////////////////////////
	
	while (1){
		if(ftell(pt) == size) break;
		fread(&Marche,sizeof(marche),1,pt);
		SetColor(3);
		if(Marche.etat == 0){ // si l'état du marche = 0 càd que sa date a expirée 
			printf("============== Marche id %d ==============\n",Marche.id_marche);
			SetColor(11);
			printf("Nom = %s\n",Marche.nom_marche);
			printf("Secteur D\'activite : %s\n",Marche.secteur);
		}
	}
	fclose(pt);
}


////////////// Fonction pour changer l'etat du marché dont la date est expirée //////////////
//pas encore commentée
void auto_expe(){
	marche Marche;
	date current;
	int cmp;
	FILE *fp = fopen("marche.bin","rb");
	FILE *nfp = fopen("nmarche.bin","wb");
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	current.y = tm.tm_year + 1900 , current.m = tm.tm_mon + 1 , current.d = tm.tm_mday;
  	
	/////////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//////////////////////////////////////
	
	while (1) {
		if(ftell(fp) == size) break;
		fread(&Marche,sizeof(marche),1,fp);
		cmp = date_cmp(Marche.date_expir,current);
		if (cmp <= 0){
			Marche.etat = 0;
			fwrite(&Marche, sizeof(marche), 1, nfp);
		}else fwrite(&Marche, sizeof(marche), 1, nfp);
	}
	fclose(fp);
	fclose(nfp);
	remove("marche.bin");
	rename("nmarche.bin","marche.bin");
}


/////////////////////// Fonction qui détécte l'etat d'un marche saisi ///////////////////////
int etatmarche(int id_marche){
	marche Marche;
	FILE *fp = fopen("marche.bin","r+b");
	while(!feof(fp)){
		fread(&Marche,sizeof(marche),1,fp);
		if(id_marche == Marche.id_marche){
			fclose(fp);
			return Marche.etat;
		}
	}
	fclose(fp);
	return -1;// si cet id_marche saisi ne revient pas à un marché existant
}


//Fonction pour s'assurer si l'entreprise d'id_entreprise a postuleé au marché d'id_marche//
//pas encore commentée
int cheack_apply(int id_marche,int id_entreprise){
	FILE *fp = fopen("postuler.bin","rb");
	m_postuler check;
	while(!feof(fp)){
		fread(&check,sizeof(m_postuler),1,fp);
		if(check.id_marche == id_marche && check.id_entreprise == id_entreprise){ 
			fclose(fp);
			return 1; //déjà postulé
		}
	}
	fclose(fp);
	return 0; 
}


//pas encore commentée
void ouverture(int id_marche){
	int chx,id_g;
	FILE *fw;
	File *file = (File*)malloc(sizeof(File));
	file->premier = (Element*)malloc(sizeof(Element));
	file->premier = NULL;
	FILE *fp = fopen("postuler.bin","rb");
	m_postuler logi;
	
	///////////////////////////////////
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	///////////////////////////////////
	while(1){
		if(ftell(fp) == size) break;
		fread(&logi,sizeof(m_postuler),1,fp);
		SetColor(3);
		if(logi.id_marche == id_marche){
			enfiler(file,logi.id_entreprise);
		}
	}
	fclose(fp);
	affichage(file);
	gotoxy(70,9);
	printChar('=',15);
	printf("Menu");
	printChar('=',15);
	gotoxy(70,10);
	printf("1 - L entreprise gagnante\n");
	gotoxy(70,11);
	printf("2 - Revenir au menu");
	gotoxy(70,13);
	printChar('=',34);
	gotoxy(70,15);
	printf("Choix : ");
	scanf("%d",&chx);
	switch(chx){
		case 1: fw = fopen("win.bin","a+b");
				if(fw == NULL){
					fw = fopen("win.bin","w+b");
				}
				system("cls");
				gotoxy(40,10);
				printf("Merci d Entrer l ID de l entreprise gagnante : \n");
				gotoxy(60,11);
				printf("----");
				gotoxy(60,12);
				printf("| ");
				gotoxy(63,12);
				printf("|");
				gotoxy(60,13);
				printf("----"); 
				gotoxy(61,12);
				scanf("%d",&id_g);
				while(!(cheack_apply(id_marche,id_g))){
					gotoxy(40,14);
					SetColor(4);
					printf("L'entreprise %d saisie n'a pas postuler au marche %d",id_g,id_marche);
					SetColor(3);
					gotoxy(61,12);
					scanf("%d",&id_g);
				}
		    	system("cls");
		    	gotoxy(40,10);
		    	printf("L entreprise %d gagne le marche %d  ",id_g,id_marche);
		    	Sleep(2000);	
		    	logi.id_marche = id_marche;
		    	logi.id_entreprise = id_g;
			 	fwrite(&logi,sizeof(m_postuler),1,fw);
			 	fclose(fw);
			 	envoi_email_au_gagnant(id_g,id_marche);
			 	//fw = fopen("win.bin","rb");
			 	//fread(&logi,sizeof(m_postuler),1,fw);
			 	//fclose(fw);
			 	//printf("%d => %d\n",logi.id_entreprise,logi.id_marche);
			 	system("pause");
			 	system("cls");
				home_admin();
				break;
		default:
				home_admin();
	}	
}

void envoi_email_au_gagnant(int id_entreprise,int marche_gagne){
	FILE *fp = fopen("Registration.bin","r");
	Entreprise entreprise;
	char parameters[100] = {"C:/Users/User/Documents/Mini_Projets/SD_Mini_Projet/send_email/init.py "};
	while(!feof(fp)){
		fread(&entreprise,sizeof(Entreprise),1,fp);
		if(entreprise.id_entreprise == id_entreprise){
			break;
		}
	}
	strcat(parameters,entreprise.email_entreprise);
	strcat(parameters," ");
	strcat(parameters,entreprise.nom_entreprise);
	system(parameters);
	system("C:/Users/User/Documents/Mini_Projets/SD_Mini_Projet/send_email/analysis1.py");
}

//*****************************************************************************************//
