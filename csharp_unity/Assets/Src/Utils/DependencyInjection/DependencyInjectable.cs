namespace sample_game.utils {
    
    /// <summary>
    /// Non-unity class that supports dependency injection.
    /// </summary>
    public abstract class DependencyInjectable : IDependencyInjectable {
        
        //-------------------------------------------------------------
        // Nested
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Class constants
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Class variables
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Class methods
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Constructor
        //-------------------------------------------------------------
        
        protected DependencyInjectable() {
            PerformInjection();
        }
        
        //-------------------------------------------------------------
        // Destructor
        //-------------------------------------------------------------
        
        ~DependencyInjectable()
        {
            // object no longer needs dependency fulfillment
            DependencyInjector.DependenciesListUpdated -= PerformInjection;
        }
        
        //-------------------------------------------------------------
        // Variables
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Events
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Properties
        //-------------------------------------------------------------

        /// <summary>
        /// If true, all dependencies are fulfilled.
        /// </summary>
        protected bool dependenciesFulfilled { get; private set; } = false;

        //-------------------------------------------------------------
        // Public methods
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Protected methods
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Private methods
        //-------------------------------------------------------------
        
        /// <summary>
        /// Injects dependencies to the current instance.
        /// </summary>
        private void PerformInjection() {
            if (dependenciesFulfilled)
                return; // already fulfilled
            
            dependenciesFulfilled = DependencyInjector.Inject(this);

            if (dependenciesFulfilled) {
                DependencyInjector.DependenciesListUpdated -= PerformInjection;
                OnDependenciesFulfilled();
            }
            else {
                // maybe dependencies will be fulfilled later
                DependencyInjector.DependenciesListUpdated += PerformInjection;
            }
        }
        
        //-------------------------------------------------------------
        // Handlers
        //-------------------------------------------------------------

        /// <summary>
        /// Can contain specific actions for case when all dependencies are fulfilled.
        /// </summary>
        protected virtual void OnDependenciesFulfilled() {
            // override if necessary
        }
    }
} // namespace sample_game.utils