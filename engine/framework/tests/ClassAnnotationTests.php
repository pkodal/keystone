<?php
include_once(realpath(dirname(__FILE__) . '/../../bootstrap.inc'));
include_once(realpath(dirname(__FILE__) . '/../AnnotatedRestController.inc'));
include_once(realpath(dirname(__FILE__) . '/TestRunBeforeHandler.inc'));

/**
 * @TestRunBeforeHandler(test="test")
 */
class TestAnnotatedClassRestController extends AnnotatedRestController
{
    /**
     * @ResourcePath(path="class/method1")
     */
    public function afterRunBefore()
    {
        return new WidgetResource('Class Annotation after: the variable test was assigned to.<br/>');
    }
}


/**
 *@Authenticated(user="user");
 */
class TestAuthAnnotatedClassRestController extends AnnotatedRestController
{
    private $user;
    /**
     * @ResourcePath(path="class/method1")
     */
    public function authenticated()
    {
        return new WidgetResource($this->user->getUserName());
    }
}


$controller = new TestAnnotatedClassRestController();
$path = RequestPath::buildRequestPath('/module/class/method1');
$result = $controller->dispatch($path->getParameters());
print $result->render();

?>
