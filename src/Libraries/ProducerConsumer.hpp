#pragma once

template <typename T, typename P>
class EgProducerConsumer
{
public:
    void RegisterConsumer(T ConsumerCallback) {
        consumerCallbacks[consumerCallbackCnt] = ConsumerCallback;
        consumerCallbackCnt++;
    }

    void NotifyConsumers(P arg) {
        for(int k = 0; k < consumerCallbackCnt; k++)
        {
            consumerCallbacks[k](arg);
        }
    }

private:
    T consumerCallbacks[10] = {0};
    int consumerCallbackCnt = 0;
};