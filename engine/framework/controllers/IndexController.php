<?php
include_once(realpath(dirname(__FILE__) . '/../../bootstrap.inc'));

function getErrorController()
{
    if (defined('ERROR_CONTROLLER'))
    {
        return ERROR_CONTROLLER;
    }
    return NULL;
}

function sendResource($resource)
{
    if ($resource != NULL && is_a($resource, 'Resource'))
    {
        setNoCacheHeaders();
        if (is_a($resource, 'JsonResource'))
        {
            header('Content-type: application/json');
        }
        print $resource->render();

        return true;
    }

    return false;
}


/* Main module system entry point. */
registerFrameworkExceptionHandler();

$requestPath = DEFAULT_MODULE;

//Registry::getRegistry()->store(SESSION_MANAGER, new SessionManager());
//Registry::getRegistry()->store(NOTIFICATION_MANAGER, new NotificationManager());


if (isset($_GET[QUERY_PARAM]))
{
    $requestPath = $_GET[QUERY_PARAM];
}

$contentLoader = new ContentLoader();
Registry::getRegistry()->store(CONTENT_LOADER_ID, $contentLoader);

$path = RequestPath::buildRequestPath($requestPath);

$dispatcher = Dispatcher::buildDispatcher(getErrorController());
Registry::getRegistry()->store(DISPATCHER_ID, $dispatcher);

$resource = $dispatcher->dispatch($path);
if (sendResource($resource) === false)
{
    $dispatcher->dispatchToErrorHandler('IndexController encountered a non-resource instance. path: ' . $requestPath);
}

?>