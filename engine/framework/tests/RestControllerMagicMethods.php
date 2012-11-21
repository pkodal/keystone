<?php
include_once(realpath(dirname(__FILE__) . '/../RestController.inc'));
include_once(realpath(dirname(__FILE__) . '/../FrameworkException.inc'));
include_once(realpath(dirname(__FILE__) . '/../resources/Resource.inc'));
include_once(realpath(dirname(__FILE__) . '/../resources/WidgetResource.inc'));

class TestController extends RestController
{
    private $returnOnBefore;

    public function __construct($returnOnBefore = false)
    {
        $this->returnOnBefore = $returnOnBefore;
    }

    protected function defaultHandler($parameters)
    {
        echo 'running default handler<br/>';
    }

    protected function getRestMapping()
    {
        return array('test' => 'restMethod');
    }

    protected function restMethod()
    {
        echo 'Running REST method<br/>';
    }

    protected function _before()
    {
        echo "running before method<br/>";

        if ($this->returnOnBefore)
        {
            return new WidgetResource("Test");
        }
    }

    protected function _after()
    {
        echo "running after method<br/>";
    }
}

$controller = new TestController();
$result = $controller->dispatch(array());
assert(!isset($result));

$controller = new TestController(true);
$result = $controller->dispatch(array());
assert(is_a($result, "Resource"));

?>
