<?php

include_once(realpath(dirname(__FILE__) . '/../AnnotatedRestController.inc'));
include_once(realpath(dirname(__FILE__) . '/../BasicResources.inc'));
include_once(realpath(dirname(__FILE__) . '/../FrameworkException.inc'));
include_once(realpath(dirname(__FILE__) . '/../NoResourceException.inc'));
include_once(realpath(dirname(__FILE__) . '/../RequestPath.inc'));


class TestController extends AnnotatedRestController
{
    private $method1Result;
    private $method2Result;
    private $parentResult;
    private $longResult;

    public function __construct($method1Result, $method2Result, $parentResult, $longResult)
    {
        $this->method1Result = $method1Result;
        $this->method2Result = $method2Result;
        $this->parentResult = $parentResult;
        $this->longResult = $longResult;
        parent::__construct();
    }


    /**
     * @ResourcePath(path="/activity/$id/method1")
     * @GetMethod
     */
    protected function restMethod1($id)
    {
        echo "method1 id=$id<br/>";
        return $this->method1Result;
    }

    /**
     * @ResourcePath(path="/activity/$id/$action")
     * @GetMethod
     * @PostMethod
     */
    protected function restMethod2($id, $action)
    {
        echo "method2 id=$id,action=$action<br/>";
        return $this->method2Result;
    }

    /**
     * @ResourcePath(path="/activity")
     */
    protected function useParentRefMethod()
    {
        echo "parent routed method<br/>";
        return $this->parentResult;
    }

    /**
     * @ResourcePath(path="/activity/$id/$action/$one/$two/$three")
     */
    protected function longMethod($one, $three, $two, $id, $action)
    {
        print "long method id=$id, action=$action, one=$one, two=$two, three=$three<br/>";
        return $this->longResult;
    }

    private function privateMethod1()
    {
        //
    }

    private function privateMethod2()
    {
        //
    }
}

class BrokenController extends AnnotatedRestController
{
    /**
     *
     * @ResourcePath(path="/activity/$id/$action")
     */
    public function brokenMethod($id)
    {
        // nothing
    }

}


$method1Result = new WidgetResource('result1');
$method2Result = new WidgetResource('result2');
$parentResult = new WidgetResource('parent');
$longResult = new WidgetResource('long result');

$controller = new TestController($method1Result, $method2Result, $parentResult, $longResult);

$path = RequestPath::buildRequestPath('/module/activity/43/method1');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $method1Result);

print "<br/><br/><br/>";


$path = RequestPath::buildRequestPath('/module/activity/4553/anotheraction');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $method2Result);

print "<br/><br/><br/>";


$path = RequestPath::buildRequestPath('/module/activity/');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $parentResult);


print "<br/><br/><br/>";


$path = RequestPath::buildRequestPath('/module/activity/my-non-number-id/an-action/one/two/three');
print_r($path->getParameters());
$result = $controller->dispatch($path->getParameters());
assert($result == $longResult);



$controller = new BrokenController();
$path = RequestPath::buildRequestPath('/module/activity/my-non-number-id/an-action/');



try
{
    $result = $controller->dispatch($path->getParameters());
    asset(false);
}
catch (FrameworkException $fEx)
{
    // all good.    
}

?>
