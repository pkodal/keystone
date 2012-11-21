<?php

/**
 * Abstract base class for a Controller that uses
 * REST-style URLS to route to a function to run.
 *
 * Uses template method pattern. base routing logic is in this class.
 * Specific routes/functions are defined in extended classes.
 */
abstract class RestController
{
    const PARENT_ROUTE = "#";
    const MAGIC_BEFORE_METHODNAME = '_before';
    const MAGIC_AFTER_METHODNAME = '_after';

    private $routeToDefaultHandlerOnError;

    /**
     * Construct a RestController.
     *
     * @param $_routeToDefaultHandlerOnError boolean if true and a REST route cannot be
     * found, the controller will route to the defaultHandler method. if false, it will
     * route to the defined framework ERROR_CONTROLLER
     */
    public function  __construct($_routeToDefaultHandlerOnError = false)
    {
        $this->routeToDefaultHandlerOnError = $_routeToDefaultHandlerOnError;
    }

    /**
     * Define the the REST URL path mapping to functions internal to this class.
     *
     * @return array a multidimensional array representing the REST url paths that route to function calls.
     */
    protected abstract function getRestMapping();

    /**
    * @return array a multidimensional array represting the REST url method to a set of Request Method annotrations.
    */
    protected abstract function getRequestMethodHandlers();

    /**
     * The default handler to handle base requests. By default, returns null
     *
     * @param array $parameters the parameters passed to the default handler
     */
    protected function defaultHandler($parameters)
    {
        return NULL;
    }

    /**
     * Handle dispatching of a REST-style request.
     *
     * @param $requestParameters array of parameters.
     * @return mixed whatever the specific handler returns. could be NULL, a string
     * of HTML, or a Resource object containing JS/CSS/HTML.
     */
    public function dispatch($requestParameters)
    {
        $returnValue = NULL;

        $returnValue = $this->runMagicMethod(self::MAGIC_BEFORE_METHODNAME);
        if ($this->isAResource($returnValue))
        {
            return $returnValue;
        }

        if (count($requestParameters) > 0)
        {
            $returnValue = $this->dispatchToRestFunction($requestParameters);
        }
        else
        {
            $returnValue = $this->defaultHandler($requestParameters);
        }

        $this->runMagicMethod(self::MAGIC_AFTER_METHODNAME);
        if ($this->isAResource($returnValue))
        {
            return  $returnValue;
        }

        return $returnValue;
    }

    /**
     * @param mixed $value object to check the type of.
     * @return true if the parameter is a resource instance.
     */
    private function isAResource($value)
    {
        return (isset($value) && is_a($value, 'Resource'));
    }

    /**
     * Do the actual dispatch to the correct method.
     *
     * @param $requestParameters array of parameters.
     * @return mixed whatever the specific handler returns. could be NULL, a string
     * of HTML, or a Resource object containing JS/CSS/HTML.
     */
    private function dispatchToRestFunction($requestParameters)
    {
        $returnValue = NULL;
        $namedParameters = array();

        $routeFunction = $this->findRestBinding($requestParameters, $namedParameters);
        if ($routeFunction != NULL)
        {
            $methodHandlers = $this->getRequestMethodHandlers();
            $methodHandlers[$routeFunction]->runHandler();
            return $this->executeRestMethod($routeFunction, $namedParameters, $requestParameters);
        }

        return $returnValue;
    }

    /**
     * Execute a Rest controller method.
     *
     * @param string $methodName name of the method to run
     * @param array $namedParameters array of named parameters and their values extracted from the REST Path
     * @param array $requestParameters all the path parameters of the REST path
     * @return Resource or NULL - result of the method run.
     */
    private function executeRestMethod($methodName, $namedParameters, $requestParameters)
    {
        // TODO can extract this exectute + param creation to another util class.
        if (method_exists($this, $methodName))
        {
            $refMethod = new ReflectionMethod(get_class($this), $methodName);
            $callingParameters = $this->createMethodParameters($refMethod, $namedParameters, $requestParameters);

            $returnValue = call_user_func_array(array($this, $methodName), $callingParameters);
            if (!is_a($returnValue, 'Resource'))
            {
                throw new NoResourceException('No Resource instance returned from ' .get_class($this) .
                        '->' . $methodName . '()');
            }
        }
        else
        {
            $returnValue = $this->routeToErrorHandler("Method '" . $methodName .
                    "' does not exist. in controller " . get_class($this));
        }

        return $returnValue;
    }

