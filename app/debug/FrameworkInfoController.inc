<?php

class FrameworkInfoController extends RestController
{
    protected function defaultHandler($parameters)
    {
        $content = $this->config()->render() . '<br/><br/>' . $this->modules()->render();

        return $resource = new WidgetResource($content, '/debug/css/debug.css');
    }
    
    protected function getRestMapping()
    {
        return array('config' => 'config',
                     'modules' => 'modules');
    }
    
    protected function config()
    {
        return new Template('debug/templates/config.tpl.inc');
    }
    
    protected function modules()
    {
        $moduleMap = array();
        $nonModuleDirs = array();
        $validModules = 0;

        $dir = dir(getcwd());
        $dispatcher = Registry::getRegistry()->fetch(DISPATCHER_ID);
        
        while (($entry = $dir->read()) !== false)
        {
            if ($this->isModuleDir($entry))
            {
                try
                {
                    $module = $dispatcher->getModule($entry);
                    $moduleMap[$entry] = $module;
                    $validModules++;
                }
                catch (FrameworkException $fException)
                {
                    array_push($nonModuleDirs, $entry);
                }
            }
        }

        $tpl = new Template('debug/templates/moduleInfo.tpl.inc');
        $tpl->bindVariable('modules', $moduleMap);
        $tpl->bindVariable('validModules', $validModules);
        $tpl->bindVariable('nonModuleDirs', $nonModuleDirs);

        return $tpl;
    }

    private function isModuleDir($dirName)
    {
        return (strpos($dirName, '.') === FALSE && strpos($dirName, 'framework') === FALSE);
    }
}

?>
