<?php

/**
 * Parse the app, and build the set of assets for distribution.
 */
class AssetBuilder extends DirectoryProcessor
{
    /** @var array of AssetSet */
    private $assetSets;
    
    public function __construct() 
    {
        $this->assetSets = array();
    }
        
    public function run($rootDirectory) 
    {        
        parent::run($rootDirectory);
        $this->buildAssets($rootDirectory);
    }
    
    public function addAssetSet(AssetSet $domain)
    {
        $this->assetSets[] = $domain;
    }
    
    protected function processDir($directoryName) 
    {
        foreach ($this->assetSets as $assetSet)
        {
            $assetSet->loadAssetsFromDirectory($directoryName);
        }
    }
    
    private function buildAssets($rootDirectory)
    {
        foreach ($this->assetSets as $assetSet)
        {
            $assetSet->buildCss();
            $assetSet->buildJavaScript($rootDirectory);
        }
    }
}

?>
