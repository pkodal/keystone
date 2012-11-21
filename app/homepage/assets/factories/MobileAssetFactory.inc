<?php

class MobileAssetFactory extends SimpleAssetFactory
{
    public function __construct() 
    {
        $this->cssFiles = array();
        $this->jsFiles = array('pkodal-m-core', 'pkodal-3p');
    }
    
    public function getJsIncludes()
    {
        return HtmlUtil::includeScript('assets/analytics/GoogleAnalytics.js') .
               HtmlUtil::includeScript(assetFile('pkodal-auth.js')) .
               parent::getJsIncludes();
    }
}

?>
