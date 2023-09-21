//вещестевенные числа
//кольцевой однонаправленный
//добавить k экземпляров последнего элемента в начало списка
#include<stdio.h>
#include<stdlib.h>

struct node {
float data;
struct node *next;
};

typedef struct node Node;

Node *head = NULL;

int len;

void insert(float value){Node *new_node = (Node*) malloc(sizeof(Node));
new_node->data = value;
new_node->next = NULL;

if(head==NULL){
    head = new_node;
}else{
    Node *current = head;
    while(current->next){
        current = current->next;
    }
    current->next = new_node;
}
len++;
}

void delete(float value){Node *current = head;
Node *prev = NULL;

if(current!=NULL && current->data==value){
    head = current->next;
    free(current);
    len--;
    return;
}

while(current!=NULL && current->data!=value){
    prev = current;
    current = current->next;
}

if(current==NULL){
    return;
}

prev->next = current->next;
free(current);
len--;
}
void printList(){
    printf("List: ");
    Node *current = head;
    while(current != NULL){
    printf("%.2f ", current->data);
    current = current->next;
}
printf("\n");
}

int length(){
    return len;
}

void add_k_instances_at_beginning(int k){
    if(k<1){
    printf("Invalid input.\n");
    return;
}
Node *current = head;
while(current->next){
    current = current->next;
}
float value = current->data;
for(int i=1; i<=k; i++){
    Node *new_node =  malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = head;
    head = new_node;
    len++;
}
}

int main(){
    int choice, k;
    float value;
    while(1){
        printf("\n1. Print List\n2. Insert\n3. Delete\n4. Length\n5. Add k instances at beginning\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
        case 1:
        printList();
        break;
        case 2:
        printf("Enter the value to be inserted: ");
        scanf("%f", &value);
        insert(value);
        break;
        case 3:
        printf("Enter the value to be deleted: ");
        scanf("%f", &value);
        delete(value);
        break;
        case 4:
        printf("Length of the list: %d\n", length());
        break;
        case 5:
        printf("Enter the value of k: ");
        scanf("%d", &k);
        add_k_instances_at_beginning(k);
        break;
        case 6:
        exit(0);
        default:
        printf("Invalid choice.\n");
}
}
    return 0;
}