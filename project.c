#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STUDENT 50

struct Student
{
    int id;
    char name[100];
    char gender ;
    float chinese_score;
    float math_score;
    float pe_score;
    struct Student* next;
};

//Global Variable
struct Student* head = NULL;
int student_count = 0;

//Instructed Functions
void add_students();
void delete_students();
void find_Students();
void modify_students();
void calc_average();
void calc_student_grades();
void Display();
void save_to_file();
void load_from_file();
void save_to_file_text();
void load_from_file_text();

int main(){
    load_from_file();
    //load_from_file_text();
    printf("\t\t================================================== \n");
    printf("\t\t             Student Management System               \n");
    printf("\t\t=================================================== \n");
    int choice;
    do{
        printf("*****************Menu******************** \n");
        printf("1. Add Student \n");
        printf("2. Delete Student \n");
        printf("3. Modify Student Data \n");
        printf("4. Find Student \n");
        printf("5. Check Students Individual Result \n");
        printf("6. Check the average result \n");
        printf("7. Display the student information List \n");
        printf("8. Exit programme \n");
        printf("Choice : ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            add_students();
            break;
        case 2:
            delete_students();
            break;
        case 3:
            modify_students();
            break;
        case 4:
            find_Students();
            break;
        case 5:
            calc_student_grades();
            break;
        case 6:
            calc_average();
            break;
        case 7:
            Display();
            break;
        default:
            printf("Invalid Choice please enter (1-8)");
            break;
        }
    }while(choice!=8);

    save_to_file();
    save_to_file_text();
    return 0;
}

void add_students(){
    if(student_count>=MAX_STUDENT){
        printf("Student Number is already reached 50. Can't add more sorry! \n");
        return;
    }

    printf("***Add New Students***\n");
    //create new node 

    struct Student *newnode = (struct Student*)malloc(sizeof(struct Student));
    newnode->next = NULL;
    if(newnode==NULL){
        printf("Memory Allocation failed");
        return;
    }
    


    //taking students information
    printf("Enter the student id : ");
    scanf("%d", &newnode->id); //here we can also add another function to check if the id already exists in our student data
    

    printf("Enter the student name: ");
    scanf(" %[^\n]", newnode->name);
    printf("Enter student Gender(M/F): ");
    scanf(" %c",&newnode->gender);
    printf("Enter student Chinese Score: ");
    scanf("%f",&newnode->chinese_score);
    printf("Enter students Math Score: ");
    scanf("%f",&newnode->math_score);
    printf("Enter students PE Score: ");
    scanf("%f",&newnode->pe_score);

    if (head == NULL) {
        head = newnode;
    } else {
        struct Student* temp = head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newnode;
    }
    
    student_count++;

    printf("Student Added Successfully! \n");

    
}



void delete_students(){
    int id;
    printf("Enter student id : ");
    scanf("%d",&id);
    if(head==NULL){
        printf("There's no Student in the list now");
        return;
    }
    struct Student* tempcurrent = head;
    struct Student* tempprev = NULL;
    
    if(head->id==id){
        head = head->next;
        printf("Deleting student with name : %s\n",tempcurrent->name);
        free(tempcurrent);
        student_count-=1;
        printf("Student Deleted Succesfully\n");
        return;
    }

    while(tempcurrent!=NULL){
        if(tempcurrent->id==id){
            tempprev->next = tempcurrent->next;
            printf("Deleting student with name : %s",tempcurrent->name);
            free(tempcurrent);
            student_count-=1;   
            printf("Student Information Deleted Successfully");
            return;
        }
        tempprev = tempcurrent;
        tempcurrent = tempcurrent->next;
    }
    printf("No student found with the id \n");
    
}

void modify_students(){
    printf("Enter student id : ");
    int student_id;
    scanf("%d",&student_id);
    if(head==NULL){
        printf("No students in the list ");
        return;
    }
    if(head->id==student_id){
        printf("Previous Information : \n");
        printf("Name : %s\t",head->name);
        printf("ID: %d\t",head->id);
        printf("Gender : %c\n",head->gender);
        printf("Chinese Score : %.2f\t",head->chinese_score);
        printf("Math_Score : %.2f\t",head->math_score);
        printf("PE Score : %.2f\t",head->pe_score);
        printf("Enter New Information \n");
        printf("Enter Chinese score : ");
        scanf("%f",&head->chinese_score);
        printf("Enter Math_Score :");
        scanf("%f",&head->math_score);
        printf("Enter PE Score : ");
        scanf("%f",&head->pe_score);
        return;
    }
    struct Student* temp = head;
    while(temp!=NULL){
        if(temp->id == student_id){
            printf("Previous Information : \n");
        printf("Name : %s\t",temp->name);
        printf("ID: %d\t",temp->id);
        printf("Gender : %c\n",temp->gender);
        printf("Math_Score : %.2f\t",temp->math_score);
        printf("Chinese Score : %.2f\t",temp->chinese_score);
        printf("PE Score : %.2f\t",temp->pe_score);
        printf("Enter New Information \n");
        printf("Enter Chinese Education score : ");
        scanf("%f",&temp->chinese_score);
        printf("Enter Math_Score :");
        scanf("%f",&temp->math_score);
        printf("Enter PE Score : ");
        scanf("%f",&temp->pe_score);
            return;
        }
        temp = temp->next;
    }
    printf("No matching student found in the list with the given id");
}


