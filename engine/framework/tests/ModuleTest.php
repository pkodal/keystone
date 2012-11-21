<?php

include_once(realpath(dirname(__FILE__) . '/../Module.inc'));

class Controller1 { };
class Controller2 { };
class PrefixController { };

$expectedToString = '[Controller1 Controller2  prefix -> PrefixController]';

// add test
$module = new Module('test');
$module->addControllerClass('Controller1');
$module->addControllerClass('Controller2');
$module->addControllerClass('PrefixController', 'prefix');
assert( $module->toString() === $expectedToString);

// encode test
$encodedModules = "s:controller1-" . "s:controller2-" . "p:prefixController:prefix-";
$module2 = Module::createModuleFromClassSet('test', $encodedModules);
assert( $module2->toString() === $expectedToString);

?>
