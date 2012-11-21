<?php

include_once(realpath(dirname(__FILE__) . '/../RestController.inc'));
include_once(realpath(dirname(__FILE__) . '/../FrameworkException.inc'));
include_once(realpath(dirname(__FILE__) . '/../BasicResources.inc'));
include_once(realpath(dirname(__FILE__) . '/../RequestPath.inc'));
include_once(realpath(dirname(__FILE__) . '/../NoResourceException.inc'));


class TestController extends RestController
{
    private $wildcard;
    private $literal;
    private $parent;
    private $multipleWildcard;

    public function __construct($wildCard, $literal, $parent, $multipleWildcard)
    {
        $this->wildcard = $wildCard;
        $this->literal = $literal;
        $this->parent = $parent;
        $this->multipleWildcard = $multipleWildcard;
    }

    protected function defaultHandler($parameters)
    {
        echo 'running default handler<br/>';
    }

    protected function getRestMapping()
    {
        return array('activity' => array('$id' => array('add' => 'wildcardFunction',
                                                        'delete' => 'deleteFunction',
                                                        '$action' => 'multipleWildcardFunction'),
                                         'conflicts' => array('add' => 'literalFunction'),
                                         self::PARENT_ROUTE => 'parentFunction'
                                        )
                   );
    }

    protected function wildcardFunction($id, $params)
    {
        echo "running wildcard function, id=$id, params=";
        print_r($params);
        print "<br/>";
        return $this->wildcard;
    }

    protected function multipleWildcardFunction($id, $action)
    {
        echo "running mulitple wildcard function id=$id, action=$action<br/>";
        return $this->multipleWildcard;
    }

    protected function literalFunction($params)
    {
        echo 'Running literal string match function<br/>';
        return $this->literal;
    }

    protected function parentFunction()
    {
        echo 'Running parent function<br/>';
        return $this->parent;
    }
}



$wildcardResult = new WidgetResource('wildcard');
$multipleWildCardsResult = new WidgetResource('multiple wildcards');
$literalResult = new WidgetResource('literal');
$parentResult = new WidgetResource('parent');


$controller = new TestController($wildcardResult, $literalResult, $parentResult, $multipleWildCardsResult);


$path = RequestPath::buildRequestPath('/module/activity/conflicts/add');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $literalResult);


print "<br/><br/><br/>";
$path = RequestPath::buildRequestPath('/module/activity/43/add');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $wildcardResult);



print "<br/><br/><br/>";
$path = RequestPath::buildRequestPath('/module/activity/');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $parentResult);


print "<br/><br/><br/>";
$path = RequestPath::buildRequestPath('/module/activity/200/newfunction');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $multipleWildCardsResult);



//assert(!isset($result));

//$controller = new TestController(true);
//$result = $controller->dispatch(array());
//assert(is_a($result, "Resource"));

?>