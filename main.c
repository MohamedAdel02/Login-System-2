#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define maxSize 50

typedef union {
  int intState;
  bool boolState;
} Status;

typedef struct {
  char username[20];
  char password[20];
  Status status;
} User;

int numOfUsers = 0;
User users[maxSize];

void addNewUser(char username[], char password[], Status accountState) {

  User newUser;
  strcpy(newUser.username, username);
  strcpy(newUser.password, password);
  newUser.status = accountState;
  users[numOfUsers] = newUser;
  numOfUsers++;
}

Status getAccountState() {

  char state[8];
  printf("Account state (true or 1 for active) (false or 0 for inactive): ");
  scanf("%s", &state);

  Status accountState;
  while(1) {
    if (strcmp(state, "true") == 0) {
      accountState.boolState = true;
      break;
    } else if (strcmp(state, "1") == 0) {
      accountState.intState = 1;
      break;
    } else if (strcmp(state, "false") == 0) {
      accountState.boolState = false;
      break;
    } else if (strcmp(state, "0") == 0) {
      accountState.intState = 0;
      break;
    } else {
    printf("Invalid state, please enter a valid state (true or 1 for active) (false or 0 for inactive): ");
    scanf("%s", &state);
    }
  }
  return accountState;
}

void registration() {

  char username[20];
  char password[20];

  if (numOfUsers >= maxSize) {
    printf("You can't add another user .... the users array is full\n");
    return;
  }

  printf("Enter your username and password\n");

  while (1) {
    int flag = 1;
    printf("Username: ");
    scanf("%s", &username);
    for (int i = 0; i < numOfUsers; i++) {
      if (strcmp(username, users[i].username) == 0) {
        printf("Username already exists ... please enter another one\n");
        flag = 0;
      }
    }
    if (flag) {
      break;
    }
  }

  printf("Password: ");
  scanf("%s", &password);

  Status accountState = getAccountState();

  addNewUser(username, password, accountState);
  printf("<------- Successfully registered ------->\n");
}


void login() {

  char username[20];
  char password[20];

  printf("Enter your username and password\n");
  printf("Username: ");
  scanf("%s", &username);
  printf("Password: ");
  scanf("%s", &password);

  for (int i = 0; i < numOfUsers; i++) {

    if ((strcmp(username, users[i].username) == 0) && (strcmp(password, users[i].password) == 0)) {
      if (users[i].status.boolState == true || users[i].status.intState == 1) {
        printf("<-------- Successful login -------->\n");
      } else {
        printf("<----- m3lesh, you are not active ----->\n");
      }
      return;
    }
  }

  printf("<----- Invalid username or password ----->\n");
}


void checkOperationNum(int num) {

  if (num == 1) {
    registration();
  } else if (num == 2) {
    login();
  } else {
    printf("<-----------------------  Invalid number, Please enter a valid number ----------------------->\n");
  }
}


int main() {

  int operationNum;

  while (1) {
    printf("1 ====> Register\n");
    printf("2 ====> Login\n");
    printf("3 ====> Exit\n");
    printf("Please enter the operation number: ");
    scanf("%d", &operationNum);

    if (operationNum == 3) {
      break;
    }

    checkOperationNum(operationNum);
    printf("<------------------------------------->\n");
  }

}
