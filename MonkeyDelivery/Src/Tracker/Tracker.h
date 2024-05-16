#pragma once
#include <cassert>
#include <string>

using namespace std;

enum PersistenceType
{
    FILE = 0,
    SERVER
};

enum SerializationType
{
    JSON = 0,
    CSV
};

class Tracker {
public:

    Tracker* instance = nullptr; // revisar singleton en C++ (static)

    Tracker* Instance() 
    {
        assert(instance != nullptr);
        return instance;
    };

    Persistence* persistenceStrategy;
    Serializer* serializationStrategy;

    EventFactory* eventFactory;

    string sessionID;

    bool Init(PersistenceType persistenceType, SerializationType serializationType, int updateMilliseconds)
    {
        assert(instance == nullptr);

        instance = new Tracker();

        instance->eventFactory = new EventFactory();
        instance->ChooseSerializationStrategy(serializationType);
        instance->ChoosePersistenceStrategy(persistenceType);

        instance->persistenceStrategy.Open(updateMilliseconds);

        // Decidir el ID de sesión único 
        instance->GenerateUniqueID();

        // Evento de inicio de sesión
        instance->SendSessionStartEvent();

        return true;
    };

    bool End()
    {
        assert(instance != nullptr);

        // Finalizar la sesión
        instance->SendSessionEndEvent();

        delete instance;
        instance = nullptr;
        return true;
    };

    void TrackEvent(TrackerEvent* tEvent)
    {
        // Rellenar timestamp, event_ID, session_ID... del evento antes de enviarlo a la cola

        tEvent->Session_ID = sessionID;

        // TODO : guid
        //tEvent->Event_ID = Guid.NewGuid().ToString();

        // TODO: tiempo. quizas pedir a la clase Timer
       /* DateTimeOffset now = DateTimeOffset.Now;
        tEvent->Timestamp = now.ToUnixTimeSeconds();*/

        persistenceStrategy->Send(tEvent);
    };

    // Envia todos los eventos almacenados en la cola
    void FlushEvents()
    {
        persistenceStrategy->SendFlush();
    };

    EventFactory* GetEventFactory() { return eventFactory; };

private:
    Tracker() { }; // Ocultar el constructor

    // Puede ser público si queremos habilitar que se cambie el tipo de persistencia a mitad del tracker
    void ChoosePersistenceStrategy(PersistenceType pType)
    {
        switch (pType)
        {
        case PersistenceType::FILE:
            persistenceStrategy = new FilePersistence(serializationStrategy);
            break;
        case PersistenceType::SERVER:
            // TODO server persistence
            persistenceStrategy = new ServerPersistence(serializationStrategy);
            break;
        default:
            break;
        }
    };

    void ChooseSerializationStrategy(SerializationType sType)
    {
        switch (sType)
        {
        case SerializationType::JSON:
            serializationStrategy = new Json_Serializer();
            break;
        case SerializationType::CSV:
            serializationStrategy = new CSVSerialize();
            break;
        default:
            break;
        }
    };

    void GenerateUniqueID()
    {
        // sessionID = Guid.NewGuid().ToString();
        // TODO : crear el GUID
    };

    void SendSessionStartEvent()
    {
        TrackEvent(new SessionStartEvent());
    };

    void SendSessionEndEvent()
    {
        TrackEvent(new SessionEndEvent());

        // Volcado de los datos restantes
        FlushEvents();

        // Cierre de la posible hebra 
        persistenceStrategy->Close();
    };
};