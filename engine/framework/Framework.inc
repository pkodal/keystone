<?php

include_once(realpath(dirname(__FILE__) . '/ContentLoader.inc'));


/**
 * Facade class to expose framework operations to the modules. This class
 * is the main interface for modules into the framework.
 */
class Framework
{
    /**
     * Register the main controller class for use by the framework to dispatch
     * control to.
     *
     * @param string $controllerClassName string name of the class process requests on
     * behalf of the module.
     * @param string $prefix (optional) define a prefix of a REST path that this controller is responsible for.
     * @return void
     */
    public static function registerController($controllerClassName, $prefix = NULL)
    {
        if ( !array_key_exists(CONTEXT_PARAM, $GLOBALS))
        {
            throw new FrameworkException("Context not set. Cannot register the controller '$controllerClassName'");
        }

        if ($GLOBALS[CONTEXT_PARAM] === CONTEXT_REGISTER)
        {
            if (isset($prefix))
            {
                print "p:" . $controllerClassName . ":" . $prefix . "-";
            }
            else
            {
                print "s:" . $controllerClassName . "-";
            }
        }
        else
        {
            throw new FrameworkException("Context is not set to registration mode. set to: '" . 
                                         $GLOBALS[CONTEXT_PARAM] . "'");
        }
    }

    /**
     * Register a controller that is responsible for a specific path prefix.
     *
     * @param string $controllerClassName class name of the controller
     * @param string $prefix the prefix to register against.
     * @return void
     */
    public static function registerControllerForPrefix($controllerClassName, $prefix)
    {
        Framework::registerController($controllerClassName, $prefix);
    }

    /**
     * Internally load a resource from another module, using a REST-style path.
     *
     * This method will always return a Resource object or NULL. If the module returns
     * HTML content, it will be wrapped in a Resource.
     *
     * @param $path string a REST-style module path (e.g. '/users/listAllUsers')
     * @return Resource object containing the results, or NULL on error.
     */
    public static function loadResource($path)
    {
        $loader = Registry::getRegistry()->fetch(CONTENT_LOADER_ID);

        $resource = NULL;
        try
        {
            $resource =  $loader->loadResource($path);
        }
        catch (FrameworkException $fEx)
        {
            trigger_error($fEx->getMessage());
        }

        return $resource;
    }
}


?>