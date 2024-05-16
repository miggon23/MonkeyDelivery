#pragma once
#include <queue>
#include "TrackerEvent.h"

class Serializer;

class Persistence {
public:

    Persistence(Serializer* serializer)
    {
        serializer = serializer;
        eventQueue = new queue<TrackerEvent*>();
    };

    void Send(TrackerEvent* tEvent)
    {
        eventQueue.push(tEvent);
    };

    void SendFlush()
    {
        mustFlush = true;
    };

    void Close()
    {
        SendFlush();
    };

    void Open(int updateMilliseconds)
    {
        updateFrequenceInMiliseconds = updateMilliseconds;

        if (!Directory.Exists(path))
        {
            Directory.CreateDirectory(path);
        }
    }

    public void Send(TrackerEvent tEvent)
    {
        eventQueueMutex.WaitOne();

        base.Send(tEvent);

        eventQueueMutex.ReleaseMutex();
    }

private:
    const std::string path = "./TrackerOutputs/";
    std::queue<TrackerEvent*> eventQueue;
    Serializer* serializer;

    int updateFrequenceInMiliseconds = 3000;

};