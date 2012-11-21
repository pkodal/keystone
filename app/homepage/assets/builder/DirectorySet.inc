<?php

/**
 * Encapsulates a set of directories containing CSS/JS to combine into a single asset
 */
class DirectorySet 
{
    /** @var array */
    private $includeDirs;
    
    /** @var array*/
    private $excludeDirs;

    
    public function __construct() 
    {
        $this->includeDirs = array();
        $this->excludeDirs = array();
    }
    
    public function addDirectory($directory)
    {
        $this->includeDirs[] = $directory;
    }
    
    public function excludeDirectory($directory)
    {
        $this->excludeDirs[] = $directory;
    }
    
    public function getExcludeDirectory()
    {
        return $this->excludeDirs;
    }
    
    public function isDirectoryPresent($dirName)
    {
         return ($this->arrayContainsDirectory($this->includeDirs, $dirName)) &&
                (!$this->arrayContainsDirectory($this->excludeDirs, $dirName));
    }
    
    private function arrayContainsDirectory(array $array, $dirname)
    {
        $isInArray = false;
        $i = 0;
        $maxCount = count($array);

        while (!$isInArray && $i < $maxCount)
        {
            $isInArray = (strpos($dirname, $array[$i++]) !== FALSE);
        }

        return $isInArray;
    }
}

?>
