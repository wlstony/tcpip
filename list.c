#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student{
	char name[20];
	int account;
	struct Student * stuNext;
};

struct Student* create(){
	struct Student *head,*last;
	printf("Please type student information\n");
	int count = 1;
	char stuName[20];

	struct Student *stu;
	while(strcmp(stuName, "q") != 0 && 
	strcmp(stuName, "Q") != 0){
		printf("name of student %d\n", count);

		scanf("%s", stuName);
		stu = (struct Student *)malloc(sizeof(struct Student));
		strcpy(stu->name, stuName);
		stu->account = count;
	
		if(count == 1){
			head = last = stu;
			stu->stuNext = NULL;
		}else{
			last->stuNext = stu;	
			last = stu;
		}

		count++;
	}

printf("head name:%s,account:%d\n", head->name, head->account);
	free(stu);

	return head;
}

void print(struct Student *stu){
	printf("students information\n");
	
	struct Student *tmp;
	tmp = stu;
	while(tmp !=NULL){
		printf("name:%s,account:%d\n", tmp->name, tmp->account);
		tmp = tmp->stuNext;
	}
}

int main(){
	struct Student *stu = create();
	print(stu);
	
	return 0;
}
