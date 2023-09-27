/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** EventManager
*/

#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <functional>
#include <any>

namespace ecs
{
    class EventManager
    {
    private:
        template <typename EventType>
        using Callable = std::function<void(const EventType &)>;
    private:
        struct BaseEvent
        {
            virtual ~BaseEvent() {}
        };

        template <typename EventType>
        struct Event: BaseEvent
        {
            Event(const EventType &event_): event(event_) {}
            const EventType &event;
        };

        template <typename EventType>
        struct CallbackWrapper
        {
            CallbackWrapper(Callable<EventType> callable) : m_callable(callable) {}

            void operator() (const BaseEvent& event) {
                m_callable(static_cast<const Event<EventType>&>(event).event);
            }

            Callable<EventType> m_callable;
        };
    public:
        EventManager(void): m_subscribers() {}
        ~EventManager(void) = default;

        template <typename EventType>
        void subscribe(Callable<EventType> func)
        {
            m_subscribers[std::type_index(typeid(EventType))].push_back(CallbackWrapper<EventType>(func));
        }

        template <typename EventType>
        void emit(const EventType &e)
        {
            Event<EventType> event(e);
            for (auto &wrappedFunction : m_subscribers[std::type_index(typeid(EventType))])
                wrappedFunction(event);
        }

        inline static EventManager &getInstance()
        {
            if (!_instance)
                _instance = new EventManager();
            return *_instance;
        }

    private:
        static EventManager *_instance;
        std::unordered_map<std::type_index, std::vector<Callable<BaseEvent>>> m_subscribers;
    };
}

inline ecs::EventManager *ecs::EventManager::_instance = nullptr;
