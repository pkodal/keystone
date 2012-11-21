<?php

/**
 * AssetFactory selectively works out what site-wide JS and CSS includes the app needs.
 */
abstract class AssetFactory
{
    const MOBILE = 'mobile';
    
    /** @var AutoAssetFactory */
    private static $autoGenFactory = NULL;
    
    public static function getAssetFactory($assetDomain)
    {
        $factory;
        
        if (AUTOLOAD_ASSETS)
        {
            return self::getAutoFactory($assetDomain);
        }

        switch ($assetDomain)
        {
            case self::MOBILE:
                $factory = new MobileAssetFactory();
                break;
            
            default:
                throw new Exception("Could not find an asset factory for asset type $assetDomain");
        }
        
        return $factory;
    }
    
    public function getCssIncludes()
    {
        $themeFactory = new ThemeFactory();
        $allCss = "";
        foreach ($themeFactory->getThemeCssFiles() as $cssFile)
        {
            $allCss .= HtmlUtil::includeCss($cssFile);
        }
        return $allCss;
    }

    public function getJsIncludes()
    {
        return HtmlUtil::includeScript("assets/jquery/jquery-1.6.1.min.js") .
               HtmlUtil::includeScript(assetFile('pkodal-jqm-boot.js')) .
               HtmlUtil::includeScript('assets/jquery/jquery.mobile-1.0b1.min.js');
    }   
    
    private function getAutoFactory($domain)
    {
        if (!isset(self::$autoGenFactory))
        {
            self::$autoGenFactory = new AutoAssetFactory();
        }
        
        self::$autoGenFactory->setDomain($domain);
        return self::$autoGenFactory;
    }
}


?>
