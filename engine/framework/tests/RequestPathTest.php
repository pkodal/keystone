<?php

include_once(realpath(dirname(__FILE__) . '/../RequestPath.inc'));

function pathCheck($path, $expectedModuleName, $params = array())
{
	$containsModule = $path->containsModuleName();
	
	if ($expectedModuleName != NULL)
	{
		if ($containsModule)
		{
			print $path->getModuleName() . "<br/>";
			print_r($path->getParameters());
			print "<br/>";
		}
		
		assert($containsModule);
		assert($path->getModuleName() === $expectedModuleName);
		assert($path->getParameters() === $params);
	}
	else
	{
		assert(!$containsModule);
	}
}


$path = RequestPath::buildRequestPath('module');
pathCheck($path, 'module');

$path = RequestPath::buildRequestPath('/module');
pathCheck($path, 'module');

$path = RequestPath::buildRequestPath('//');
pathCheck($path, NULL);

$path = RequestPath::buildRequestPath('/mod/foo1/foo2/foo3/foo4');
pathCheck($path, 'mod', array('foo1', 'foo2', 'foo3', 'foo4'));


$path = RequestPath::buildRequestPath('/mod/ foo1  /foo2/foo3/foo4//    /');
pathCheck($path, 'mod', array('foo1', 'foo2', 'foo3', 'foo4'));

?>