<?php

/**
 * Represents a REST-style request path - the part in the URL after the hostname.
 *
 *  Exepcted format is '/<modulename>/<param-1>/<param-2>/.../<param-n>'
 *  E.g. '/users/status/display'.
 *
 *  Params are the responsibility of a module to process. The framework only
 *  sees the module name and redirects a request based on that.
 */
class RequestPath
{
    const SEPARATOR = '/';

    private $path;

    private $moduleName;
    private $parameterArray;

    /**
     * Factory method.
     * Create a new RequestPath from a string, and parse it.
     *
     * @param $_path string to parse.
     * @return RequestPath object.
     */
    public static function buildRequestPath($_path)
    {
        $path = new RequestPath($_path);
        $path->parsePath();

        return $path;
    }

    public function __construct($_path)
    {
        $this->path = $_path;
        $this->moduleName = "";
        $this->parameterArray = array();
    }

    public function containsModuleName()
    {
        return (strlen($this->moduleName) > 0);
    }

    public function getModuleName()
    {
        return $this->moduleName;
    }

    public function getParameters()
    {
        return $this->parameterArray;
    }

    public function parametersToString()
    {
        return self::SEPARATOR . implode(self::SEPARATOR, $this->parameterArray);
    }

    public function parsePath()
    {
        $tok = strtok($this->path, self::SEPARATOR);

        while ($tok !== false)
        {
            $tok = trim($tok);
            if (strlen($tok) > 0)
            {
                $this->setPathElement($tok);
            }
            $tok = strtok(self::SEPARATOR);
        }
    }

    private function setPathElement($element)
    {
        if (!$this->containsModuleName())
        {
            $this->moduleName = $element;
        }
        else
        {
            array_push($this->parameterArray, $element);
        }
    }
}

?>