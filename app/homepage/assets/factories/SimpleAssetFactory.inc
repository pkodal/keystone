<?php


class SimpleAssetFactory extends AssetFactory
{
    const BASE_ASSET_DIR = 'assets/';
    const CSS_INCLUDE = '.css';
    const JS_INCLUDE = '.js';
    
    /** @var array */
    protected $cssFiles;
    
    /** @var array */
    protected $jsFiles;
    
    
    public function getCssIncludes() 
    {
        return parent::getCssIncludes() . $this->getIncludes($this->cssFiles, self::CSS_INCLUDE);
    }
    
    public function getJsIncludes() 
    {
        return parent::getJsIncludes() . $this->getIncludes($this->jsFiles, self::JS_INCLUDE);
    }
    
    private function getIncludes(array $includes, $extension)
    {
        $includeHtml = "";
        foreach ($includes as $file)
        {
            if ($extension == self::CSS_INCLUDE)
            {
                $includeHtml .= HtmlUtil::includeCss(self::BASE_ASSET_DIR . $file . '-' . VERSION . $extension);
            }
            else
            {
                $includeHtml .= HtmlUtil::includeScript(self::BASE_ASSET_DIR . $file . '-' . VERSION . $extension);
            }
        }
        return $includeHtml;
    }
}

?>
