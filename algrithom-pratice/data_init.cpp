/*===================================================
*	Copyright(c) 2023All rights reserved.
*
* file   name:data_init.cpp
*      Author: miracle
* crete  date:20230303/07/23
* description:
*
=========================================================*/
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName) {
  int i;
  fprintf(stderr, "%s: ", (const char *)data);
  for (i = 0; i < argc; i++) {
    printf("%s=%s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}

int main(int argc, char **argv) {
  sqlite3 *db;

  char *messageError;

  int exit = sqlite3_open("testDb.db", &db);

  string querySql = "select * from persion ;";

  cout << "state of table ";

  sqlite3_exec(db, querySql.c_str(), callback, NULL, NULL);
  sqlite3_close(db);
  return 0;
}
