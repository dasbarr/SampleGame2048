#ifndef UTILS_SERVICEHOLDER_H
#define UTILS_SERVICEHOLDER_H

#include <typeindex>
#include <memory>
#include <utility>
#include "base/CCMap.h"
#include "base/CCRef.h"
#include "SimpleLogger.h"

// for convenience
#define GET_SERVICE(T) utils::ServiceLocator::getService<T>()

namespace sample_game::utils {
    /**
     * Stores and provides services for an application.
     */
    class ServiceLocator {
        public:
            ServiceLocator() = delete;
            ~ServiceLocator() = delete;

            /**
             * Registers an already existed service.
             * @tparam T Service type, should derive from Ref. Note that it can be different from actual service
             *           type (for example, a service can be registered by its interface).
             * @param service Service to register.
             */
            template<class T>
            static void registerService(cocos2d::Ref* service) {
                auto serviceTypeIndex = std::type_index(typeid(T));

                if (s_services.at(serviceTypeIndex) != nullptr) {
                    // service was already registered
                    utils::SimpleLogger::error("Service '" + std::string(serviceTypeIndex.name()) + "' was already registered.");
                }
                else {
                    s_services.insert(serviceTypeIndex, service);
                }
            }

            /**
             * Gets a registered service.
             * @tparam T Type that corresponds to requested service.
             * @return Service (if registered), nullptr otherwise.
             */
            template<class T>
            static T* getService() {
                auto serviceTypeIndex = std::type_index(typeid(T));

                auto* service = s_services.at(serviceTypeIndex);
                if (service == nullptr) {
                    // service was not registered
                    utils::SimpleLogger::error("Service '" + std::string(serviceTypeIndex.name()) + "' wasn't registered");
                }

                return (T*)service;
            }

            /**
             * Clears service locator, destroys all registered services.
             */
            static void clear();

        private:
            static cocos2d::Map<std::type_index, cocos2d::Ref*> s_services;
    };
}

#endif // UTILS_SERVICEHOLDER_H
