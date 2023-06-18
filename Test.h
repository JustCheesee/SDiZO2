#ifndef SDIZO_TEST_H
#define SDIZO_TEST_H

class Test{
public:
    double PCFreq = 0.0;
    __int64 CounterStart = 0;
    void StartCounter();
    double GetCounter();
};

#endif //SDIZO_TEST_H
