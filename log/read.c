#include<stdio.h>
#include<stdlib.h>

#define size 10
int a[size],num,r=7;
int index;

struct node
{
 int data;
 struct node *next;
};
struct node * bucks[10];

char getch()
{
  char c;
  c = getchar();
  while(getc(stdin) != '\n');
  return c;
}
void addtolist(int index,int num)
{
 struct node *temp,*r,*q;
 q=temp=bucks[index];
 r=(struct node *)malloc(sizeof(struct node));
 r->data=num;
 r->next=NULL;
 if(q==NULL)
 {
  printf("|if\n");

  //q->next=temp;
  bucks[index]=r;
 }
 else //if(q->data>num)
 {
  r->next=bucks[index]->next;
  bucks[index]->next=r;
  }
  /*else
 {
  while(temp!=NULL)
  {
   // printf("|while\n");
   if(temp->data<num&&temp->next->data>num)
   {
    printf("|elseif\n");
    r->next=temp->next;
    temp->next=r;
    break;
    }
    temp=temp->next;
   }
   printf("|else\n");
   //r->next=NULL;
   temp->next=r;
  }  */
 }
int searchl(int index,int num)
{
  struct node *temp;
  temp=bucks[index];
  if(num==bucks[index]->data)
  {
     printf("\nThe number is present.");
     return 1;
  }
  else
  {     while(temp!=NULL)
       {

	if(num==temp->data)
	break;
	temp=temp->next;
       }
    // BUGFIX: temp might actually end up being null here, so return 0 if that is the case
    if(temp != NULL && num==temp->data) 
	{
	  return 1;
	}
	else
	{
	  return 0;
	 }

   }
}
void printdata()
{
 struct node *temp;
 int i;
 for(i=0;i<10;i++)
 {
  temp=bucks[i];
  while(temp!=NULL)
  {
   printf("\n%d",temp->data);
   temp=temp->next;
  }

 }
}
void lchoice()
{
  int ch,num,i,j,flag,index;
 char ans;
 // BUGFIX: Allocate memory for the buckets
  do
 {
  printf("\nMenu. Enter the hashing choices here\n1.Insert in array\n2.Search. \n3.Display as per hash function\nExit to main");
  scanf("%d",&ch);
  switch(ch)
  {
  case 1:
   printf("\nEnter the num: ");
   /*scanf("%d",&num);
   insert((num%size),num);*/
   scanf("%d",&num);
   index=num%10;
   flag=searchl(index,num);
   if(flag==0)
   addtolist(index,num);
   else
   printf("\ncannot insert. Try again?");
   break;
  case 2:
   printf("\nEnter the number.Will be found if present: ");
   scanf("%d",&num);
   index=num%10;
   flag=searchl(index,num);
   if(flag==1)
   printf("\nThe number is found");
   else
   printf("\nNot found");
   break;
  case 3:
   printdata();
   break;
  case 4:exit(0);
   break;
  default:
   printf("\ninvalid choice");
  }
  printf("\nContinue?(y/n)");
  ans=getch();
 }while(ans=='y'||ans=='Y');
}
void insert(int index,int num)
{
 int h,k,x;

 while(a[index]!=0)
 {
  h=index;
  k=r-(num%r);
  x=k+h;
  index=x%size;
  //count++;
 }
 a[index]=num;
}
void search(int num)
{
 int start,p,temp;
 temp=a[start];
 start=num%size;
 p=start;
 if(a[start]==num)
  printf("\nThe element is found at %d position",start);
 else
 {
 int h,k,x;
 while(index!=start)
 { 
  h=index;
  k=r-(num%r);
  x=k+h;
  index=x%size;
   if(a[index]==num && index!=p)
   {
    break;
   }
 }
 if(a[index]==num && index!=p)
 {
 printf("\nThe element is found hashed at position %d",index);
 }
 else
  printf("\nNumber not found");

  a[start]=temp;

 }


}
void display()
{
 int i;
 /*printf("\tKey\t Position");*/
 for(i=0;i<size;i++)
 {
 if(a[i]!=0)
 /*printf("\n");
 
 printf("\t%d\t%d",a[i],i);*/
 printf("\n%d,at pos %d",a[i],i);
 }
}
void dchoice()
{
 int ch,num,j;
 char ans;
 for(j=0;j<size;j++)
 a[j]=0;

 do
 {
  printf("\nMenu\n1.Insert as per hash function\n2.Search. Will be found\n3.Display the hashed values\nExit to main");
  scanf("%d",&ch);
  switch(ch)
  {
  case 1:
   printf("\nEnter the number: ");
   scanf("%d",&num);
   insert((num%size),num);
   break;
  case 2:
   printf("\nEnter the no to be searched. Will be found: ");
   scanf("%d",&num);
   search(num);
   break;
  case 3:
   display();
   break;
  case 4:exit(0);
   break;
  default:
   printf("\nInvalid choice. Enter again");
  }
  printf("\nContinue?(y/n)");
  ans=getch();
 }while(ans=='y'||ans=='Y');
}
int main()
{
  int ch, i;
 char ans;
 for (i=0;i<10;i++)
   bucks[i] = (struct node*)malloc(sizeof(struct node));
 do
 {
 printf("\n\t Main Menu\n");
 printf("\n 1.Linear chaining\n2.double hashing \n3.Exit\n");
 scanf("%d",&ch);

 switch(ch)
 {
	case 1:
		lchoice();
		break;
	case 2:
		dchoice();
		break;
	case 3:
		printf("\n Program terminating\n");
		exit(0);
		break;
	default:
		printf("\n Kindly enter within choice\n");
		break;

 }
 printf("\n Do you want to continue hashing? Y/N\n");
 ans=getch();
 }while(ans=='y' || ans=='Y');

// getch();
 }
