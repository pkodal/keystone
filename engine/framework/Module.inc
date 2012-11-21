<?php

class Module
{
    private $moduleName;
    private $sequentialControllers;
    private $controllerPrefixMap;
    
    public static function createModuleFromClassSet($moduleName, $classSet)
    {
        // decode set into internal object
        $module = new Module($moduleName);

        // split into lines
        $lines = explode('-', $classSet);
        foreach ($lines as $line)
        {
            $parts = explode(':', $line);

            if (trim($parts[0]) == 's')
            {
                $module->addControllerClass($parts[1]);
            }
            else if (trim($parts[0]) == 'p')
            {
                $module->addControllerClass($parts[1], $parts[2]);
            }
        }

        return $module;
    }

    public function __construct($moduleName)
    {
        $this->moduleName = $moduleName;
        $this->sequentialControllers = array();
        $this->controllerPrefixMap = array();
    }

    public function addControllerClass($controllerClassName, $prefix = NULL)
    {
        $controller = $this->createController($controllerClassName);

        if (isset ($prefix))
        {
            if (array_key_exists($prefix, $this->controllerPrefixMap))
            {
                throw new FrameworkException("prefix '" . $prefix .
                        "' was registered twice for module '" . $this->moduleName);
            }

            $this->controllerPrefixMap[$prefix] = $controller;
        }
        else
        {
            array_push($this->sequentialControllers, $controller);
        }
    }

    /**
     * Dispatch to a controller for the given module.
     *
     * @param RequestPath $requestPath
     * @return Resource from the controller.
     */
    public function dispatch($requestPath)
    {
        $params = $requestPath->getParameters();
        
        if (count($params) > 0 && array_key_exists($params[0], $this->controllerPrefixMap))
        {
            $prefix = array_shift($params);
            return $this->controllerPrefixMap[$prefix]->dispatch($params);
        }

        $result = NULL;
        $i = 0;
        $seqControllerCount = count($this->sequentialControllers);

        while ($result == NULL && $i < $seqControllerCount)
        {
            try
            {
                $result = $this->sequentialControllers[$i]->dispatch($params);
            }
            catch (NoResourceException $ex)
            {
                // ignore, move on to the next controller in the sequence.
                $result = NULL;
            }
            $i++;
        }

        if (!isset($result))
        {
            throw new NoResourceException('No valid resources could be returned from module ' . 
                                          $this->getModuleName() . ' for the path "' .
                                          $requestPath->parametersToString() . '"');
        }
        return $result;
    }


    private function createController($className)
    {
        if (class_exists($className))
        {
            return new $className();
        }
        else
        {
            throw new FrameworkException("can't create controller for class '$className' in module '" .
                                         $this->moduleName);
        }
    }

    public function getModuleName()
    {
        return $this->moduleName;
    }

    public function toString()
    {
        $string = "[";
        foreach ($this->sequentialControllers as $controller)
        {
            $string .= get_class($controller) . " ";
        }


        foreach ($this->controllerPrefixMap as $key => $value)
        {
            $string .= " $key -> " . get_class($value);
        }
        $string .= "]";

        return $string;
    }

    /**
     * @return array array of controller class names.
     */
    public function getControllerClassNames()
    {
        $classNames = array();

        foreach ($this->sequentialControllers as $controller)
        {
            array_push($classNames, get_class($controller));
        }

        foreach ($this->controllerPrefixMap as $controller)
        {
            array_push($classNames, get_class($controller));
        }

        return $classNames;
    }
}

?>
