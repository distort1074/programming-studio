  // Enter your student ID and Fullname

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  struct st_class{
    int code;		// class code
    char name[30]; 	// class name
    int unit;		// credites
    int grading;	// grading (1:A+~F, 2:P/F)
  };

  char kname[2][10] = {"A+~F", "P/F"}; // String for grading

  // Functions provided
  int loadData(struct st_class* c[]); // Load all class list from data file.
  void printAllClasses(struct st_class* c[], int csize); // Print all class list

  // Functions for modifying
  int addNewClass(struct st_class* c[], int csize); // Add a class into the list
  void editClass(struct st_class* c[], int csize); // Modify a class in the list
  void findClasses(char* name, struct st_class* c[], int csize); // Search a class by name from the list

  // Functions for making
  int applyMyClasses(int my[], int msize, struct st_class* c[], int csize); // Apply a class
  void printMyClasses(int my[], int msize, struct st_class* c[], int csize); // Print my classes
  void saveMyClass(int my[], int msize, struct st_class* c[], int csize); // Save my classes
  void saveAllClasses(struct st_class* c[], int csize); // Save all class list


  int main(void) {
    int no;	// menu number 
    struct st_class* classes[50]; // Class list (max. 50 classes)

    int myclass[10]; // My classes (max. 10 classes of code)
    int mycount = 0; // Amount of my classes

    srand(time(0));
    int count = loadData(classes);
    printf("> Load %d classes.\n", count);

    while(1){
      printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
      printf(">> Menu? > ");
      scanf("%d", &no);

      if(no == 1){ 
        printf("> 1.Class list (%d classes)\n", count);
        printAllClasses(classes, count);
      }
      else if(no == 2){ 
        printf("> 2.Add a Class\n");
        count = addNewClass(classes, count);
      }
      else if(no == 3){ 
        printf("> 3.Modify a Class\n");
        editClass(classes, count);
      }
      else if(no == 4){
        printf("> 4.Search a Class\n");
        printf(">> Enter class name > ");
        char name[30];
        scanf("%s", name);
        findClasses(name, classes, count);
      }
      else if(no == 5){
        printf("> 5.Apply a class\n");
        mycount = applyMyClasses(myclass, mycount, classes, count);
        printf("%d classes has been applied.\n", mycount);
      }
      else if(no == 6){
        printf("> 6.My classes\n");
        printMyClasses(myclass, mycount, classes, count);
      }
      else if(no == 7){
        printf("> 7.Save\n");
        saveMyClass(myclass, mycount, classes, count);
        printf("\n> All my classes ware saved to my_classes.txt.\n");
        saveAllClasses(classes, count);
        printf("\n> All of class list ware saved to classes.txt.\n");
      }
      else break;
    }
    return 0;
  }

  int loadData(struct st_class* c[]){
    int count=0;
    FILE* file;

    file=fopen("classes.txt", "r");
    while(!feof(file)){
      c[count] = (struct st_class*)malloc(sizeof(struct st_class));
      int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
      if(r < 4) break;
      count++;
    }
    fclose(file);
    return count;
  }

  void printAllClasses(struct st_class* c[], int csize){
    for(int i=0; i<csize; i++){
      printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
    }
  }

  void saveAllClasses(struct st_class* c[], int csize){
    FILE* file;
    file = fopen("classes.txt", "w");
    for(int i=0; i<csize; i++){
      fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
    }
    fclose(file);	
  }

  void findClasses(char* name, struct st_class* c[], int csize){
    int count = 0;

    printf("Searching (keyword : %s)\n", name);
    for(int i=0; i<csize; i++){
      if(strstr(c[i]->name, name)){
        printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
        count++;
      }
    }
    printf("%d classes found.\n", count);
  }

  // You must complete these functions.
  int addNewClass(struct st_class* c[], int csize){
  // Caution : Don't allow the duplicate class code.
  // You must complete this function.
    

    struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));
    
    int newCode;
    int isDuplicate;

    while (1) {
        printf(">> code number > ");
        scanf("%d", &newCode);

        // 이미 등록된 과목 코드인지 확인
        isDuplicate = 0; // 중복 플래그 초기화
        for (int i = 0; i < csize; i++) {
            if (c[i]->code == newCode) {
                printf("Error: Class code %d is already registered.\n", newCode);
                isDuplicate = 1; // 중복된 코드 발견
                break; // 중복 발견시 for 루프 탈출
            }
        }

        if (!isDuplicate) {
            // 중복되지 않은 경우, while 루프 탈출
            break;
        }
    }

    // 중복되지 않은 새 과목 코드에 대한 추가 처리...

        // 중복되지 않은 경우, 새 과목 정보 입력 받기
        p->code = newCode;
        printf(">> class name > ");
        scanf("%s", p->name);
        printf(">> credits > ");
        scanf("%d", &(p->unit));
        printf(">> grading (1: A+~F, 2: P/F) > ");
        scanf("%d", &(p->grading));

        // 새 과목을 클래스 목록에 추가
        c[csize] = p;
        return csize + 1; // 추가된 과목을 포함한 새로운 과목 수 반환
    }



void editClass(struct st_class* c[], int csize) {
    int code, found = 0;
    printf(">> Enter a code of class > ");
    scanf("%d", &code);

    // 입력받은 코드에 해당하는 과목 찾기
    for (int i = 0; i < csize; i++) {
        if (c[i]->code == code) {
            // 과목 코드가 일치하는 과목을 찾음
            found = 1; // 과목을 찾았으므로 found를 1로 설정
            printf("> Current: [%d] %s [credits %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);

            // 새로운 과목 정보 입력 받기
            printf("> Enter new class name > ");
            scanf("%s", c[i]->name);
            printf("> Enter new credits > ");
            scanf("%d", &(c[i]->unit));
            printf("> Enter new grading(1: A+~F, 2: P/F) > ");
            scanf("%d", &(c[i]->grading));

            printf("> Modified.\n");
            break; // 과목을 찾고 수정했으므로 루프 탈출
        }
    }

    // 입력받은 코드에 해당하는 과목이 목록에 없는 경우
    if (!found) {
        printf("Error: No class found with code %d.\n", code);
    }

}


  // You must make all these functions.

  
    int applyMyClasses(int my[], int msize, struct st_class* c[], int csize) {
        int code, found, alreadyExists;
        while (1) {
            printf("Enter class code to apply (0 to finish): ");
            scanf("%d", &code);

            // If user inputs 0, break the loop to finish applying for classes
            if (code == 0) {
                break;
            }

            // Check if the class code already exists in the user's class list
            alreadyExists = 0;
            for (int i = 0; i < msize; i++) {
                if (my[i] == code) {
                    alreadyExists = 1;
                    printf("You have already applied for class code %d.\n", code);
                    break;
                }
            }

            // If the class code is not in the user's class list, check if it exists in the full class list
            if (!alreadyExists) {
                found = 0;
                for (int i = 0; i < csize; i++) {
                    if (c[i]->code == code) {
                        found = 1;
                        // If the class code is found and there's space in the user's class list, add it
                        if (msize < 10) { // Assuming 10 is the max number of classes a user can apply for
                            my[msize++] = code;
                            printf("Class code %d applied successfully.\n", code);
                        } else {
                            printf("You cannot apply for more than 10 classes.\n");
                        }
                        break;
                    }
                }
                if (!found) {
                    printf("Class code %d does not exist.\n", code);
                }
            }
        }

        // Return the updated number of classes in the user's class list
        return msize;
    }





  void printMyClasses(int my[], int msize, struct st_class* c[], int csize){




  }

  void saveMyClass(int my[], int msize, struct st_class* c[], int csize){




  }
