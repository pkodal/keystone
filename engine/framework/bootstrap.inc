<?php
//SYSTEM GLOBAL DEFINES
define('CONTEXT_PARAM', 'context');
define('CONTEXT_REGISTER', 'ctxt_register');

// unique id's for framework objects in the Registry
define('DISPATCHER_ID', 'dispatcher');
define('CONTENT_LOADER_ID', 'contentLoader');
define('USER_ID', 'user');

//db entity manager.
define('ENTITY_MANAGER', 'entitymanager');
define('SESSION_MANAGER', 'sessionmanger');

/**
 * Bootstrap needed resources for the framework.
 */

//annotations

//base framework
include_once(realpath(dirname(__FILE__) . '/Dispatcher.inc'));
include_once(realpath(dirname(__FILE__) . '/RestController.inc'));
include_once(realpath(dirname(__FILE__) . '/Registry.inc'));
include_once(realpath(dirname(__FILE__) . '/UncaughtExceptionHandler.inc'));
include_once(realpath(dirname(__FILE__) . '/AnnotatedRestController.inc'));
include_once(realpath(dirname(__FILE__) . '/Framework.inc'));
include_once(realpath(dirname(__FILE__) . '/RequestPath.inc'));

// framework Util classes
include_once(realpath(dirname(__FILE__) . '/util/helperFunctions.inc'));
include_once(realpath(dirname(__FILE__) . '/util/HtmlUtil.inc'));
include_once(realpath(dirname(__FILE__) . '/util/Enum.inc'));
include_once(realpath(dirname(__FILE__) . '/util/PhpUtils.inc'));

//framework resrouces
include_once(realpath(dirname(__FILE__) . '/resources/Resource.inc'));
include_once(realpath(dirname(__FILE__) . '/resources/JsonResource.inc'));
include_once(realpath(dirname(__FILE__) . '/resources/WidgetResource.inc'));
include_once(realpath(dirname(__FILE__) . '/resources/Template.inc'));

?>