    /**
     * Piece together the array of parameters to pass to the REST method when called.
     * Named parameters are positioned correctly, and any extra parameters are assigned the whole
     * set of request parameters.
     *
     * @param ReflectionMethod $method the method to call
     * @param array $namedParameters assoc. array of param name to value
     * @param array $requestParameters the complete set of parameters
     * @return array the combined parameters 
     */
    private function createMethodParameters(ReflectionMethod $method, $namedParameters, $requestParameters)
    {
        $callingParameters = array();

        if ($method->getNumberOfRequiredParameters() < count($namedParameters))
        {
            throw new FrameworkException('Not enough parameters on method ' . $method->getName() .
                                         '. expected at least ' . count($namedParameters));
        }

        foreach ($method->getParameters() as $param)
        {
            if (array_key_exists($param->getName(), $namedParameters))
            {
                $callingParameters[$param->getPosition()] = $namedParameters[$param->getName()];
            }
            else
            {
                // Assume that unnamed params are there to accept all the path.
                $callingParameters[$param->getPosition()] = $requestParameters;
            }
        }

        return $callingParameters;
    }

    /**
     * find a binding from a REST path to a class method
     * to execute.
     *
     * @param $requestParameters array of parameters.
     * @return void
     */
    private function findRestBinding(&$requestParameters, &$namedParameters)
    {
        $routeFound = FALSE;
        $parameters = $requestParameters;

        $element = $this->getRestMapping();

        // Always include the default routing.
        $element[self::PARENT_ROUTE] = 'defaultHandler';

        while ($routeFound == FALSE)
        {
            $element = $this->getRoute(array_shift($parameters), $element, $namedParameters);
            if (!is_array($element)) // step into an array and keep going.

            {
                $routeFound = TRUE;
            }
        }

        if (!$routeFound)
        {
            $element = NULL;
        }

        return $element;
    }

    /**
     * Exectute one of the magic method on this instance.
     *
     * @param string $methodName method to run
     * @return mixed the result of the method.
     */
    private function runMagicMethod($methodName)
    {
        if (method_exists($this, $methodName))
        {
            return $this->$methodName();
        }

        return NULL;
    }

    /**
     * Pull out a REST path-to-function route.
     *
     * @param $pathElement the element of the REST mapping
     * @param $restMapping the mapped element to search through
     * @return mixed array/string of function name(s), NULL if nothing found.
     *
     * @see #getRestMapping()
     */
    private function getRoute($pathElement, $restMapping, &$namedParameters)
    {
        // 1: no element. we fall back to the parent route.
        if (!isset($pathElement))
        {
            return $this->getElement(self::PARENT_ROUTE, $restMapping);
        }

        // 2: try direct mapping
        $element = $this->getElement($pathElement, $restMapping);
        if ($element != NULL)
        {
            return $element;
        }

        // 3: try any wildcard matches within the current branch level
        $wildcardParameter = $this->findWildcardParameter(array_keys($restMapping));
        if ($wildcardParameter !== false)
        {
            $namedParameters[substr($wildcardParameter, 1)] = $pathElement;
            return $restMapping[$wildcardParameter];
        }

        // fallback to parent route if its available.
        return $this->getElement(self::PARENT_ROUTE, $restMapping);
    }

    /**
     * Attempt to retrieve a wildcard Parameter from the branch level.
     * NOTE: return type is mixed. returning false on no match. Use type matching to check if
     * a result is returned.
     *
     * @param array $array array to search
     * @return mixed the wildcard parameter if one is found, or false if one cannot be found
     */
    private function findWildcardParameter($array)
    {
        $wildcardParameter = false;
        $i = 0;

        while ($wildcardParameter === false && $i < count($array))
        {
            if (strpos($array[$i], "$") === 0)
            {
                $wildcardParameter = $array[$i];
            }
            else
            {
                $i++;
            }
        }

        return $wildcardParameter;
    }

    /**
     * Safte retrieval of a value from an associative array.
     *
     * @param string $key
     * @param array $map
     * @return mixed vlaue from the array or NULL if not found.
     */
    private function getElement($key, $map)
    {
        if (array_key_exists($key, $map))
        {
            return $map[$key];
        }
        return NULL;
    }

    /**
     * route control to an error handler - something bad must
     * have happened while trying to find a REST route.
     *
     * @param $message string error message
     * @return void
     */
    private function routeToErrorHandler($message)
    {
        if ($this->routeToDefaultHandlerOnError)
        {
            $this->defaultHandler();
        }
        else
        {
            Registry::getRegistry()->fetch(DISPATCHER_ID)->dispatchToErrorHandler($message);
        }
    }
}

?>