<?php

include_once(realpath(dirname(__FILE__) . '/FrameworkException.inc'));
include_once(realpath(dirname(__FILE__) . '/NoResourceException.inc'));
include_once(realpath(dirname(__FILE__) . '/Registry.inc'));
include_once(realpath(dirname(__FILE__) . '/Module.inc'));


/**
 * Module dispatcher. This class is responsible for dispatching control to the
 * correct module.
 */
class Dispatcher
{
    const DISPATCHER_REG_ID = 'dispatcher';
    const MODULE_CONTROLLER_FILENAME = 'control.inc';
    const APP_PATH = "/../../app/";

    /** @var string optional error handler to dispatch processing errors to */
    private $errorControllerFile;

    /** @var Registry object registry */
    private $registry;

    /**
     * Factory method. Construct a Dispatcher to use.
     *
     * @param $_errorController optional error controller to dispatch to if
     * no valid module is found. If left out, defaults to a PHP trigger_error.
     * @return Dispatcher object.
     */
    public static function buildDispatcher($_errorControllerFile = NULL, $_registry = NULL)
    {
        $dispatcher = new Dispatcher($_errorControllerFile, $_registry);
        return $dispatcher;
    }

    /**
     * Private constructor. use the factory method/accessor to use this class.
     *
     * @param $_errorController optional error controller to dispatch to if
     * no valid module is found. If left out, defaults to a PHP trigger_error.
     *
     * @see buildDispatcher
     * @see getDispatcher
     */
    private function __construct($_errorControllerFile = NULL, $_registry = NULL)
    {
        $this->errorControllerFile = $_errorControllerFile;
        
        if ($_registry == NULL)
        {
            $this->registry = Registry::getRegistry();
        }

    }

    /**
     * Dispatch a request to a module.
     * @param $path RequestPath object.
     * @return mixed whatever the dispatched controller returns. This could be NULL,
     * or possible a Resource object, or just a string of HTML content. Totally up to
     * the controller.
     */
    public function dispatch($path)
    {
        $returnValue = NULL;

        $module = $this->getModule($path->getModuleName());
        $returnValue = $module->dispatch($path);

        return $returnValue;
    }

    public function getModule($moduleName)
    {
        $module = $this->registry->fetch($moduleName);
        if ($module === false)
        {
            $this->registerModule($moduleName);
            $module = $this->registry->fetch($moduleName);
        }
        return $module;
    }

    private function registerModule($moduleName)
    {
        $filename = dirname(__FILE__) . self::APP_PATH .
                $moduleName . '/' . self::MODULE_CONTROLLER_FILENAME;
        $moduleController = realpath($filename);

        if ($moduleController !== false)
        {
            $encodedModuleInfo = $this->includeFile($moduleController, CONTEXT_REGISTER);
            $this->validateEncodedInfo($filename, $encodedModuleInfo);

            $module = Module::createModuleFromClassSet($moduleName, $encodedModuleInfo);
            $this->addModuleToCache($module);
        }
        else
        {
            throw new FrameworkException("File '" . $filename . "' missing. cannot load module.");
        }
    }

    private function validateEncodedInfo($filename, $encodedModuleInfo)
    {
        $spaces = substr_count(trim($encodedModuleInfo), ' ');
        if ($spaces > 0)
        {
            throw new FrameworkException("Problems encountered loading module from $filename.<br/>" .
                                         "Could not Interpret the encoded module info. It's likely there are PHP " .
                                          "errors or warnings being outputed. see below:<br/><br/><br/>" .
                                         $encodedModuleInfo);
        }
    }

    private function includeFile($filename, $context)
    {
        $GLOBALS[CONTEXT_PARAM] = $context;

        ob_start();
        include($filename);

        unset($GLOBALS[CONTEXT_PARAM]);

        return ob_get_clean();
    }

    private function addModuleToCache($module)
    {
        $this->registry->store($module->getModuleName(), $module);
    }

    public function dispatchToErrorHandler($message)
    {
        if ($this->errorControllerFile != NULL)
        {
            $this->dispatchToCustomErrorHandler($message);
        }
        else
        {
            $this->defaultErrorHandler($message);
        }
    }

    private function dispatchToCustomErrorHandler($_message)
    {
        $errorHandler = realpath($this->errorControllerFile);

        print "handler: " . $errorHandler . "<br/>";

        if ($errorHandler !== FALSE)
        {
            $message = $_message;
            include_once($errorHandler);
        }
        else
        {
            $this->defaultErrorHandler($_message);
        }
    }

    private function defaultErrorHandler($message)
    {
        trigger_error("Dispatcher default error handler: " . $message, E_USER_ERROR);
    }
}

?>