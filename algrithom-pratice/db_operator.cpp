/*===================================================
 *	Copyright(c) 2023All rights reserved.
 *
 * file   name:db_operator.cpp
 *      Author: miracle
 * crete  date:20230303/07/23
 * description:
 *=========================================================*/
#include "sqlite3.h"
#include <iostream>
using namespace std;

int main() {
  sqlite3 *db;
  int res = sqlite3_open("test.db", &db);
  if (res) {
    cout << "database failed to open " << endl;
  } else {
    cout << "do some db operaor" << endl;
  }
  sqlite3_close(db);
}
