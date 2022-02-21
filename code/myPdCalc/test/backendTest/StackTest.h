#ifndef STACK_TEST_H_
#define STACK_TEST_H_

#include <QtTest/QtTest>

class StackTest : public QObject
{
    Q_OBJECT
  private slots:
    void testPushPop();
    void testSwapPop();
    void testErrors();
}

#endif