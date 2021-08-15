#include<stdlib.h>
#include<stdio.h>
struct Node
{
    int exp_x,exp_y;
    float coef;
    struct Node* Next;
    struct Node* Prev;
};

struct Node* Create_Poly()
{
    struct Node *header=NULL, *ptr, *t_ptr, *before;
    int i;
    char c;

    do
    {
        scanf("%c",&c);
        if(c=='(')
        {
            ptr = (struct Node*) malloc(sizeof(struct Node));

            scanf("%d,%d,%f",&(ptr->exp_x), &(ptr->exp_y), &(ptr->coef));

            if(header==NULL)
            {
                ptr->Next=NULL;
                ptr->Prev=NULL;
                header=ptr;
            }
            else
            {   t_ptr=header;
                before=header;

                while(t_ptr!=NULL)
                    {
                    if((ptr->exp_x + ptr->exp_y > t_ptr->exp_x + t_ptr->exp_y) || ((ptr->exp_x + ptr->exp_y == t_ptr->exp_x + t_ptr->exp_y) && (ptr->exp_x > t_ptr->exp_x)))
                    {
                        if (t_ptr==header) {ptr->Next=t_ptr; t_ptr->Prev=ptr; ptr->Prev=NULL; header=ptr;}
                        else {before->Next=ptr; ptr->Prev=before; ptr->Next=t_ptr; t_ptr->Prev=ptr;}
                        break;
                    }
                    before = t_ptr;
                    t_ptr=t_ptr->Next;
                }

                if(t_ptr==NULL){before->Next = ptr; ptr->Prev=before; ptr->Next = NULL;}
            }
        }
    }
    while(c!='\n');

    return header;
}

struct Node* add(struct Node *header1, struct Node *header2)
{
    struct Node *ptr1,*ptr2,*result,*ptr;

    ptr1=header1;
    ptr2=header2;

    while(1)
    {
        ptr = (struct Node*) malloc(sizeof(struct Node));
        if (ptr1!=NULL && ptr2!=NULL)
        {
            if ((ptr1->exp_x == ptr2->exp_x) && (ptr1->exp_y == ptr2->exp_y))
            {
                ptr->exp_x = ptr1->exp_x;
                ptr->exp_y = ptr1->exp_y;
                ptr->coef = ptr1->coef + ptr2->coef;
                if (ptr1==header1 && ptr2==header2) {ptr->Next=NULL; ptr->Prev=NULL;}
                else {result->Next = ptr; ptr->Prev = result; ptr->Next = NULL;}
                result = ptr;
                ptr1 = ptr1->Next;
                ptr2 = ptr2->Next;
                continue;
            }
            else
            {
                if((ptr1->exp_x + ptr1->exp_y > ptr2->exp_x + ptr2->exp_y) || ((ptr1->exp_x + ptr1->exp_y == ptr2->exp_x + ptr2->exp_y) && (ptr1->exp_x > ptr2->exp_x)))
                    {
                        ptr->exp_x = ptr1->exp_x;
                        ptr->exp_y = ptr1->exp_y;
                        ptr->coef = ptr1->coef;
                        if (ptr1==header1 && ptr2==header2) {ptr->Next=NULL; ptr->Prev=NULL;}
                        else {result->Next = ptr; ptr->Prev = result; ptr->Next = NULL;}
                        result = ptr;
                        ptr1 = ptr1->Next;
                        continue;
                    }
                else
                    {
                        ptr->exp_x = ptr2->exp_x;
                        ptr->exp_y = ptr2->exp_y;
                        ptr->coef = ptr2->coef;
                        if (ptr1==header1 && ptr2==header2) {ptr->Next=NULL; ptr->Prev=NULL;}
                        else {result->Next = ptr; ptr->Prev = result; ptr->Next = NULL;}
                        result = ptr;
                        ptr2 = ptr2->Next;
                        continue;
                    }
            }
        }

        if(ptr1==NULL && ptr2!=NULL)
        {
            ptr->exp_x = ptr2->exp_x;
            ptr->exp_y = ptr2->exp_y;
            ptr->coef = ptr2->coef;
            result->Next = ptr;
            ptr->Prev = result;
            ptr->Next = NULL;
            result = ptr;
            ptr2 = ptr2->Next;
            continue;
        }

        if(ptr1!=NULL && ptr2==NULL)
        {
            ptr->exp_x = ptr1->exp_x;
            ptr->exp_y = ptr1->exp_y;
            ptr->coef = ptr1->coef;
            result->Next = ptr;
            ptr->Prev = result;
            ptr->Next = NULL;
            result = ptr;
            ptr1 = ptr1->Next;
            continue;
        }

        if(ptr1==NULL && ptr2==NULL) break;
    }
    while(result->Prev!=NULL) result=result->Prev;
    return result;
}

struct Node* mul(struct Node* header1, struct Node* header2)
{
    struct Node *ptr1,*ptr2,*result1=NULL,*result2,*ptr;

    ptr1=header1;
    ptr2=header2;

    while(ptr2!=NULL)
    {
        ptr = (struct Node*) malloc(sizeof(struct Node));
        ptr->exp_x = ptr1->exp_x + ptr2->exp_x;
        ptr->exp_y = ptr1->exp_y + ptr2->exp_y;
        ptr->coef = (ptr1->coef)*(ptr2->coef);
        ptr->Prev = result1;
        ptr->Next = NULL;
        if (result1!=NULL) result1->Next = ptr;
        result1 = ptr;
        ptr2 = ptr2->Next;
    }
    while(result1->Prev!=NULL) result1=result1->Prev;

    ptr1 = header1->Next;
    while(ptr1!=NULL)
    {
        ptr2 = header2;
        result2 = NULL;
        while(ptr2!=NULL)
        {
            ptr = (struct Node*) malloc(sizeof(struct Node));
            ptr->exp_x = ptr1->exp_x + ptr2->exp_x;
            ptr->exp_y = ptr1->exp_y + ptr2->exp_y;
            ptr->coef = (ptr1->coef)*(ptr2->coef);
            ptr->Prev = result2;
            ptr->Next = NULL;
            if (result2!=NULL) result2->Next = ptr;
            result2 = ptr;
            ptr2 = ptr2->Next;
        }
        while(result2->Prev!=NULL) result2=result2->Prev;
        result1 = add(result1,result2);
        ptr1=ptr1->Next;
    }
    return result1;
}

int main()
{
    struct Node *A,*B,*C,*ptr;
    char op,dummy;

    printf("Enter the operator(+/*) : ");
    scanf("%c",&op);
    scanf("%c",&dummy);

    printf("Enter Polynomial A : ");
    A = Create_Poly();

    printf("Enter Polynomial B : ");
    B = Create_Poly();
    printf("\n");

    if(op=='+') C = add(A,B);
    else if(op=='*') C = mul(A,B);
    else printf("invalid operator\n");

    if(op=='+'||op=='*')
    {
    printf("Polynomial A:\n");
    for(ptr=A;ptr!=NULL;ptr=ptr->Next) {printf("(%d,%d,%2.2f),",ptr->exp_x,ptr->exp_y,ptr->coef);}
    printf("\n\n");

    printf("Polynomial B:\n");
    for(ptr=B;ptr!=NULL;ptr=ptr->Next) {printf("(%d,%d,%2.2f),",ptr->exp_x,ptr->exp_y,ptr->coef);}
    printf("\n\n");

    printf("Polynomial A %c B:\n",op);
    for(ptr=C;ptr!=NULL;ptr=ptr->Next) {printf("(%d,%d,%2.2f),",ptr->exp_x,ptr->exp_y,ptr->coef);}
    }
    return 0;
}
