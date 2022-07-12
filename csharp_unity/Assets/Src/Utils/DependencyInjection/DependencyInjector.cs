using System;
using System.Linq;
using System.Reflection;

namespace sample_game.utils {
    
    /// <summary>
    /// Class that performs dependency injection.
    /// </summary>
    public static class DependencyInjector {
        
        //-------------------------------------------------------------
        // Nested
        //-------------------------------------------------------------

        /// <summary>
        /// Attribute for dependency fields.
        /// </summary>
        [AttributeUsage(AttributeTargets.Field, AllowMultiple = false)]
        public class DependencyAttribute : Attribute {
            // no implementation needed
        }
        
        //-------------------------------------------------------------
        // Class constants
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Class variables
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Class events
        //-------------------------------------------------------------

        /// <summary>
        /// Dispatched when number of available dependencies updated, and now maybe it's possible to fulfill
        /// dependencies that couldn't be fulfilled before.
        /// </summary>
        public static event Action DependenciesListUpdated;
        
        //-------------------------------------------------------------
        // Public class methods
        //-------------------------------------------------------------

        /// <summary>
        /// Injects dependencies if possible.
        /// </summary>
        /// <param name="dependencyInjectable">Injection destination.</param>
        /// <param name="refillAlreadyFilledFields">
        /// If true, fields that were already fulfilled, will be fulfilled again (and will be set to null
        /// if fulfillment is not possible).
        /// </param>
        /// <returns>True if all dependencies was fulfilled, false otherwise.</returns>
        public static bool Inject(IDependencyInjectable dependencyInjectable, bool refillAlreadyFilledFields = false) {
            bool allDependenciesFulfilled = true;
            
            // If dependencyInjectable has some private dependency fields in parent classes, that fields
            // can't be obtained through DependencyInjectable type - we need to traverse over all parent types.
            // Also use BindingFlags.DeclaredOnly flag to get rid of duplicates.
            var currentType = dependencyInjectable.GetType();
            do {
                // get dependency fields in current type that should be fulfilled
                var dependencyFieldsToFulfillInCurrentType = currentType.GetFields(
                    BindingFlags.Public | BindingFlags.NonPublic |
                    BindingFlags.Instance | BindingFlags.DeclaredOnly
                ).Where(
                    // get only fields that has needed attribute and needed to be fulfilled
                    fieldInfo => fieldInfo.GetCustomAttribute<DependencyAttribute>() != null &&
                                 (fieldInfo.GetValue(dependencyInjectable) == null || refillAlreadyFilledFields)
                );

                foreach (var dependencyField in dependencyFieldsToFulfillInCurrentType) {
                    var dependency = ServiceLocator.GetService(dependencyField.FieldType);
                    // set even in case when dependency is null
                    dependencyField.SetValue(dependencyInjectable, dependency);

                    if (dependency == null) {
                        // dependency not fulfilled, it will be necessary to try again later
                        allDependenciesFulfilled = false;
                    }
                }

                // then start search for dependency fields in parent type
                currentType = currentType.BaseType;
            } while (currentType != null && typeof(IDependencyInjectable).IsAssignableFrom(currentType));

            return allDependenciesFulfilled;
        }

        //-------------------------------------------------------------
        // Constructor
        //-------------------------------------------------------------
        
        static DependencyInjector() {
            ServiceLocator.OnServicesListUpdated += ServicesListUpdatedHandler;
        }
        
        //-------------------------------------------------------------
        // Handlers
        //-------------------------------------------------------------
        
        /// <summary>
        /// Performs an update when number of internal stuff items updated.
        /// </summary>
        private static void ServicesListUpdatedHandler() {
            DependenciesListUpdated?.Invoke();
        }
    }
} // namespace sample_game.utils