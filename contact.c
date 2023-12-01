
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
char nom[20];
int ntlf;
char* adresse[30];
char* email[30];
}contact ;
typedef struct cellule {
contact val;
struct cellule * next;
}cellule ;


typedef  cellule*liste;

void initialiser_liste(FILE *fichier,liste* L){
*L=NULL;
  if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }
rewind(fichier);
cellule* c,*parcours;
while (!feof(fichier)){

c= malloc(sizeof(cellule) );
fscanf(fichier,"%[^\n-]-%d-%[^\n-]-%[^\n-]\n",c->val.nom,&(c->val.ntlf),c->val.adresse,c->val.email);
            c->next=NULL;
if (*L == NULL)
{

*L=c;

}
else
{

parcours = *L;
while ( parcours->next !=NULL)
{
parcours = parcours->next ;
}
parcours->next= c ;


 }

    }

}
void lister_contacts (liste * L){
cellule * p ;

p = *L ;
printf("       Nom          \tNumero tf\tAdresse                       \tEmail                         \n");
while (p!=NULL)
{

 printf("%-20s\t%-8d\t%-30s\t%-30s\n", p->val.nom, p->val.ntlf, p->val.adresse,p->val.email);
p = p->next;
}
printf("\n");
}


void lire_contact(contact * c){
    char buffer[20];  // Assurez-vous que la taille du tampon est suffisamment grande
    do{
printf("donner nom (avec longeur sup a 3)\n");
scanf(" %[^\n]",c->nom);
}while(strlen((char*)c->nom)<3);

    do{
printf("donner email qui contient @ et . et longeur sup a 5 \n");
scanf(" %[^\n]",c->email);
}while(!strchr((char*)c->email,'@') || !strchr((char*)c->email, '.') || strlen((char*)c->email)<5);
    do{
printf("donner numero tlf qui contient 8 chiffre\n");
scanf("%d",&c->ntlf);
sprintf(buffer, "%d",c->ntlf);
}while(strlen(buffer)!=8);
  do{
printf("donner adresse avec longeur sup a 5\n");
scanf(" %[^\n]",c->adresse);
}while(strlen((char*)c->adresse)<5);

}


void ajouter_contact(FILE *fichier,liste* L){
cellule *c,*parcours;
c=(cellule*) malloc(sizeof(cellule) );
lire_contact(&c->val);
fprintf(fichier,"%s-%d-%s-%s\n",c->val.nom,c->val.ntlf,c->val.adresse,c->val.email);
printf("=>contacte enregistrer avec succes \n");

if (*L == NULL)
{
printf("L NULL");
*L=c;

}
else
{

parcours = *L;
while ( parcours->next !=NULL)
{
parcours = parcours->next ;
}
parcours->next= c ;
printf("=>contacte ajouter a la liste avec succes \n");
 }

fclose(fichier);
}

void search_contact(liste* L){

 printf("search_contact");
}
void edit_contact(FILE *fichier,liste* L){
 printf("edit_contact");
}
void delete_contact(FILE *fichier,liste* L){
 printf("delete_contact");
}
int main(){
 FILE *fichier=fopen("contacts.txt", "a+");
liste L;

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
initialiser_liste(fichier,&L);

int s,q=0;
while(q==0){
    printf("**** welcome to contact managment system ****\n");
    printf("                MAIN MENU\n");
    printf("----------------------------\n");
    printf("[1] add a new contact\n");
    printf("[2] list all contacts\n");
    printf("[3] search for contact\n");
     printf("[4] edit a contact\n");
    printf("[5] delete a contact\n");
     printf("[0] Exit\n");
      printf("----------------------------\n");
      printf("Enter your choice\n");
      scanf("%d",&s);
      switch(s){
         case 1: ajouter_contact(fichier,&L); break;
         case 2:lister_contacts(&L); break;
         case 3:search_contact(&L); break;
         case 4:edit_contact(fichier,&L); break;
         case 5: delete_contact(fichier,&L); break;
         case 0: q=1; break;
         default : printf("merci de choisir depuis le menu \n");


          }





}
 fclose(fichier);
 return 0;
}
