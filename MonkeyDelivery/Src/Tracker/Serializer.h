#pragma once
#include <string>

using namespace std;

class Serializer {
public:
    std::string EndFileFormat()
    {
        return "{}]}";
    }

    string GetFileExtension()
    {
        return ".json";
    }

    string InitFileFormat()
    {
        return "{\n \"Events\": [\n";
    }

    string serialize(TrackerEvent* trackerEvent)
    {
        return trackerEvent->ToJson() + "," + "\n";
    }
};