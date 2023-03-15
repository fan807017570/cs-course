/*===================================================
*	Copyright(c) 2023All rights reserved.
*
* file   name:rocket_producer.cpp
*      Author: miracle
* crete  date:20230303/07/23
* description:
*
=========================================================*/
#include "DefaultMQProducer.h"
#include <atomic>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <vector>
#define INTEGRATE_TOPIC "accounting-integrate"
#define NAME_SRV_DEV "10.162.86.189:9876"

using namespace rocketmq;
using namespace std;

std::atomic<bool> g_quit{true};
std::atomic<int> g_msgCount{0};
std::mutex g_max;
std::condition_variable g_fininshed;
SendCallback *g_callback = NULL;

class MySendCallback : public SendCallback {

  virtual void onSuccess(SendResult &sendResult) {
    cout << "SendResult:" << sendResult.getSendStatus()
         << ",Message id:" << sendResult.getMsgId() << endl;
  }
  virtual void onException(MQException &e) { cout << "send Exceptoin\n"; }
};

int main(int argc, char **argv) {
  DefaultMQProducer producer("accounting integrate");

  producer.setNamesrvAddr(NAME_SRV_DEV);
  producer.start();

  MQMessage msg("accounting-integrate", "*", "the example ");
  g_callback = new MySendCallback();
  try {
    producer.send(msg, g_callback);
  } catch (MQException e) {
    cout << e << endl;
  }
  producer.shutdown();
}
