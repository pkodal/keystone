<?php

class ContentLoader
{
    /**
     * load a REST URL as a Resource object instance. If the load call returns a string, it is
     * considered to be 'html' and wrapped in a Resource.
     *
     * @param $modulePath REST module path and parameters
     * @return Resource on success, NULL on failure to load.
     */
    public function loadResource($modulePath)
    {
        $dispatcher = Registry::getRegistry()->fetch(DISPATCHER_ID);
        $resource = $dispatcher->dispatch(RequestPath::buildRequestPath($modulePath));

        if ($resource != NULL && is_a($resource, 'Resource'))
        {
            return $resource;
        }

        throw new FrameworkException("No valid internal Resource object provided by the " .
                "resource query '" . $modulePath . "'");
    }
}



?>