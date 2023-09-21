#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct parstree{
	char value;
	struct parstree* left;
	struct parstree* right;
	struct parstree* prev;
};
typedef struct parstree PTREE;

void printpt(PTREE* root){
	if(root->left != 0){
		printf("(");
		printpt(root->left);
	}
	printf("%c",root->value);
	if(root->right != 0){
		printpt(root->right);
		printf(")");
	}
}

void printt(PTREE* root, int counter){
	if(root->left !=0)printt(root->left, counter + 1);
	for(int i = 0;i<counter;i++){
		printf("   ");
	}
	printf("_%c\n",root->value);
	if(root->right != 0)printt(root->right, counter + 1);
}

PTREE* rbuildt(PTREE* root){
	PTREE* temp;
	temp = root;
	char general;
	char tempc;
	if(temp->value == '-')
		if(temp->left != 0 && temp->right != 0 && temp->left->value == temp->right->value && temp->left->value == '*')
			if(temp->left->left->left == 0 && temp->left->left->right ==0 && temp->right->left->left == 0 && temp->right->left->right == 0
			&& temp->right->right->left == 0 && temp->right->right->right == 0 && temp->left->right->left == 0 && temp->left->right->right == 0){
				if(temp->left->left->value == temp->right->left->value){
					general = temp->left->left->value;
					tempc = temp->value;
					temp->value = temp->right->value;
					temp->right->value = tempc;
					temp->left->value = general;//
					temp->right->left->value = temp->left->right->value;
					free(temp->left->left);
					temp->left->left = 0;
					free(temp->left->right);
					temp->left->right = 0;
					return (temp);
				}
				if(temp->left->left->value == temp->right->right->value){
					general = temp->left->left->value;
					tempc = temp->value;
					temp->value = temp->right->value;
					temp->right->value = tempc;
					temp->left->value = general;//
					temp->right->right->value = temp->right->left->value;
					temp->right->left->value = temp->left->right->value;
					free(temp->left->left);
					temp->left->left = 0;
					free(temp->left->right);
					temp->left->right = 0;
					return (temp);
				}
				if(temp->left->right->value == temp->right->left->value){
					general = temp->left->right->value;
					tempc = temp->value;
					temp->value = temp->right->value;
					temp->right->value = tempc;
					temp->left->value = general;//
					temp->right->left->value = temp->left->left->value;
					free(temp->left->left);
					temp->left->left = 0;
					free(temp->left->right);
					temp->left->right = 0;
					return (temp);
				}
				if(temp->left->right->value == temp->right->right->value){
					general = temp->left->right->value;
					tempc = temp->value;
					temp->value = temp->right->value;
					temp->right->value = tempc;
					temp->left->value = general;//
					temp->right->right->value = temp->right->left->value;
					temp->right->left->value = temp->left->left->value;
					free(temp->left->left);
					temp->left->left = 0;
					free(temp->left->right);
					temp->left->right = 0;
					return (temp);
				}
	}
	if(temp->left != 0) temp->left = rbuildt(temp->left);
	if(temp->right != 0) temp->right = rbuildt(temp->right);
	return (temp);
}

PTREE* getptree(PTREE* root, char* c, int len){
	PTREE * temp;
	temp = root;
	for(int i= 0; i < len-1;i++){
		if(c[i] == '('){
			temp->left = malloc(sizeof(PTREE));
			temp->left->prev  = temp;
			temp= temp->left;
			temp->left = 0;
			temp->right = 0;
			continue;
		}
		if(c[i] == ')'){
			temp= temp->prev;
			continue;
		}
		if(c[i] == '+' || c[i] == '-' || c[i] == '/' || c[i] == '*' || c[i] == '^'){
			temp->value  = c[i];
			temp->right = malloc(sizeof(PTREE));
			temp->right->prev = temp;
			temp = temp->right;
			temp->left = 0;
			temp->right = 0;
			continue;
		}
		else{
			temp->value = c[i];
			temp = temp->prev;
			continue;
		}
	}
	return (temp);
}

int main(){
	char* c;
	c = malloc(sizeof(char));
	char temp;
	int len = 0;
	printf("Enter arithmetical expression: ");
	while(1){
		scanf("%c", &temp);
		if(temp == '\n') break;
		len++;
		c = realloc(c, len*sizeof(char));
		c[len-1] = temp;
	}
	PTREE* root;
	root = malloc(sizeof(PTREE));
	root->prev = 0;
	root->left = 0;
	root->right = 0;
	printf("[%s], %d\n", c, len);
	printf("Creating of tree...\n");
	root = getptree(root, c, len);
	printf("Created parsing tree: \n");
	printt(root, 0);
	root = rbuildt(root);
	printf("\n");
	printf("Changed Tree: \n");
	printt(root, 0);
	printf("Changed expression: ");
	printpt(root);
	printf("\n");
	return 0;
}
