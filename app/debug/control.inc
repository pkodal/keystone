<?php 
// include_once(realpath(dirname(__FILE__) . '/../themes/ThemeFactory.inc'));
include_once(realpath(dirname(__FILE__) . '/FrameworkInfoController.inc'));

Framework::registerController('DebugController');
Framework::registerControllerForPrefix('FrameworkInfoController', 'info');

class DebugController extends RestController
{
    const CSS = 'debug/css/debug.css';

    public function __construct()
    {
        parent::__construct(false);
    }

    protected function defaultHandler($params)
    {
        if (count($params) > 0)
        {
            return $this->moduleGateway($params);
        }
        else
        {
            $template = new Template('debug/templates/gatewayinfo.tpl.inc');
            return new WidgetResource($template->render());
        }

        return new WidgetResource("params: " . $params);
        // TODO make a basic PageBuilder, and use here.
        // build <head> automatically. include all CSS.

        $parametersResource = Framework::loadResource("debug/parameters/" . join('/', $params));
        $dbDetailsResource = Framework::loadResource('debug/db');
        $registryResource = Framework::loadResource('debug/registry');

        $temp = new Template('debug/templates/main.tpl.inc');

        $resource = new WidgetResource();
        $resource->setCssFile(self::CSS);
        $resource->setHtml($temp->render(array('parameters' => $parametersResource->getHtml(),
                'dbDetails' => $dbDetailsResource->getHtml(),
                'registry' => $registryResource->getHtml())));
        return $resource;
    }

    protected function getRestMapping()
    {
        return array(
                'db' => array(self::PARENT_ROUTE => 'showDbDetails',
                        'css' => 'getDbCss',
                        'foo' => 'runFoo1'
                ),
                'parameters' => 'showParameters',
                'registry' => 'showRegistry',
                'console' => 'debugConsole'
                ,
        );
    }

    protected function getDbCss()
    {
        throw new Exception("exception message", 666);
//        throw new FrameworkException("foobar message");
    }

    protected function moduleGateway($params)
    {
        $path = join('/', $params);

//        $themeFactory = new ThemeFactory();
        $headerCss = HtmlUtil::includeCss(self::CSS);
//        foreach ($themeFactory->getThemeCssFiles() as $cssFile)
//        {
//            $headerCss .= HtmlUtil::includeCss($cssFile);
//        }


        $headerJs =  HtmlUtil::includeScript('debug/js/debug.js');
//                    HtmlUtil::includeScript('homepage/js/jquery-ui-1.8.custom.min.js');

        $resource = Framework::loadResource($path);

        $template = new Template('debug/templates/gateway.tpl.inc');
        $template->bindVariable('headerCssIncludes', $headerCss);
        $template->bindVariable('headerScriptIncludes', $headerJs);
        $template->bindVariable('modulePath', $path);
        $template->bindVariable('moduleContent', $resource->render());

        return new WidgetResource($template->render());
    }

    protected function debugConsole($params)
    {
        $parametersResource = Framework::loadResource("debug/parameters/" . join('/', $params));
        $dbDetailsResource = Framework::loadResource('debug/db');
        $registryResource = Framework::loadResource('debug/registry');

        $temp = new Template('debug/templates/main.tpl.inc');

        $resource = new WidgetResource();
        $resource->setCssFile(self::CSS);
        $resource->setHtml($temp->render(array('parameters' => $parametersResource->getHtml(),
                'dbDetails' => $dbDetailsResource->getHtml(),
                'registry' => $registryResource->getHtml())));
        return $resource;
    }

    protected function showDbDetails($params)
    {
        $template = new Template('debug/templates/dbdetails.tpl.inc');
        return new WidgetResource($template->render(), self::CSS);
    }

    protected function showParameters($params)
    {
        $template = new Template('debug/templates/parameters.tpl.inc');
        $template->bindVariable('parameters', $params);

        $resource = new WidgetResource();
        $resource->setHtml($template->render());
        $resource->setCssFile(self::CSS);

        return $resource;
    }

    protected function showRegistry()
    {
        $reg = Registry::getRegistry();

        $count = $reg->getLocalObjectCount();
        $list = $reg->getLocalTypeList();

        $template = new Template('debug/templates/registry.tpl.inc');

        return new WidgetResource($template->render(array('objectCount' => $count, 'objects' => $list)), 
                                  self::CSS);
    }
}

?>



