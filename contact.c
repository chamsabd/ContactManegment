
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//for ftruncate
#include <unistd.h>
//for isdigit
#include <ctype.h>
typedef struct {
char nom[20];
int ntlf;
char* adresse[30];
char* email[30];
}contact ;
typedef struct cellule {
struct cellule * prev;
contact val;
struct cellule * next;
}cellule ;


typedef  cellule*liste;
//hathi bech ta5ou les contact ili fil fichier w t7othoum fil liste chainee
void initialiser_liste(FILE *fichier,liste* L){
*L=NULL;
  if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        exit(1);
    }
rewind(fichier);

cellule* c,*parcours;
cellule* prev;
prev=NULL;
while (!feof(fichier)){

c=(cellule *) malloc(sizeof(cellule) );
if(fscanf(fichier,"%[^\n-]-%d-%[^\n-]-%[^\n-]\n",c->val.nom,&(c->val.ntlf),c->val.adresse,c->val.email)==4){
            c->next=NULL;
            c->prev=prev;
            prev=c;

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

}

//hathi bech taffichi les contact el kol
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
int digit_check(char key[])
{
    for(int i = 0; i < strlen(key); i++)
    {
        if(isdigit(key[i])==0)
        {
            return 0;
        }
    }
    return 1;
}

//hathi bech ta9ra el contact ili 3taha el utilisateur w thabet ili houma s7a7
void lire_contact(contact * c){
    char buffer[20];  // Assurez-vous que la taille du tampon est suffisamment grande
    do{
            printf("la caractere - n'est pas supporter merci d'eviter\n");
printf("donner nom (avec longeur sup a 3)\n");
scanf(" %[^\n]",c->nom);
}while(strlen((char*)c->nom)<3 || strchr((char*)c->nom,'-'));

    do{
printf("donner email qui contient @ et . et longeur sup a 5 \n");
scanf(" %[^\n]",c->email);
}while(!strchr((char*)c->email,'@') || !strchr((char*)c->email, '.') || strlen((char*)c->email)<5|| strchr((char*)c->email,'-'));
    do{

printf("donner numero tlf qui contient 8 chiffre\n");
scanf("%s",buffer);
if(digit_check(buffer))
sscanf(buffer, "%d", &c->ntlf);

}while(!digit_check(buffer)||strlen(buffer)!=8);
  do{
printf("donner adresse avec longeur sup a 5\n");
scanf(" %[^\n]",c->adresse);
}while(strlen((char*)c->adresse)<5|| strchr((char*)c->adresse,'-'));

}

//hathi bech tajouti el contact fi a5er el liste chainne  w tzidou zada fil fichier
void ajouter_contact(FILE *fichier,liste* L){
cellule *c,*parcours;
c=(cellule*) malloc(sizeof(cellule) );
printf("-------------New Contact--------------\n");
lire_contact(&c->val);
fprintf(fichier,"%s-%d-%s-%s\n",c->val.nom,c->val.ntlf,c->val.adresse,c->val.email);

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
printf("contacte enregistrer avec succes \n");
 }

fclose(fichier);
}
//hathi bech tlawej ala contact 7asm num tlf w traja3ou w jedna * fi type de retour 5ater el contact ili bech traj3ou n7ebou nbadlou fih
cellule* find_contact(liste* L ){
    int ntlf;
printf("donner le ntlf du contact a chercher\n");
scanf("%d",&ntlf);

   cellule * parcours;
if (*L == NULL)
{

return NULL;

}
else
{

parcours = *L;

while (parcours !=NULL  && parcours->val.ntlf!=ntlf)
{

parcours = parcours->next ;

}
if(parcours==NULL){
        printf("ce not found\n");
    return NULL;}
return parcours;
}}
//hathi bech ta5ou find contact w tafichih kanou mawjoud makanech t9olek contact n'existe pas
void search_contact(liste* L ){
    cellule* p;
p=find_contact(L);
if(p==NULL){
    printf("contact dosen't exist\n");
}else{
printf("       Nom          \tNumero tf\tAdresse                       \tEmail                         \n");


 printf("%-20s\t%-8d\t%-30s\t%-30s\n", p->val.nom, p->val.ntlf, p->val.adresse,p->val.email);

}

}
//hathi bech ta5ou el find contact w kan l9atou t3ajet l lire contact bech hakaka tbadel fil les information mta3ou
//w ba3ed tfasa5 el fichier el kol w t3awed t3amrou bel liste chainee
void edit_contact(FILE *fichier,liste* L){
  cellule* p;
p=find_contact(L);
if(p==NULL){
    printf("contact dosen't exist\n");
}else{
lire_contact(&p->val);

    ftruncate(fileno(fichier), 0);
    rewind(fichier);
p = *L;
while ( p!=NULL)
{
fprintf(fichier,"%s-%d-%s-%s\n",p->val.nom,p->val.ntlf,p->val.adresse,p->val.email);

p= p->next ;
}

printf("contacte modefier avec succes \n");
 }




}




//hathi bech ta5ou el find contact w kan l9atou bech tfas5ou mn liste channe ya3ni el c.prev.next=c.next w ba3ed ta3mel free(c)
//w ba3ed tfasa5 el fichier el kol w t3awed t3amrou bel liste chainee
void delete_contact(FILE *fichier,liste* L){
   cellule* p;
p=find_contact(L);
if(p==NULL){
    printf("contact dosen't exist\n");
}else{
p->next=p->prev;

    ftruncate(fileno(fichier), 0);
    rewind(fichier);
p = *L;
while ( p!=NULL)
{
fprintf(fichier,"%s-%d-%s-%s\n",p->val.nom,p->val.ntlf,p->val.adresse,p->val.email);

p= p->next ;
}
free(p);

printf("contacte supprimer avec succes \n");
 }

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
char n;
while(q==0){
       system("cls");
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
         case 1: ajouter_contact(fichier,&L);
    system("Pause");    system("cls"); break;
         case 2:lister_contacts(&L);
  system("Pause");       system("cls");break;
         case 3:search_contact(&L);
  system("Pause");       system("cls");break;
         case 4:edit_contact(fichier,&L);
   system("Pause");             system("cls"); break;
         case 5: delete_contact(fichier,&L);
    system("Pause");    system("cls"); break;
         case 0: q=1; break;
         default : printf("merci de choisir depuis le menu \n");


          }





}
 fclose(fichier);
 return 0;
}
