<?php

namespace Framework\Annotations;

include_once(realpath(dirname(__FILE__) . '/../Annotations.inc'));

/**
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
class TestRunBeforeHandler extends \Framework\Annotations\RunBeforeHandler
{
    public $test;

    public function runBefore()
    {
        print 'Class Annotation before : the variable test was assigned to \''.$this->test.'\' <br/>';
    }
}

?>