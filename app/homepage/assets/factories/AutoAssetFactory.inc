<?php

/**
 * Regenerates assets and includes them. This factory deals with all asset sets.
 */
class AutoAssetFactory extends AssetFactory
{
    const ASSET_DIR = 'auto-assets/';
    
    /** @var PkodalAssetGenerator */
    private $generator;
    
    private $cssIncludes;
    private $jsIncludes;
    
    private $domain;
    
    public function __construct() 
    {
        $this->generator = NULL;
        
        $this->cssIncludes = array(
            AssetFactory::MOBILE => array()
            
        );
        
        
                                /*AssetFactory::APPLICATION => array(self::ASSET_DIR . 'pkodal-3p.css',
                                                                      self::ASSET_DIR . 'pkodal-a.css'),
                                   AssetFactory::LANDING_PAGE => array(self::ASSET_DIR . 'pkodal-l.css'),
                                   AssetFactory::POPUP => array(self::ASSET_DIR . 'pkodal.popup.css'),
                                   AssetFactory::INFO => array(self::ASSET_DIR . 'pkodal-i.css'),*/
//                                   AssetFactory::MOBILE => array(self::ASSET_DIR . 'pkodal-l.css'));
        
        
        

        $this->jsIncludes = array(/*AssetFactory::APPLICATION => array(self::ASSET_DIR . 'pkodal-3p.js',
                                                                     self::ASSET_DIR . 'pkodal-fw.js',
                                                                     self::ASSET_DIR . 'pkodal-a.js'),
                                  AssetFactory::LANDING_PAGE => array(self::ASSET_DIR . 'pkodal-fw.js',
                                                                       self::ASSET_DIR . 'pkodal-l.js'),
                                  AssetFactory::POPUP => array(self::ASSET_DIR . 'pkodal.popup.js'),*/
                                  AssetFactory::MOBILE => array(self::ASSET_DIR . 'pkodal-m-core.js',
                                                                self::ASSET_DIR . 'pkodal-3p.js',
                                                                assetFile('pkodal-auth.js'))
                                                                );
        
        if (!DEV_MODE)
        {
            array_push($this->jsIncludes[AssetFactory::APPLICATION], 'http://connect.facebook.net/en_US/all.js');
        }        
    }
    
    public function getCssIncludes() 
    {
        $this->refreshAssets();
        return parent::getCssIncludes() . $this->getCssIncludesForDomain();
    }
    
    public function getJsIncludes() 
    {
        $this->refreshAssets();
        return parent::getJsIncludes() . $this->getJsIncludesForDomain();
    }
    
    public function setDomain($domain)
    {
        $this->domain = $domain;
    }
        
    private function getCssIncludesForDomain()
    {
        return HtmlUtil::includeCss($this->cssIncludes[$this->domain]);
    }
    
    private function getJsIncludesForDomain()
    {
        return HtmlUtil::includeScript($this->jsIncludes[$this->domain]);
    }
    
    private function refreshAssets()
    {
        if ($this->generator == null)
        {
            $this->removeOldAssets();
            $this->createAssetsDirectory();
            
            $this->generator = new PkodalAssetGenerator();
            $this->generator->run();   
        }
    }
    
    private function removeOldAssets()
    {
        $allOldAssets = glob(self::ASSET_DIR . "*.*");

        foreach ($allOldAssets as $asset)
        {
            unlink($asset);
        }
    }
    
    private function createAssetsDirectory()
    {
        if (!is_dir(self::ASSET_DIR))
        {
            mkdir(self::ASSET_DIR);
        }
    }
}


?>
