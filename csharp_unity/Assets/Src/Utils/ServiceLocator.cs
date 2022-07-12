using System;
using System.Collections.Generic;
using UnityEngine;

namespace sample_game.utils {
    
    /// <summary>
    /// Stores and provides services for an application.
    /// </summary>
    public static class ServiceLocator {
        
        //-------------------------------------------------------------
        // Class variables
        //-------------------------------------------------------------

        private static readonly Dictionary<Type, object> _services = new Dictionary<Type, object>();

        //-------------------------------------------------------------
        // Class events
        //-------------------------------------------------------------

        /// <summary>
        /// Dispatched when a new service was added to the locator.
        /// </summary>
        public static event Action OnServicesListUpdated;

        //-------------------------------------------------------------
        // Public class methods
        //-------------------------------------------------------------

        public static void RegisterService(object service) {
            InternalRegisterService(service, service.GetType());
        }
        
        /// <summary>
        /// Register a service in the locator. Type for register may differ from actual service type
        /// (useful for interfaces).
        /// </summary>
        /// <param name="service">Service to register.</param>
        /// <typeparam name="T">Service will be registered with that type.</typeparam>
        public static void RegisterService<T>(object service) {
            InternalRegisterService(service, typeof(T));
        }

        /// <summary>
        /// Gets a registered service.
        /// </summary>
        /// <typeparam name="T">Service type.</typeparam>
        /// <returns>Service (if it was registered), null otherwise.</returns>
        public static T GetService<T>() {
            _services.TryGetValue(typeof(T), out var item);
            return (T)item;
        }
        /// <summary>
        /// Gets a registered service.
        /// </summary>
        /// <param name="serviceType">Service type.</param>
        /// <returns>Service (if it was registered), null otherwise.</returns>
        public static object GetService(Type serviceType) {
            _services.TryGetValue(serviceType, out var item);
            return item;
        }

        //-------------------------------------------------------------
        // Private class methods
        //-------------------------------------------------------------
        
        /// <summary>
        /// Internal method for service registering.
        /// </summary>
        /// <param name="service">Service to register.</param>
        /// <param name="type">Service will be registered with that type.</param>
        private static void InternalRegisterService(object service, Type type) {
            if (_services.ContainsKey(type)) {
                Debug.LogWarning("Service was already registered for type '" + type.Name + "'");
                return;
            }
            
            _services[type] = service;
            OnServicesListUpdated?.Invoke();
        }
    }
} // namespace sample_game.utils