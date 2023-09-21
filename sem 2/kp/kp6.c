//Выяснить, в какой группе студенты имеют максимальный средний балл
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void Usage(){
 printf("Usage: use -f to print -d to run func\n"); 
 }

int Compare(char *str1, char *str2){
    int i = 0;
    for (;; str1[i] == '\0' || str2[i] == '\0'){
        if (str1[i] != str2[i]){
            return 0;
        }

    }
    return 1;
}


typedef struct Student{
    char firstname[50];
    char lastname[50];
    int age;
    int group;
    int zach;
    int informatics;
    int mathematics;
    int english;
    char gender;
} Student;

void Insert(char* db_name, Student* student){
    FILE* f = fopen(db_name, "ab");
    int size = sizeof(Student);
    fwrite(student, size, 1,f);
    fclose(f);


}






Student* Create_Student(char firstname[50], char lastname[50],int zach,int group,  int age, int informatics, int mathematics, int english, char gender){
    Student* stud = (Student*)malloc(sizeof(Student));
    strncpy(stud->firstname, firstname, 50);
    stud->firstname[49] = '\0';

    strncpy(stud->lastname, lastname, 50);
    stud->lastname[49] = '\0';
    stud->zach = zach;
    stud->age = age;
    stud->group = group;
    stud->informatics = informatics;
    stud->mathematics = mathematics;
    stud->english = english;
    stud->gender = gender;
}

void Read(char* db_name){;
    int age, group, zach, inf, mat, eng;
    char gen;
    char name[50];
    char laname[50];


    scanf("%s %s %d %d %d %d %d %d %c", name, laname, &age,&group,&zach,&inf,&mat,&eng,&gen);

    

    
    int flag = 1;
    if (age < 0 || age > 120){
        flag = 0;
    }
    if (group < 101 || group > 112){
        flag = 0;
    }
    if (inf < 0 || inf > 5){
        flag = 0;
    }
    if (mat < 0 || mat > 5){
        flag = 0;
    }
    if (eng < 0 || eng > 5){
        flag = 0;
    }
    if (flag){
        Student* s = Create_Student(name, laname,zach,group,age,inf,mat,eng,gen);
        Insert(db_name, s);
    }
    

}

void Print(char* db_name){
    FILE* f = fopen(db_name, "rb");
    Student* stud = (Student*)malloc(sizeof(Student));
    while(fread(stud, sizeof(Student), 1, f)){
        printf("|firstname: %s | lastname: %s | zach %d | group: %d | age: %d | inf: %d | mat: %d | eng: %d | gen: %c |\n",stud->firstname, stud->lastname,stud->zach,stud->group ,stud->age, stud->informatics, stud->mathematics, stud->english, stud->gender);
        
    } 
    fclose(f);
}


void Select(char* db_name,int zach){
    FILE* f = fopen(db_name, "rb");
    Student* stud = (Student*)malloc(sizeof(Student));
    int flag = 0;
    while(fread(stud, sizeof(Student), 1, f)){
        if (stud->zach == zach){
            printf("|firstname: %s | lastname: %s | zach %d | group: %d | age: %d | inf: %d | mat: %d | eng: %d | gen: %c|",stud->firstname, stud->lastname,stud->zach,stud->group ,stud->age, stud->informatics, stud->mathematics, stud->english, stud->gender);
            printf("\n");
            flag = 1; 
        }

    }
    if (!flag){
        printf("not found\n");
    }
    fclose(f);
}

void Func(char db_name[50], int* groups){
    for (int i = 0; i < 100; ++i){
        groups[i] = 0;
    }
    FILE* f = fopen(db_name, "rb");
    Student* stud = (Student*)malloc(sizeof(Student));
    while(fread(stud, sizeof(Student), 1, f)){
        if (stud->gender != 'f'){
            continue;
        }

        groups[3*(stud->group -101)] = stud->group;
        groups[3*(stud->group -101) + 1] += stud->informatics + stud->english + stud->mathematics;
        groups[3*(stud->group -101) + 2] += 3;
    }
    int max_group = 0;
    double mx = 0;
    for (int i = 0; i < 36; i+=3){;
    double tmp = (double)((1.0 * groups[i+1]) / (1.0 * groups[i+2]));
 
         if (mx < tmp){
             mx = tmp;
             max_group = groups[i];
            
         }
       
    }
    printf("group: %d sr_bal: %lf\n",max_group, mx);
    fclose(f);
}
 void Drop(char* db_name){
    FILE* f = fopen(db_name, "w");
    fclose(f);

 }

int main(int argc, char* argv[]){
    char db_name[50] = "students.txt";
     Student* stud = Create_Student("mihail", "qwertov",121,101, 18,5,5,5,'m');
      Insert(db_name, stud);
      stud = Create_Student("jinada", "wertuk",134,110, 18,4,4,5,'f');
       Insert(db_name, stud);
       stud = Create_Student("lopuhov", "tatarenko",213,109, 18,4,5,5,'f');
       Insert(db_name, stud);
       stud = Create_Student("maria", "kanao",234,103, 18,5,2,5,'f');
       Insert(db_name, stud);
       stud = Create_Student("ulia", "nechiporenko",134,101, 18,4,5,5,'f');
       Insert(db_name, stud);
       stud = Create_Student("evgenia", "shlahova",142,104, 18,5,4,5,'f');
      Insert(db_name, stud);
 int groups[100];



    if (argc != 2){
        Usage();
        return 0;
    }
    if (!strcmp(argv[1], "-f")){
        Print(db_name);
    }
    else if (!strcmp(argv[1], "-d")){
        int groups[100];
        Func(db_name, groups);
    }
    else if (!strcmp(argv[1], "-a")){
        printf("Enter amount: \n");
        int n;
        scanf("%d", &n);
        printf("enter value like\n");
        printf("Firstname Lastname age group zach informatics mathematics english gander\n");
        for (int i = 0; i < n; ++i){
            Read(db_name);
        }
    }
    else{
        Usage();
        return 1;
    }


}