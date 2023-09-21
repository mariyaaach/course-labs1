#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
typedef struct Num{
    float val;
    int flag;
}Num;


Num GetNum(){
    int musor = getchar();
    Num pr;
    pr.flag = 1;
    int point = 0;
    int c;
    int num = 0;
    float drob = 0;
    int k = 1;
    int minus = 0;
    while(1){
         c = getchar();
         if (c == '-'){
            if (minus == 0){
                minus = 1;
                continue;
            }
            else{
                pr.flag = 0;
                break;
            }
         }

         else if (c =='.'){
            if (point == 0){
               point = 1;
               continue;
            }
            else{
               pr.flag = -0;
            }
            
         }

         else if (c == EOF || c == '\n' || c ==' ' || c =='\t'){
            break;
         }
         else if ((c-'0') < 0 || (c -'0') > 9){
             pr.flag = 0;
             break;
         }
         else if (point == 0){
            num = num * 10 + (c - '0');
         }
         
         else if (point == 1){
            k *= 10;
            drob = drob + ((float)( -'0') / k);
         }
         

    }
    float res = (float)num + drob;
    if (minus){
        res = res * (-1);
    }
    pr.val = res;
    return pr;
}
int tabs = 0;
typedef float Data;
typedef struct Node {
    Data data;
    struct Node*left;
    struct Node*right;

}Node;
void tree_print(Node*tree);
Node* tree_add(Node*tree, Data d);

void print(Node*tree){
    tree_print(tree);
    printf("\n");
}
void tree_print(Node*tree){
    if (tree == NULL){
        return;
    }
    tabs+=5;
    tree_print(tree->right);
    for (int i = 0;i < tabs; i++){
        printf(" ");
    }
    printf("%f\n", tree->data);
    tree_print(tree->left);
    tabs -= 5;
    return;
}
    

Node* tree_add(Node*tree, Data d){
    if (tree == NULL){
        Node*t = malloc(sizeof(Node));
        t->data = d;
        t->left = NULL;
        t->right = NULL;
        return t;
    }
    if (d<tree->data){
        tree->left = tree_add(tree->left, d);
        
    }
    if (d>tree->data){
        tree->right = tree_add(tree->right, d);
        
    }
    return tree;
}
Node* removeRecursive(Node* tree, int val) {
    if (!tree) {
        return tree;
    }

    if (val < tree->data) {
        tree->left = removeRecursive(tree->left, val);
    } else if (val > tree->data) {
        tree->right = removeRecursive(tree->right, val);
    } else {
        //Удаляем найденный угол 
        if (!tree->left) {
            Node* rightChild = tree->right;
            free(tree);
            return rightChild;
        } else if (!tree->right) {
            Node* leftChild = tree->left;
            free(tree);
            return leftChild;
        }

        //Если у узла два ребенка
        Node* tmp = tree->right;
        while (tmp->left) tmp = tmp->left;

    
        tree->data = tmp->data;

        //Удаляем ребенка по порядку из правого поддерева
        tree->right = removeRecursive(tree->right, tmp->data);
    }

    return tree;
}
int HeightOfTree(Node* tree){
    if(tree -> data == 0)
        return 0;
    int left, right;
    if (tree -> left != NULL) {
        left = HeightOfTree(tree->left);
    } else 
        left = -1;
    if (tree -> right != NULL) {
        right = HeightOfTree(tree -> right);
    } else 
        right = -1;
    int max = left > right ? left : right;
    return max + 1;

}

int main(){
    
    Node *tree = NULL;
    struct Num element;
    char choice;
    int  ans;

		printf("                                 TREE MENU\n");
        printf("+-----------------------------------------------------------------------+\n");
		printf("| a. Add an element                                                     |\n");
		printf("| b. Display                                                            |\n");
		printf("| c. Delete menu                                                        |\n");
		printf("| d. Delete an element in the tree                                      |\n");
		printf("| e. Know the depth                                                     |\n");
        printf("+-----------------------------------------------------------------------+\n");
		printf("Enter your choice: ");
   do {
        
		
		scanf("%c", &choice);
        if (choice == '\n'){

        }
        switch (choice) {
        case 'a':
            printf("\nEnter the element to be added: ");
            element=GetNum();
            if(element.val == 0){
                printf("Error!\n");
                break;
            }
            tree=tree_add(tree, element.val);
            break;
        case 'b':
            tree_print(tree);
            break;
        case 'c':
            break;
        case 'd':
            
			printf("\nEnter the element to be deleted: ");
			element = GetNum();
            if (element.val == 0){
                printf("Error!\n");
                break;
            }
			tree=removeRecursive(tree, element.val);
            break;
        case 'e':
            ans = HeightOfTree(tree);
            printf("%d\n", ans);
        case '\n':
            continue;
        default:
            printf("\nERROR\nERROR\nERROR");
            return 0;
        }
    } while (choice != 'c');
    
}