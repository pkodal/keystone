<?php

namespace Framework\Annotations;

/**
 * The RunBeforeHandler class is an abstract class that can be extended
 * by any class that wishes to have the runBefore method run in the _before
 * method of the AnnotatedRestController.
 */
abstract class RunBeforeHandler extends \Doctrine\Common\Annotations\Annotation
{
    /** @var AnnotatedRestController*/
    protected $restController;

    public function setRestController($restController)
    {
        $this->restController = $restController;
    }
    /**
     * Method is run in the before method of AnnotatedRestcontroller.
     */
    abstract public function runBefore();
}


abstract class RequestMethodHandler extends \Doctrine\Common\Annotations\Annotation
{
    /**
     * Method is run in the before method of AnnotatedRestcontroller.
     */
    abstract public function runHandler();
}

?>