void find_Students(){
    printf("Enter student id : ");
    int student_id;
    scanf("%d",&student_id);
    if(head==NULL){
        printf("No students in the list ");
        return;
    }
    if(head->id==student_id){
        printf("Name : %s , ID : %d",head->name,head->id);
        return;
    }
    struct Student* temp = head;
    while(temp!=NULL){
        if(temp->id == student_id){
            printf("Name : %s , ID : %d \n",temp->name,temp->id);
            return;
        }
        temp = temp->next;
    }
    printf("No matching student found in the list with the given id \n");
}
void calc_average(){
    if (head==NULL){
        printf("The list is Empty ");
        return;
    }
    float math_score = 0;
    float chinese_score=0;
    float pe_score = 0;
    struct Student* temp = head;
    while(temp!=NULL){
        math_score+=temp->math_score;
        chinese_score+=temp->chinese_score;
        pe_score+=temp->pe_score;
        temp=temp->next;
    }
    printf("This run successfully and calculated the average. \n");
    printf("Math : %.2f \tChinese : %.2f \tPE : %.2f\n",math_score/student_count,chinese_score/student_count,pe_score/student_count); //i divide by student number(student_count) here   
}


void calc_student_grades(){
    if(head==NULL){
        printf("The list is empty ");
        return;
    }
    
    float initial_score;
    struct Student* temp=head;
    printf("Student's grade : \n");
    while(temp!=NULL){
        printf("Name : %s \t ID : %d \t",temp->name,temp->id);
        initial_score = (0.3*temp->chinese_score) +(0.4*temp->math_score)+(0.3*temp->pe_score);
        if(initial_score>=90 && initial_score<=100){
            printf("Grade : A \n");
        }else if(initial_score>=80 && initial_score<90){
            printf("Grade : B \n");
        }else if(initial_score>=70 && initial_score<80){
            printf("Grade : C \n");
        }else if(initial_score>=60 && initial_score<70){
            printf("Grade : D \n");
        }else if(initial_score<60){
            printf("Grade : F \n");
        }else{
            printf("the score calculation system fails");
            printf("The current score status : \nMath : %.2f \t Chinese : %.2f \t PE : %.2f ",temp->math_score,temp->chinese_score,temp->pe_score);
        }
        temp = temp->next;
    }
}


void Display(){
    struct Student* temp;
    printf("******************Current List*******************\n\n");
    if (head==NULL){
        printf("No student in the list ");
        return;
    }
    
        temp = head;
        while(temp!=NULL){
            printf("Name :  %s\t Id : %d \tGender : %c\n",temp->name,temp->id,temp->gender);
            printf("Chinese Score : %.2f \tMath : %.2f \tPE : %.2f \n",temp->chinese_score,temp->math_score,temp->pe_score);
            temp = temp->next;
            printf("\n");
        }
}


void load_from_file(){
    FILE *fp = fopen("student.dat","rb");
    if(fp==NULL){
        //file doesn't exist yet. First Run!!!
        return;
    }
    struct Student* temp= NULL;
    struct Student* last = NULL;
    while(1){
        temp = (struct Student *) malloc(sizeof(struct Student));
        if(fread(temp,sizeof(struct Student),1,fp)!=1){
            free(temp);
            break;
        }
        temp->next = NULL;
        if(head==NULL){
            head=temp;
        }else{
            last->next = temp;
        }
        last = temp;
        student_count++;
    }
    fclose(fp);
}


void save_to_file(){
    FILE *fp = fopen("student.dat","wb");
    if(fp==NULL){
        printf("Error opening file for saving \n");
        return;
    }
    struct Student* temp = head;
    while(temp!=NULL){
        fwrite(temp,sizeof(struct Student),1,fp);
        temp = temp->next;
    }
    fclose(fp);
}   


void save_to_file_text(){
    FILE *fp = fopen("students.txt","w");
    if(fp==NULL){
        printf("Error opening file for return ");
        return ;
    }

    struct Student* temp = head;
    while(temp!=NULL){
        fprintf(fp,"%d,%s,%c,%.2f,%.2f,%.2f\n",temp->id,temp->name,temp->gender,temp->chinese_score,temp->math_score,temp->pe_score);
        temp = temp->next;
    }
    fclose(fp);   
}


void load_from_file_text(){
    FILE *fp = fopen("students.txt","r");
    if (fp==NULL){
        return;
    }
    while(1){
        struct Student* newnode = (struct Student*) malloc (sizeof(struct Student));
        if (fscanf(fp,  "%d,%99[^,],%c,%f,%f,%f\n",&newnode->id,newnode->name,&newnode->gender,&newnode->chinese_score,&newnode->math_score,&newnode->pe_score)!=6){
            free(newnode);
            break;
        }
        newnode->next = NULL;
        if(head==NULL){
            head=newnode;
        }else{
            struct Student* temp = head;
            while(temp->next!=NULL)
                temp = temp->next;
                temp->next = newnode;
        }
        student_count++;
    }
    fclose(fp);
}