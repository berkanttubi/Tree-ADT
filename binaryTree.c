#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 16
#define FALSE 0
#define TRUE 1

/*A tree Node declaration*/
struct Node
{
  int val;
  struct Node* left;
  struct Node* right;
};



typedef struct Node * Tree;
/*Function signatures*/
Tree CreateTree(void);
Tree MakeEmptyTree(Tree);
Tree InsertElement(int, Tree);
void DisplayTree(Tree,int);
int IterativeFindMinimum(Tree);
int IterativeFindMaximum(Tree);
int RecursiveFindMaximum(Tree);
int RecursiveFindMinimum(Tree);
int findElement(Tree,int);
struct Node * DeleteBinarySearchTree(Tree,int);
int CountNodes(Tree);
int CountLeaves(Tree);
int TreeHeight(Tree);
Tree CopyTree(Tree);


int main()
{
    Tree myTree, pos;
    int exit, val, height;
    char command;
    Tree myTree2;


        myTree = CreateTree();
        exit = FALSE;

        while (!exit)
        {
               fflush(stdin);
               printf("\nMenu:\n i)nitialize\n n)ew element \n a)find min iteratively \n b)find max iteratively \n c)recursive max \n d)recursive min \n x)finding \n y) deleting \n z)count nodes \n t)count leaves \n o)tree height \n p)copy tree \n e)xit\nEnter command: ");
               scanf("%c", &command);
               fflush(stdin);

                  switch(command)
                  {
                         case 'i':
                                myTree = MakeEmptyTree(myTree);
                                break;
                         case 'n':
                                printf("enter value: ");
                                scanf("%d", &val);
                                myTree = InsertElement(val, myTree);
                                DisplayTree(myTree,0);
                                break;
                         case 'a':
                                printf("%d",IterativeFindMinimum(myTree));
                                break;
                         case 'b':
                                printf("%d",IterativeFindMaximum(myTree));
                                break;
                        case 'c':
                                printf("%d",RecursiveFindMaximum(myTree));
                                break;
                        case 'd':
                                printf("%d",RecursiveFindMinimum(myTree));
                                break;
                        case 'x':
                                printf("Enter the val: ");
                                scanf("%d",&val);

                                printf("%d",findElement(myTree,val));
                                break;
                        case 'y':
                                printf("Enter the val: ");
                                scanf("%d",&val);
                                DeleteBinarySearchTree(myTree,val);
                                DisplayTree(myTree,0);
                                break;
                        case 'z':

                            printf("%d",CountNodes(myTree));
                            break;

                        case 't':

                            printf("%d",CountLeaves(myTree));
                            break;
                        case 'o':

                            printf("%d",TreeHeight(myTree));
                            break;
                        case 'p':

                            myTree2=CopyTree(myTree);
                            DisplayTree(myTree2,0);
                            break;

                         case 'e':
                                exit = TRUE;
                                break;
                         default:
                                 printf("command not recognized\n");
                                 break;
                  }


        }

    printf("\n\n");
    system("PAUSE");
    return 0;
}

/*Function that mainly creates a tree which is initially NULL*/
Tree CreateTree(void)
{
    return NULL;
}

/*Function that takes a tree and makes it an empty tree by removing all the nodes from that tree*/
Tree MakeEmptyTree(Tree t)
{
     if (t != NULL)
     {
         MakeEmptyTree(t->left);
         MakeEmptyTree(t->right);
         free(t);
     }
     return NULL;
}

/*This function takes an integer value and a tree,
  and inserts that value to the tree*/
Tree InsertElement(int val, Tree t)
{

   struct Node *newNode;

   newNode=(struct Node *) malloc(sizeof(struct Node));

   if(t==NULL){

        newNode->val=val;
        newNode->left=NULL;
        newNode->right=NULL;

        return newNode;

   }

   else{

    if(t->val < val){
        t->right=InsertElement(val,t->right);
        return t;
    }
    else{
        t->left=InsertElement(val,t->left);
        return t;
    }

   }



}

int IterativeFindMinimum(Tree myTree){

    while(myTree->left!=NULL)
        myTree=myTree->left;

    return myTree->val;

}
int IterativeFindMaximum(Tree myTree){

   while(myTree->right!=NULL)
        myTree=myTree->right;

    return myTree->val;


}

int RecursiveFindMaximum(Tree myTree){

    if(myTree->right==NULL)
        return myTree->val;


    return RecursiveFindMaximum(myTree->right);

}

int RecursiveFindMinimum(Tree myTree){

    if(myTree->left==NULL)
        return myTree->val;


    return RecursiveFindMaximum(myTree->left);

}

int findElement(Tree myTree,int val){


    if(myTree!=NULL){

    if(myTree->val == val)
        return 1;

    else{

        if(val>myTree->val)
            findElement(myTree->right,val);

        else
            findElement(myTree->left,val);


        }
    }

    else
        return -1;


}
struct Node * DeleteBinarySearchTree(Tree myTree, int val){

    if(myTree==NULL)
        return NULL;

    if(myTree->val == val){

        if(myTree->left == NULL && myTree->right == NULL)
            return NULL;

        if(myTree->right !=NULL){

            myTree->val = RecursiveFindMinimum(myTree->right);
            myTree->right = DeleteBinarySearchTree(myTree->right,RecursiveFindMinimum(myTree->right));
            return myTree;

        }
        myTree->val = RecursiveFindMaximum(myTree->left);
        myTree->left = DeleteBinarySearchTree(myTree->left,RecursiveFindMaximum(myTree->left));
        return myTree;

    }

    if(myTree->val < val){
        myTree->right = DeleteBinarySearchTree(myTree->right,val);
        return myTree;
    }

    myTree->left = DeleteBinarySearchTree(myTree->left,val);
    return myTree;




}

/*This function takes a tree and displays its content on the screen*/
void DisplayTree(Tree t, int depth)
{
   int i;
   if (t !=NULL)
   {
		DisplayTree(t->right, depth + 1);
		for(i = 0; i < depth; i++)
            printf("__");
        if(t->val < 10)
            printf("_");
		printf("%d\n", t->val);
		DisplayTree(t->left, depth + 1);
   }
}
int CountNodes(Tree t){

    int c =  1;             //Node itself should be counted
    if (t ==NULL)
        return 0;
    else
    {
        c += (CountNodes(t->left)+CountNodes(t->right));

        return c;
    }
}

int CountLeaves(Tree t){

    int c=0;

    if(t==NULL)
        return 0;

    if(t->right == NULL && t->left== NULL)
        return 1;

    else{

        c+=CountLeaves(t->left);
        c+=CountLeaves(t->right);
        return c;
    }

}

int TreeHeight(Tree t){

    int left=0;
    int right=0;

     if (t == NULL) {
        return -1;
    }

    left=1+TreeHeight(t->left);
    right=1+TreeHeight(t->right);

    if (left > right) {
        return left;
    } 
    else {
        return right;
    }

}

Tree CopyTree(Tree t){

    struct Node *newNode;

    newNode= (struct Node *) malloc(sizeof(struct Node));


    if(t==NULL){
        return NULL;

    }

    newNode->val=t->val;
    newNode->left=NULL;
    newNode->right=NULL;

    newNode->left = CopyTree(t->left);
    newNode->right = CopyTree(t->right);
    return newNode;





}
