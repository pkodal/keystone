<?php
include_once(realpath(dirname(__FILE__) . '/../bootstrap.inc'));
include_once(realpath(dirname(__FILE__) . '/../../themes/ThemeFactory.inc'));

include_once(realpath(dirname(__FILE__) . '/../../admin/common/AdminSession.inc'));
include_once(realpath(dirname(__FILE__) . '/../../admin/common/AdminPage.inc'));


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
        if (is_a($resource, 'JsonResource'))
        {
            header('Content-type: application/json');
        }
        
        if (is_a($resource, 'PngImageResource'))
        {
            header('Content-type: image/png');
            $resource->render();
            return true;
        }
        
        $page = new AdminPage($resource);
        print $page->render();

        return true;
    }

    return false;
}


/* Main module system entry point. */
registerFrameworkExceptionHandler();

$requestPath = 'admin';

$entityManager = Registry::getRegistry()->fetch(ENTITY_MANAGER);

if (isset ($_COOKIE[AdminSession::SESSION_ID]))
{
    $session = new AdminSession();
    $session->load();
    $session->start();

    Registry::getRegistry()->store(AdminSession::SESSION_ID, $session);
}


if (isset($_GET[QUERY_PARAM]))
{
    $requestPath = 'admin/' . $_GET[QUERY_PARAM];
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