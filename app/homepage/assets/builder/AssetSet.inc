<?php

include_once(realpath(dirname(__FILE__) . '/SprocketCaller.inc'));

/**
 * Assets info for a single purpose
 */
class AssetSet
{
    /** @var DirectorySet */
    private $dirSet;
    
    private $cssOutputFile;
    private $jsOutputFile;
    
    private $jsFiles;   
    private $cssFiles;
    
    public function __construct(DirectorySet $dirs, $jsOutputFile, $cssOutputFile = NULL) 
    {
        $this->dirSet = $dirs;
        $this->jsOutputFile = $jsOutputFile;
        $this->cssOutputFile = $cssOutputFile;
        
        $this->jsFiles = array();
        $this->cssFiles = array();
    }
    
    public function loadAssetsFromDirectory($directory)
    {
        if ($this->dirSet->isDirectoryPresent($directory))
        {
            $js = glob("$directory/*.js");
            $this->jsFiles = array_merge($this->jsFiles, $js);

            $css = glob("$directory/*.css");
            $this->cssFiles = array_merge($this->cssFiles, $css);
            
        }
    }
    
    public function buildCss()
    {
        if (isset($this->cssOutputFile))
        {
            $this->concatFile($this->cssFiles, $this->cssOutputFile);
        }
    }
    
    public function buildJavaScript($appRootDirectory)
    {
        if (isset($this->jsOutputFile))
        {
            $caller = new SprocketCaller($this->jsFiles, $this->jsOutputFile, $appRootDirectory);
            $caller->run();
        }
    }
    
    private function concatFile($files, $result)
    {
        $content = '';
        foreach ($files as $file)
        {
            $content .= file_get_contents($file);
        }
        file_put_contents($result, $content);
    }
     

    public function getJsOutputFile()
    {
        return $this->jsOutputFile;
    }
    
    public function getCssOutputFile()
    {
        return $this->cssOutputFile;
    }
}

?>
